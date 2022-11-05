/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


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
  size_t condition_length[MAX_NUM / 2];
  Condition conditions[MAX_NUM / 2][MAX_NUM / 2];
  RelAttr attrs[MAX_NUM];
  Expr exprs[MAX_NUM * 2];
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


#line 145 "yacc_sql.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_UNIQUE = 9,                     /* UNIQUE  */
  YYSYMBOL_SELECT = 10,                    /* SELECT  */
  YYSYMBOL_DESC = 11,                      /* DESC  */
  YYSYMBOL_SHOW = 12,                      /* SHOW  */
  YYSYMBOL_SYNC = 13,                      /* SYNC  */
  YYSYMBOL_INSERT = 14,                    /* INSERT  */
  YYSYMBOL_DELETE = 15,                    /* DELETE  */
  YYSYMBOL_UPDATE = 16,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 17,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 18,                    /* RBRACE  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 20,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 21,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 22,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 23,                     /* INT_T  */
  YYSYMBOL_STRING_T = 24,                  /* STRING_T  */
  YYSYMBOL_TEXT_T = 25,                    /* TEXT_T  */
  YYSYMBOL_FLOAT_T = 26,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 27,                    /* DATE_T  */
  YYSYMBOL_MAX = 28,                       /* MAX  */
  YYSYMBOL_MIN = 29,                       /* MIN  */
  YYSYMBOL_COUNT = 30,                     /* COUNT  */
  YYSYMBOL_AVG = 31,                       /* AVG  */
  YYSYMBOL_SUM = 32,                       /* SUM  */
  YYSYMBOL_GROUP = 33,                     /* GROUP  */
  YYSYMBOL_BY = 34,                        /* BY  */
  YYSYMBOL_HAVING = 35,                    /* HAVING  */
  YYSYMBOL_LENGTH = 36,                    /* LENGTH  */
  YYSYMBOL_ROUND = 37,                     /* ROUND  */
  YYSYMBOL_DATE_FORMAT = 38,               /* DATE_FORMAT  */
  YYSYMBOL_HELP = 39,                      /* HELP  */
  YYSYMBOL_EXIT = 40,                      /* EXIT  */
  YYSYMBOL_DOT = 41,                       /* DOT  */
  YYSYMBOL_INTO = 42,                      /* INTO  */
  YYSYMBOL_VALUES = 43,                    /* VALUES  */
  YYSYMBOL_FROM = 44,                      /* FROM  */
  YYSYMBOL_WHERE = 45,                     /* WHERE  */
  YYSYMBOL_AND = 46,                       /* AND  */
  YYSYMBOL_OR = 47,                        /* OR  */
  YYSYMBOL_SET = 48,                       /* SET  */
  YYSYMBOL_ON = 49,                        /* ON  */
  YYSYMBOL_LOAD = 50,                      /* LOAD  */
  YYSYMBOL_DATA = 51,                      /* DATA  */
  YYSYMBOL_INFILE = 52,                    /* INFILE  */
  YYSYMBOL_EQ = 53,                        /* EQ  */
  YYSYMBOL_LT = 54,                        /* LT  */
  YYSYMBOL_GT = 55,                        /* GT  */
  YYSYMBOL_LE = 56,                        /* LE  */
  YYSYMBOL_GE = 57,                        /* GE  */
  YYSYMBOL_NE = 58,                        /* NE  */
  YYSYMBOL_LIKE = 59,                      /* LIKE  */
  YYSYMBOL_IN = 60,                        /* IN  */
  YYSYMBOL_EXISTS = 61,                    /* EXISTS  */
  YYSYMBOL_INNER = 62,                     /* INNER  */
  YYSYMBOL_JOIN = 63,                      /* JOIN  */
  YYSYMBOL_IS = 64,                        /* IS  */
  YYSYMBOL_NOT = 65,                       /* NOT  */
  YYSYMBOL_NULL_TOKEN = 66,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 67,                  /* NULLABLE  */
  YYSYMBOL_ORDER = 68,                     /* ORDER  */
  YYSYMBOL_ASC = 69,                       /* ASC  */
  YYSYMBOL_PLUS = 70,                      /* PLUS  */
  YYSYMBOL_MINUS = 71,                     /* MINUS  */
  YYSYMBOL_STAR = 72,                      /* STAR  */
  YYSYMBOL_DIVIDE = 73,                    /* DIVIDE  */
  YYSYMBOL_AS = 74,                        /* AS  */
  YYSYMBOL_NUMBER = 75,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 76,                     /* FLOAT  */
  YYSYMBOL_ID = 77,                        /* ID  */
  YYSYMBOL_PATH = 78,                      /* PATH  */
  YYSYMBOL_SSS = 79,                       /* SSS  */
  YYSYMBOL_STRING_V = 80,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_commands = 82,                  /* commands  */
  YYSYMBOL_command = 83,                   /* command  */
  YYSYMBOL_exit = 84,                      /* exit  */
  YYSYMBOL_help = 85,                      /* help  */
  YYSYMBOL_sync = 86,                      /* sync  */
  YYSYMBOL_begin = 87,                     /* begin  */
  YYSYMBOL_commit = 88,                    /* commit  */
  YYSYMBOL_rollback = 89,                  /* rollback  */
  YYSYMBOL_drop_table = 90,                /* drop_table  */
  YYSYMBOL_show_tables = 91,               /* show_tables  */
  YYSYMBOL_show_index = 92,                /* show_index  */
  YYSYMBOL_desc_table = 93,                /* desc_table  */
  YYSYMBOL_create_index = 94,              /* create_index  */
  YYSYMBOL_attrone = 95,                   /* attrone  */
  YYSYMBOL_attr_index = 96,                /* attr_index  */
  YYSYMBOL_attr_index_list = 97,           /* attr_index_list  */
  YYSYMBOL_drop_index = 98,                /* drop_index  */
  YYSYMBOL_create_table = 99,              /* create_table  */
  YYSYMBOL_attr_def_list = 100,            /* attr_def_list  */
  YYSYMBOL_attr_def = 101,                 /* attr_def  */
  YYSYMBOL_number = 102,                   /* number  */
  YYSYMBOL_type = 103,                     /* type  */
  YYSYMBOL_ID_get = 104,                   /* ID_get  */
  YYSYMBOL_nullable = 105,                 /* nullable  */
  YYSYMBOL_insert = 106,                   /* insert  */
  YYSYMBOL_v_list = 107,                   /* v_list  */
  YYSYMBOL_node = 108,                     /* node  */
  YYSYMBOL_value_list = 109,               /* value_list  */
  YYSYMBOL_expr_value = 110,               /* expr_value  */
  YYSYMBOL_value = 111,                    /* value  */
  YYSYMBOL_delete = 112,                   /* delete  */
  YYSYMBOL_update = 113,                   /* update  */
  YYSYMBOL_update_attr = 114,              /* update_attr  */
  YYSYMBOL_update_attr_list = 115,         /* update_attr_list  */
  YYSYMBOL_update_unit = 116,              /* update_unit  */
  YYSYMBOL_select = 117,                   /* select  */
  YYSYMBOL_select_unit = 118,              /* select_unit  */
  YYSYMBOL_func_attr_list = 119,           /* func_attr_list  */
  YYSYMBOL_func_attr = 120,                /* func_attr  */
  YYSYMBOL_func_type_1 = 121,              /* func_type_1  */
  YYSYMBOL_func_type_2 = 122,              /* func_type_2  */
  YYSYMBOL_alias = 123,                    /* alias  */
  YYSYMBOL_select_begin = 124,             /* select_begin  */
  YYSYMBOL_select_attr = 125,              /* select_attr  */
  YYSYMBOL_select_attr_list = 126,         /* select_attr_list  */
  YYSYMBOL_expr = 127,                     /* expr  */
  YYSYMBOL_add_expr = 128,                 /* add_expr  */
  YYSYMBOL_mul_expr = 129,                 /* mul_expr  */
  YYSYMBOL_primary_expr = 130,             /* primary_expr  */
  YYSYMBOL_attr = 131,                     /* attr  */
  YYSYMBOL_aggr_attr = 132,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 133,                /* aggr_type  */
  YYSYMBOL_rel_list = 134,                 /* rel_list  */
  YYSYMBOL_join = 135,                     /* join  */
  YYSYMBOL_join_list = 136,                /* join_list  */
  YYSYMBOL_where = 137,                    /* where  */
  YYSYMBOL_condition_list = 138,           /* condition_list  */
  YYSYMBOL_condition = 139,                /* condition  */
  YYSYMBOL_comOp = 140,                    /* comOp  */
  YYSYMBOL_null_comOp = 141,               /* null_comOp  */
  YYSYMBOL_condition_value = 142,          /* condition_value  */
  YYSYMBOL_condition_value_list = 143,     /* condition_value_list  */
  YYSYMBOL_group_by = 144,                 /* group_by  */
  YYSYMBOL_group_list = 145,               /* group_list  */
  YYSYMBOL_having = 146,                   /* having  */
  YYSYMBOL_having_list = 147,              /* having_list  */
  YYSYMBOL_order_by = 148,                 /* order_by  */
  YYSYMBOL_order_list = 149,               /* order_list  */
  YYSYMBOL_order = 150,                    /* order  */
  YYSYMBOL_load_data = 151                 /* load_data  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   422

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  377

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   198,   198,   200,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   225,   230,   235,   241,   247,   253,   259,   265,
     271,   278,   285,   291,   299,   305,   311,   313,   320,   327,
     336,   338,   342,   349,   357,   360,   361,   362,   363,   364,
     367,   372,   373,   374,   378,   391,   392,   397,   405,   407,
     412,   417,   422,   428,   434,   439,   444,   449,   455,   462,
     472,   479,   482,   485,   487,   490,   494,   499,   504,   512,
     522,   523,   529,   533,   537,   543,   545,   546,   551,   554,
     557,   563,   569,   572,   584,   587,   589,   592,   596,   599,
     604,   608,   612,   616,   620,   624,   628,   632,   636,   640,
     644,   650,   655,   660,   666,   670,   676,   686,   687,   688,
     689,   690,   693,   695,   698,   702,   705,   707,   711,   713,
     716,   718,   721,   727,   732,   737,   742,   747,   752,   757,
     763,   769,   779,   789,   800,   813,   814,   815,   816,   817,
     818,   819,   820,   823,   824,   827,   830,   832,   836,   838,
     841,   843,   846,   848,   856,   858,   867,   869,   872,   874,
     878,   881,   884,   887,   890,   893,   899
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "UNIQUE", "SELECT", "DESC", "SHOW",
  "SYNC", "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA",
  "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "TEXT_T",
  "FLOAT_T", "DATE_T", "MAX", "MIN", "COUNT", "AVG", "SUM", "GROUP", "BY",
  "HAVING", "LENGTH", "ROUND", "DATE_FORMAT", "HELP", "EXIT", "DOT",
  "INTO", "VALUES", "FROM", "WHERE", "AND", "OR", "SET", "ON", "LOAD",
  "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "LIKE", "IN",
  "EXISTS", "INNER", "JOIN", "IS", "NOT", "NULL_TOKEN", "NULLABLE",
  "ORDER", "ASC", "PLUS", "MINUS", "STAR", "DIVIDE", "AS", "NUMBER",
  "FLOAT", "ID", "PATH", "SSS", "STRING_V", "$accept", "commands",
  "command", "exit", "help", "sync", "begin", "commit", "rollback",
  "drop_table", "show_tables", "show_index", "desc_table", "create_index",
  "attrone", "attr_index", "attr_index_list", "drop_index", "create_table",
  "attr_def_list", "attr_def", "number", "type", "ID_get", "nullable",
  "insert", "v_list", "node", "value_list", "expr_value", "value",
  "delete", "update", "update_attr", "update_attr_list", "update_unit",
  "select", "select_unit", "func_attr_list", "func_attr", "func_type_1",
  "func_type_2", "alias", "select_begin", "select_attr",
  "select_attr_list", "expr", "add_expr", "mul_expr", "primary_expr",
  "attr", "aggr_attr", "aggr_type", "rel_list", "join", "join_list",
  "where", "condition_list", "condition", "comOp", "null_comOp",
  "condition_value", "condition_value_list", "group_by", "group_list",
  "having", "having_list", "order_by", "order_list", "order", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-285)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-96)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -285,   362,  -285,    35,    51,  -285,   -44,    61,    37,     3,
      27,    12,    99,   101,   105,   125,   133,   102,  -285,  -285,
    -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,
    -285,  -285,  -285,  -285,  -285,  -285,   148,   200,  -285,    82,
      85,   155,    87,    88,   164,   165,   129,  -285,    98,   108,
     138,  -285,  -285,  -285,  -285,  -285,   141,  -285,     6,  -285,
    -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,   279,   175,
    -285,  -285,   156,  -285,  -285,   -45,   178,   181,   159,   -45,
      49,    65,  -285,  -285,  -285,   182,   183,   171,   128,   211,
     218,  -285,  -285,   145,   184,   179,   149,   146,   252,   232,
      -4,  -285,   227,  -285,     1,   157,  -285,     5,   279,   279,
     158,   175,   252,   252,   279,   279,    41,   174,   176,   203,
    -285,  -285,   257,   244,    95,   259,   214,   179,   249,   228,
    -285,  -285,   -45,   -45,  -285,  -285,  -285,   227,  -285,  -285,
     255,   126,   -45,  -285,    65,    65,  -285,  -285,   256,  -285,
     260,   268,  -285,   269,   216,   270,   212,  -285,    64,   273,
     230,   231,   284,   233,   235,   236,   241,   154,   123,   241,
     100,  -285,    22,   289,   240,  -285,   288,   175,   175,   -45,
    -285,  -285,   279,    28,  -285,  -285,  -285,   174,   301,  -285,
    -285,  -285,  -285,  -285,     9,   243,   304,  -285,   247,  -285,
    -285,  -285,   305,   315,   309,   266,    76,  -285,  -285,  -285,
    -285,  -285,  -285,  -285,  -285,   274,   227,   317,    90,   227,
    -285,    95,    95,  -285,   315,   249,  -285,   282,   249,   261,
    -285,  -285,     5,   314,   262,   277,   179,  -285,   269,   333,
     267,   271,  -285,  -285,  -285,   322,   243,  -285,    64,   325,
     326,   315,   280,  -285,  -285,  -285,  -285,    20,   330,  -285,
    -285,   100,   100,   331,  -285,    22,  -285,   345,  -285,  -285,
     -45,   275,   318,  -285,  -285,   335,  -285,   287,   339,   322,
     305,   346,  -285,   350,  -285,  -285,   351,   352,    20,  -285,
    -285,  -285,   249,  -285,    28,   -45,   336,   311,    -7,  -285,
     322,   377,   363,  -285,   368,   383,    64,  -285,  -285,    64,
     369,   370,   352,  -285,  -285,   340,   313,   357,  -285,  -285,
    -285,  -285,   389,  -285,  -285,   305,   352,  -285,  -285,   375,
      95,   376,   319,  -285,   379,  -285,  -285,   100,   313,   359,
      10,   380,   346,   338,   376,   217,  -285,  -285,   321,  -285,
     319,  -285,  -285,   341,  -285,  -285,   154,    11,   380,   328,
      64,  -285,  -285,  -285,   -45,   360,   354,   217,  -285,    95,
     154,   100,    64,   338,   360,  -285,  -285
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    91,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    77,     0,   117,
     118,   119,   120,   121,    85,    86,    87,    63,     0,    95,
      60,    61,   111,    62,   110,    88,     0,     0,     0,    88,
      98,   102,   106,   108,   109,     0,     0,     0,     0,     0,
       0,    31,    29,     0,     0,   128,     0,     0,     0,     0,
       0,   105,     0,    93,     0,     0,    90,    80,     0,     0,
       0,    95,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    38,     0,     0,     0,     0,     0,   128,    73,     0,
      99,   107,    88,    88,   113,   112,    89,     0,    78,    92,
       0,     0,    88,    94,   100,   101,   103,   104,     0,    44,
       0,     0,    50,    40,     0,     0,     0,    30,     0,     0,
       0,    63,     0,    60,    61,    62,     0,     0,     0,   108,
     130,    69,     0,     0,     0,    72,     0,    95,    95,    88,
      82,    84,     0,   122,   115,   116,   114,     0,     0,    45,
      46,    47,    48,    49,    51,     0,     0,    68,     0,    64,
      66,    67,    58,     0,     0,    60,     0,   143,   145,   146,
     147,   148,   149,   150,   151,     0,     0,     0,     0,     0,
     144,     0,     0,   129,     0,    73,    70,     0,    73,     0,
      97,    96,    80,     0,     0,     0,   128,   124,    40,     0,
       0,     0,    52,    43,    34,    36,     0,    65,     0,     0,
       0,     0,     0,   153,   152,   134,   135,     0,     0,   136,
     133,   130,   130,     0,    71,     0,    75,     0,    81,    83,
      88,     0,   158,    41,    39,     0,    53,     0,     0,    36,
      58,    55,   141,     0,   154,   155,     0,   156,     0,   131,
     132,    76,    73,   176,   122,    88,     0,   166,    51,    35,
      36,     0,     0,    59,     0,     0,     0,   142,   139,     0,
       0,     0,   156,    74,   123,     0,     0,     0,    79,    42,
      37,    33,     0,    57,    54,    58,   156,   137,   140,     0,
       0,   160,     0,    32,     0,   157,   138,   130,     0,   162,
     170,   168,    55,   126,   160,     0,   159,   171,     0,   172,
       0,   167,    56,     0,   125,   161,     0,   173,   168,     0,
       0,   174,   175,   169,    88,   164,     0,     0,   163,     0,
       0,   130,     0,   126,   164,   127,   165
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,  -285,
    -285,  -285,  -285,  -285,   161,  -285,  -252,  -285,  -285,   170,
     222,   173,  -285,  -285,   112,  -285,    69,  -285,  -261,  -285,
    -154,  -285,  -285,  -285,  -208,   242,  -285,   -55,   185,   -32,
    -285,  -285,   -79,  -285,  -285,   -61,   -27,   -33,    45,   -53,
    -115,  -253,  -285,   120,  -285,    42,  -114,  -250,  -215,  -166,
     250,  -257,  -284,  -285,    74,  -285,    46,  -285,    63,    72,
    -285
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   245,   300,   278,    30,    31,   188,
     153,   150,   194,   154,   243,    32,   305,   306,   249,    74,
     166,    33,    34,   127,   175,   128,    35,    36,   138,   167,
      76,    77,   107,    37,    78,   230,   168,    80,    81,    82,
      83,    84,    85,   236,   237,   354,   125,   223,   170,   216,
     207,   287,   310,   297,   339,   346,   368,   318,   351,   341,
      38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     111,   151,   219,    99,   202,    75,   261,   262,   103,   169,
      79,   289,   290,   173,   131,   101,     5,   264,   225,   303,
     266,   347,   361,    98,   137,   100,   240,   302,   329,   105,
       5,   312,   106,    44,    59,    60,    61,    62,    63,   224,
      47,    39,   335,    40,    41,    48,   139,   234,   320,   -95,
     143,   348,   326,   177,   178,   140,   141,    42,   241,    43,
     242,   146,   147,   183,   334,   100,   112,   113,    45,    46,
     132,    49,    67,   134,   241,   133,   242,    68,   135,   349,
     362,    70,    71,    72,   313,    73,   197,   343,   197,    50,
     235,   198,   356,   198,   280,   199,   200,   199,   200,   201,
     232,   201,    51,   285,    52,   179,   169,   169,    53,   101,
     133,   292,    58,   148,   370,   337,   149,   231,    72,   112,
     113,   373,   272,    59,    60,    61,    62,    63,    54,   233,
     197,    64,    65,    66,   285,   198,    55,   114,   115,   199,
     200,   252,   253,   201,   181,   182,   221,   222,   250,   254,
     258,    57,   325,    56,   371,   285,   159,   144,   145,    86,
     160,   161,    87,    88,    89,    90,   162,    91,    92,   263,
     163,   164,    72,    93,   165,    94,   208,   209,   210,   211,
     212,   213,   214,   217,   255,    95,    96,   259,   218,   256,
     360,   294,   260,    97,   102,   108,   283,   104,   109,   116,
     117,   331,   286,   110,   372,   119,   365,   208,   209,   210,
     211,   212,   213,   214,   120,   169,   315,    58,   374,   215,
     118,   121,   122,   344,   124,   129,   126,   123,    59,    60,
      61,    62,    63,   311,   136,   142,    64,    65,    66,   189,
     190,   191,   192,   193,    58,    59,    60,    61,    62,    63,
     130,   152,   156,   155,   169,    59,    60,    61,    62,    63,
     157,   158,   171,    64,    65,    66,    67,   172,   174,    98,
     176,    68,    69,   180,   184,    70,    71,    72,   185,    73,
      59,    60,    61,    62,    63,   366,   186,   195,   187,   196,
     203,   204,   226,    67,   229,   -68,    98,   -64,    68,   -66,
     -67,    98,    70,    71,    72,   206,    73,    59,    60,    61,
      62,    63,    59,    60,    61,    62,    63,   227,    67,   239,
     244,   246,   247,    68,   248,     5,   251,    70,    71,    72,
     -65,    73,   269,   254,   257,   265,   274,   276,   267,   270,
     271,   277,   149,   281,   282,    67,   284,   288,   293,   291,
      67,   296,   295,   298,    70,    71,    72,   301,    73,   205,
      71,    72,     2,    73,   299,   304,     3,     4,   307,   308,
     316,   309,     5,     6,     7,     8,     9,    10,    11,   317,
     321,   322,    12,    13,    14,   323,   324,   327,   328,   330,
      72,   332,   333,   336,   345,   338,   340,   342,   357,   350,
     353,    15,    16,   369,   359,   364,   367,   279,   273,   238,
     319,   352,    17,   275,   314,   375,   228,   268,   355,   220,
     376,   363,   358
};

static const yytype_int16 yycheck[] =
{
      79,   116,   168,    58,   158,    37,   221,   222,    69,   124,
      37,   261,   262,   127,    18,    68,    10,   225,   172,   280,
     228,    11,    11,    17,    19,    58,    17,   279,   312,    74,
      10,   288,    77,    77,    28,    29,    30,    31,    32,    17,
       3,     6,   326,     8,     9,    42,   107,    19,   300,    44,
     111,    41,   309,   132,   133,   108,   109,     6,    65,     8,
      67,   114,   115,   142,   325,    98,    70,    71,     7,     8,
     102,    44,    66,    72,    65,   102,    67,    71,    77,    69,
      69,    75,    76,    77,   292,    79,    66,   337,    66,    77,
      62,    71,   345,    71,   248,    75,    76,    75,    76,    79,
     179,    79,     3,   257,     3,   137,   221,   222,     3,   162,
     137,   265,    17,    72,   367,   330,    75,   178,    77,    70,
      71,   371,   236,    28,    29,    30,    31,    32,     3,   182,
      66,    36,    37,    38,   288,    71,     3,    72,    73,    75,
      76,    65,    66,    79,    18,    19,    46,    47,   203,    59,
      60,     3,   306,    51,   369,   309,    61,   112,   113,    77,
      65,    66,    77,     8,    77,    77,    71,     3,     3,   224,
      75,    76,    77,    44,    79,    77,    53,    54,    55,    56,
      57,    58,    59,    60,   216,    77,    48,   219,    65,   216,
     356,   270,   219,    52,    19,    17,   251,    41,    17,    17,
      17,   316,   257,    44,   370,    77,   360,    53,    54,    55,
      56,    57,    58,    59,     3,   330,   295,    17,   372,    65,
      49,     3,    77,   338,    45,    79,    77,    43,    28,    29,
      30,    31,    32,   288,    77,    77,    36,    37,    38,    23,
      24,    25,    26,    27,    17,    28,    29,    30,    31,    32,
      18,    77,    49,    77,   369,    28,    29,    30,    31,    32,
       3,    17,     3,    36,    37,    38,    66,    53,    19,    17,
      42,    71,    72,    18,    18,    75,    76,    77,    18,    79,
      28,    29,    30,    31,    32,   364,    18,    17,    19,    77,
      17,    61,     3,    66,     6,    64,    17,    64,    71,    64,
      64,    17,    75,    76,    77,    64,    79,    28,    29,    30,
      31,    32,    28,    29,    30,    31,    32,    77,    66,    18,
      77,    17,    75,    71,    19,    10,    17,    75,    76,    77,
      64,    79,    18,    59,    17,    53,     3,    66,    77,    77,
      63,    19,    75,    18,    18,    66,    66,    17,     3,    18,
      66,    33,    77,    18,    75,    76,    77,    18,    79,    75,
      76,    77,     0,    79,    77,    19,     4,     5,    18,    18,
      34,    19,    10,    11,    12,    13,    14,    15,    16,    68,
       3,    18,    20,    21,    22,    17,     3,    18,    18,    49,
      77,    34,     3,    18,    35,    19,    77,    18,    77,    19,
      62,    39,    40,    49,    63,    77,    46,   246,   238,   187,
     298,   342,    50,   240,   294,   373,   174,   232,   344,   169,
     374,   358,   350
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    82,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    39,    40,    50,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      98,    99,   106,   112,   113,   117,   118,   124,   151,     6,
       8,     9,     6,     8,    77,     7,     8,     3,    42,    44,
      77,     3,     3,     3,     3,     3,    51,     3,    17,    28,
      29,    30,    31,    32,    36,    37,    38,    66,    71,    72,
      75,    76,    77,    79,   110,   120,   121,   122,   125,   127,
     128,   129,   130,   131,   132,   133,    77,    77,     8,    77,
      77,     3,     3,    44,    77,    77,    48,    52,    17,   118,
     128,   130,    19,   126,    41,    74,    77,   123,    17,    17,
      44,   123,    70,    71,    72,    73,    17,    17,    49,    77,
       3,     3,    77,    43,    45,   137,    77,   114,   116,    79,
      18,    18,   120,   127,    72,    77,    77,    19,   119,   126,
     130,   130,    77,   126,   129,   129,   130,   130,    72,    75,
     102,   131,    77,   101,   104,    77,    49,     3,    17,    61,
      65,    66,    71,    75,    76,    79,   111,   120,   127,   131,
     139,     3,    53,   137,    19,   115,    42,   123,   123,   120,
      18,    18,    19,   123,    18,    18,    18,    19,   100,    23,
      24,    25,    26,    27,   103,    17,    77,    66,    71,    75,
      76,    79,   111,    17,    61,    75,    64,   141,    53,    54,
      55,    56,    57,    58,    59,    65,   140,    60,    65,   140,
     141,    46,    47,   138,    17,   111,     3,    77,   116,     6,
     126,   126,   123,   130,    19,    62,   134,   135,   101,    18,
      17,    65,    67,   105,    77,    95,    17,    75,    19,   109,
     118,    17,    65,    66,    59,   120,   127,    17,    60,   120,
     127,   139,   139,   118,   115,    53,   115,    77,   119,    18,
      77,    63,   137,   100,     3,   102,    66,    19,    97,    95,
     111,    18,    18,   118,    66,   111,   118,   142,    17,   138,
     138,    18,   111,     3,   123,    77,    33,   144,    18,    77,
      96,    18,    97,   109,    19,   107,   108,    18,    18,    19,
     143,   118,   142,   115,   134,   123,    34,    68,   148,   105,
      97,     3,    18,    17,     3,   111,   142,    18,    18,   143,
      49,   131,    34,     3,   109,   143,    18,   139,    19,   145,
      77,   150,    18,   138,   131,    35,   146,    11,    41,    69,
      19,   149,   107,    62,   136,   145,   132,    77,   150,    63,
     140,    11,    69,   149,    77,   111,   123,    46,   147,    49,
     132,   139,   140,   138,   111,   136,   147
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    82,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    94,    95,    96,    97,    97,    98,    99,
     100,   100,   101,   101,   102,   103,   103,   103,   103,   103,
     104,   105,   105,   105,   106,   107,   107,   108,   109,   109,
     110,   110,   110,   110,   111,   111,   111,   111,   111,   112,
     113,   114,   114,   115,   115,   115,   116,   117,   118,   118,
     119,   119,   120,   120,   120,   121,   122,   122,   123,   123,
     123,   124,   125,   125,   125,   126,   126,   126,   127,   127,
     128,   128,   128,   129,   129,   129,   129,   130,   130,   130,
     130,   131,   131,   131,   132,   132,   132,   133,   133,   133,
     133,   133,   134,   134,   134,   135,   136,   136,   137,   137,
     138,   138,   138,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   140,   140,   140,   140,   140,
     140,   140,   140,   141,   141,   142,   143,   143,   144,   144,
     145,   145,   146,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   150,   150,   150,   150,   151
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,    11,    10,     1,     1,     0,     3,     4,     8,
       0,     3,     6,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     2,    10,     0,     5,     2,     0,     3,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     5,
       6,     4,     2,     0,     5,     3,     5,     2,     4,     9,
       0,     4,     4,     6,     4,     1,     1,     1,     0,     2,
       1,     1,     3,     2,     3,     0,     4,     4,     1,     3,
       3,     3,     1,     3,     3,     2,     1,     3,     1,     1,
       1,     1,     3,     3,     4,     4,     4,     1,     1,     1,
       1,     1,     0,     4,     1,     8,     0,     8,     0,     3,
       0,     3,     3,     3,     3,     3,     3,     6,     7,     5,
       6,     4,     5,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     1,     0,     3,     0,     5,
       0,     3,     0,     5,     0,     5,     0,     4,     0,     3,
       1,     2,     2,     3,     4,     4,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, void *scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YY_USE (yyvaluep);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 22: /* exit: EXIT SEMICOLON  */
