//
// Created by Moon on 2022/10/31.
//

#pragma once

#include "common/lang/defer.h"
#include "sql/expr/tuple.h"
#include "sql/operator/aggregation_operator.h"
#include "sql/operator/table_scan_operator.h"
#include "sql/operator/join_operator.h"
#include "sql/operator/index_scan_operator.h"
#include "sql/operator/predicate_operator.h"
#include "sql/operator/update_operator.h"
#include "sql/operator/delete_operator.h"
#include "sql/operator/project_operator.h"
#include "sql/operator/operator_factory.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/index/index.h"

class OperatorFactory {
public:
  static inline RC GetProjectOperator(SelectStmt *select_stmt, ProjectOperator *project_oper)
  {
    RC rc = RC::SUCCESS;
    // >= 2 tables
    // TODO(anybody): implement multi tables, 主要是栈上声明对象的问题.
    if (select_stmt->tables().size() != 1) {
      std::vector<TableScanOperator *> scan_ops;
      std::vector<PredicateOperator> pred_ops;
      std::vector<JoinOperator> join_ops;
      scan_ops.reserve(select_stmt->tables().size());
      pred_ops.reserve(select_stmt->tables().size());
      join_ops.reserve(select_stmt->tables().size() - 1);
      for (size_t i = 0; i < select_stmt->tables().size(); i++) {
        scan_ops.emplace_back(new TableScanOperator(select_stmt->tables()[i]));
        pred_ops.emplace_back(PredicateOperator(select_stmt->filter_stmt()));
        pred_ops[i].add_child(scan_ops[i]);
      }

      DEFER([&]() {
        for (size_t i = 0; i < select_stmt->tables().size(); i++) {
          delete scan_ops[i];
        }
      });

      for (size_t i = 0; i < select_stmt->tables().size() - 1; i++) {
        if (i == 0) {
          join_ops.emplace_back(JoinOperator(&pred_ops[0], &pred_ops[1], true, select_stmt->filter_stmt()));
        } else {
          join_ops.emplace_back(JoinOperator(&join_ops[i - 1], &pred_ops[i + 1], false, select_stmt->filter_stmt()));
        }
      }

      auto final_pre = PredicateOperator(select_stmt->filter_stmt());
      final_pre.add_child(&join_ops[join_ops.size() - 1]);

      ProjectOperator project_oper;

      project_oper.add_child(&final_pre);
      for (const Field &field : select_stmt->query_fields()) {
        project_oper.add_projection(field.table(), field.meta(), field.aggr_type(), true);
      }
      rc = project_oper.open();
      if (rc != RC::SUCCESS) {
        LOG_WARN("failed to open operator");
        return rc;
      }

      std::stringstream ss;
      while ((rc = project_oper.next()) == RC::SUCCESS) {
        // get current record
        // write to response
        Tuple *tuple = project_oper.current_tuple();
        if (nullptr == tuple) {
          rc = RC::INTERNAL;
          LOG_WARN("failed to get current record. rc=%s", strrc(rc));
          break;
        }

        ss << std::endl;
      }

      if (rc != RC::RECORD_EOF) {
        LOG_WARN("something wrong while iterate operator. rc=%s", strrc(rc));
        project_oper.close();
      } else {
        rc = project_oper.close();
      }
    }

    Operator *scan_oper = try_to_create_index_scan_operator(select_stmt->filter_stmt());
    if (nullptr == scan_oper) {
      scan_oper = new TableScanOperator(select_stmt->tables()[0]);
    }

    auto pred_oper = new PredicateOperator(select_stmt->filter_stmt());
    pred_oper->add_child(scan_oper);
    auto aggr_oper = new AggregationOperator(select_stmt->aggr_fields(), select_stmt->group_by_fields());
    for (const Field &field : select_stmt->query_fields()) {
      project_oper->add_projection(field.table(), field.meta(), field.aggr_type(), false);
    }
    if (select_stmt->aggr_fields().empty()) {
      project_oper->add_child(pred_oper);
    } else {
      aggr_oper->add_child(pred_oper);
      project_oper->add_child(aggr_oper);
    }
    return rc;
  };

private:
  static IndexScanOperator *try_to_create_index_scan_operator(FilterStmt *filter_stmt)
  {
    const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
    if (filter_units.empty()) {
      return nullptr;
    }

    // 在所有过滤条件中，找到字段与值做比较的条件，然后判断字段是否可以使用索引
    // 如果是多列索引，这里的处理需要更复杂。
    // 这里的查找规则是比较简单的，就是尽量找到使用相等比较的索引
    // 如果没有就找范围比较的，但是直接排除不等比较的索引查询. (你知道为什么?)
    const FilterUnit *better_filter = nullptr;
    for (const FilterUnit *filter_unit : filter_units) {
      if (filter_unit->comp() == NOT_EQUAL) {
        continue;
      }

      Expression *left = filter_unit->left();
      Expression *right = filter_unit->right();
      if (left->type() == EXPR_ATTR && right->type() == EXPR_VALUE) {
      } else if (left->type() == EXPR_VALUE && right->type() == EXPR_ATTR) {
        std::swap(left, right);
      } else if (left->type() == EXPR_VALUE && right->type() == EXPR_VALUE) {
        continue;
      }
      FieldExpr &left_field_expr = *(FieldExpr *)left;
      const Field &field = left_field_expr.field();
      const Table *table = field.table();
      Index *index = table->find_index_by_field(field.field_name());
      if (index != nullptr) {
        if (better_filter == nullptr) {
          better_filter = filter_unit;
        } else if (filter_unit->comp() == EQUAL_TO) {
          better_filter = filter_unit;
          break;
        }
      }
    }

    if (better_filter == nullptr) {
      return nullptr;
    }

    Expression *left = better_filter->left();
    Expression *right = better_filter->right();
    CompOp comp = better_filter->comp();
    if (left->type() == EXPR_VALUE && right->type() == EXPR_ATTR) {
      std::swap(left, right);
      switch (comp) {
        case EQUAL_TO: {
          comp = EQUAL_TO;
        } break;
        case LESS_EQUAL: {
          comp = GREAT_THAN;
        } break;
        case NOT_EQUAL: {
          comp = NOT_EQUAL;
        } break;
        case LESS_THAN: {
          comp = GREAT_EQUAL;
        } break;
        case GREAT_EQUAL: {
          comp = LESS_THAN;
        } break;
        case GREAT_THAN: {
          comp = LESS_EQUAL;
        } break;
        default: {
          LOG_WARN("should not happen");
        }
      }
    }

    FieldExpr &left_field_expr = *(FieldExpr *)left;
    const Field &field = left_field_expr.field();
    const Table *table = field.table();
    Index *index = table->find_index_by_field(field.field_name());
    assert(index != nullptr);

    ValueExpr &right_value_expr = *(ValueExpr *)right;
    TupleCell value;
    right_value_expr.get_tuple_cell(value);

    const TupleCell *left_cell = nullptr;
    const TupleCell *right_cell = nullptr;
    bool left_inclusive = false;
    bool right_inclusive = false;

    switch (comp) {
      case EQUAL_TO: {
        left_cell = &value;
        right_cell = &value;
        left_inclusive = true;
        right_inclusive = true;
      } break;

      case LESS_EQUAL: {
        left_cell = nullptr;
        left_inclusive = false;
        right_cell = &value;
        right_inclusive = true;
      } break;

      case LESS_THAN: {
        left_cell = nullptr;
        left_inclusive = false;
        right_cell = &value;
        right_inclusive = false;
      } break;

      case GREAT_EQUAL: {
        left_cell = &value;
        left_inclusive = true;
        right_cell = nullptr;
        right_inclusive = false;
      } break;

      case GREAT_THAN: {
        left_cell = &value;
        left_inclusive = false;
        right_cell = nullptr;
        right_inclusive = false;
      } break;

      default: {
        LOG_WARN("should not happen. comp=%d", comp);
      } break;
    }

    auto oper = new IndexScanOperator(table, index, left_cell, left_inclusive, right_cell, right_inclusive);

    LOG_INFO("use index for scan: %s in table %s", index->index_meta().name(), table->name());
    return oper;
  }
};
