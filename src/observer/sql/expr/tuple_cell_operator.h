//
// Created by Moon on 2022/11/1.
//

#pragma once

#include <cfloat>
#include "sql/expr/tuple_cell.h"
#include <sstream>
#include <math.h>
#include "util/util.h"

class TupleCellOperator {
public:
  static inline TupleCell Plus(const TupleCell &left, const TupleCell &right)
  {
    if (left.attr_type() == INTS && right.attr_type() == INTS) {
      int result = TupleCellToInt(left) + TupleCellToInt(right);
      Value value;
      value_init_integer(&value, result);
      return {INTS, static_cast<char *>(value.data)};
    }
    if ((left.attr_type() == INTS && right.attr_type() == FLOATS) ||
        (left.attr_type() == FLOATS && right.attr_type() == INTS) ||
        (left.attr_type() == FLOATS && right.attr_type() == FLOATS)) {
      float result = TupleCellToFloat(left) + TupleCellToFloat(right);
      Value value;
      value_init_float(&value, result);
      return {FLOATS, static_cast<char *>(value.data)};
    }
    assert(false);
  }

  static inline TupleCell Minus(const TupleCell &left, const TupleCell &right)
  {
    if (left.attr_type() == INTS && right.attr_type() == INTS) {
      int result = TupleCellToInt(left) - TupleCellToInt(right);
      Value value;
      value_init_integer(&value, result);
      return {INTS, static_cast<char *>(value.data)};
    }
    if ((left.attr_type() == INTS && right.attr_type() == FLOATS) ||
        (left.attr_type() == FLOATS && right.attr_type() == INTS) ||
        (left.attr_type() == FLOATS && right.attr_type() == FLOATS)) {
      float result = TupleCellToFloat(left) - TupleCellToFloat(right);
      Value value;
      value_init_float(&value, result);
      return {FLOATS, static_cast<char *>(value.data)};
    }
    assert(false);
  }

  static inline TupleCell Multiply(const TupleCell &left, const TupleCell &right)
  {
    if (left.attr_type() == INTS && right.attr_type() == INTS) {
      int result = TupleCellToInt(left) * TupleCellToInt(right);
      Value value;
      value_init_integer(&value, result);
      return {INTS, static_cast<char *>(value.data)};
    }
    if ((left.attr_type() == INTS && right.attr_type() == FLOATS) ||
        (left.attr_type() == FLOATS && right.attr_type() == INTS) ||
        (left.attr_type() == FLOATS && right.attr_type() == FLOATS)) {
      float result = TupleCellToFloat(left) * TupleCellToFloat(right);
      Value value;
      value_init_float(&value, result);
      return {FLOATS, static_cast<char *>(value.data)};
    }
    // TODO: add type cast
    assert(false);
  }

  static inline TupleCell Divide(const TupleCell &left, const TupleCell &right)
  {
    if ((left.attr_type() == INTS && right.attr_type() == INTS) ||
        (left.attr_type() == INTS && right.attr_type() == FLOATS) ||
        (left.attr_type() == FLOATS && right.attr_type() == INTS) ||
        (left.attr_type() == FLOATS && right.attr_type() == FLOATS)) {
      if (TupleCellToFloat(right) == 0) {
        return {NULLS, nullptr};
      }
      float result = TupleCellToFloat(left) / TupleCellToFloat(right);
      Value value;
      value_init_float(&value, result);
      return {FLOATS, static_cast<char *>(value.data)};
    }
    assert(false);
  }

  static inline TupleCell Negative(const TupleCell &left, const TupleCell &right)
  {
    if (left.attr_type() == INTS) {
      int result = -TupleCellToInt(left);
      Value value;
      value_init_integer(&value, result);
      return {INTS, static_cast<char *>(value.data)};
    } else if (left.attr_type() == FLOATS) {
      float result = -TupleCellToFloat(left);
      Value value;
      value_init_float(&value, result);
      return {FLOATS, static_cast<char *>(value.data)};
    }
    assert(false);
  }

  static inline TupleCell Length(const TupleCell &cell)
  {
    if (cell.attr_type() != CHARS) {
      return {UNDEFINED, nullptr};
    }
    std::stringstream ss;
    cell.to_string(ss);
    int result = ss.str().size();
    Value value;
    value_init_integer(&value, result);
    return {INTS, static_cast<char *>(value.data)};
  }

  static inline double my_round(double number, unsigned int bits)
  {
    long long integerPart = number;
    number -= integerPart;
    for (unsigned int i = 0; i < bits; ++i)
      number *= 10;
    number = (long long)(number + 0.5);
    for (unsigned int i = 0; i < bits; ++i)
      number /= 10;
    return integerPart + number;
  }

