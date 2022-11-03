//
// Created by Moon on 2022/11/2.
//

#pragma once

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/expr/expression.h"
#include "storage/common/db.h"
#include "storage/common/table.h"

class ExpressionFactory {
public:
  static inline Expression *NewExpression(
      const Expr &expr, Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables)
  {
    switch (expr.expr_type) {
      case EXPR_PLUS:
      case EXPR_MINUS:
      case EXPR_MULTIPLY:
      case EXPR_DIVIDE:
        return new ExprExpr(expr.expr_type,
            NewExpression(*expr.left, db, default_table, tables),
            NewExpression(*expr.right, db, default_table, tables));
      case EXPR_NEGATIVE:
        return new ExprExpr(expr.expr_type, NewExpression(*expr.left, db, default_table, tables), nullptr);
      case EXPR_VALUE:
        return new ValueExpr(expr.value);
      case EXPR_ATTR: {
        Table *table = nullptr;
        const FieldMeta *field = nullptr;
        get_table_and_field(db, default_table, tables, expr.attr, table, field);
        return new FieldExpr(table, field, expr.attr.aggr_type);
      }
      case EXPR_SELECT: {
        // TODO
      }
      case EXPR_NONE:
      default: {
        assert(false);
      } break;
    }
  }

  static RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
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

    field = table->table_meta().field(attr.attribute_name);
    if (nullptr == field) {
      LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name);
      table = nullptr;
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    return RC::SUCCESS;
  }
};