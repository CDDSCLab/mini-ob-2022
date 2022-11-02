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
    } else if (left.attr_type() == FLOATS && right.attr_type() == FLOATS) {
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
    } else if (left.attr_type() == FLOATS && right.attr_type() == FLOATS) {
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
    } else if (left.attr_type() == FLOATS && right.attr_type() == FLOATS) {
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
    if (left.attr_type() == INTS && right.attr_type() == INTS) {
      float result = (float)TupleCellToInt(left) / TupleCellToInt(right);
      Value value;
      value_init_float(&value, result);
      return {FLOATS, static_cast<char *>(value.data)};
    } else if (left.attr_type() == FLOATS && right.attr_type() == FLOATS) {
      float result = TupleCellToFloat(left) - TupleCellToFloat(right);
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
      value_init_float(&value, result);
      return {INTS, static_cast<char *>(value.data)};
    } else if (left.attr_type() == FLOATS) {
      float result = -TupleCellToFloat(left);
      Value value;
      value_init_float(&value, result);
      return {FLOATS, static_cast<char *>(value.data)};
    }
    assert(false);
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
    if (cell.attr_type() != FLOATS) {
      assert(false);
    }
    return *(float *)cell.data();
  }
};
