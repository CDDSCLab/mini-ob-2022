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
// Created by Meiyi
//

#include <mutex>
#include "sql/parser/parse.h"
#include "rc.h"
#include "common/log/log.h"

RC parse(char *st, Query *sqln);

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name)
{
  if (relation_name != nullptr) {
    relation_attr->relation_name = strdup(relation_name);
  } else {
    relation_attr->relation_name = nullptr;
  }
  relation_attr->attribute_name = strdup(attribute_name);
  relation_attr->aggr_type = AGGR_NONE;
}

void relation_attr_aggr(RelAttr *relation_attr, AggrType aggr_type)
{
  relation_attr->aggr_type = aggr_type;
}

void relation_attr_destroy(RelAttr *relation_attr)
{
  free(relation_attr->relation_name);
  free(relation_attr->attribute_name);
  relation_attr->relation_name = nullptr;
  relation_attr->attribute_name = nullptr;
}

void value_init_integer(Value *value, int v)
{
  value->type = INTS;
  value->data = malloc(sizeof(v));
  value->is_null = false;
  memcpy(value->data, &v, sizeof(v));
}
void value_init_float(Value *value, float v)
{
  value->type = FLOATS;
  value->data = malloc(sizeof(v));
  value->is_null = false;
  memcpy(value->data, &v, sizeof(v));
}
void value_init_string(Value *value, const char *v)
{
  value->type = CHARS;
  value->is_null = false;
  value->data = strdup(v);
}
void value_init_null(Value *value)
{
  value->type = NULLS;
  value->is_null = true;
  int v = 0;
  value->data = malloc(sizeof(v));
  memcpy(value->data, &v, sizeof(v));
}
void value_destroy(Value *value)
{
  value->type = UNDEFINED;
  free(value->data);
  value->data = nullptr;
  value->is_null = false;
}

void expr_init_value(Expr *expr, Value *value)
{
  expr->expr_type = EXPR_VALUE;
  expr->value = *value;
}
void expr_append_value(Expr *expr, Value *value)
{
  expr->expr_type = EXPR_VALUES;
  expr->values[expr->value_num] = (Value *)malloc(sizeof(Value));
  *expr->values[expr->value_num++] = *value;
}
void expr_init_attr(Expr *expr, RelAttr *relation_attr)
{
  expr->expr_type = EXPR_ATTR;
  expr->attr = *relation_attr;
}
void expr_init_select(Expr *expr, Selects *selects)
{
  expr->expr_type = EXPR_SELECT;
  expr->select = (Selects *)malloc(sizeof(Selects));
  *expr->select = *selects;
}
void expr_init_expr(Expr *expr, ExprType expr_type, Expr *left_expr, Expr *right_expr)
{
  expr->expr_type = expr_type;
  expr->left = (Expr *)malloc(sizeof(Expr));
  expr->right = (Expr *)malloc(sizeof(Expr));
  *expr->left = *left_expr;
  if (right_expr != nullptr) {
    *expr->right = *right_expr;
  }
}
void expr_destroy(Expr *expr)
{
  if (expr == nullptr) {
    return;
  }
  switch (expr->expr_type) {
    case EXPR_PLUS:
    case EXPR_MINUS:
    case EXPR_MULTIPLY:
    case EXPR_DIVIDE: {
      expr_destroy(expr->left);
      expr_destroy(expr->right);
    } break;
    case EXPR_NEGATIVE:
    case EXPR_BRACE: {
      expr_destroy(expr->left);
    } break;
    case EXPR_VALUE: {
      value_destroy(&expr->value);
    } break;
    case EXPR_ATTR: {
      relation_attr_destroy(&expr->attr);
    } break;
    case EXPR_SELECT:
    case EXPR_LENGTH:
    case EXPR_ROUND:
    case EXPR_DATE_FORMAT: {
    } break;
    case EXPR_VALUES: {
      for (int i = 0; i < expr->value_num; ++i) {
        value_destroy(expr->values[i]);
      }
    } break;
    case EXPR_NONE:
    default: {
      assert(false);
    } break;
  }
}

void condition_init(Condition *condition, CompOp comp, Expr *left_expr, Expr *right_expr)
{
  condition->comp = comp;
  condition->left_expr = *left_expr;
  condition->right_expr = *right_expr;
}

void condition_init_logical(Condition *condition, LogicalOp logical_op)
{
  condition->logical_op = logical_op;
}

