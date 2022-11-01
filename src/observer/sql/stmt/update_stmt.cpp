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

#include "sql/stmt/update_stmt.h"

#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "select_stmt.h"

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const Updates &update_sql, Stmt *&stmt)
{
  const char *table_name = update_sql.relation_name;
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  std::vector<const FieldMeta *> update_fields;
  std::vector<Value *> values;
  std::vector<SelectStmt *> selects;
  for (size_t i = update_sql.attr_num - 1;; i--) {
    const FieldMeta *field_meta = table->table_meta().field(update_sql.attribute_name[i]);
    if (nullptr == field_meta) {
      LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), update_sql.attribute_name[i]);
      return RC::SCHEMA_FIELD_MISSING;
    }
    update_fields.push_back(field_meta);
    values.emplace_back(const_cast<Value *>(&update_sql.values[i]));
    Stmt *select_stmt = nullptr;
    if (update_sql.selects[i] != nullptr) {
      RC rc = SelectStmt::create(db, *update_sql.selects[i], select_stmt);
      if (rc != RC::SUCCESS) {
        return rc;
      }
    }
    selects.emplace_back(dynamic_cast<SelectStmt *>(select_stmt));

    if (i == 0) {
      break;
    }
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, table, &table_map, update_sql.conditions, update_sql.condition_num, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  auto update_stmt = new UpdateStmt();
  update_stmt->table_ = table;
  update_stmt->update_fields_.swap(update_fields);
  update_stmt->values_.swap(values);
  update_stmt->select_stmt_.swap(selects);
  update_stmt->filter_stmt_ = filter_stmt;
  stmt = update_stmt;
  return rc;
}
