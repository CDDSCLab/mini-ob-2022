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

#include "rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/common/db.h"
#include "storage/common/table.h"
#include "sql/expr/expression_factory.h"
#include "util/util.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const Condition *conditions, int condition_num, FilterStmt *&stmt)
{
  return create(db, default_table, nullptr, tables, conditions, condition_num, stmt);
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    std::unordered_map<std::string, Table *> *parent_tables, const Condition *conditions, int condition_num,
    FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt = nullptr;

  auto tmp_stmt = new FilterStmt();
  for (int i = 0; i < condition_num; i++) {
    FilterUnit *filter_unit = nullptr;
    std::unordered_map<std::string, Table *> temp_tables;
    if (tables != nullptr) {
      temp_tables.insert(tables->begin(), tables->end());
    }
    if (parent_tables != nullptr) {
      temp_tables.insert(parent_tables->begin(), parent_tables->end());
    }
    rc = create_filter_unit(db, default_table, &temp_tables, conditions[i], filter_unit);
    if (rc != RC::SUCCESS) {
      delete tmp_stmt;
      LOG_WARN("failed to create filter unit. condition index=%d", i);
      return rc;
    }
    tmp_stmt->filter_units_.push_back(filter_unit);
  }

  stmt = tmp_stmt;
  return rc;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttr &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name)) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(std::string(attr.relation_name));
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name);
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (0 == strcmp(attr.attribute_name, "*")) {
    if (AggrType::AGGR_COUNT == attr.aggr_type) {
      field = table->table_meta().field(0);
    }
  } else {
    field = table->table_meta().field(attr.attribute_name);
  }
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name);
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const Condition &condition, FilterUnit *&filter_unit)
{
  RC rc = RC::SUCCESS;

  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }

  Expression *left = nullptr;
  Expression *right = nullptr;
  AttrType left_type = UNDEFINED;
  AttrType right_type = UNDEFINED;
  auto left_expr = &const_cast<Condition &>(condition).left_expr;
  auto right_expr = &const_cast<Condition &>(condition).right_expr;

  // Check if field exists.
  if (left_expr->expr_type == EXPR_ATTR) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, left_expr->attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    left_type = field->type();
  }
  if (right_expr->expr_type == EXPR_ATTR) {
    Table *table = nullptr;
    const FieldMeta *field = nullptr;
    rc = get_table_and_field(db, default_table, tables, right_expr->attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    right_type = field->type();
  }

  // Try to typecast.
  if (left_expr->expr_type == EXPR_ATTR && right_expr->expr_type == EXPR_VALUE) {
    if (left_type == DATES && right_expr->value.type == CHARS) {
      int date;
      rc = char2date((const char *)right_expr->value.data, &date);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      right_expr->value.type = DATES;
      memcpy(right_expr->value.data, &date, sizeof(date));
    }
  } else if (left_expr->expr_type == EXPR_VALUE && right_expr->expr_type == EXPR_ATTR) {
    if (left_expr->value.type == CHARS && right_type == DATES) {
      int date;
      rc = char2date((const char *)left_expr->value.data, &date);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      left_expr->value.type = DATES;
      memcpy(left_expr->value.data, &date, sizeof(date));
    }
  }

  //    if (comp == LIKE_OP || comp == NOT_LIKE_OP) {
  //      if (right_expr->expr_type != EXPR_VALUE) {
  //        return RC::INVALID_ARGUMENT;
  //      } else if (left_type != CHARS || right_type != CHARS) {
  //        return RC::INVALID_ARGUMENT;
  //      }
  //    }

  left = ExpressionFactory::NewExpression(condition.left_expr, db, default_table, tables);
  right = ExpressionFactory::NewExpression(condition.right_expr, db, default_table, tables);
  if (left == nullptr || right == nullptr) {
    return RC::GENERIC_ERROR;
  }

  // TODO(yueyang): handle typecast

  filter_unit = new FilterUnit;
  filter_unit->set_comp(comp);
  filter_unit->set_logical_op(condition.logical_op);
  filter_unit->set_left(left);
  filter_unit->set_right(right);

  // 检查两个类型是否能够比较
  return rc;
}