void condition_destroy(Condition *condition)
{
  expr_destroy(&condition->left_expr);
  expr_destroy(&condition->right_expr);
}

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, bool nullable)
{
  attr_info->name = strdup(name);
  attr_info->type = type;
  attr_info->length = length;
  attr_info->nullable = nullable;
}
void attr_info_destroy(AttrInfo *attr_info)
{
  free(attr_info->name);
  attr_info->name = nullptr;
}

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr)  // UNUSE
{
  selects->attributes[selects->attr_num++] = *rel_attr;
}
void selects_append_expr(Selects *selects, Expr *expr, const char *attr_alias)
{
  selects->exprs[selects->expr_num] = *expr;
  // TODO: 仅为了本地测试能跑， 后面应该优化
  if (attr_alias == NULL) {
    selects->select_expr_alias[selects->expr_num++] = nullptr;
  } else {
    selects->select_expr_alias[selects->expr_num++] = strdup(attr_alias);
  }
  selects_append_attr(selects, expr);
}
void selects_append_attr(Selects *selects, Expr *expr)  // UNUSE
{
  switch (expr->expr_type) {
    case EXPR_PLUS:
    case EXPR_MINUS:
    case EXPR_MULTIPLY:
    case EXPR_DIVIDE: {
      selects_append_attr(selects, expr->left);
      selects_append_attr(selects, expr->right);
    } break;
    case EXPR_NEGATIVE: {
      selects_append_attr(selects, expr->left);
    } break;
    case EXPR_ATTR: {
      selects->attributes[selects->attr_num++] = expr->attr;
    } break;
    case EXPR_SELECT:
      break;
    case EXPR_BRACE: {
      selects_append_attr(selects, expr->left);
    } break;
    case EXPR_VALUE:
    case EXPR_NONE:
    default:
      break;
  }
}
void selects_append_relation(Selects *selects, const char *relation_name, const char *relation_alias)
{
  selects->relations[selects->relation_num] = strdup(relation_name);
  if (relation_alias == NULL) {
    selects->relation_alias[selects->relation_num++] = nullptr;
  } else {
    selects->relation_alias[selects->relation_num++] = strdup(relation_alias);
  }
}

void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(selects->conditions) / sizeof(selects->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    selects->conditions[i] = conditions[i];
  }
  selects->condition_num = condition_num;
}

void selects_append_groups(Selects *selects, RelAttr *rel_attr)
{
  selects->group_attributes[selects->group_num++] = *rel_attr;
}

void selects_append_having(Selects *selects, Condition *condition)
{
  selects->having[selects->having_num++] = *condition;
}

void selects_append_order(Selects *selects, char *attribute_name, OrderType type, char *relation_name)
{
  RelAttr tmp;
  tmp.relation_name = relation_name;
  tmp.attribute_name = attribute_name;
  selects->order[selects->order_num].order_type = type;
  selects->order[selects->order_num].attr = tmp;
  selects->order_num++;
}

void selects_destroy(Selects *selects)
{
  // TODO handle destroy expr.
  for (size_t i = 0; i < selects->attr_num; i++) {
    relation_attr_destroy(&selects->attributes[i]);
  }
  selects->attr_num = 0;

  for (size_t i = 0; i < selects->relation_num; i++) {
    free(selects->relations[i]);
    selects->relations[i] = NULL;
  }
  selects->relation_num = 0;

  for (size_t i = 0; i < selects->condition_num; i++) {
    condition_destroy(&selects->conditions[i]);
  }
  selects->condition_num = 0;

  for (size_t i = 0; i < selects->order_num; i++) {
    // free(selects->order[i].attr.relation_name);
    // free(selects->order[i].attr.attribute_name);
    // selects->order[i].attr.relation_name = NULL;
    // selects->order[i].attr.attribute_name = NULL;
  }
  selects->order_num = 0;
}

