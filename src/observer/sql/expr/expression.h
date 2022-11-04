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
// Created by Wangyunlai on 2022/07/05.
//

#pragma once

#include <string.h>
#include "storage/common/field.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/tuple_cell_operator.h"

class Tuple;
class ProjectOperator;

class Expression {
public:
  Expression() = default;
  virtual ~Expression() = default;

  virtual RC get_value(const Tuple &tuple, TupleCell &cell) const = 0;
  virtual ExprType type() const = 0;
  virtual void get_alias(std::ostream &os) = 0;
};

class FieldExpr : public Expression {
public:
  FieldExpr() = default;
  FieldExpr(const Table *table, const FieldMeta *field, AggrType aggr_type) : field_(table, field, aggr_type)
  {}

  virtual ~FieldExpr() = default;

  ExprType type() const override
  {
    return EXPR_ATTR;
  }

  Field &field()
  {
    return field_;
  }

  const Field &field() const
  {
    return field_;
  }

  const char *table_name() const
  {
    return field_.table_name();
  }

  const char *field_name() const
  {
    return field_.field_name();
  }

  void get_alias(std::ostream &os) override
  {
    os << field_.field_name();
    return;
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;

private:
  Field field_;
};

class ValueExpr : public Expression {
public:
  ValueExpr() = default;
  ValueExpr(const Value &value) : tuple_cell_(value.type, (char *)value.data)
  {
    if (value.type == CHARS) {
      tuple_cell_.set_length(strlen((const char *)value.data));
    }
  }

  virtual ~ValueExpr() = default;

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;
  ExprType type() const override
  {
    return EXPR_VALUE;
  }

  void get_tuple_cell(TupleCell &cell) const
  {
    cell = tuple_cell_;
  }

  void get_alias(std::ostream &os) override
  {
    tuple_cell_.to_string(os);
    return;
  }

private:
  TupleCell tuple_cell_;
};

class ExprExpr : public Expression {
public:
  ExprExpr(ExprType type, Expression *left_expr, Expression *right_expr)
      : type_(type), left_expr_(left_expr), right_expr_(right_expr)
  {}

  ExprType type() const override
  {
    return type_;
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override
  {
    RC rc = RC::SUCCESS;
    TupleCell left_cell;
    TupleCell right_cell;
    if (type_ >= EXPR_PLUS && type_ <= EXPR_DIVIDE) {
      left_expr_->get_value(tuple, left_cell);
      right_expr_->get_value(tuple, right_cell);
    } else if (type_ == EXPR_NEGATIVE) {
      left_expr_->get_value(tuple, left_cell);
    } else if (type_ == EXPR_BRACE) {
      return left_expr_->get_value(tuple, cell);
    } else {
      return RC::GENERIC_ERROR;
    }
    if (left_cell.attr_type() == NULLS || right_cell.attr_type() == NULLS) {
      cell = {NULLS, nullptr};
      return rc;
    } else if (type_ >= EXPR_PLUS && type_ <= EXPR_DIVIDE &&
               (left_cell.attr_type() == UNDEFINED || right_cell.attr_type() == UNDEFINED)) {
      cell = {UNDEFINED, nullptr};
      return rc;
    } else if (type_ == EXPR_NEGATIVE && left_cell.attr_type() == UNDEFINED) {
      cell = {UNDEFINED, nullptr};
      return rc;
    }
    switch (type_) {
      case EXPR_PLUS: {
        cell = TupleCellOperator::Plus(left_cell, right_cell);
      } break;
      case EXPR_MINUS: {
        cell = TupleCellOperator::Minus(left_cell, right_cell);
      } break;
      case EXPR_MULTIPLY: {
        cell = TupleCellOperator::Multiply(left_cell, right_cell);
      } break;
      case EXPR_DIVIDE: {
        cell = TupleCellOperator::Divide(left_cell, right_cell);
      } break;
      case EXPR_NEGATIVE: {
        cell = TupleCellOperator::Negative(left_cell, right_cell);
      } break;
      case EXPR_NONE:
      case EXPR_VALUE:
      case EXPR_ATTR:
      case EXPR_SELECT: {
        assert(false);
      } break;
    }
    return rc;
  }

  void get_alias(std::ostream &os) override
  {
    if (type_ == EXPR_NONE || type_ == EXPR_SELECT) {
      return;
    }

    if (type_ == EXPR_BRACE) {
      os << "(";
      left_expr_->get_alias(os);
      os << ")";
      return;
    }

    if (type_ == EXPR_NEGATIVE) {
      os << "-";
      left_expr_->get_alias(os);
      return;
    }

    left_expr_->get_alias(os);

    switch (type_) {
      case EXPR_PLUS: {
        os << "+";
        break;
      }
      case EXPR_MINUS: {
        os << "-";
        break;
      }
      case EXPR_MULTIPLY: {
        os << "*";
        break;
      }
      case EXPR_DIVIDE: {
        os << "/";
        break;
      }
      default:
        break;
    }

    if (right_expr_->type() == EXPR_NEGATIVE) {
      os << "(";
      right_expr_->get_alias(os);
      os << ")";
    } else {
      right_expr_->get_alias(os);
    }
    return;
  }

private:
  ExprType type_;
  Expression *left_expr_;
  Expression *right_expr_;
};

class SelectExpr : public Expression {
public:
  SelectExpr(ProjectOperator *project_oper) : project_oper_(project_oper)
  {}

  SelectExpr() = default;

  ExprType type() const override
  {
    return EXPR_SELECT;
  }

  RC get_value(const Tuple &tuple, TupleCell &cell) const override;

  RC get_values(const Tuple &tuple, std::vector<TupleCell> *cells);

  RC has_value(const Tuple &tuple, bool *result);

  void get_alias(std::ostream &os) override
  {
    return;
  }

private:
  ProjectOperator *project_oper_;
};
