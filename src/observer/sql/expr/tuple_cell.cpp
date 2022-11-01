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
// Created by WangYunlai on 2022/07/05.
//

#include "sql/expr/tuple_cell.h"
#include "storage/common/field.h"
#include "common/log/log.h"
#include "util/comparator.h"
#include "util/util.h"
#include "storage/common/text.h"

void TupleCell::to_string(std::ostream &os) const
{
  switch (attr_type_) {
    case INTS: {
      os << *(int *)data_;
    } break;
    case FLOATS: {
      float v = *(float *)data_;
      os << double2string(v);
    } break;
    case CHARS: {
      for (int i = 0; i < length_; i++) {
        if (data_[i] == '\0') {
          break;
        }
        os << data_[i];
      }
    } break;
    case DATES: {
      os << date2string(*(int *)data_);
    } break;
    case TEXTS: {
      int id = *(int *)data_;
      char *s = static_cast<char *>(malloc(sizeof(char) * TEXT_SIZE));
      get_text(id, s);
      int length = strlen(s);
      for (int i = 0; i < length; i++) {
        // if (data_[i] == '\0') {
        //   break;
        // }
        os << s[i];
      }
      free(s);
    } break;
    case NULLS: {
      os << "null";
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
}

Value TupleCell::to_value() const
{
  char *data = nullptr;
  int length = sizeof(int);
  switch (attr_type_) {
    case INTS: {
      length = sizeof(int);
    } break;
    case FLOATS: {
      length = sizeof(float);
    } break;
    case CHARS: {
      length = length_;
    } break;
    case DATES: {
      length = sizeof(int);
    } break;
    case TEXTS: {
      // TODO(yueyang): implement later.
    }
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  data = new char[length];
  memcpy(data, data_, length);
  return {attr_type_, data};
}

int TupleCell::compare(const TupleCell &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS:
      case DATES:
        return compare_int(this->data_, other.data_);
      case FLOATS:
        return compare_float(this->data_, other.data_);
      case CHARS:
        return compare_string(this->data_, this->length_, other.data_, other.length_);
      case NULLS:
        return 0;
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = *(int *)data_;
    return compare_float(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = *(int *)other.data_;
    return compare_float(data_, &other_data);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
    float other_data = atof(other.data_);
    float float_data = *(int *)this->data_;
    return compare_float(&float_data, &other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    int this_data = atoi(data_);
    return compare_int(&this_data, other.data_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    float other_data = atof(other.data_);
    return compare_float(this->data_, &other_data);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    float this_data = atof(data_);
    return compare_float(&this_data, other.data_);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

void TupleCell::plus(const TupleCell &other)
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        int result = *(int *)data_ + *(int *)other.data_;
        memcpy(data_, &result, sizeof(result));
      } break;
      case FLOATS: {
        float result = *(float *)data_ + *(float *)other.data_;
        memcpy(data_, &result, sizeof(result));
      } break;
      case UNDEFINED:
      case CHARS:
      case TEXTS:
      case DATES:
      case NULLS:
        // LOG_WARN("Wrong type of summation.");
        break;
    }
  } else {
    if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
      float result = *(float *)data_ + *(int *)other.data_;
      memcpy(data_, &result, sizeof(result));
    } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
      float result = *(int *)data_ + *(float *)other.data_;
      memcpy(data_, &result, sizeof(result));
    } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
      float result = *(float *)data_ + atof((char *)other.data_);
      memcpy(data_, &result, sizeof(result));
    } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
      int result = *(int *)data_ + atoi((char *)other.data_);
      memcpy(data_, &result, sizeof(result));
    } else {
      // only in COUNT()
    }
    // TODO(yueyang): implement
  }
}
