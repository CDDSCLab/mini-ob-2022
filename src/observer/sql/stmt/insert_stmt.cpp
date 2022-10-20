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
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "util/util.h"
#include "util/typecast.h"

InsertStmt::InsertStmt(Table *table, const Value *values, int value_amount, int group_num, const InsertGroup *group)
    : table_(table), values_(values), value_amount_(value_amount), group_num_(group_num), groups_(group)
{}

RC InsertStmt::create(Db *db, const Inserts &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name;
  if (nullptr == db || nullptr == table_name || inserts.value_num <= 0) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d", db, table_name, inserts.value_num);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  for (int i = 0; i < inserts.group_num; i++) {
    const Value *values;
    int value_num;
    if (i == 0) {
      values = inserts.values;
      value_num = inserts.value_num;
    } else {
      values = inserts.group[i - 1].values;
      value_num = inserts.group[i - 1].value_num;
    }

    const TableMeta &table_meta = table->table_meta();
    const int field_num = table_meta.field_num() - table_meta.sys_field_num();
    if (field_num != value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d,%d", value_num, field_num, i);
      return RC::SCHEMA_FIELD_MISSING;
    }

    // check fields type
    const int sys_field_num = table_meta.sys_field_num();
    for (int j = 0; j < value_num; j++) {
      const FieldMeta *field_meta = table_meta.field(j + sys_field_num);
      const AttrType field_type = field_meta->type();
      const AttrType value_type = values[j].type;
      if (field_type != value_type) {  // TODO try to convert the value type to field type
        auto value = const_cast<Value *>(values + j);
        RC rc = typecast(value_type, field_type, value);
        if (rc == RC::SCHEMA_FIELD_TYPE_MISMATCH) {
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
              table_name,
              field_meta->name(),
              field_type,
              value_type);
          return rc;
        }
        if (rc != RC::SUCCESS) {
          return rc;
        }
      }
    }
  }

  const Value *values = inserts.values;
  const InsertGroup *groups = inserts.group;

  // everything alright
  stmt = new InsertStmt(table, values, (int)inserts.value_num, (int)inserts.group_num, groups);
  return RC::SUCCESS;
}