void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t groups[], size_t group_num)
{
  if (group_num == 1) {
    assert(groups[0] <= sizeof(inserts->values) / sizeof(inserts->values[0]));  // mine 字节数

    inserts->relation_name = strdup(relation_name);
    for (size_t i = 0; i < groups[0]; i++) {
      inserts->values[i] = values[i];
    }
    inserts->value_num = groups[0];
    inserts->group_num = group_num;
  } else {  // group_num>1
    // mine 检查括号的数量，不能超过MAX_NUM=20
    assert(group_num <= sizeof(inserts->values) / sizeof(inserts->values[0]));

    inserts->relation_name = strdup(relation_name);
    inserts->group_num = group_num;
    size_t read_count = 0;
    for (size_t i = 0; i < group_num; i++) {
      // mine 每个括号中值得数量，都不能超过MAX_NUM=20
      assert(groups[i] <= sizeof(inserts->values) / sizeof(inserts->values[0]));
      if (i == 0) {
        for (size_t j = 0; j < groups[i]; j++) {
          inserts->values[j] = values[j];
          read_count++;
        }
        inserts->value_num = groups[0];
      } else {
        inserts->group[i - 1].value_num = groups[i];
        size_t j = 0;
        for (; j < groups[i]; j++) {
          inserts->group[i - 1].values[j] = values[j + read_count];
        }
        read_count = read_count + j;
      }
    }
  }
}
void inserts_destroy(Inserts *inserts)
{
  free(inserts->relation_name);
  inserts->relation_name = nullptr;

  for (size_t i = 0; i < inserts->value_num; i++) {
    value_destroy(&inserts->values[i]);
  }
  inserts->value_num = 0;
}

void deletes_init_relation(Deletes *deletes, const char *relation_name)
{
  deletes->relation_name = strdup(relation_name);
}

void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num)
{
  assert(condition_num <= sizeof(deletes->conditions) / sizeof(deletes->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    deletes->conditions[i] = conditions[i];
  }
  deletes->condition_num = condition_num;
}
void deletes_destroy(Deletes *deletes)
{
  for (size_t i = 0; i < deletes->condition_num; i++) {
    condition_destroy(&deletes->conditions[i]);
  }
  deletes->condition_num = 0;
  free(deletes->relation_name);
  deletes->relation_name = nullptr;
}

void updates_init(Updates *updates, const char *relation_name, Condition conditions[], size_t condition_num)
{
  updates->relation_name = strdup(relation_name);

  assert(condition_num <= sizeof(updates->conditions) / sizeof(updates->conditions[0]));
  for (size_t i = 0; i < condition_num; i++) {
    updates->conditions[i] = conditions[i];
  }
  updates->condition_num = condition_num;
}

void updates_append_attr(Updates *updates, const char *relation_name, Value *value)
{
  updates->attribute_name[updates->attr_num] = strdup(relation_name);
  updates->is_value[updates->attr_num] = true;
  updates->values[updates->attr_num++] = *value;
}

void updates_append_select(Updates *updates, const char *relation_name, Selects *selects)
{
  updates->attribute_name[updates->attr_num] = strdup(relation_name);
  updates->is_value[updates->attr_num] = false;
  updates->selects[updates->attr_num++] = *selects;
}

void updates_destroy(Updates *updates)
{
  free(updates->relation_name);
  for (int i = 0; i < updates->attr_num; i++) {
    free(updates->attribute_name[i]);
    updates->attribute_name[i] = nullptr;
    value_destroy(&updates->values[i]);
  }
  updates->relation_name = nullptr;

  for (size_t i = 0; i < updates->condition_num; i++) {
    condition_destroy(&updates->conditions[i]);
  }
  updates->condition_num = 0;
}

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info)
{
  create_table->attributes[create_table->attribute_count++] = *attr_info;
}

void create_table_init_name(CreateTable *create_table, const char *relation_name)
{
  create_table->relation_name = strdup(relation_name);
}

void create_table_destroy(CreateTable *create_table)
{
  for (size_t i = 0; i < create_table->attribute_count; i++) {
    attr_info_destroy(&create_table->attributes[i]);
  }
  create_table->attribute_count = 0;
  free(create_table->relation_name);
  create_table->relation_name = nullptr;
}

void drop_table_init(DropTable *drop_table, const char *relation_name)
{
  drop_table->relation_name = strdup(relation_name);
}

void drop_table_destroy(DropTable *drop_table)
{
  free(drop_table->relation_name);
  drop_table->relation_name = nullptr;
}

void show_index_init(ShowIndex *show_index, const char *relation_name)
{
  show_index->relation_name = strdup(relation_name);
}

void show_index_destroy(ShowIndex *show_index)
{
  free(show_index->relation_name);
  show_index->relation_name = nullptr;
}

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, int is_unique, int attr_num)
{
  create_index->index_name = strdup(index_name);
  create_index->relation_name = strdup(relation_name);
  create_index->is_unique = is_unique;
  create_index->attr_num = attr_num;
}

