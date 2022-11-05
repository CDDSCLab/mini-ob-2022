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
#include "sql/stmt/select_stmt.h"
#include "sql/operator/operator_factory.h"

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
      case EXPR_ROUND: {
        if (expr.right->expr_type != EXPR_VALUE) {
          return new ExprExpr(expr.expr_type, NewExpression(*expr.left, db, default_table, tables), nullptr);
        } else {
          return new ExprExpr(expr.expr_type,
              NewExpression(*expr.left, db, default_table, tables),
              NewExpression(*expr.right, db, default_table, tables));
        }
      }
      case EXPR_DATE_FORMAT:
        return new ExprExpr(expr.expr_type,
            NewExpression(*expr.left, db, default_table, tables),
            NewExpression(*expr.right, db, default_table, tables));
      case EXPR_NEGATIVE:
      case EXPR_BRACE:
      case EXPR_LENGTH:
        return new ExprExpr(expr.expr_type, NewExpression(*expr.left, db, default_table, tables), nullptr);
      case EXPR_VALUE:
        return new ValueExpr(expr.value);
      case EXPR_ATTR: {
        Table *table = nullptr;
        const FieldMeta *field = nullptr;
        if (0 == strcmp(expr.attr.attribute_name, "*")) {
          if (expr.attr.aggr_type == AGGR_COUNT) {
            return new FieldExpr(default_table, default_table->table_meta().field(0), expr.attr.aggr_type);
          }
        }
        get_table_and_field(db, default_table, tables, expr.attr, table, field);
        return new FieldExpr(table, field, expr.attr.aggr_type);
      }
      case EXPR_SELECT: {
        Stmt *select_stmt;
        SelectStmt::create(db, *expr.select, *tables, select_stmt);
        auto project_oper = new ProjectOperator();
        OperatorFactory::GetProjectOperator(dynamic_cast<SelectStmt *>(select_stmt), project_oper);
        return new SelectExpr(project_oper);
      }
      case EXPR_VALUES: {
        auto values_expr = new ValuesExpr();
        for (int i = 0; i < expr.value_num; ++i) {
          values_expr->add_value(expr.values[i]);
        }
        return values_expr;
      }
      case EXPR_NONE:
      default: {
        return nullptr;
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

  static void wildcard_expr(
      Table *table, std::vector<Expression *> &exprs, Db *db, std::unordered_map<std::string, Table *> table_map)
  {
    const TableMeta &table_meta = table->table_meta();
    const int field_num = table_meta.field_num();
    for (int i = table_meta.sys_field_num(); i < field_num; i++) {
      Expr tmp;
      tmp.expr_type = EXPR_ATTR;
      tmp.attr.relation_name = const_cast<char *>(table->name());
      tmp.attr.attribute_name = const_cast<char *>(table_meta.field(i)->name());
      exprs.emplace_back(ExpressionFactory::NewExpression(tmp, db, table, &table_map));
    }
  }
};