#line 225 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1569 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 230 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1577 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 235 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1585 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 241 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1593 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 247 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1601 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 253 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1609 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 259 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1618 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 265 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1626 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 271 "yacc_sql.y"
                                 {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1635 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 278 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1644 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 286 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1654 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 292 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1664 "yacc_sql.tab.c"
    break;

  case 34: /* attrone: ID  */
#line 300 "yacc_sql.y"
        {
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1672 "yacc_sql.tab.c"
    break;

  case 35: /* attr_index: ID  */
#line 306 "yacc_sql.y"
        {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, (yyvsp[0].string));
		CONTEXT->attr_num++;
	}
#line 1681 "yacc_sql.tab.c"
    break;

  case 37: /* attr_index_list: COMMA attr_index attr_index_list  */
#line 314 "yacc_sql.y"
        {

	}
#line 1689 "yacc_sql.tab.c"
    break;

  case 38: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 321 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1698 "yacc_sql.tab.c"
    break;

  case 39: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 328 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1710 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 338 "yacc_sql.y"
                                   {    }
#line 1716 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 342 "yacc_sql.y"
                                              {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
    }
#line 1728 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type nullable  */
#line 349 "yacc_sql.y"
                           {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4 + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
	}
#line 1740 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 357 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1746 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 360 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1752 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 361 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 1758 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 362 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1764 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 363 "yacc_sql.y"
              { (yyval.number) = FLOATS; }
#line 1770 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 364 "yacc_sql.y"
             { (yyval.number) = DATES; }
#line 1776 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 367 "yacc_sql.y"
       {
        char *temp=(yyvsp[0].string);
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1785 "yacc_sql.tab.c"
    break;

  case 51: /* nullable: %empty  */
#line 372 "yacc_sql.y"
                  { (yyval.number) = false; }
#line 1791 "yacc_sql.tab.c"
    break;

  case 52: /* nullable: NULLABLE  */
#line 373 "yacc_sql.y"
               { (yyval.number) = true; }
#line 1797 "yacc_sql.tab.c"
    break;

  case 53: /* nullable: NOT NULL_TOKEN  */
#line 374 "yacc_sql.y"
                         { (yyval.number) = false; }
#line 1803 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE v_list SEMICOLON  */
#line 379 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_INSERT;
		CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
		CONTEXT->every_group_count=0;
        CONTEXT->group_num = CONTEXT->group_num + 1;

		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->insert_groups, CONTEXT->group_num);

		//临时变量清零
		CONTEXT->value_length=0;
    }
