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
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include <vector>

#include "rc.h"
#include "sql/stmt/stmt.h"
#include "sql/parser/parse_defs.h"
#include "sql/executor/execute_stage.h"
#include "storage/common/field_meta.h"

class Table;
class FilterStmt;
class SelectStmt;

class UpdateStmt : public Stmt {
public:
  UpdateStmt() = default;
  ~UpdateStmt() override;

public:
  static RC create(Db *db, const Updates &update_sql, Stmt *&stmt);

public:
  Table *table() const
  {
    return table_;
  }
  const std::vector<const FieldMeta *> &update_fields() const
  {
    return update_fields_;
  }
  const std::vector<Value *> &values() const
  {
    return values_;
  }
  std::vector<Value *> &get_values()
  {
    return values_;
  }
  const std::vector<SelectStmt *> &select_stmt() const
  {
    return select_stmt_;
  }
  FilterStmt *filter_stmt() const
  {
    return filter_stmt_;
  }

  StmtType type() const override
  {
    return StmtType::UPDATE;
  }

private:
  Table *table_ = nullptr;
  std::vector<const FieldMeta *> update_fields_;
  std::vector<Value *> values_;
  std::vector<SelectStmt *> select_stmt_;
  FilterStmt *filter_stmt_ = nullptr;
};
