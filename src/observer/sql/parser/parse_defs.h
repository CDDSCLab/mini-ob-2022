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

#ifndef __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
#define __OBSERVER_SQL_PARSER_PARSE_DEFS_H__

#include <stddef.h>
#include <stdbool.h>

#define MAX_NUM 20
#define MAX_REL_NAME 20
#define MAX_ATTR_NAME 20
#define MAX_ERROR_MESSAGE 20
#define MAX_DATA 50

// 聚合类型
typedef enum { AGGR_NONE, AGGR_MAX, AGGR_MIN, AGGR_COUNT, AGGR_AVG, AGGR_SUM } AggrType;

// 属性结构体
typedef struct _RelAttr {
  char *relation_name;   // relation name (may be NULL) 表名
  char *attribute_name;  // attribute name              属性名
  AggrType aggr_type;    // aggregation type            聚合类型
} RelAttr;

typedef enum {
  EQUAL_TO,       // "="            0
  LESS_EQUAL,     // "<="           1
  NOT_EQUAL,      // "<>"           2
  LESS_THAN,      // "<"            3
  GREAT_EQUAL,    // ">="           4
  GREAT_THAN,     // ">"            5
  LIKE_OP,        // "like"         6
  NOT_LIKE_OP,    // "not like"     7
  IS_NULL,        // "is null"      8
  IS_NOT_NULL,    // "is not null"  9
  IN_OP,          // "in"           10
  NOT_IN_OP,      // "not in"       11
  EXISTS_OP,      // "exists"       12
  NOT_EXISTS_OP,  // "not exists"   13
  NO_OP
} CompOp;

// 属性值类型
typedef enum { UNDEFINED, CHARS, TEXTS, INTS, FLOATS, DATES, NULLS } AttrType;

// 属性值
typedef struct _Value {
  AttrType type;  // type of value
  void *data;     // value
  char is_null;
} Value;

typedef enum {
  EXPR_NONE,
  EXPR_PLUS,
  EXPR_MINUS,
  EXPR_MULTIPLY,
  EXPR_DIVIDE,
  EXPR_NEGATIVE,
  EXPR_VALUE,
  EXPR_ATTR,
  EXPR_SELECT,
} ExprType;

typedef struct _Expr {
  ExprType expr_type;
  struct _Expr *left;
  struct _Expr *right;
  Value value;
  RelAttr attr;
  struct _Selects *select;
} Expr;

typedef enum { CONDITION_UNDEFINED, CONDITION_ATTR, CONDITION_VALUE, CONDITION_SELECT } ConditionType;

typedef struct _Condition {
  CompOp comp;  // comparison operator
  Expr left_expr;
  Expr right_expr;
  RelAttr left_attr;  // left-hand side attribute
  Value right_value;  // right-hand side value if right_is_attr = FALSE
} Condition;

typedef enum { ORDER_ASC = 0, ORDER_DESC } OrderType;

// struct of order
typedef struct _Order {
  RelAttr attr;
  OrderType order_type;
} Order;

// struct of select
typedef struct _Selects {
  size_t attr_num;                    // Length of attrs in Select clause
  Expr exprs[MAX_NUM];                // express in Select clause
  size_t expr_num;                    // Length of express in Select clause
  char *select_expr_alias[MAX_NUM];   // attrs alias in Select clause
  RelAttr attributes[MAX_NUM];        // attrs in Select clause
  size_t relation_num;                // Length of relations in From clause
  char *relations[MAX_NUM];           // relations in From clause
  char *relation_alias[MAX_NUM];      // relation alias in From clause
  size_t condition_num;               // Length of conditions in Where clause
  Condition conditions[MAX_NUM];      // conditions in Where clause
  size_t group_num;                   // Length of group by in Select clause
  RelAttr group_attributes[MAX_NUM];  // attrs in group by clause
  size_t having_num;                  // Length of conditions in Where clause
  Condition having[MAX_NUM];          // conditions in Having clause
  Order order[MAX_NUM];               // fields used by order by
  size_t order_num;                   // num of order by
} Selects;

typedef struct {
  size_t value_num;       // Length of values
  Value values[MAX_NUM];  // value group to insert
} InsertGroup;

// struct of insert
typedef struct {
  char *relation_name;             // Relation to insert into
  size_t value_num;                // Length of values
  Value values[MAX_NUM];           // values to insert
  size_t group_num;                // mine number of value groups
  InsertGroup group[MAX_NUM - 1];  // mine other value groups to insert
} Inserts;