#line 1819 "yacc_sql.tab.c"
    break;

  case 56: /* v_list: node value value_list RBRACE v_list  */
#line 393 "yacc_sql.y"
    {
    }
#line 1826 "yacc_sql.tab.c"
    break;

  case 57: /* node: COMMA LBRACE  */
#line 398 "yacc_sql.y"
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    }
#line 1837 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 407 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1845 "yacc_sql.tab.c"
    break;

  case 60: /* expr_value: NUMBER  */
#line 412 "yacc_sql.y"
             {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1855 "yacc_sql.tab.c"
    break;

  case 61: /* expr_value: FLOAT  */
#line 417 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1865 "yacc_sql.tab.c"
    break;

  case 62: /* expr_value: SSS  */
#line 422 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1876 "yacc_sql.tab.c"
    break;

  case 63: /* expr_value: NULL_TOKEN  */
#line 428 "yacc_sql.y"
                 {
         value_init_null(&CONTEXT->values[CONTEXT->value_length]);
         (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
         CONTEXT->every_group_count++;
     }
#line 1886 "yacc_sql.tab.c"
    break;

  case 64: /* value: NUMBER  */
#line 434 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1896 "yacc_sql.tab.c"
    break;

  case 65: /* value: MINUS NUMBER  */
#line 439 "yacc_sql.y"
                   {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], -(yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1906 "yacc_sql.tab.c"
    break;

  case 66: /* value: FLOAT  */
#line 444 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
	}
#line 1916 "yacc_sql.tab.c"
    break;

  case 67: /* value: SSS  */
#line 449 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1927 "yacc_sql.tab.c"
    break;

  case 68: /* value: NULL_TOKEN  */
#line 455 "yacc_sql.y"
                 {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1937 "yacc_sql.tab.c"
    break;

  case 69: /* delete: DELETE FROM ID where SEMICOLON  */
#line 462 "yacc_sql.y"
                                   {
        CONTEXT->ssql->flag = SCF_DELETE;//"delete";
        deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
        deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->conditions[CONTEXT->select_length],
                CONTEXT->condition_length[CONTEXT->select_length]);
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
#line 1949 "yacc_sql.tab.c"
    break;

  case 70: /* update: UPDATE ID SET update_attr where SEMICOLON  */
#line 472 "yacc_sql.y"
                                              {
        CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), CONTEXT->conditions[CONTEXT->select_length],
		        CONTEXT->condition_length[CONTEXT->select_length]);
		CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
#line 1960 "yacc_sql.tab.c"
    break;

  case 71: /* update_attr: ID EQ value update_attr_list  */
#line 479 "yacc_sql.y"
                                 {
		updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1968 "yacc_sql.tab.c"
    break;

  case 72: /* update_attr: update_unit update_attr_list  */
#line 482 "yacc_sql.y"
                                   {

    }
#line 1976 "yacc_sql.tab.c"
    break;

  case 74: /* update_attr_list: COMMA ID EQ value update_attr_list  */
#line 487 "yacc_sql.y"
                                         {
        updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1984 "yacc_sql.tab.c"
    break;

  case 75: /* update_attr_list: COMMA update_unit update_attr_list  */
#line 490 "yacc_sql.y"
                                         {

    }
#line 1992 "yacc_sql.tab.c"
    break;

  case 76: /* update_unit: ID EQ LBRACE select_unit RBRACE  */
#line 494 "yacc_sql.y"
                                    {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), (yyvsp[-1]._select));
    }
#line 2000 "yacc_sql.tab.c"
    break;

  case 77: /* select: select_unit SEMICOLON  */
#line 499 "yacc_sql.y"
                          {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[1];
    }
#line 2009 "yacc_sql.tab.c"
    break;

  case 78: /* select_unit: select_begin func_attr alias func_attr_list  */
#line 504 "yacc_sql.y"
                                                {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));

        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 2022 "yacc_sql.tab.c"
    break;

  case 79: /* select_unit: select_begin select_attr FROM ID alias rel_list where group_by order_by  */
#line 512 "yacc_sql.y"
                                                                              {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length],
                CONTEXT->conditions[CONTEXT->select_length], CONTEXT->condition_length[CONTEXT->select_length]);
        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 2036 "yacc_sql.tab.c"
    break;

  case 81: /* func_attr_list: COMMA func_attr alias func_attr_list  */
