
%{

#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  Selects selects[MAX_NUM];
  size_t value_length;
  size_t attr_length;
  size_t expr_length;
  Value values[MAX_NUM];
  size_t condition_length[MAX_NUM];
  Condition conditions[MAX_NUM][MAX_NUM];
  RelAttr attrs[MAX_NUM];
  Expr exprs[MAX_NUM * 10];
  char id[MAX_NUM];

  // add by us
  size_t group_num;
  size_t every_group_count;
  size_t insert_groups[MAX_NUM*MAX_NUM];
  size_t attr_num;

} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  for (int i = 0; i < MAX_NUM; i++) {
    context->condition_length[i] = 0;
  }
  context->value_length = 0;
  context->select_length = 0;
  context->ssql->sstr.insertion.value_num = 0;

  // add by us
  context->group_num = 0;
  context->every_group_count=0;
  context->attr_num = 0;

  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)

%}

%define api.pure full
%lex-param { yyscan_t scanner }
%parse-param { void *scanner }

//标识tokens
%token  SEMICOLON
        CREATE
        DROP
        TABLE
        TABLES
        INDEX
        UNIQUE
        SELECT
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        LBRACE
        RBRACE
        COMMA
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
		TEXT_T
        FLOAT_T
        DATE_T
        MAX
        MIN
        COUNT
        AVG
        SUM
        GROUP
        BY
        HAVING
        HELP
        EXIT
        DOT // QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EQ
        LT
        GT
        LE
        GE
        NE
        LIKE
        IN
        EXISTS
        INNER
        JOIN
        IS
        NOT
        NULL_TOKEN
        NULLABLE
        ORDER
        ASC
        PLUS
        MINUS
        STAR
        DIVIDE
        AS

%union {
  struct _RelAttr *_attr;
  struct _Condition *_condition;
  struct _Value *_value;
  struct _Selects *_select;
  struct _Expr *_expr;
  char *string;
  int number;
  float floats;
  char *position;
}

%token <number> NUMBER
%token <floats> FLOAT 
%token <string> ID
%token <string> PATH
%token <string> SSS
%token <string> STRING_V
// 非终结符

%type <number> type;
%type <number> aggr_type;
%type <_attr> attr;
%type <_attr> aggr_attr;
%type <_condition> condition;
%type <_value> value;
%type <_value> expr_value;
%type <number> number;
%type <number> comOp;
%type <number> null_comOp;
%type <number> nullable;

%type <_select> select_unit;
%type <_expr> expr;
%type <_expr> add_expr;
%type <_expr> mul_expr;
%type <_expr> primary_expr;
%type <string> alias;

%%

commands:		//commands or sqls. parser starts here.
    /* empty */
    | commands command
    ;

command:
	  select  
	| insert
	| update
	| delete
	| create_table
	| drop_table
	| show_tables
	| show_index
	| desc_table
	| create_index	
	| drop_index
	| sync
	| begin
	| commit
	| rollback
	| load_data
	| help
	| exit
    ;

exit:
    EXIT SEMICOLON {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    };

help:
    HELP SEMICOLON {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    };

sync:
    SYNC SEMICOLON {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
    ;

begin:
    TRX_BEGIN SEMICOLON {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
    ;

commit:
    TRX_COMMIT SEMICOLON {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
    ;

rollback:
    TRX_ROLLBACK SEMICOLON {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
    ;

drop_table:		/*drop table 语句的语法解析树*/
    DROP TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, $3);
    };

show_tables:
    SHOW TABLES SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
    ;

show_index:
    SHOW INDEX FROM ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, $4);
    }
    ;

desc_table:
    DESC ID SEMICOLON {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, $2);
    }
    ;

create_index:		/*create index 语句的语法解析树*/
    CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON
	{
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, $4, $6, 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
    | CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON
	{
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, $3, $5, 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
    ;
attrone:
    ID
	{
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, $1);
	}
    ;
attr_index:
    ID
	{
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, $1);
		CONTEXT->attr_num++;
	}
    ;
attr_index_list:
    /* empty */
    | COMMA attr_index attr_index_list
	{

	}
    ;

drop_index:			/*drop index 语句的语法解析树*/
    DROP INDEX ID  SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, $3);
		}
    ;