// struct of delete
typedef struct {
  char *relation_name;            // Relation to delete from
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Deletes;

// struct of update
typedef struct {
  char *relation_name;            // Relation to update
  size_t attr_num;                // attributes in Set clause
  char *attribute_name[MAX_NUM];  // Attribute to update
  Value values[MAX_NUM];          // update value
  Selects *selects[MAX_NUM];      // update select
  size_t condition_num;           // Length of conditions in Where clause
  Condition conditions[MAX_NUM];  // conditions in Where clause
} Updates;

typedef struct {
  char *name;     // Attribute name
  AttrType type;  // Type of attribute
  size_t length;  // Length of attribute
  bool nullable;  // Nullability of attribute
} AttrInfo;

// struct of create_table
typedef struct {
  char *relation_name;           // Relation name
  size_t attribute_count;        // Length of attribute
  AttrInfo attributes[MAX_NUM];  // attributes
} CreateTable;

// struct of drop_table
typedef struct {
  char *relation_name;  // Relation name
} DropTable;

typedef struct {
  char *relation_name;
} ShowIndex;

// struct of create_index
typedef struct {
  char *index_name;                // Index name
  char *relation_name;             // Relation name
  char *attribute_name;            // Attribute name
  char *attribute_names[MAX_NUM];  // Other attribute name
  size_t is_unique;
  size_t attr_num;  // Number of attrs
} CreateIndex;

// struct of  drop_index
typedef struct {
  const char *index_name;  // Index name
} DropIndex;

typedef struct {
  const char *relation_name;
} DescTable;

typedef struct {
  const char *relation_name;
  const char *file_name;
} LoadData;

union Queries {
  Selects selection;
  Inserts insertion;
  Deletes deletion;
  Updates update;
  CreateTable create_table;
  DropTable drop_table;
  CreateIndex create_index;
  DropIndex drop_index;
  DescTable desc_table;
  LoadData load_data;
  ShowIndex show_index;
  char *errors;
};

// 修改yacc中相关数字编码为宏定义
enum SqlCommandFlag {
  SCF_ERROR = 0,
  SCF_SELECT,
  SCF_INSERT,
  SCF_UPDATE,
  SCF_DELETE,
  SCF_CREATE_TABLE,
  SCF_DROP_TABLE,
  SCF_CREATE_INDEX,
  SCF_DROP_INDEX,
  SCF_SYNC,
  SCF_SHOW_TABLES,
  SCF_DESC_TABLE,
  SCF_BEGIN,
  SCF_COMMIT,
  SCF_CLOG_SYNC,
  SCF_ROLLBACK,
  SCF_LOAD_DATA,
  SCF_HELP,
  SCF_EXIT,
  SCF_SHOW_INDEX
};
// struct of flag and sql_struct
typedef struct Query {
  enum SqlCommandFlag flag;
  union Queries sstr;
} Query;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus

void relation_attr_init(RelAttr *relation_attr, const char *relation_name, const char *attribute_name);
void relation_attr_aggr(RelAttr *relation_attr, AggrType aggr_type);
void relation_attr_destroy(RelAttr *relation_attr);

void value_init_integer(Value *value, int v);
void value_init_float(Value *value, float v);
void value_init_string(Value *value, const char *v);
void value_init_null(Value *value);
void value_destroy(Value *value);

void expr_init_value(Expr *expr, Value *value);
void expr_init_attr(Expr *expr, RelAttr *relation_attr);
void expr_init_select(Expr *expr, Selects *selects);
void expr_init_expr(Expr *expr, ExprType expr_type, Expr *left_expr, Expr *right_expr);
void expr_destroy(Expr *expr);

void condition_init(Condition *condition, CompOp comp, Expr *left_expr, Expr *right_expr);
void condition_destroy(Condition *condition);

void attr_info_init(AttrInfo *attr_info, const char *name, AttrType type, size_t length, bool nullable);
void attr_info_destroy(AttrInfo *attr_info);

void selects_init(Selects *selects, ...);
void selects_append_attribute(Selects *selects, RelAttr *rel_attr);
void selects_append_expr(Selects *selects, Expr *expr, const char *attr_alias);
void selects_append_attr(Selects *selects, Expr *expr);
void selects_append_relation(Selects *selects, const char *relation_name, const char *relation_alias);
void selects_append_conditions(Selects *selects, Condition conditions[], size_t condition_num);
void selects_append_groups(Selects *selects, RelAttr *rel_attr);
void selects_append_having(Selects *selects, Condition *condition);
void selects_append_order(Selects *selects, char *attribute_name, OrderType type, char *relation_name);
void selects_destroy(Selects *selects);

// void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t value_num, size_t group_num);
void inserts_init(Inserts *inserts, const char *relation_name, Value values[], size_t groups[], size_t group_num);
void inserts_destroy(Inserts *inserts);

void deletes_init_relation(Deletes *deletes, const char *relation_name);
void deletes_set_conditions(Deletes *deletes, Condition conditions[], size_t condition_num);
void deletes_destroy(Deletes *deletes);

void updates_init(Updates *updates, const char *relation_name, Condition conditions[], size_t condition_num);
void updates_append_attr(Updates *updates, const char *relation_name, Value *value);
void updates_append_select(Updates *updates, const char *relation_name, Selects *selects);
void updates_destroy(Updates *updates);

void create_table_append_attribute(CreateTable *create_table, AttrInfo *attr_info);
void create_table_init_name(CreateTable *create_table, const char *relation_name);
void create_table_destroy(CreateTable *create_table);

void show_index_init(ShowIndex *show_index, const char *relation_name);
void show_index_destroy(ShowIndex *show_index);

void drop_table_init(DropTable *drop_table, const char *relation_name);
void drop_table_destroy(DropTable *drop_table);

void create_index_init(
    CreateIndex *create_index, const char *index_name, const char *relation_name, int is_unique, int attr_num);
void create_index_first_attr(CreateIndex *create_index, const char *attr_name);
void create_index_append_attr(CreateIndex *create_index, int num, const char *attr_name);
void create_index_destroy(CreateIndex *create_index);

void drop_index_init(DropIndex *drop_index, const char *index_name);
void drop_index_destroy(DropIndex *drop_index);

void desc_table_init(DescTable *desc_table, const char *relation_name);
void desc_table_destroy(DescTable *desc_table);

void load_data_init(LoadData *load_data, const char *relation_name, const char *file_name);
void load_data_destroy(LoadData *load_data);

void query_init(Query *query);
Query *query_create();  // create and init
void query_reset(Query *query);
void query_destroy(Query *query);  // reset and delete

#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // __OBSERVER_SQL_PARSER_PARSE_DEFS_H__