#line 523 "yacc_sql.y"
                                          {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2044 "yacc_sql.tab.c"
    break;

  case 82: /* func_attr: func_type_1 LBRACE primary_expr RBRACE  */
#line 529 "yacc_sql.y"
                                                 {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-3].number), (yyvsp[-1]._expr), NULL);
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2053 "yacc_sql.tab.c"
    break;

  case 83: /* func_attr: func_type_2 LBRACE primary_expr COMMA primary_expr RBRACE  */
#line 533 "yacc_sql.y"
                                                                {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-5].number), (yyvsp[-3]._expr), (yyvsp[-1]._expr));
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2062 "yacc_sql.tab.c"
    break;

  case 84: /* func_attr: func_type_2 LBRACE primary_expr RBRACE  */
#line 537 "yacc_sql.y"
                                             {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-3].number), (yyvsp[-1]._expr), NULL);
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2071 "yacc_sql.tab.c"
    break;

  case 85: /* func_type_1: LENGTH  */
#line 543 "yacc_sql.y"
                  { (yyval.number) = EXPR_LENGTH; }
#line 2077 "yacc_sql.tab.c"
    break;

  case 86: /* func_type_2: ROUND  */
#line 545 "yacc_sql.y"
                 { (yyval.number) = EXPR_ROUND; }
