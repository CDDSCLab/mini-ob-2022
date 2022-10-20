//
// Created by Moonmen on 2022/10/20.
//

#include "typecast.h"

#include <cstdlib>
#include <cstring>

#include "util/util.h"

RC int2float(Value *value)
{
  value->type = FLOATS;
  int int_data = *(int *)value->data;
  float float_data = int_data;
  memcpy(value->data, &float_data, sizeof(float));
  return RC::SUCCESS;
}

RC int2char(Value *value)
{
  value->type = CHARS;
  int int_data = *(int *)value->data;
  free(value->data);
  value->data = strdup(std::to_string(int_data).c_str());
  return RC::SUCCESS;
}

RC float2int(Value *value)
{
  value->type = INTS;
  float float_data = *(float *)value->data;
  int int_data = float_data + 0.5;
  memcpy(value->data, &int_data, sizeof(int));
  return RC::SUCCESS;
}

RC float2char(Value *value)
{
  value->type = CHARS;
  float float_data = *(float *)value->data;
  free(value->data);
  value->data = strdup(double2string(float_data).c_str());
  return RC::SUCCESS;
}

RC char2int(Value *value)
{
  value->type = INTS;
  int int_data = atoi((char *)value->data);
  free(value->data);
  value->data = malloc(sizeof(int));
  memcpy(value->data, &int_data, sizeof(int));
  return RC::SUCCESS;
}

RC char2float(Value *value)
{
  value->type = FLOATS;
  float float_data = atof((char *)value->data);
  free(value->data);
  value->data = malloc(sizeof(float));
  memcpy(value->data, &float_data, sizeof(float));
  return RC::SUCCESS;
}

RC char2date(Value *value)
{
  value->type = DATES;
  const char *chars = static_cast<const char *>(value->data);
  int date;
  RC rc = char2date(chars, &date);
  if (rc != RC::SUCCESS) {
    return rc;
  }
  free(value->data);
  value->data = malloc(sizeof(int));
  memcpy(value->data, &date, sizeof(int));
  return rc;
}