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

#include "util/util.h"

#include <cstring>
#include <cmath>
#include <string>
#include <sstream>

#include "rc.h"

std::string double2string(double v)
{
  char buf[256];
  snprintf(buf, sizeof(buf), "%.2f", v);
  size_t len = strlen(buf);
  while (buf[len - 1] == '0') {
    len--;
  }
  if (buf[len - 1] == '.') {
    len--;
  }

  return {buf, len};
}

int char2date(const char *chars)
{
  std::stringstream input(chars);
  std::string token;
  char delim = '-';
  int year, month, day;
  getline(input, token, delim);
  year = std::stoi(token);
  getline(input, token, delim);
  month = std::stoi(token);
  getline(input, token, delim);
  day = std::stoi(token);

  if (!is_legal_date(year, month, day)) {
    return RC::SCHEMA_FIELD_DATE_ILLEGAL;
  }

  double temp = year * pow(10, kMonthLen + kDayLen) + month * pow(10, kDayLen) + day;
  return static_cast<int>(temp);
}

std::string date2string(int date)
{
  constexpr int bufferSize = kYearLen + 1 + kMonthLen + 1 + kDayLen + 1;
  char buf[bufferSize];
  int year, month, day;
  year = static_cast<int>(date / pow(10, kYearLen));
  month = static_cast<int>((date - pow(10, kYearLen) * year) / pow(10, kMonthLen));
  day = static_cast<int>(date - pow(10, kYearLen) * year - pow(10, kMonthLen) * month);
  snprintf(buf, bufferSize, "%4d-%02d-%02d", year, month, day);
  return {buf};
}

bool is_legal_date(int year, int month, int day)
{
  //  if (year > 2038 || year < 1970 || (year == 2038 && month > 2)) {
  //    return false;
  //  }
  if (month <= 0 || month > 12 || day <= 0 || day > 31) {
    return false;
  }
  if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
    return true;
  }
  if (day == 31) {
    return false;
  }
  if (month == 2) {
    if (((year % 4 == 0) && (year % 100 != 0)) || year % 400 == 0) {
      if (30 == day) {
        return false;
      }
    } else {
      if (29 == day || 30 == day) {
        return false;
      }
    }
  }
  return true;
}
