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

#include "sql/expr/tuple.h"
#include "sql/operator/project_operator.h"

RC FieldExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  return tuple.find_cell(field_, cell);
}

RC ValueExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  cell = tuple_cell_;
  return RC::SUCCESS;
}

RC SelectExpr::get_value(const Tuple &tuple, TupleCell &cell) const
{
  RC rc = project_oper_->open();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  if ((rc = project_oper_->next()) != RC::SUCCESS) {
    project_oper_->close();
    return rc;
  }
  auto current_tuple = project_oper_->current_tuple();
  if (current_tuple->cell_num() > 1) {
    project_oper_->close();
    return RC::GENERIC_ERROR;
  }
  current_tuple->cell_at(0, cell);
  if (project_oper_->next() == RC::SUCCESS) {
    project_oper_->close();
    return RC::GENERIC_ERROR;
  }
  project_oper_->close();
  return RC::SUCCESS;
}

RC SelectExpr::get_values(const Tuple &tuple, std::vector<TupleCell> *cells)
{
  RC rc = project_oper_->open();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  while (project_oper_->next() == RC::SUCCESS) {
    auto current_tuple = project_oper_->current_tuple();
    if (current_tuple->cell_num() > 1) {
      project_oper_->close();
      return RC::GENERIC_ERROR;
    }
    auto cell = new TupleCell();
    rc = current_tuple->cell_at(0, *cell);
    cells->emplace_back(*cell);
  }

  project_oper_->close();
  return rc;
}

RC SelectExpr::has_value(const Tuple &tuple, bool *result)
{
  RC rc = project_oper_->open();
  if (rc != RC::SUCCESS) {
    return rc;
  }
  *result = project_oper_->next() == RC::SUCCESS;

  project_oper_->close();
  return rc;
}