#line 2083 "yacc_sql.tab.c"
    break;

  case 87: /* func_type_2: DATE_FORMAT  */
#line 546 "yacc_sql.y"
                       { (yyval.number) = EXPR_DATE_FORMAT; }
#line 2089 "yacc_sql.tab.c"
    break;

  case 88: /* alias: %empty  */
#line 551 "yacc_sql.y"
    {
        (yyval.string) = NULL;
    }
#line 2097 "yacc_sql.tab.c"
    break;

  case 89: /* alias: AS ID  */
#line 554 "yacc_sql.y"
           {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2105 "yacc_sql.tab.c"
    break;

  case 90: /* alias: ID  */
#line 557 "yacc_sql.y"
        {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2113 "yacc_sql.tab.c"
    break;

  case 91: /* select_begin: SELECT  */
#line 563 "yacc_sql.y"
           {
        CONTEXT->select_length++;
        memset(&CONTEXT->selects[CONTEXT->select_length], 0, sizeof(Selects));
    }
#line 2122 "yacc_sql.tab.c"
    break;

  case 92: /* select_attr: func_attr alias select_attr_list  */
#line 569 "yacc_sql.y"
                                    {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2130 "yacc_sql.tab.c"
    break;

  case 93: /* select_attr: STAR select_attr_list  */
#line 572 "yacc_sql.y"
                            {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], &attr);
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], &CONTEXT->exprs[CONTEXT->expr_length++], NULL);
    }
