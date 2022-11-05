/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_TAB_H_INCLUDED
# define YY_YY_YACC_SQL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    UNIQUE = 264,                  /* UNIQUE  */
    SELECT = 265,                  /* SELECT  */
    DESC = 266,                    /* DESC  */
    SHOW = 267,                    /* SHOW  */
    SYNC = 268,                    /* SYNC  */
    INSERT = 269,                  /* INSERT  */
    DELETE = 270,                  /* DELETE  */
    UPDATE = 271,                  /* UPDATE  */
    LBRACE = 272,                  /* LBRACE  */
    RBRACE = 273,                  /* RBRACE  */
    COMMA = 274,                   /* COMMA  */
    TRX_BEGIN = 275,               /* TRX_BEGIN  */
    TRX_COMMIT = 276,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 277,            /* TRX_ROLLBACK  */
    INT_T = 278,                   /* INT_T  */
    STRING_T = 279,                /* STRING_T  */
    TEXT_T = 280,                  /* TEXT_T  */
    FLOAT_T = 281,                 /* FLOAT_T  */
    DATE_T = 282,                  /* DATE_T  */
    MAX = 283,                     /* MAX  */
    MIN = 284,                     /* MIN  */
    COUNT = 285,                   /* COUNT  */
    AVG = 286,                     /* AVG  */
    SUM = 287,                     /* SUM  */
    GROUP = 288,                   /* GROUP  */
    BY = 289,                      /* BY  */
    HAVING = 290,                  /* HAVING  */
    LENGTH = 291,                  /* LENGTH  */
    ROUND = 292,                   /* ROUND  */
    DATE_FORMAT = 293,             /* DATE_FORMAT  */
    HELP = 294,                    /* HELP  */
    EXIT = 295,                    /* EXIT  */
    DOT = 296,                     /* DOT  */
    INTO = 297,                    /* INTO  */
    VALUES = 298,                  /* VALUES  */
    FROM = 299,                    /* FROM  */
    WHERE = 300,                   /* WHERE  */
    AND = 301,                     /* AND  */
    SET = 302,                     /* SET  */
    ON = 303,                      /* ON  */
    LOAD = 304,                    /* LOAD  */
    DATA = 305,                    /* DATA  */
    INFILE = 306,                  /* INFILE  */
    EQ = 307,                      /* EQ  */
    LT = 308,                      /* LT  */
    GT = 309,                      /* GT  */
    LE = 310,                      /* LE  */
    GE = 311,                      /* GE  */
    NE = 312,                      /* NE  */
    LIKE = 313,                    /* LIKE  */
    IN = 314,                      /* IN  */
    EXISTS = 315,                  /* EXISTS  */
    INNER = 316,                   /* INNER  */
    JOIN = 317,                    /* JOIN  */
    IS = 318,                      /* IS  */
    NOT = 319,                     /* NOT  */
    NULL_TOKEN = 320,              /* NULL_TOKEN  */
    NULLABLE = 321,                /* NULLABLE  */
    ORDER = 322,                   /* ORDER  */
    ASC = 323,                     /* ASC  */
    PLUS = 324,                    /* PLUS  */
    MINUS = 325,                   /* MINUS  */
    STAR = 326,                    /* STAR  */
    DIVIDE = 327,                  /* DIVIDE  */
    AS = 328,                      /* AS  */
    NUMBER = 329,                  /* NUMBER  */
    FLOAT = 330,                   /* FLOAT  */
    ID = 331,                      /* ID  */
    PATH = 332,                    /* PATH  */
    SSS = 333,                     /* SSS  */
    STRING_V = 334                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 153 "yacc_sql.y"

  struct _RelAttr *_attr;
  struct _Condition *_condition;
  struct _Value *_value;
  struct _Selects *_select;
  struct _Expr *_expr;
  char *string;
  int number;
  float floats;
  char *position;

#line 155 "yacc_sql.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_YACC_SQL_TAB_H_INCLUDED  */
