//
// Created by Moon on 2022/10/26.
//

#pragma once

#include <cfloat>
#include "sql/expr/tuple_cell.h"

class TupleCellFactory {
public:
  static inline TupleCell GetCharTupleCell(const char *data)
  {
    Value value;
    value_init_string(&value, data);
    return {CHARS, static_cast<char *>(value.data)};
  }

  static inline TupleCell GetIntegerTupleCell(int data)
  {
    Value value;
    value_init_integer(&value, data);
    return {INTS, static_cast<char *>(value.data)};
  }

  static inline TupleCell GetFloatTupleCell(float data)
  {
    Value value;
    value_init_float(&value, data);
    return {FLOATS, static_cast<char *>(value.data)};
  }

  static inline TupleCell GetDateTupleCell(int data)
  {
    Value value;
    value_init_integer(&value, data);
    return {DATES, static_cast<char *>(value.data)};
  }

  static inline TupleCell GetMaxTupleCellByType(AttrType type, int length)
  {
    switch (type) {
      case UNDEFINED:
        assert(false);
      case CHARS: {
        auto data = static_cast<char *>(malloc(length * sizeof(int) + 1));
        memset(data, 0, length * sizeof(int) + 1);
        memset(data, INT8_MAX, length * sizeof(int));
        return GetCharTupleCell(data);
      }
      case INTS:
        return GetIntegerTupleCell(INT32_MAX);
      case FLOATS:
        return GetFloatTupleCell(FLT_MAX);
      case DATES:
        return GetDateTupleCell(INT32_MAX);
    }
    assert(false);
  }

  static inline TupleCell GetMinTupleCellByType(AttrType type)
  {
    switch (type) {
      case UNDEFINED:
        assert(false);
      case CHARS:
        return GetCharTupleCell("");
      case INTS:
        return GetIntegerTupleCell(INT32_MIN);
      case FLOATS:
        return GetFloatTupleCell(FLT_MIN);
      case DATES:
        return GetDateTupleCell(INT32_MIN);
    }
    assert(false);
  }
};