  static inline TupleCell Round(const TupleCell &left_cell, const TupleCell &right_cell)
  {
    float left = TupleCellToFloat(left_cell);
    int right = TupleCellToInt(right_cell);
    // double res = my_round(left, right);
    // float result = std::round(left * pow(10, right)) / pow(10, right);
    int num = 0;
    float tmp;
    if (left < 0) {
      tmp = 0 - left;
      num++;
    } else {
      tmp = left;
    }

    while (tmp / 10 > 1) {
      tmp = tmp / 10;
      num++;
    }
    Value value;
    value_init_float(&value, atof(double2string(left, right).c_str()));
    TupleCell re = {FLOATS, static_cast<char *>(value.data)};
    re.set_num(right);
    return re;
  }

  static inline TupleCell Round_default(const TupleCell &left_cell)
  {
    float left = TupleCellToFloat(left_cell);
    float result = std::round(left);
    std::stringstream ss;
    ss << result;
    Value value;
    value_init_float(&value, atof(double2string(left, 2).c_str()));
    TupleCell re = {FLOATS, static_cast<char *>(value.data)};
    re.set_num(0);
    return re;
  }

  static inline TupleCell DateFormat(const TupleCell &left_cell, const TupleCell &right_cell)
  {
    // y m d
    int y, m, d = 0;
    if (left_cell.attr_type() == CHARS) {
      int date = 0;
      RC rc = char2date((char *)left_cell.data(), &date);
      if (rc != RC::SUCCESS) {
        return left_cell;
      }
      auto ymd = date2ymd(date);
      y = ymd[0];
      m = ymd[1];
      d = ymd[2];
    } else {
      auto ymd = date2ymd(*(int *)left_cell.data());
      y = ymd[0];
      m = ymd[1];
      d = ymd[2];
    }

    // format
    std::stringstream ss;
    ss << right_cell.data();
    std::string format = ss.str();
    std::stringstream os;
    int length = 0;
    for (size_t i = 0; i < format.size(); i++) {
      if (format[i] == '%') {
        if (i != format.size() - 1) {
          i++;
          switch (format[i]) {
            case 'Y': {
              if (y <= 9) {
                os << 0;
              }
              if (y <= 99) {
                os << 0;
              }
              if (y <= 999) {
                os << 0;
              }
              os << y;
              length += 4;
              break;
            }
            case 'y': {
              y = y % 100;
              if (y <= 9) {
                os << 0;
              }
              os << y;
              length += 2;
              break;
            }
            case 'M': {
              switch (m) {
                case 1: {
                  os << "January";
                  length += 7;
                } break;
                case 2: {
                  os << "February";
                  length += 8;
                } break;
                case 3: {
                  os << "March";
                  length += 5;
                } break;
                case 4: {
                  os << "April";
                  length += 5;
                } break;
                case 5: {
                  os << "May";
                  length += 3;
                } break;
                case 6: {
                  os << "June";
                  length += 4;
                } break;
                case 7: {
                  os << "July";
                  length += 4;
                } break;
                case 8: {
                  os << "August";
                  length += 6;
                } break;
                case 9: {
                  os << "September";
                  length += 9;
                } break;
                case 10: {
                  os << "October";
                  length += 7;
                } break;
                case 11: {
                  os << "November";
                  length += 8;
                } break;
                case 12: {
                  os << "December";
                  length += 8;
                } break;
                default:
                  break;
              }
              break;
            }
            case 'm': {
              if (m <= 9) {
                os << 0;
              }
              os << m;
              length += 2;
              break;
            }
            case 'D': {
              os << d;
              switch (d % 10) {
                case 1: {
                  os << "st";
                } break;
                case 2: {
                  os << "nd";
                } break;
                case 3: {
                  os << "rd";
                } break;
                default: {
                  os << "th";
                } break;
              }
              if (d <= 9) {
                length += 3;
              } else {
                length += 4;
              }

              break;
            }
            case 'd': {
              if (d <= 9) {
                os << 0;
              }
              os << d;
              length += 2;
              break;
            }
            default: {
              os << format[i];
              length += 1;
              break;
            }
          }

        } else {
          length++;
          os << format[i];
        }
      } else {
        length++;
        os << format[i];
      }
    }

    Value value;
    value_init_string(&value, os.str().c_str());
    TupleCell re = {CHARS, static_cast<char *>(value.data)};
    re.set_length(length);
    return re;
  }
  static inline int TupleCellToInt(const TupleCell &cell)
  {
    if (cell.attr_type() != INTS) {
      assert(false);
    }
    return *(int *)cell.data();
  }

  static inline float TupleCellToFloat(const TupleCell &cell)
  {
    if (cell.attr_type() == INTS) {
      return *(int *)cell.data();
    }
    if (cell.attr_type() == FLOATS) {
      return *(float *)cell.data();
    }
    assert(false);
  }
};
