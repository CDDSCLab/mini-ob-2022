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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <unordered_map>

#include "rc.h"
#include "sql/stmt/stmt.h"
#include "storage/common/field.h"
#include "sql/expr/expression.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

class SelectStmt : public Stmt {
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override
  {
    return StmtType::SELECT;
  }

public:
  static RC create(Db *db, const Selects &select_sql, Stmt *&stmt);

  static RC create(
      Db *db, const Selects &select_sql, std::unordered_map<std::string, Table *> &parents_map, Stmt *&stmt);

public:
  const std::vector<Table *> &tables() const
  {
    return tables_;
  }
  const std::vector<Expression *> &express() const
  {
    return express_;
  }
  const std::vector<Field> &query_fields() const
  {
    return query_fields_;
  }
  const std::vector<Field> &aggr_fields() const
  {
    return aggr_fields_;
  }
  const std::vector<Field> &group_by_fields() const
  {
    return group_by_fields_;
  }
  const std::vector<Field> &order_by_fields() const
  {
    return order_by_fields_;
  }
  const std::vector<OrderType> &order_by_types() const
  {
    return order_by_types_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }
  FilterStmt *having_stmt() const
  {
    return having_stmt_;
  }

  const std::vector<char *> &select_expr_alias() const
  {
    return select_expr_alias_;
  }

private:
  std::vector<Expression *> express_;
  std::vector<Field> query_fields_;
  std::vector<Field> aggr_fields_;
  std::vector<Field> group_by_fields_;
  std::vector<Table *> tables_;
  std::vector<Field> order_by_fields_;
  std::vector<OrderType> order_by_types_;
  std::vector<char *> select_expr_alias_;
  FilterStmt *filter_stmt_ = nullptr;
  FilterStmt *having_stmt_ = nullptr;
};
