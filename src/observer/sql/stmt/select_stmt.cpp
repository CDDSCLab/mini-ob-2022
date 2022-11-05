/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"

#include <algorithm>

#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/expr/expression_factory.h"

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.emplace_back(table, table_meta.field(i));
  }
}

static void wildcard_expr(Table *table, std::vector<Expression *> &exprs, Db *db,
    std::unordered_map<std::string, Table *> table_map, std::vector<char *> &select_expr_alias)
{
  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    Expr tmp;
    tmp.expr_type = EXPR_ATTR;
    tmp.attr.relation_name = const_cast<char *>(table->name());
    tmp.attr.attribute_name = const_cast<char *>(table_meta.field(i)->name());
    tmp.attr.aggr_type = AGGR_NONE;
    exprs.emplace_back(ExpressionFactory::NewExpression(tmp, db, table, &table_map));
    select_expr_alias.emplace_back(nullptr);
  }
}

RC SelectStmt::create(Db *db, const Selects &select_sql, Stmt *&stmt)
{
  std::unordered_map<std::string, Table *> table_map;
  return create(db, select_sql, table_map, stmt);
}

RC SelectStmt::create(
    Db *db, const Selects &select_sql, std::unordered_map<std::string, Table *> &parents_map, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  // collect tables in `from` statement
  std::vector<Table *> tables;
  std::unordered_map<std::string, Table *> table_map;
  if (select_sql.relation_num > 0) {
    // check duplicate table alias
    for (size_t i = 0; i < select_sql.relation_num; i++) {
      if (common::is_blank(select_sql.relation_alias[i])) {
        continue;
      }
      const char *table_alias = select_sql.relation_alias[i];
      for (size_t j = i + 1; j < select_sql.relation_num; j++) {
        if (strcmp(table_alias, select_sql.relation_alias[j]) == 0) {
          return RC::GENERIC_ERROR;
        }
      }
    }

    for (size_t i = select_sql.relation_num - 1;; --i) {
      const char *table_name = select_sql.relations[i];
      const char *table_alias = select_sql.relation_alias[i];
      if (nullptr == table_name) {
        LOG_WARN("invalid argument. relation name is null. index=%d", i);
        return RC::INVALID_ARGUMENT;
      }

      Table *table = db->find_table(table_name);
      if (nullptr == table) {
        LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
        return RC::SCHEMA_TABLE_NOT_EXIST;
      }

      table->set_alias(table_alias);
      tables.push_back(table);
      table_map.insert(std::pair<std::string, Table *>(table_name, table));
      if (table_alias != NULL) {
        table_map.insert(std::pair<std::string, Table *>(table_alias, table));
      }
      if (i == 0) {
        break;
      }
    }
  }

  // Check aggregation type.
  // collect query fields in `select` statement
  std::vector<Field> aggr_fields;
  std::vector<Field> query_fields;
  if (select_sql.attr_num > 0) {
    for (size_t i = select_sql.attr_num - 1;; i--) {
      const RelAttr &relation_attr = select_sql.attributes[i];
      auto aggr_type = relation_attr.aggr_type;
      if (aggr_type == AGGR_NONE) {
        if (i == 0) {
          break;
        }
        continue;
      }
      if (0 == strcmp(relation_attr.attribute_name, "*") && aggr_type != AGGR_NONE && aggr_type != AGGR_COUNT) {
        return RC::GENERIC_ERROR;
      } else if (0 == strcmp(relation_attr.attribute_name, "1") && aggr_type != AGGR_COUNT) {
        return RC::GENERIC_ERROR;
      }
      if (i == 0) {
        break;
      }
    }

    for (size_t i = select_sql.attr_num - 1;; i--) {
      const RelAttr &relation_attr = select_sql.attributes[i];
      auto aggr_type = relation_attr.aggr_type;

      if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {
        if (aggr_type != AGGR_NONE) {
          const auto table = tables[0];
          const auto field_meta = table->table_meta().field(0);
          query_fields.emplace_back(table, field_meta, aggr_type);
          aggr_fields.emplace_back(table, field_meta, aggr_type);
        } else {
          for (Table *table : tables) {
            wildcard_fields(table, query_fields);
          }
        }
      } else if (!common::is_blank(relation_attr.relation_name)) {  // TODO
        const char *table_name = relation_attr.relation_name;
        const char *field_name = relation_attr.attribute_name;

        if (0 == strcmp(table_name, "*")) {
          if (0 != strcmp(field_name, "*")) {
            LOG_WARN("invalid field name while table is *. attr=%s", field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          if (aggr_type != AGGR_NONE) {
            const auto table = tables[0];
            const auto field_meta = table->table_meta().field(0);
            query_fields.emplace_back(table, field_meta, aggr_type);
            aggr_fields.emplace_back(table, field_meta, aggr_type);
          } else {
            for (Table *table : tables) {
              wildcard_fields(table, query_fields);
            }
          }
        } else {
          auto iter = table_map.find(table_name);
          if (iter == table_map.end()) {
            LOG_WARN("no such table in from list: %s", table_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = iter->second;
          if (0 == strcmp(field_name, "*")) {
            if (aggr_type != AGGR_NONE) {
              const auto field_meta = table->table_meta().field(0);
              query_fields.emplace_back(table, field_meta, aggr_type);
              aggr_fields.emplace_back(table, field_meta, aggr_type);
            } else {
              wildcard_fields(table, query_fields);
            }
          } else {
            const FieldMeta *field_meta = table->table_meta().field(field_name);
            if (nullptr == field_meta) {
              LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }

            query_fields.emplace_back(table, field_meta, aggr_type);
            if (aggr_type != AGGR_NONE) {
              aggr_fields.emplace_back(table, field_meta, aggr_type);
            }
          }
        }
      } else {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = tables[0];
        const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
        if (nullptr == field_meta) {
          LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        query_fields.emplace_back(table, field_meta, aggr_type);
        if (aggr_type != AGGR_NONE) {
          aggr_fields.emplace_back(table, field_meta, aggr_type);
        }
      }
      if (i == 0) {
        break;
      }
    }
  }

  std::vector<Expression *> express;
  std::vector<char *> select_expr_alias;  // select_expr_alias给单表用的
  if (select_sql.expr_num > 0) {
    for (size_t i = select_sql.expr_num - 1;; i--) {
      if (select_sql.exprs[i].expr_type == EXPR_ATTR) {
        if (common::is_blank(select_sql.exprs[i].attr.relation_name) &&
            0 == strcmp(select_sql.exprs[i].attr.attribute_name, "*")) {  //*
          if (select_sql.exprs[i].attr.aggr_type == AGGR_COUNT) {
            express.emplace_back(new FieldExpr(tables[0], tables[0]->table_meta().field(0), AGGR_COUNT));
            select_expr_alias.emplace_back(select_sql.select_expr_alias[i]);
          } else {
            if (select_sql.select_expr_alias[i] != nullptr) {
              return RC::GENERIC_ERROR;
            }
            for (Table *table : tables) {
              wildcard_expr(table, express, db, table_map, select_expr_alias);
            }
          }
        } else if ((!common::is_blank(select_sql.exprs[i].attr.relation_name)) &&
                   0 == strcmp(select_sql.exprs[i].attr.attribute_name, "*")) {  // t.*
          auto table = table_map[select_sql.exprs[i].attr.relation_name];
          // TODO: check relation_name
          if (select_sql.exprs[i].attr.aggr_type == AGGR_COUNT) {
            express.emplace_back(new FieldExpr(table, table->table_meta().field(0), AGGR_COUNT));
            select_expr_alias.emplace_back(select_sql.select_expr_alias[i]);
          } else {
            if (select_sql.select_expr_alias[i] != nullptr) {
              return RC::GENERIC_ERROR;
            }
            wildcard_expr(table, express, db, table_map, select_expr_alias);
          }
        } else {
          express.emplace_back(ExpressionFactory::NewExpression(select_sql.exprs[i], db, tables[0], &table_map));
          select_expr_alias.emplace_back(select_sql.select_expr_alias[i]);
        }
      } else {
        if (tables.size() > 0) {
          express.emplace_back(ExpressionFactory::NewExpression(select_sql.exprs[i], db, tables[0], &table_map));
        } else {
          express.emplace_back(ExpressionFactory::NewExpression(select_sql.exprs[i], db, nullptr, &table_map));
        }

        select_expr_alias.emplace_back(select_sql.select_expr_alias[i]);
      }
      if (i == 0) {
        break;
      }
    }
  }

  // check function expr
  for (auto &expr : express) {
    if (expr->type() == EXPR_LENGTH) {
      auto expr_expr = dynamic_cast<ExprExpr *>(expr);
      auto left = expr_expr->left();
      switch (left->type()) {
        case EXPR_ATTR: {
          FieldExpr *expr_left = dynamic_cast<FieldExpr *>(left);
          const FieldMeta *f = expr_left->field().meta();
          if (f == nullptr || f->type() != CHARS) {
            return RC::GENERIC_ERROR;
          }
        } break;
        case EXPR_VALUE: {
          ValueExpr *expr_left = dynamic_cast<ValueExpr *>(left);
          TupleCell cell;
          expr_left->get_tuple_cell(cell);
          if (cell.attr_type() != CHARS) {
            return RC::GENERIC_ERROR;
          }
        } break;
        default:
          return RC::GENERIC_ERROR;
          break;
      }
    }
    if (expr->type() == EXPR_ROUND) {
      auto expr_expr = dynamic_cast<ExprExpr *>(expr);
      // check left
      auto left = expr_expr->left();
      switch (left->type()) {
        case EXPR_ATTR: {
          FieldExpr *expr_left = dynamic_cast<FieldExpr *>(left);
          const FieldMeta *f = expr_left->field().meta();
          if (f == nullptr || f->type() != FLOATS) {
            return RC::GENERIC_ERROR;
          }
        } break;
        case EXPR_VALUE: {
          ValueExpr *expr_left = dynamic_cast<ValueExpr *>(left);
          TupleCell cell;
          expr_left->get_tuple_cell(cell);
          if (cell.attr_type() != FLOATS) {
            return RC::GENERIC_ERROR;
          }
        } break;
        default:
          return RC::GENERIC_ERROR;
          break;
      }

      // check right
      auto right = expr_expr->right();
      if (right == nullptr) {
        continue;
      }
      switch (right->type()) {
        case EXPR_VALUE: {
          ValueExpr *expr_right = dynamic_cast<ValueExpr *>(right);
          TupleCell cell;
          expr_right->get_tuple_cell(cell);
          if (cell.attr_type() != INTS) {
            return RC::GENERIC_ERROR;
          }
        } break;
        default:
          return RC::GENERIC_ERROR;
          break;
      }
    }
    if (expr->type() == EXPR_DATE_FORMAT) {
      auto expr_expr = dynamic_cast<ExprExpr *>(expr);
      // check left
      auto left = expr_expr->left();
      switch (left->type()) {
        case EXPR_ATTR: {
          FieldExpr *expr_left = dynamic_cast<FieldExpr *>(left);
          const FieldMeta *f = expr_left->field().meta();
          if (f == nullptr || f->type() != DATES) {
            return RC::GENERIC_ERROR;
          }
        } break;
        case EXPR_VALUE: {
          ValueExpr *expr_left = dynamic_cast<ValueExpr *>(left);
          TupleCell cell;
          expr_left->get_tuple_cell(cell);
          if (cell.attr_type() != CHARS) {
            return RC::GENERIC_ERROR;
          }
        } break;
        default:
          return RC::GENERIC_ERROR;
          break;
      }

      // check right
      auto right = expr_expr->right();
      if (right == nullptr) {
        continue;
      }
      switch (right->type()) {
        case EXPR_VALUE: {
          ValueExpr *expr_right = dynamic_cast<ValueExpr *>(right);
          TupleCell cell;
          expr_right->get_tuple_cell(cell);
          if (cell.attr_type() != CHARS) {
            return RC::GENERIC_ERROR;
          }
        } break;
        default:
          return RC::GENERIC_ERROR;
          break;
      }
    }
  }

  // collect group by field in `select` statement
  std::vector<Field> group_by_fields;
  if (select_sql.group_num > 0) {
    for (size_t i = select_sql.group_num - 1;; i--) {
      const RelAttr &relation_attr = select_sql.group_attributes[i];
      const char *table_name = relation_attr.relation_name;
      const char *field_name = relation_attr.attribute_name;

      if (relation_attr.aggr_type != AGGR_NONE) {
        return RC::GENERIC_ERROR;
      }
      if (strcmp(field_name, "*") == 0) {
        return RC::GENERIC_ERROR;
      }

      Table *table;
      if (common::is_blank(table_name)) {
        if (tables.size() != 1) {
          LOG_WARN("invalid. I do not know the attr's table. attr=%s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        table = tables[0];
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        table = iter->second;
      }
      const FieldMeta *field_meta = table->table_meta().field(field_name);
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
        return RC::SCHEMA_FIELD_MISSING;
      }
      group_by_fields.emplace_back(table, field_meta, AGGR_NONE);

      if (i == 0) {
        break;
      }
    }
  }

  std::vector<Field> order_by_fields;
  std::vector<OrderType> order_by_types;
  for (size_t i = 0; i < select_sql.order_num; i++) {
    order_by_types.emplace_back(select_sql.order[i].order_type);
    const RelAttr &order_attr = select_sql.order[i].attr;
    if (common::is_blank(order_attr.relation_name)) {  // 单表查询order by
      if (tables.size() != 1) {
        LOG_WARN("in muti selects no exist relation name");
        return RC::SCHEMA_FIELD_MISSING;
      }
      const auto table = tables[0];
      const auto field_meta = table->table_meta().field(order_attr.attribute_name);
      if (field_meta == nullptr) {
        LOG_WARN("cannot find the order by field");
        return RC::SCHEMA_FIELD_MISSING;
      }
      order_by_fields.emplace_back(table, field_meta);
    } else {  // 多表查询order by
      bool exist = false;
      for (size_t i = 0; i < tables.size(); i++) {
        if (std::string(tables[i]->name()) == std::string(order_attr.relation_name)) {
          const auto field_meta = tables[i]->table_meta().field(order_attr.attribute_name);
          if (field_meta == nullptr) {
            LOG_WARN("cannot find the order by field");
            return RC::SCHEMA_FIELD_MISSING;
          }
          order_by_fields.emplace_back(tables[i], field_meta);
          exist = true;
          break;
        }
      }
      if (!exist) {
        LOG_WARN("cannot find the order by relation name");
        return RC::SCHEMA_FIELD_MISSING;
      }
    }
  }

  for (const auto &field : query_fields) {
    if (!aggr_fields.empty() && std::count(aggr_fields.begin(), aggr_fields.end(), field) == 0 &&
        std::count(group_by_fields.begin(), group_by_fields.end(), field) == 0) {
      // Error mixing aggregated columns with normal columns.
      return RC::GENERIC_ERROR;
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());

  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  // TODO: add parent table
  RC rc = RC::SUCCESS;
  if (tables.size() != 0) {
    rc = FilterStmt::create(
        db, default_table, &table_map, &parents_map, select_sql.conditions, select_sql.condition_num, filter_stmt);
  }
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // creat filter statement in 'having' statement
  FilterStmt *having_stmt = nullptr;
  if (select_sql.having_num > 0) {
    // 组织 having aggr filed 和 having filter
    rc = FilterStmt::create(db, default_table, &table_map, select_sql.having, select_sql.having_num, having_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot construct filter stmt");
      return rc;
    }

    // add aggr in having. having 里的 feild 必须是聚合
    for (size_t i = select_sql.having_num - 1;; i--) {
      const Condition &condition = select_sql.having[i];

      if (condition.left_expr.expr_type == EXPR_ATTR) {
        const RelAttr &relation_attr = condition.left_expr.attr;
        auto aggr_type = relation_attr.aggr_type;
        if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {
          if (aggr_type != AGGR_NONE) {
            const auto table = tables[0];
            const auto field_meta = table->table_meta().field(0);
            aggr_fields.emplace_back(table, field_meta, aggr_type);
          } else {
            // for (Table *table : tables) {
            //   wildcard_fields(table, query_fields);
            // }
            LOG_ERROR("use non-aggr field in having");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        } else if (!common::is_blank(relation_attr.relation_name)) {  // TODO
          const char *table_name = relation_attr.relation_name;
          const char *field_name = relation_attr.attribute_name;

          if (0 == strcmp(table_name, "*")) {
            if (0 != strcmp(field_name, "*")) {
              LOG_WARN("invalid field name while table is *. attr=%s", field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }
            if (aggr_type != AGGR_NONE) {
              const auto table = tables[0];
              const auto field_meta = table->table_meta().field(0);
              aggr_fields.emplace_back(table, field_meta, aggr_type);
            } else {
              // for (Table *table : tables) {
              //   wildcard_fields(table, query_fields);
              // }
              LOG_ERROR("use non-aggr field in having");
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
            }
          } else {
            auto iter = table_map.find(table_name);
            if (iter == table_map.end()) {
              LOG_WARN("no such table in from list: %s", table_name);
              return RC::SCHEMA_FIELD_MISSING;
            }

            Table *table = iter->second;
            if (0 == strcmp(field_name, "*")) {
              if (aggr_type != AGGR_NONE) {
                const auto field_meta = table->table_meta().field(0);
                aggr_fields.emplace_back(table, field_meta, aggr_type);
              } else {
                // wildcard_fields(table, query_fields);
                LOG_ERROR("use non-aggr field in having");
                return RC::SCHEMA_FIELD_TYPE_MISMATCH;
              }
            } else {
              const FieldMeta *field_meta = table->table_meta().field(field_name);
              if (nullptr == field_meta) {
                LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
                return RC::SCHEMA_FIELD_MISSING;
              }

              if (aggr_type != AGGR_NONE) {
                aggr_fields.emplace_back(table, field_meta, aggr_type);
              } else {
                LOG_ERROR("use non-aggr field in having");
                return RC::SCHEMA_FIELD_TYPE_MISMATCH;
              }
            }
          }
        } else {
          if (tables.size() != 1) {
            LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = tables[0];
          const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          if (aggr_type != AGGR_NONE) {
            aggr_fields.emplace_back(table, field_meta, aggr_type);
          } else {
            LOG_ERROR("use non-aggr field in having");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }
      }

      if (condition.right_expr.expr_type == EXPR_ATTR) {
        const RelAttr &relation_attr = condition.right_expr.attr;
        auto aggr_type = relation_attr.aggr_type;
        if (common::is_blank(relation_attr.relation_name) && 0 == strcmp(relation_attr.attribute_name, "*")) {
          if (aggr_type != AGGR_NONE) {
            const auto table = tables[0];
            const auto field_meta = table->table_meta().field(0);
            aggr_fields.emplace_back(table, field_meta, aggr_type);
          } else {
            // for (Table *table : tables) {
            //   wildcard_fields(table, query_fields);
            // }
            LOG_ERROR("use non-aggr field in having");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        } else if (!common::is_blank(relation_attr.relation_name)) {  // TODO
          const char *table_name = relation_attr.relation_name;
          const char *field_name = relation_attr.attribute_name;

          if (0 == strcmp(table_name, "*")) {
            if (0 != strcmp(field_name, "*")) {
              LOG_WARN("invalid field name while table is *. attr=%s", field_name);
              return RC::SCHEMA_FIELD_MISSING;
            }
            if (aggr_type != AGGR_NONE) {
              const auto table = tables[0];
              const auto field_meta = table->table_meta().field(0);
              aggr_fields.emplace_back(table, field_meta, aggr_type);
            } else {
              // for (Table *table : tables) {
              //   wildcard_fields(table, query_fields);
              // }
              LOG_ERROR("use non-aggr field in having");
              return RC::SCHEMA_FIELD_TYPE_MISMATCH;
            }
          } else {
            auto iter = table_map.find(table_name);
            if (iter == table_map.end()) {
              LOG_WARN("no such table in from list: %s", table_name);
              return RC::SCHEMA_FIELD_MISSING;
            }

            Table *table = iter->second;
            if (0 == strcmp(field_name, "*")) {
              if (aggr_type != AGGR_NONE) {
                const auto field_meta = table->table_meta().field(0);
                aggr_fields.emplace_back(table, field_meta, aggr_type);
              } else {
                // wildcard_fields(table, query_fields);
                LOG_ERROR("use non-aggr field in having");
                return RC::SCHEMA_FIELD_TYPE_MISMATCH;
              }
            } else {
              const FieldMeta *field_meta = table->table_meta().field(field_name);
              if (nullptr == field_meta) {
                LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
                return RC::SCHEMA_FIELD_MISSING;
              }

              if (aggr_type != AGGR_NONE) {
                aggr_fields.emplace_back(table, field_meta, aggr_type);
              } else {
                LOG_ERROR("use non-aggr field in having");
                return RC::SCHEMA_FIELD_TYPE_MISMATCH;
              }
            }
          }
        } else {
          if (tables.size() != 1) {
            LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          Table *table = tables[0];
          const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          if (aggr_type != AGGR_NONE) {
            aggr_fields.emplace_back(table, field_meta, aggr_type);
          } else {
            LOG_ERROR("use non-aggr field in having");
            return RC::SCHEMA_FIELD_TYPE_MISMATCH;
          }
        }
      }

      if (i == 0) {
        break;
      }
    }
  }
  // TODO: having 前提语法检查

  // everything alright
  auto select_stmt = new SelectStmt();
  select_stmt->tables_.swap(tables);
  select_stmt->express_.swap(express);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->aggr_fields_.swap(aggr_fields);
  select_stmt->group_by_fields_.swap(group_by_fields);
  select_stmt->order_by_fields_.swap(order_by_fields);
  select_stmt->order_by_types_.swap(order_by_types);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->having_stmt_ = having_stmt;
  select_stmt->select_expr_alias_.swap(select_expr_alias);
  stmt = select_stmt;
  return RC::SUCCESS;
}
