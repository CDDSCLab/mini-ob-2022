
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
  size_t condition_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
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
  context->condition_length = 0;
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
        INNER
        JOIN
        IS
        NOT
        NULL_TOKEN
        NULLABLE

%union {
  struct _RelAttr *_attr;
  struct _Condition *_condition;
  struct _Value *_value;
  struct _Selects *_select;
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
%token <string> STAR
%token <string> STRING_V
// 非终结符

%type <number> type;
%type <number> aggr_type;
%type <_attr> attr;
%type <_attr> aggr_attr;
%type <_condition> condition;
%type <_value> value;
%type <number> number;
%type <number> nullable;

%type <_select> select_unit;

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
        attr_info_init(&attribute, CONTEXT->id, $2, $4, $6);
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
    }
    | ID_get type nullable {
        AttrInfo attribute;
        attr_info_init(&attribute, CONTEXT->id, $2, 4, $3);
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
value:
    NUMBER {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length - 1];
        CONTEXT->every_group_count++;
    }
    | FLOAT {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length - 1];
        CONTEXT->every_group_count++;
	}
    | SSS {
        $1 = substr($1,1,strlen($1)-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length++], $1);
        $$ = &CONTEXT->values[CONTEXT->value_length - 1];
        CONTEXT->every_group_count++;
    }
    | NULL_TOKEN {
        value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
        CONTEXT->every_group_count++;
    };
    
delete:		/*  delete 语句的语法解析树*/
    DELETE FROM ID where SEMICOLON 
		{
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, $3);
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
    ;

update:			/*  update 语句的语法解析树*/
    UPDATE ID SET update_attr where SEMICOLON {
		CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, $2, CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
    };
update_attr:
    ID EQ value update_attr_list {
		updates_append_attr(&CONTEXT->ssql->sstr.update, $1, $3);
    }
    | ID EQ LBRACE select_unit RBRACE update_attr_list {
        updates_append_select(&CONTEXT->ssql->sstr.update, $1, $4);
    };
update_attr_list:
    /* empty */
    | COMMA ID EQ value update_attr_list {
        updates_append_attr(&CONTEXT->ssql->sstr.update, $2, $4);
    }
    | COMMA ID EQ LBRACE select_unit RBRACE update_attr_list {
        updates_append_select(&CONTEXT->ssql->sstr.update, $2, $5);
    };

select:				/*  select 语句的语法解析树*/
    select_unit SEMICOLON {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[CONTEXT->select_length - 1];
    };
select_unit:
    SELECT select_attr FROM ID rel_list where group {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $4);
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions, CONTEXT->condition_length);

        // 临时变量清零
        CONTEXT->condition_length = 0;
        CONTEXT->value_length = 0;
        $$ = &CONTEXT->selects[CONTEXT->select_length++];
    };

select_attr:
    STAR select_attr_list {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
    | attr select_attr_list {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], $1);
        free($1);
    }
    | aggr_attr select_attr_list {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], $1);
        free($1);
    };
select_attr_list:
    /* empty */
    | COMMA attr select_attr_list {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], $2);
        free($2);
    }
    | COMMA aggr_attr select_attr_list {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], $2);
        free($2);
    };
attr:
    ID {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, NULL, $1);
        $$ = attr;
    }
    | ID DOT ID {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, $1, $3);
        $$ = attr;
    };
aggr_attr:
      aggr_type LBRACE attr RBRACE {
        relation_attr_aggr($3, $1);
        $$ = $3;
    }
    | aggr_type LBRACE STAR RBRACE {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, $1);
        $$ = attr;
    }
    | aggr_type LBRACE number RBRACE {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
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
    | COMMA ID rel_list {
            selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $2);
    }
    | join {
    };

join:
	INNER JOIN ID ON condition condition_list join_list {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $3);
	};
join_list:
	/* empty */
	| INNER JOIN ID  ON condition condition_list join_list {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], $3);
	};

where:
    /* empty */ 
    | WHERE condition condition_list {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition_list:
    /* empty */
    | AND condition condition_list {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
    ;
condition:
    ID comOp value {
        RelAttr left_attr;
        relation_attr_init(&left_attr, NULL, $1);

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| value comOp value {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| ID comOp ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
    | value comOp ID {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, $3);

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
    | ID DOT ID comOp value {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    | value comOp ID DOT ID {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, $3, $5);

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
    | ID DOT ID comOp ID DOT ID {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);
		RelAttr right_attr;
		relation_attr_init(&right_attr, $5, $7);

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
	| value null_comOp {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);

		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| ID null_comOp {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, $1);

		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
	| ID DOT ID null_comOp {
		RelAttr left_attr;
		relation_attr_init(&left_attr, $1, $3);

		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
    ;
comOp:
  	  EQ { CONTEXT->comp = EQUAL_TO; }
    | LT { CONTEXT->comp = LESS_THAN; }
    | GT { CONTEXT->comp = GREAT_THAN; }
    | LE { CONTEXT->comp = LESS_EQUAL; }
    | GE { CONTEXT->comp = GREAT_EQUAL; }
    | NE { CONTEXT->comp = NOT_EQUAL; }
    | LIKE { CONTEXT->comp = LIKE_OP; }
    | NOT LIKE { CONTEXT->comp = NOT_LIKE_OP; }
    ;
null_comOp:
      IS NULL_TOKEN { CONTEXT->comp = IS_NULL; }
    | IS NOT NULL_TOKEN { CONTEXT->comp = IS_NOT_NULL; }
    ;

group:
    /* empty */
    | GROUP BY attr group_list having {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], $3);
        free($3);
    };
group_list:
    /* empty */
    | COMMA attr group_list {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], $2);
        free($2);
    };
having:
    /* empty */
    | HAVING aggr_attr comOp value having_list {
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

        Condition condition;
        condition_init(&condition, CONTEXT->comp, 1, $2, NULL, 0, NULL, right_value);
        free($2);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    };
having_list:
    /* empty */
    | AND aggr_attr comOp value having_list {
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

        Condition condition;
        condition_init(&condition, CONTEXT->comp, 1, $2, NULL, 0, NULL, right_value);
        free($2);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    };

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
