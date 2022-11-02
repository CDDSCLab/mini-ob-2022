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
// Created by Wangyunlai on 2021/5/14.
//

#pragma once

#include <memory>
#include <vector>

#include "common/log/log.h"
#include "sql/parser/parse.h"
#include "sql/expr/tuple_cell.h"
#include "sql/expr/expression.h"
#include "storage/record/record.h"

class Table;

class TupleCellSpec {
public:
  TupleCellSpec() = default;
  explicit TupleCellSpec(Expression *expr) : expression_(expr)
  {}

  ~TupleCellSpec()
  {
    if (expression_) {
      delete expression_;
      expression_ = nullptr;
    }
  }

  void set_alias(const char *alias)
  {
    this->alias_ = alias;
  }

  const char *alias() const
  {
    return alias_;
  }

  Expression *expression() const
  {
    return expression_;
  }

private:
  const char *alias_ = nullptr;
  Expression *expression_ = nullptr;
};

class Tuple {
public:
  Tuple() = default;
  virtual ~Tuple() = default;

  virtual int cell_num() const = 0;
  virtual RC cell_at(int index, TupleCell &cell) const = 0;
  virtual RC find_cell(const Field &field, TupleCell &cell) const = 0;

  virtual RC cell_spec_at(int index, const TupleCellSpec *&spec) const = 0;
};

class RowTuple : public Tuple {
public:
  RowTuple() = default;
  ~RowTuple() override
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_record(Record *record)
  {
    this->record_ = record;
  }

  void set_schema(const Table *table, const std::vector<FieldMeta> *fields)
  {
    table_ = table;
    this->speces_.reserve(fields->size());
    for (const FieldMeta &field : *fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(table, &field)));
    }
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    const TupleCellSpec *spec = speces_[index];
    auto field_expr = dynamic_cast<FieldExpr *>(spec->expression());
    const FieldMeta *field_meta = field_expr->field().meta();
    cell.set_type(field_meta->type());
    if (this->record_->data() == nullptr) {
      cell.set_data(this->record_->data());
      cell.set_length(field_meta->len() - 1);
      return RC::SUCCESS;
    }
    if (*(bool *)(this->record_->data() + field_meta->offset() + field_meta->len() - 1)) {
      cell.set_type(NULLS);
    }
    cell.set_data(this->record_->data() + field_meta->offset());
    cell.set_length(field_meta->len() - 1);  // NOTE: 多的那个字节在 tuple 这一层被干掉
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    const char *table_name = field.table_name();
    if (0 != strcmp(table_name, table_->name())) {
      return RC::NOTFOUND;
    }

    const char *field_name = field.field_name();
    for (size_t i = 0; i < speces_.size(); ++i) {
      const auto *field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &field = field_expr->field();
      if (0 == strcmp(field_name, field.field_name())) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  Record &record()
  {
    return *record_;
  }

  const Record &record() const
  {
    return *record_;
  }

  const Table *table()
  {
    return table_;
  }
  std::vector<TupleCellSpec *> speces()
  {
    return speces_;
  }

private:
  Record *record_ = nullptr;
  const Table *table_ = nullptr;
  std::vector<TupleCellSpec *> speces_;
};

/*
class CompositeTuple : public Tuple
{
public:
  int cell_num() const override;
  RC  cell_at(int index, TupleCell &cell) const = 0;
private:
  int cell_num_ = 0;
  std::vector<Tuple *> tuples_;
};
*/

class AggregateTuple : public Tuple {
public:
  AggregateTuple(const std::vector<Field> &aggr_fields, const std::vector<Field> &group_by_fields)
  {
    this->speces_.reserve(aggr_fields.size() + group_by_fields.size());
    for (const auto &field : aggr_fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(field.table(), field.meta(), field.aggr_type())));
    }
    for (const auto &field : group_by_fields) {
      speces_.push_back(new TupleCellSpec(new FieldExpr(field.table(), field.meta(), field.aggr_type())));
    }
  }
  ~AggregateTuple() override
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }

    cell = tuple_cells_[index];
    return RC::SUCCESS;
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    for (size_t i = 0; i < speces_.size(); ++i) {
      const auto field_expr = (const FieldExpr *)speces_[i]->expression();
      const Field &f = field_expr->field();
      if (field == f) {
        return cell_at(i, cell);
      }
    }
    return RC::NOTFOUND;
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

  void set_data(const std::vector<TupleCell> &aggr_cell, const std::vector<TupleCell> &group_by_cell)
  {
    tuple_cells_.clear();
    for (const auto &cell : aggr_cell) {
      // TODO: handle null
      tuple_cells_.emplace_back(cell);
    }
    for (const auto &cell : group_by_cell) {
      tuple_cells_.emplace_back(cell);
    }
  }

private:
  std::vector<TupleCellSpec *> speces_;
  std::vector<TupleCell> tuple_cells_;
};

class ProjectTuple : public Tuple {
public:
  ProjectTuple() = default;
  ~ProjectTuple() override
  {
    for (TupleCellSpec *spec : speces_) {
      delete spec;
    }
    speces_.clear();
  }

  void set_tuple(Tuple *tuple)
  {
    this->tuple_ = tuple;
  }

  void add_cell_spec(TupleCellSpec *spec)
  {
    speces_.push_back(spec);
  }
  int cell_num() const override
  {
    return speces_.size();
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::GENERIC_ERROR;
    }
    if (tuple_ == nullptr) {
      return RC::GENERIC_ERROR;
    }

    const TupleCellSpec *spec = speces_[index];
    return spec->expression()->get_value(*tuple_, cell);
  }

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    return tuple_->find_cell(field, cell);
  }
  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index < 0 || index >= static_cast<int>(speces_.size())) {
      return RC::NOTFOUND;
    }
    spec = speces_[index];
    return RC::SUCCESS;
  }

private:
  std::vector<TupleCellSpec *> speces_;
  Tuple *tuple_ = nullptr;
};

class JoinTuple : public Tuple {
public:
  JoinTuple() = default;

  void set_tuple(Tuple *left, Tuple *right, bool left_is_row)
  {
    left_ = left;
    right_ = right;
    left_is_row_ = left_is_row;
  };

  RC find_cell(const Field &field, TupleCell &cell) const override
  {
    if (left_->find_cell(field, cell) == RC::SUCCESS || right_->find_cell(field, cell) == RC::SUCCESS) {
      return RC::SUCCESS;
    }
    return RC::NOTFOUND;
  }

  RC cell_at(int index, TupleCell &cell) const override
  {
    if (index <= 0 || index >= cell_num()) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    if (index < left_->cell_num()) {
      return left_->cell_at(index, cell);
    } else {
      return right_->cell_at(index - left_->cell_num(), cell);
    }
  }

  RC cell_spec_at(int index, const TupleCellSpec *&spec) const override
  {
    if (index <= 0 || index >= cell_num()) {
      LOG_WARN("invalid argument. index=%d", index);
      return RC::INVALID_ARGUMENT;
    }
    if (index < left_->cell_num()) {
      return left_->cell_spec_at(index, spec);
    } else {
      return right_->cell_spec_at(index - left_->cell_num(), spec);
    }
  }

  int cell_num() const override
  {
    return (left_->cell_num() + right_->cell_num());
  }

private:
  Tuple *left_;
  Tuple *right_;
  bool left_is_row_ = false;
};