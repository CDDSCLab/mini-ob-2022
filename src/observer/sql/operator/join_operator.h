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
// Created by WangYunlai on 2021/6/10.
//

#pragma once

#include "sql/parser/parse.h"
#include "sql/operator/operator.h"
#include "rc.h"
#include <vector>

class FilterStmt;

// TODO fixme
class JoinOperator : public Operator {
public:
  JoinOperator(Operator *left, Operator *right, bool left_is_row, FilterStmt *filter_stmt)
      : left_(left), right_(right), left_is_row_(left_is_row), filter_stmt_(filter_stmt)
  {
    if (left_ == nullptr) {
      printf("left is null\n");
    }
    if (right_ == nullptr) {
      printf("right is null\n");
    }
    //    joined_tuple_ = new JoinTuple();
  }

  //  JoinOperator(const JoinOperator &obj) : Operator(obj)
  //  {
  //    printf("new copy join operator\n");
  //    //    joined_tuple_ = new JoinTuple();
  //  }

  ~JoinOperator() override
  {
    //    delete joined_tuple_;
  }

  RC open() override;
  RC next() override;
  RC close() override;
  Tuple *current_tuple() override;
  bool do_join(Tuple *left, Tuple *right);
  bool do_predicate(RowTuple &tuple);

private:
  Operator *left_ = nullptr;
  Operator *right_ = nullptr;
  bool left_is_row_ = false;
  bool round_done_ = true;

  JoinTuple joined_tuple_;
  FilterStmt *filter_stmt_ = nullptr;
};
