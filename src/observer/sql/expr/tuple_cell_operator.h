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

  static inline TupleCell Round(const TupleCell &left_cell, const TupleCell &right_cell)
  {
    float left = TupleCellToFloat(left_cell);
    int right = TupleCellToInt(right_cell);
    float result = std::round(left * pow(10, right)) / pow(10, right);
    std::stringstream ss;
    ss << result;
    Value value;
    value_init_string(&value, ss.str().c_str());
    TupleCell re = {CHARS, static_cast<char *>(value.data)};
    re.set_length(right + (result / 10) + 2);
    return re;
  }

  static inline TupleCell Round_default(const TupleCell &left_cell)
  {
    float left = TupleCellToFloat(left_cell);
    float result = std::round(left);
    std::stringstream ss;
    ss << result;
    Value value;
    value_init_string(&value, ss.str().c_str());
    TupleCell re = {CHARS, static_cast<char *>(value.data)};
    re.set_length((result / 10) + 2);
    return re;
  }

  static inline TupleCell DateFormat(const TupleCell &left_cell, const TupleCell &right_cell)
  {
    // y m d
    auto ymd = date2ymd(*(int *)left_cell.data());
    // auto s = date2string(*(int *)left_cell.data());
    int y = ymd[0];
    int m = ymd[1];
    int d = ymd[2];

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
            case 'Y':
            case 'y': {
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
            case 'M':
            case 'm': {
              if (m <= 9) {
                os << 0;
              }
              os << m;
              length += 2;
              break;
            }
            case 'D':
            case 'd': {
              if (d <= 9) {
                os << 0;
              }
              os << d;
              length += 2;
              break;
            }
            default: {
              os << '%' << format[i];
              length += 2;
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
