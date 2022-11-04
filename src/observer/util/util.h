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
// Created by wangyunlai on 2022/9/28
//

#pragma once

#include <string>

#include "rc.h"
#include "sql/parser/parse_defs.h"
#include <vector>

constexpr int kYearLen = 4;
constexpr int kMonthLen = 2;
constexpr int kDayLen = 2;

std::string double2string(double v);

RC char2date(const char *chars, int *date);

std::string date2string(int date);

std::vector<int> date2ymd(int date);

bool is_legal_date(int year, int month, int day);

std::string aggr_type_to_string(AggrType aggr_type);