create_table:		/*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON 
		{
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, $3);
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
    ;
attr_def_list:
    /* empty */
    | COMMA attr_def attr_def_list {    }
    ;
    
attr_def:
    ID_get type LBRACE number RBRACE nullable {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, $2, $4 + 1, $6);
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
    }
    | ID_get type nullable {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, $2, 4 + 1, $3);
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
	};
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T { $$ = INTS; }
    | STRING_T { $$ = CHARS; }
    | TEXT_T { $$=TEXTS; }
    | FLOAT_T { $$ = FLOATS; }
    | DATE_T { $$ = DATES; }
    ;
ID_get:
    ID {
        char *temp=$1;
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    };
nullable:
      /* empty */ { $$ = false; }
    | NULLABLE { $$ = true; }
	| NOT NULL_TOKEN { $$ = false; }
	;

insert:				/*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE value value_list RBRACE v_list SEMICOLON 
	{
		CONTEXT->ssql->flag=SCF_INSERT;
		CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
		CONTEXT->every_group_count=0;
        CONTEXT->group_num = CONTEXT->group_num + 1;

		inserts_init(&CONTEXT->ssql->sstr.insertion, $3, CONTEXT->values, CONTEXT->insert_groups, CONTEXT->group_num);

		//临时变量清零
		CONTEXT->value_length=0;
    }

v_list:
    | node value value_list RBRACE v_list
    {
    };

node:
    COMMA LBRACE
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    };

value_list:
    /* empty */
    | COMMA value value_list  { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
    ;
expr_value:
      NUMBER {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
    | FLOAT {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
    | SSS {
        $1 = substr($1,1,strlen($1)-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
    | NULL_TOKEN {
         value_init_null(&CONTEXT->values[CONTEXT->value_length]);
         $$ = &CONTEXT->values[CONTEXT->value_length++];
         CONTEXT->every_group_count++;
     };
value:
    NUMBER {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
    | MINUS NUMBER {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], -$2);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
    | FLOAT {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
	}
    | SSS {
        $1 = substr($1,1,strlen($1)-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
    | NULL_TOKEN {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        $$ = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    };
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON {
        CONTEXT->ssql->flag = SCF_DELETE;//"delete";
        deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
        deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->conditions[CONTEXT->select_length],
                CONTEXT->condition_length[CONTEXT->select_length]);
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
    ;

update:			/*  update 语句的语法解析树*/
    UPDATE ID SET update_attr where SEMICOLON {
        CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, $2, CONTEXT->conditions[CONTEXT->select_length],
		        CONTEXT->condition_length[CONTEXT->select_length]);
		CONTEXT->condition_length[CONTEXT->select_length] = 0;
    };
update_attr:
    ID EQ value update_attr_list {
		updates_append_attr(&CONTEXT->ssql->sstr.update, $1, $3);
    }
    | update_unit update_attr_list {

    };
update_attr_list:
    /* empty */
    | COMMA ID EQ value update_attr_list {
        updates_append_attr(&CONTEXT->ssql->sstr.update, $2, $4);
    }
    | COMMA update_unit update_attr_list {

    };
update_unit:
    ID EQ LBRACE select_unit RBRACE {
        updates_append_select(&CONTEXT->ssql->sstr.update, $1, $4);
    };

select:				/*  select 语句的语法解析树*/
    select_unit SEMICOLON {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[1];
    };
select_unit:
    select_begin select_attr FROM ID alias rel_list where group_by order_by {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $4, $5);
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length],
                CONTEXT->conditions[CONTEXT->select_length], CONTEXT->condition_length[CONTEXT->select_length]);
        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        $$ = &CONTEXT->selects[CONTEXT->select_length--];
    };

alias:
    // empty
    {
        $$ = NULL;
    }
    | AS ID{
        $$ = $2;
    }
    | ID{
        $$ = $1;
    }
    ;

select_begin:
    SELECT {
        CONTEXT->select_length++;
        memset(&CONTEXT->selects[CONTEXT->select_length], 0, sizeof(Selects));
    }
    ;
select_attr:
     STAR select_attr_list {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], &attr);
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], &CONTEXT->exprs[CONTEXT->expr_length++], NULL);
    }
    | expr alias select_attr_list {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], $1, $2);
    };