#line 2141 "yacc_sql.tab.c"
    break;

  case 94: /* select_attr: expr alias select_attr_list  */
#line 584 "yacc_sql.y"
                                  {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2149 "yacc_sql.tab.c"
    break;

  case 96: /* select_attr_list: COMMA expr alias select_attr_list  */
#line 589 "yacc_sql.y"
                                        {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2157 "yacc_sql.tab.c"
    break;

  case 97: /* select_attr_list: COMMA func_attr alias select_attr_list  */
#line 592 "yacc_sql.y"
                                             {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2165 "yacc_sql.tab.c"
    break;

  case 98: /* expr: add_expr  */
#line 596 "yacc_sql.y"
             {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2173 "yacc_sql.tab.c"
    break;

  case 99: /* expr: LBRACE select_unit RBRACE  */
#line 599 "yacc_sql.y"
                                {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2182 "yacc_sql.tab.c"
    break;

  case 100: /* add_expr: add_expr PLUS mul_expr  */
#line 604 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_PLUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2191 "yacc_sql.tab.c"
    break;

  case 101: /* add_expr: add_expr MINUS mul_expr  */
#line 608 "yacc_sql.y"
                              {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MINUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2200 "yacc_sql.tab.c"
    break;

  case 102: /* add_expr: mul_expr  */
#line 612 "yacc_sql.y"
               {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2208 "yacc_sql.tab.c"
    break;

  case 103: /* mul_expr: mul_expr STAR primary_expr  */
#line 616 "yacc_sql.y"
                               {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MULTIPLY, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2217 "yacc_sql.tab.c"
    break;

  case 104: /* mul_expr: mul_expr DIVIDE primary_expr  */
#line 620 "yacc_sql.y"
                                   {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_DIVIDE, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2226 "yacc_sql.tab.c"
    break;

  case 105: /* mul_expr: MINUS primary_expr  */
#line 624 "yacc_sql.y"
                         {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_NEGATIVE, (yyvsp[0]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2235 "yacc_sql.tab.c"
    break;

  case 106: /* mul_expr: primary_expr  */
#line 628 "yacc_sql.y"
                   {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2243 "yacc_sql.tab.c"
    break;

  case 107: /* primary_expr: LBRACE add_expr RBRACE  */
#line 632 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_BRACE, (yyvsp[-1]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2252 "yacc_sql.tab.c"
    break;

  case 108: /* primary_expr: attr  */
#line 636 "yacc_sql.y"
           {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2261 "yacc_sql.tab.c"
    break;

  case 109: /* primary_expr: aggr_attr  */
#line 640 "yacc_sql.y"
                {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2270 "yacc_sql.tab.c"
    break;

  case 110: /* primary_expr: expr_value  */
#line 644 "yacc_sql.y"
                 {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2279 "yacc_sql.tab.c"
    break;

  case 111: /* attr: ID  */
#line 650 "yacc_sql.y"
       {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2289 "yacc_sql.tab.c"
    break;

  case 112: /* attr: ID DOT ID  */
#line 655 "yacc_sql.y"
                {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2299 "yacc_sql.tab.c"
    break;

  case 113: /* attr: ID DOT STAR  */
#line 660 "yacc_sql.y"
                  {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, (yyvsp[-2].string), "*");
        (yyval._attr) = attr;
    }
#line 2309 "yacc_sql.tab.c"
    break;

  case 114: /* aggr_attr: aggr_type LBRACE attr RBRACE  */
#line 666 "yacc_sql.y"
                                   {
        relation_attr_aggr((yyvsp[-1]._attr), (yyvsp[-3].number));
        (yyval._attr) = (yyvsp[-1]._attr);
    }
#line 2318 "yacc_sql.tab.c"
    break;

  case 115: /* aggr_attr: aggr_type LBRACE STAR RBRACE  */
#line 670 "yacc_sql.y"
                                   {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2329 "yacc_sql.tab.c"
    break;

  case 116: /* aggr_attr: aggr_type LBRACE number RBRACE  */
#line 676 "yacc_sql.y"
                                     {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        if ((yyvsp[-1].number) != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2343 "yacc_sql.tab.c"
    break;

  case 117: /* aggr_type: MAX  */
#line 686 "yacc_sql.y"
          { (yyval.number) = AGGR_MAX; }
#line 2349 "yacc_sql.tab.c"
    break;

  case 118: /* aggr_type: MIN  */
#line 687 "yacc_sql.y"
          { (yyval.number) = AGGR_MIN; }
#line 2355 "yacc_sql.tab.c"
    break;

  case 119: /* aggr_type: COUNT  */
#line 688 "yacc_sql.y"
            { (yyval.number) = AGGR_COUNT; }
#line 2361 "yacc_sql.tab.c"
    break;

  case 120: /* aggr_type: AVG  */
#line 689 "yacc_sql.y"
          { (yyval.number) = AGGR_AVG; }
#line 2367 "yacc_sql.tab.c"
    break;

  case 121: /* aggr_type: SUM  */
#line 690 "yacc_sql.y"
          { (yyval.number) = AGGR_SUM; }
#line 2373 "yacc_sql.tab.c"
    break;

  case 123: /* rel_list: COMMA ID alias rel_list  */
#line 695 "yacc_sql.y"
                              {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2].string), (yyvsp[-1].string));
    }
#line 2381 "yacc_sql.tab.c"
    break;

  case 124: /* rel_list: join  */
#line 698 "yacc_sql.y"
           {
    }
#line 2388 "yacc_sql.tab.c"
    break;

  case 125: /* join: INNER JOIN ID alias ON condition condition_list join_list  */
#line 702 "yacc_sql.y"
                                                                  {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2396 "yacc_sql.tab.c"
    break;

  case 127: /* join_list: INNER JOIN ID alias ON condition condition_list join_list  */
#line 707 "yacc_sql.y"
                                                                     {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2404 "yacc_sql.tab.c"
    break;

  case 129: /* where: WHERE condition condition_list  */
#line 713 "yacc_sql.y"
                                     {
        condition_init_logical((yyvsp[-1]._condition), LOGICAL_NONE);
    }
#line 2412 "yacc_sql.tab.c"
    break;

  case 131: /* condition_list: AND condition condition_list  */
#line 718 "yacc_sql.y"
                                   {
        condition_init_logical((yyvsp[-1]._condition), LOGICAL_AND);
    }
#line 2420 "yacc_sql.tab.c"
    break;

  case 132: /* condition_list: OR condition condition_list  */
#line 721 "yacc_sql.y"
                                  {
        condition_init_logical((yyvsp[-1]._condition), LOGICAL_OR);
    }
#line 2428 "yacc_sql.tab.c"
    break;

  case 133: /* condition: expr comOp expr  */
#line 727 "yacc_sql.y"
                    {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2438 "yacc_sql.tab.c"
    break;

  case 134: /* condition: func_attr comOp func_attr  */
#line 732 "yacc_sql.y"
                                {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2448 "yacc_sql.tab.c"
    break;

  case 135: /* condition: func_attr comOp expr  */
#line 737 "yacc_sql.y"
                           {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2458 "yacc_sql.tab.c"
    break;

  case 136: /* condition: expr comOp func_attr  */
#line 742 "yacc_sql.y"
                           {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2468 "yacc_sql.tab.c"
    break;

  case 137: /* condition: expr IN LBRACE condition_value condition_value_list RBRACE  */
#line 747 "yacc_sql.y"
                                                                 {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2478 "yacc_sql.tab.c"
    break;

  case 138: /* condition: expr NOT IN LBRACE condition_value condition_value_list RBRACE  */
#line 752 "yacc_sql.y"
                                                                     {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                NOT_IN_OP, (yyvsp[-6]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2488 "yacc_sql.tab.c"
    break;

  case 139: /* condition: expr IN LBRACE select_unit RBRACE  */
#line 757 "yacc_sql.y"
                                         {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                IN_OP, (yyvsp[-4]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2499 "yacc_sql.tab.c"
    break;

  case 140: /* condition: expr NOT IN LBRACE select_unit RBRACE  */
#line 763 "yacc_sql.y"
                                            {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                NOT_IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2510 "yacc_sql.tab.c"
    break;

  case 141: /* condition: EXISTS LBRACE select_unit RBRACE  */
#line 769 "yacc_sql.y"
                                       {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *left_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], left_value);

        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                EXISTS_OP, &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2525 "yacc_sql.tab.c"
    break;

  case 142: /* condition: NOT EXISTS LBRACE select_unit RBRACE  */
#line 779 "yacc_sql.y"
                                           {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *left_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], left_value);

        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                NOT_EXISTS_OP, &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
    }
#line 2540 "yacc_sql.tab.c"
    break;

  case 143: /* condition: value null_comOp  */
#line 789 "yacc_sql.y"
                           {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
	}
#line 2556 "yacc_sql.tab.c"
    break;

  case 144: /* condition: attr null_comOp  */
#line 800 "yacc_sql.y"
                          {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._attr));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        (yyval._condition) = &CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++];
	}
#line 2572 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: EQ  */
#line 813 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2578 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: LT  */
#line 814 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2584 "yacc_sql.tab.c"
    break;

  case 147: /* comOp: GT  */
#line 815 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2590 "yacc_sql.tab.c"
    break;

  case 148: /* comOp: LE  */
#line 816 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2596 "yacc_sql.tab.c"
    break;

  case 149: /* comOp: GE  */
#line 817 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2602 "yacc_sql.tab.c"
    break;

  case 150: /* comOp: NE  */
#line 818 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2608 "yacc_sql.tab.c"
    break;

  case 151: /* comOp: LIKE  */
#line 819 "yacc_sql.y"
           { (yyval.number) = LIKE_OP; }
#line 2614 "yacc_sql.tab.c"
    break;

  case 152: /* comOp: NOT LIKE  */
#line 820 "yacc_sql.y"
               { (yyval.number) = NOT_LIKE_OP; }
#line 2620 "yacc_sql.tab.c"
    break;

  case 153: /* null_comOp: IS NULL_TOKEN  */
#line 823 "yacc_sql.y"
                    { (yyval.number) = IS_NULL; }
#line 2626 "yacc_sql.tab.c"
    break;

  case 154: /* null_comOp: IS NOT NULL_TOKEN  */
#line 824 "yacc_sql.y"
                        { (yyval.number) = IS_NOT_NULL; }
#line 2632 "yacc_sql.tab.c"
    break;

  case 155: /* condition_value: value  */
#line 827 "yacc_sql.y"
          {
        expr_append_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
    }
#line 2640 "yacc_sql.tab.c"
    break;

  case 157: /* condition_value_list: COMMA condition_value condition_value_list  */
#line 832 "yacc_sql.y"
                                                 {

    }
#line 2648 "yacc_sql.tab.c"
    break;

  case 159: /* group_by: GROUP BY attr group_list having  */
#line 838 "yacc_sql.y"
                                      {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._attr));
    }
#line 2656 "yacc_sql.tab.c"
    break;

  case 161: /* group_list: COMMA attr group_list  */
#line 843 "yacc_sql.y"
                            {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
    }
#line 2664 "yacc_sql.tab.c"
    break;

  case 163: /* having: HAVING aggr_attr comOp value having_list  */
#line 848 "yacc_sql.y"
                                               {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2677 "yacc_sql.tab.c"
    break;

  case 165: /* having_list: AND aggr_attr comOp value having_list  */
#line 858 "yacc_sql.y"
                                            {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2690 "yacc_sql.tab.c"
    break;

  case 167: /* order_by: ORDER BY order order_list  */
#line 869 "yacc_sql.y"
                                {
    }
#line 2697 "yacc_sql.tab.c"
    break;

  case 169: /* order_list: COMMA order order_list  */
#line 874 "yacc_sql.y"
                            {
    }
#line 2704 "yacc_sql.tab.c"
    break;

  case 170: /* order: ID  */
#line 878 "yacc_sql.y"
      {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, "");
    }
#line 2712 "yacc_sql.tab.c"
    break;

  case 171: /* order: ID DESC  */
#line 881 "yacc_sql.y"
             {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, "");
    }
#line 2720 "yacc_sql.tab.c"
    break;

  case 172: /* order: ID ASC  */
#line 884 "yacc_sql.y"
            {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, "");
    }
#line 2728 "yacc_sql.tab.c"
    break;

  case 173: /* order: ID DOT ID  */
#line 887 "yacc_sql.y"
               {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, (yyvsp[-2].string));
    }
#line 2736 "yacc_sql.tab.c"
    break;

  case 174: /* order: ID DOT ID DESC  */
#line 890 "yacc_sql.y"
                    {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, (yyvsp[-3].string));
    }
#line 2744 "yacc_sql.tab.c"
    break;

  case 175: /* order: ID DOT ID ASC  */
#line 893 "yacc_sql.y"
                   {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, (yyvsp[-3].string));
    }
#line 2752 "yacc_sql.tab.c"
    break;

  case 176: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 899 "yacc_sql.y"
                                                 {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
    }
#line 2761 "yacc_sql.tab.c"
    break;


#line 2765 "yacc_sql.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (scanner, YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 904 "yacc_sql.y"

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