void create_index_first_attr(CreateIndex *create_index, const char *attr_name)
{
  create_index->attribute_name = strdup(attr_name);
}
void create_index_append_attr(CreateIndex *create_index, int num, const char *attr_name)
{
  create_index->attribute_names[num] = strdup(attr_name);
}

void create_index_destroy(CreateIndex *create_index)
{
  free(create_index->index_name);
  free(create_index->relation_name);
  free(create_index->attribute_name);

  create_index->index_name = nullptr;
  create_index->relation_name = nullptr;
  create_index->attribute_name = nullptr;
}

void drop_index_init(DropIndex *drop_index, const char *index_name)
{
  drop_index->index_name = strdup(index_name);
}

void drop_index_destroy(DropIndex *drop_index)
{
  free((char *)drop_index->index_name);
  drop_index->index_name = nullptr;
}

void desc_table_init(DescTable *desc_table, const char *relation_name)
{
  desc_table->relation_name = strdup(relation_name);
}

void desc_table_destroy(DescTable *desc_table)
{
  free((char *)desc_table->relation_name);
  desc_table->relation_name = nullptr;
}

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name)
{
  load_data->relation_name = strdup(relation_name);

  if (file_name[0] == '\'' || file_name[0] == '\"') {
    file_name++;
  }
  char *dup_file_name = strdup(file_name);
  int len = strlen(dup_file_name);
  if (dup_file_name[len - 1] == '\'' || dup_file_name[len - 1] == '\"') {
    dup_file_name[len - 1] = 0;
  }
  load_data->file_name = dup_file_name;
}

void load_data_destroy(LoadData *load_data)
{
  free((char *)load_data->relation_name);
  free((char *)load_data->file_name);
  load_data->relation_name = nullptr;
  load_data->file_name = nullptr;
}

void query_init(Query *query)
{
  query->flag = SCF_ERROR;
  memset(&query->sstr, 0, sizeof(query->sstr));
}

Query *query_create()
{
  Query *query = (Query *)malloc(sizeof(Query));
  if (nullptr == query) {
    LOG_ERROR("Failed to alloc memroy for query. size=%ld", sizeof(Query));
    return nullptr;
  }

  query_init(query);
  return query;
}

void query_reset(Query *query)
{
  switch (query->flag) {
    case SCF_SELECT: {
      selects_destroy(&query->sstr.selection);
    } break;
    case SCF_INSERT: {
      inserts_destroy(&query->sstr.insertion);
    } break;
    case SCF_DELETE: {
      deletes_destroy(&query->sstr.deletion);
    } break;
    case SCF_UPDATE: {
      updates_destroy(&query->sstr.update);
    } break;
    case SCF_CREATE_TABLE: {
      create_table_destroy(&query->sstr.create_table);
    } break;
    case SCF_DROP_TABLE: {
      drop_table_destroy(&query->sstr.drop_table);
    } break;
    case SCF_SHOW_INDEX: {
      show_index_destroy(&query->sstr.show_index);
    } break;
    case SCF_CREATE_INDEX: {
      create_index_destroy(&query->sstr.create_index);
    } break;
    case SCF_DROP_INDEX: {
      drop_index_destroy(&query->sstr.drop_index);
    } break;
    case SCF_SYNC: {

    } break;
    case SCF_SHOW_TABLES:
      break;

    case SCF_DESC_TABLE: {
      desc_table_destroy(&query->sstr.desc_table);
    } break;

    case SCF_LOAD_DATA: {
      load_data_destroy(&query->sstr.load_data);
    } break;
    case SCF_CLOG_SYNC:
    case SCF_BEGIN:
    case SCF_COMMIT:
    case SCF_ROLLBACK:
    case SCF_HELP:
    case SCF_EXIT:
    case SCF_ERROR:
      break;
  }
}

void query_destroy(Query *query)
{
  query_reset(query);
  free(query);
}
#ifdef __cplusplus
}  // extern "C"
#endif  // __cplusplus

////////////////////////////////////////////////////////////////////////////////

extern "C" int sql_parse(const char *st, Query *sqls);

RC parse(const char *st, Query *sqln)
{
  sql_parse(st, sqln);

  if (sqln->flag == SCF_ERROR)
    return SQL_SYNTAX;
  else
    return SUCCESS;
}