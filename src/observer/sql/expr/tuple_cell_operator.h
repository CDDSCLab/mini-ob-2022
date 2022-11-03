//
// Created by Moon on 2022/11/1.
//

#pragma once

#include <cfloat>
#include "sql/expr/tuple_cell.h"

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
    int result = cell.length();
    Value value;
    value_init_integer(&value, result);
    return {INTS, static_cast<char *>(value.data)};
  }

  static inline TupleCell Round(const TupleCell &cell)
  {
    if (cell.attr_type() != FLOATS) {
      return {UNDEFINED, nullptr};
    }
    int result = TupleCellToFloat(cell) + 0.5;
    Value value;
    value_init_integer(&value, result);
    return {INTS, static_cast<char *>(value.data)};
  }

  static inline TupleCell DateFormat(const TupleCell &cell)
  {
    Value value;
    value_init_string(&value, "result");
    return {CHARS, static_cast<char *>(value.data)};
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
