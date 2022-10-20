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
// Created by Meiyi & Wangyunlai.wyl on 2021/5/18.
//

#include "storage/common/index_meta.h"
#include "storage/common/field_meta.h"
#include "storage/common/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "rc.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_name");

const static Json::StaticString FIELD_ISUNIQUE("isUnique");
const static Json::StaticString FIELD_ISCOMPOUND("isCompound");
const static Json::StaticString FIELD_NAMES("field_names");

RC IndexMeta::init(
    const char *name, const FieldMeta &field, int isUnique, int isCompound, std::vector<std::string> fields)
{
  if (nullptr == name || common::is_blank(name)) {
    return RC::INVALID_ARGUMENT;
  }
  for (size_t i = 0; i < fields.size(); i++) {
    if (common::is_blank(fields[i].c_str())) {
      return RC::INVALID_ARGUMENT;
    }
  }

  name_ = name;
  field_ = field.name();
  isUnique_ = isUnique;
  isCompound_ = isCompound;
  fields_ = fields;
  return RC::SUCCESS;
}

int IndexMeta::queryIsUnique() const
{
  return isUnique_;
}

int IndexMeta::queryIsCompound() const
{
  return isCompound_;
}

std::vector<std::string> IndexMeta::getOtherFields() const
{
  return fields_;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  json_value[FIELD_FIELD_NAME] = field_;

  json_value[FIELD_ISUNIQUE] = isUnique_;
  json_value[FIELD_ISCOMPOUND] = isCompound_;
  for (size_t i = 0; i < fields_.size(); i++) {
    json_value[FIELD_NAMES].append(fields_[i]);
  }
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &field_value = json_value[FIELD_FIELD_NAME];
  const Json::Value &isUnique = json_value[FIELD_ISUNIQUE];
  const Json::Value &isCompound = json_value[FIELD_ISCOMPOUND];
  const Json::Value &field_names = json_value[FIELD_NAMES];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  if (!field_value.isString()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        name_value.asCString(),
        field_value.toStyledString().c_str());
    return RC::GENERIC_ERROR;
  }

  const FieldMeta *field = table.field(field_value.asCString());
  if (nullptr == field) {
    LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), field_value.asCString());
    return RC::SCHEMA_FIELD_MISSING;
  }

  std::vector<std::string> tmp;
  for (int i = 0; i < field_names.size(); i++) {
    tmp.push_back(field_names[i].asString());
  }

  return index.init(name_value.asCString(), *field, isUnique.asInt(), isCompound.asInt(), tmp);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const char *IndexMeta::field() const
{
  return field_.c_str();
}

void IndexMeta::desc(std::ostream &os, std::string table_name) const
{
  int nonUnique = 1;
  if (isUnique_ == 1) {
    nonUnique = 0;
  }

  os << table_name << " | " << nonUnique << " | " << name_ << " | " << 1 << " | " << field_ << "\n";
  for (int i = 0; i < fields_.size(); i++) {
    os << table_name << " | " << nonUnique << " | " << name_ << " | " << i + 2 << " | " << fields_[i] << "\n";
  }
}