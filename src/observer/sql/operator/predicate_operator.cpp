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
// Created by WangYunlai on 2022/6/27.
//
#include "sql/operator/predicate_operator.h"

#include <regex>

#include "common/log/log.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/field.h"

RC PredicateOperator::open()
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }

  return children_[0]->open();
}

RC PredicateOperator::next()
{
  RC rc = RC::SUCCESS;
  Operator *oper = children_[0];

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    bool result = false;
    rc = do_predicate(static_cast<RowTuple &>(*tuple), &result);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (result) {
      return rc;
    }
  }
  return rc;
}

RC PredicateOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicateOperator::current_tuple()
{
  return children_[0]->current_tuple();
}

RC PredicateOperator::do_predicate(RowTuple &tuple, bool *result)
{
  RC rc = RC::SUCCESS;
  if (filter_stmt_ == nullptr || filter_stmt_->filter_units().empty()) {
    *result = true;
    return rc;
  }

  for (const FilterUnit *filter_unit : filter_stmt_->filter_units()) {
    Expression *left_expr = filter_unit->left();
    Expression *right_expr = filter_unit->right();
    CompOp comp = filter_unit->comp();
    TupleCell left_cell;
    TupleCell right_cell;
    left_expr->get_value(tuple, left_cell);
    right_expr->get_value(tuple, right_cell);

    bool filter_result = false;
    if (comp == IN_OP) {
      std::vector<TupleCell> cells;
      if (right_expr->type() == EXPR_SELECT) {
        rc = dynamic_cast<SelectExpr *>(right_expr)->get_values(tuple, &cells);
      } else if (right_expr->type() == EXPR_VALUES) {
        rc = dynamic_cast<ValuesExpr *>(right_expr)->get_values(tuple, &cells);
      }
      if (rc != RC::SUCCESS) {
        return rc;
      }
      for (const auto cell : cells) {
        if (cell.compare(left_cell) == 0) {
          filter_result = true;
          break;
        }
        filter_result = false;
      }
    } else if (comp == NOT_IN_OP) {
      std::vector<TupleCell> cells;
      if (right_expr->type() == EXPR_SELECT) {
        rc = dynamic_cast<SelectExpr *>(right_expr)->get_values(tuple, &cells);
      } else if (right_expr->type() == EXPR_VALUES) {
        rc = dynamic_cast<ValuesExpr *>(right_expr)->get_values(tuple, &cells);
      }
      if (rc != RC::SUCCESS) {
        return rc;
      }
      for (const auto cell : cells) {
        if (cell.compare(left_cell) == 0) {
          filter_result = false;
          break;
        }
        filter_result = true;
      }
    } else if (comp == EXISTS_OP) {
      rc = dynamic_cast<SelectExpr *>(right_expr)->has_value(tuple, &filter_result);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (comp == NOT_EXISTS_OP) {
      rc = dynamic_cast<SelectExpr *>(right_expr)->has_value(tuple, &filter_result);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      filter_result = !filter_unit;
    } else if (right_expr->type() == EXPR_SELECT) {
      std::vector<TupleCell> cells;
      rc = dynamic_cast<SelectExpr *>(right_expr)->get_value(tuple, right_cell);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    } else if (left_cell.attr_type() == UNDEFINED || right_cell.attr_type() == UNDEFINED) {
      *result = true;
      return rc;
    }

    // NULL 特殊处理
    if (left_cell.attr_type() == NULLS || right_cell.attr_type() == NULLS) {
      switch (comp) {
        case IS_NULL:
          filter_result = left_cell.attr_type() == NULLS;
          break;
        case IS_NOT_NULL:
          filter_result = left_cell.attr_type() != NULLS;
          break;
        default:
          *result = false;
          return rc;
      }
    }

    if (comp == LIKE_OP) {
      filter_result = like(left_cell, right_cell);
    } else if (comp == NOT_LIKE_OP) {
      filter_result = !like(left_cell, right_cell);
    } else {
      const int compare = left_cell.compare(right_cell);
      switch (comp) {
        case EQUAL_TO: {
          filter_result = (0 == compare);
        } break;
        case LESS_EQUAL: {
          filter_result = (compare <= 0);
        } break;
        case NOT_EQUAL: {
          filter_result = (compare != 0);
        } break;
        case LESS_THAN: {
          filter_result = (compare < 0);
        } break;
        case GREAT_EQUAL: {
          filter_result = (compare >= 0);
        } break;
        case GREAT_THAN: {
          filter_result = (compare > 0);
        } break;
        default: {
          LOG_WARN("invalid compare type: %d", comp);
        } break;
      }
    }
    if (!filter_result) {
      *result = false;
      return rc;
    }
  }
  *result = true;
  return rc;
}

bool PredicateOperator::like(const TupleCell &left_cell, const TupleCell &right_cell)
{
  std::stringstream ss;
  for (int i = 0; i < right_cell.length(); ++i) {
    const char &data = right_cell.data()[i];
    if (data == '%') {
      ss << kRegexStar;
    } else if (data == '_') {
      ss << kRegexDot;
    } else {
      ss << data;
    }
  }
  std::regex regex(ss.str(), std::regex_constants::icase);
  auto data = std::string(left_cell.data());
  if (data.size() > left_cell.length()) {
    data.resize(left_cell.length());
  }
  return std::regex_match(data, regex);
}

// int PredicateOperator::tuple_cell_num() const
// {
//   return children_[0]->tuple_cell_num();
// }
// RC PredicateOperator::tuple_cell_spec_at(int index, TupleCellSpec &spec) const
// {
//   return children_[0]->tuple_cell_spec_at(index, spec);
// }