select_attr_list:
    /* empty */
    | COMMA expr alias select_attr_list {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], $2, $3);
    };
expr:
    add_expr {
        $$ = $1;
    }
    | LBRACE select_unit RBRACE {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], $2);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    };
add_expr:
    add_expr PLUS mul_expr {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_PLUS, $1, $3);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | add_expr MINUS mul_expr {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MINUS, $1, $3);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | mul_expr {
        $$ = $1;
    };
mul_expr:
    mul_expr STAR primary_expr {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MULTIPLY, $1, $3);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | mul_expr DIVIDE primary_expr {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_DIVIDE, $1, $3);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | MINUS primary_expr {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_NEGATIVE, $2, NULL);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | primary_expr {
        $$ = $1;
    };
primary_expr:
    LBRACE add_expr RBRACE {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_BRACE, $2, NULL);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | attr {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], $1);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | aggr_attr {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], $1);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
    | expr_value {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length], $1);
        $$ = &CONTEXT->exprs[CONTEXT->expr_length++];
    };

attr:
    ID {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, $1);
        $$ = attr;
    }
    | ID DOT ID {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, $1, $3);
        $$ = attr;
    };
aggr_attr:
      aggr_type LBRACE attr RBRACE {
        relation_attr_aggr($3, $1);
        $$ = $3;
    }
    | aggr_type LBRACE STAR RBRACE {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, $1);
        $$ = attr;
    }
    | aggr_type LBRACE number RBRACE {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        if ($3 != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, $1);
        $$ = attr;
    };
aggr_type:
      MAX { $$ = AGGR_MAX; }
    | MIN { $$ = AGGR_MIN; }
    | COUNT { $$ = AGGR_COUNT; }
    | AVG { $$ = AGGR_AVG; }
    | SUM { $$ = AGGR_SUM; }
    ;

rel_list:
    /* empty */
    | COMMA ID alias rel_list {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $2, $3);
    }
    | join {
    };

join:
	INNER JOIN ID alias ON condition condition_list join_list {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $3, $4);
	};
join_list:
	/* empty */
	| INNER JOIN ID alias  ON condition condition_list join_list {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $3, $4);
	};

where:
    /* empty */ 
    | WHERE condition condition_list {}
    ;
condition_list:
    /* empty */
    | AND condition condition_list {}
    ;

condition:
    expr comOp expr {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                $2, $1, $3);
    }
    | expr IN LBRACE select_unit RBRACE  {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], $4);
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                IN_OP, $1, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
    | expr NOT IN LBRACE select_unit RBRACE {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], $5);
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_IN_OP, $1, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
    | EXISTS LBRACE select_unit RBRACE {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], $3);
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
    | NOT EXISTS LBRACE select_unit RBRACE {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], $4);
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
	| value null_comOp {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], $1);

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                $2, &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
	| attr null_comOp {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], $1);

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                $2, &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
    ;
comOp:
  	  EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LIKE_OP; }
    | NOT LIKE { $$ = NOT_LIKE_OP; }
    ;
null_comOp:
      IS NULL_TOKEN { $$ = IS_NULL; }
    | IS NOT NULL_TOKEN { $$ = IS_NOT_NULL; }
    ;

group_by:
    /* empty */
    | GROUP BY attr group_list having {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], $3);
    };
group_list:
    /* empty */
    | COMMA attr group_list {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], $2);
    };
having:
    /* empty */
    | HAVING aggr_attr comOp value having_list {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], $2);
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], $4);
        Condition condition;
        condition_init(&condition, $3, &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    };
having_list:
    /* empty */
    | AND aggr_attr comOp value having_list {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], $2);
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], $4);
        Condition condition;
        condition_init(&condition, $3, &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    };

order_by:
    // empty
    | ORDER BY order order_list {
    }
    ;
order_list:
    // empty
    | COMMA order order_list{
    }
    ;
order:
    ID{
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], $1, 0, "");
    }
    | ID DESC{
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], $1, 1, "");
    }
    | ID ASC{
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], $1, 0, "");
    }
    | ID DOT ID{
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], $3, 0, $1);
    }
    | ID DOT ID DESC{
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], $3, 1, $1);
    }
    | ID DOT ID ASC{
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], $3, 0, $1);
    }
    ;

load_data:
    LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, $7, $4);
    }
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
