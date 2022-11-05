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
  YYSYMBOL_HELP = 36,                      /* HELP  */
  YYSYMBOL_EXIT = 37,                      /* EXIT  */
  YYSYMBOL_DOT = 38,                       /* DOT  */
  YYSYMBOL_INTO = 39,                      /* INTO  */
  YYSYMBOL_VALUES = 40,                    /* VALUES  */
  YYSYMBOL_FROM = 41,                      /* FROM  */
  YYSYMBOL_WHERE = 42,                     /* WHERE  */
  YYSYMBOL_AND = 43,                       /* AND  */
  YYSYMBOL_SET = 44,                       /* SET  */
  YYSYMBOL_ON = 45,                        /* ON  */
  YYSYMBOL_LOAD = 46,                      /* LOAD  */
  YYSYMBOL_DATA = 47,                      /* DATA  */
  YYSYMBOL_INFILE = 48,                    /* INFILE  */
  YYSYMBOL_EQ = 49,                        /* EQ  */
  YYSYMBOL_LT = 50,                        /* LT  */
  YYSYMBOL_GT = 51,                        /* GT  */
  YYSYMBOL_LE = 52,                        /* LE  */
  YYSYMBOL_GE = 53,                        /* GE  */
  YYSYMBOL_NE = 54,                        /* NE  */
  YYSYMBOL_LIKE = 55,                      /* LIKE  */
  YYSYMBOL_IN = 56,                        /* IN  */
  YYSYMBOL_EXISTS = 57,                    /* EXISTS  */
  YYSYMBOL_INNER = 58,                     /* INNER  */
  YYSYMBOL_JOIN = 59,                      /* JOIN  */
  YYSYMBOL_IS = 60,                        /* IS  */
  YYSYMBOL_NOT = 61,                       /* NOT  */
  YYSYMBOL_NULL_TOKEN = 62,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 63,                  /* NULLABLE  */
  YYSYMBOL_ORDER = 64,                     /* ORDER  */
  YYSYMBOL_ASC = 65,                       /* ASC  */
  YYSYMBOL_PLUS = 66,                      /* PLUS  */
  YYSYMBOL_MINUS = 67,                     /* MINUS  */
  YYSYMBOL_STAR = 68,                      /* STAR  */
  YYSYMBOL_DIVIDE = 69,                    /* DIVIDE  */
  YYSYMBOL_AS = 70,                        /* AS  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_PATH = 74,                      /* PATH  */
  YYSYMBOL_SSS = 75,                       /* SSS  */
  YYSYMBOL_STRING_V = 76,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_commands = 78,                  /* commands  */
  YYSYMBOL_command = 79,                   /* command  */
  YYSYMBOL_exit = 80,                      /* exit  */
  YYSYMBOL_help = 81,                      /* help  */
  YYSYMBOL_sync = 82,                      /* sync  */
  YYSYMBOL_begin = 83,                     /* begin  */
  YYSYMBOL_commit = 84,                    /* commit  */
  YYSYMBOL_rollback = 85,                  /* rollback  */
  YYSYMBOL_drop_table = 86,                /* drop_table  */
  YYSYMBOL_show_tables = 87,               /* show_tables  */
  YYSYMBOL_show_index = 88,                /* show_index  */
  YYSYMBOL_desc_table = 89,                /* desc_table  */
  YYSYMBOL_create_index = 90,              /* create_index  */
  YYSYMBOL_attrone = 91,                   /* attrone  */
  YYSYMBOL_attr_index = 92,                /* attr_index  */
  YYSYMBOL_attr_index_list = 93,           /* attr_index_list  */
  YYSYMBOL_drop_index = 94,                /* drop_index  */
  YYSYMBOL_create_table = 95,              /* create_table  */
  YYSYMBOL_attr_def_list = 96,             /* attr_def_list  */
  YYSYMBOL_attr_def = 97,                  /* attr_def  */
  YYSYMBOL_number = 98,                    /* number  */
  YYSYMBOL_type = 99,                      /* type  */
  YYSYMBOL_ID_get = 100,                   /* ID_get  */
  YYSYMBOL_nullable = 101,                 /* nullable  */
  YYSYMBOL_insert = 102,                   /* insert  */
  YYSYMBOL_v_list = 103,                   /* v_list  */
  YYSYMBOL_node = 104,                     /* node  */
  YYSYMBOL_value_list = 105,               /* value_list  */
  YYSYMBOL_expr_value = 106,               /* expr_value  */
  YYSYMBOL_value = 107,                    /* value  */
  YYSYMBOL_delete = 108,                   /* delete  */
  YYSYMBOL_update = 109,                   /* update  */
  YYSYMBOL_update_attr = 110,              /* update_attr  */
  YYSYMBOL_update_attr_list = 111,         /* update_attr_list  */
  YYSYMBOL_update_unit = 112,              /* update_unit  */
  YYSYMBOL_select = 113,                   /* select  */
  YYSYMBOL_select_unit = 114,              /* select_unit  */
  YYSYMBOL_alias = 115,                    /* alias  */
  YYSYMBOL_select_begin = 116,             /* select_begin  */
  YYSYMBOL_select_attr = 117,              /* select_attr  */
  YYSYMBOL_select_attr_list = 118,         /* select_attr_list  */
  YYSYMBOL_expr = 119,                     /* expr  */
  YYSYMBOL_add_expr = 120,                 /* add_expr  */
  YYSYMBOL_mul_expr = 121,                 /* mul_expr  */
  YYSYMBOL_primary_expr = 122,             /* primary_expr  */
  YYSYMBOL_attr = 123,                     /* attr  */
  YYSYMBOL_aggr_attr = 124,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 125,                /* aggr_type  */
  YYSYMBOL_rel_list = 126,                 /* rel_list  */
  YYSYMBOL_join = 127,                     /* join  */
  YYSYMBOL_join_list = 128,                /* join_list  */
  YYSYMBOL_where = 129,                    /* where  */
  YYSYMBOL_condition_list = 130,           /* condition_list  */
  YYSYMBOL_condition = 131,                /* condition  */
  YYSYMBOL_comOp = 132,                    /* comOp  */
  YYSYMBOL_null_comOp = 133,               /* null_comOp  */
  YYSYMBOL_condition_value = 134,          /* condition_value  */
  YYSYMBOL_condition_value_list = 135,     /* condition_value_list  */
  YYSYMBOL_group_by = 136,                 /* group_by  */
  YYSYMBOL_group_list = 137,               /* group_list  */
  YYSYMBOL_having = 138,                   /* having  */
  YYSYMBOL_having_list = 139,              /* having_list  */
  YYSYMBOL_order_by = 140,                 /* order_by  */
  YYSYMBOL_order_list = 141,               /* order_list  */
  YYSYMBOL_order = 142,                    /* order  */
  YYSYMBOL_load_data = 143                 /* load_data  */
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
#define YYLAST   387

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  343

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


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
      75,    76
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   191,   191,   193,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   218,   223,   228,   234,   240,   246,   252,   258,
     264,   271,   278,   284,   292,   298,   304,   306,   313,   320,
     329,   331,   335,   342,   350,   353,   354,   355,   356,   357,
     360,   365,   366,   367,   371,   384,   385,   390,   398,   400,
     405,   410,   415,   421,   427,   432,   437,   442,   448,   455,
     465,   472,   475,   478,   480,   483,   487,   492,   497,   509,
     512,   515,   521,   527,   533,   536,   538,   542,   545,   550,
     554,   558,   562,   566,   570,   574,   578,   582,   586,   590,
     596,   601,   607,   611,   617,   627,   628,   629,   630,   631,
     634,   636,   639,   643,   646,   648,   652,   654,   656,   658,
     662,   666,   670,   674,   679,   684,   689,   694,   704,   716,
     717,   718,   719,   720,   721,   722,   723,   726,   727,   730,
     733,   735,   739,   741,   744,   746,   749,   751,   759,   761,
     770,   772,   775,   777,   781,   784,   787,   790,   793,   796,
     802
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
  "HAVING", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE",
  "GE", "NE", "LIKE", "IN", "EXISTS", "INNER", "JOIN", "IS", "NOT",
  "NULL_TOKEN", "NULLABLE", "ORDER", "ASC", "PLUS", "MINUS", "STAR",
  "DIVIDE", "AS", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STRING_V",
  "$accept", "commands", "command", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "show_index",
  "desc_table", "create_index", "attrone", "attr_index", "attr_index_list",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "nullable", "insert", "v_list", "node", "value_list",
  "expr_value", "value", "delete", "update", "update_attr",
  "update_attr_list", "update_unit", "select", "select_unit", "alias",
  "select_begin", "select_attr", "select_attr_list", "expr", "add_expr",
  "mul_expr", "primary_expr", "attr", "aggr_attr", "aggr_type", "rel_list",
  "join", "join_list", "where", "condition_list", "condition", "comOp",
  "null_comOp", "condition_value", "condition_value_list", "group_by",
  "group_list", "having", "having_list", "order_by", "order_list", "order",
  "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-295)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-69)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -295,   332,  -295,    86,    29,  -295,   -37,    21,    37,    19,
      12,   -11,    85,    96,    98,   108,   128,    88,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,  -295,  -295,   129,   182,  -295,    60,
      66,    64,    67,    68,   139,   142,   105,  -295,    87,    90,
     117,  -295,  -295,  -295,  -295,  -295,   118,  -295,     2,  -295,
    -295,  -295,  -295,  -295,  -295,   253,   146,  -295,  -295,   130,
    -295,  -295,   131,    42,   -18,    39,  -295,  -295,  -295,   152,
     154,   132,   100,   172,   175,  -295,  -295,   106,   143,   140,
     111,   110,   189,   169,    -1,  -295,   205,  -295,   120,   122,
     124,  -295,   146,   189,   189,   253,   253,    14,   127,   134,
     157,  -295,  -295,   201,   186,   119,   202,   160,   140,   196,
     177,  -295,  -295,    42,  -295,    42,  -295,  -295,    39,    39,
    -295,  -295,   211,  -295,   212,   213,  -295,   224,   200,   215,
     173,  -295,   -15,   228,   190,   188,   258,   192,   198,   199,
     203,   103,   203,   222,  -295,    38,   263,   195,  -295,   265,
     146,    20,  -295,  -295,  -295,   127,   251,  -295,  -295,  -295,
    -295,  -295,    -2,   206,   256,  -295,   220,  -295,  -295,  -295,
     255,   282,   276,   234,    18,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,   278,    71,   205,  -295,   119,  -295,   282,
     196,  -295,   247,   196,   225,  -295,   226,   238,   140,  -295,
     224,   297,   230,   240,  -295,  -295,  -295,   284,   206,  -295,
     -15,   286,   287,   282,   244,  -295,    31,  -295,   290,  -295,
     222,   291,  -295,    38,  -295,   305,    42,   237,   279,  -295,
    -295,   293,  -295,   241,   295,   284,   255,   298,  -295,   300,
    -295,  -295,   301,   302,    31,  -295,  -295,   196,  -295,    20,
      42,   288,   252,    23,  -295,   284,   320,   309,  -295,   317,
     335,   -15,  -295,  -295,   -15,   321,   322,   302,  -295,  -295,
     296,   262,   315,  -295,  -295,  -295,  -295,   347,  -295,  -295,
     255,   302,  -295,  -295,   333,   119,   336,   283,  -295,   339,
    -295,  -295,   222,   262,   323,     5,   340,   298,   303,   336,
     210,  -295,  -295,   289,  -295,   283,  -295,  -295,   304,  -295,
    -295,    69,    11,   340,   292,   311,   -15,  -295,  -295,  -295,
      42,   324,   319,   210,  -295,   119,    69,   222,   -15,   303,
     324,  -295,  -295
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    77,     0,   105,
     106,   107,   108,   109,    63,     0,    85,    60,    61,   100,
      62,    99,     0,    79,    87,    91,    95,    97,    98,     0,
       0,     0,     0,     0,     0,    31,    29,     0,     0,   116,
       0,     0,     0,     0,     0,    94,     0,    83,     0,     0,
       0,    81,    85,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    38,     0,     0,     0,     0,     0,   116,    73,
       0,    88,    96,    79,   101,    79,    80,    84,    89,    90,
      92,    93,     0,    44,     0,     0,    50,    40,     0,     0,
       0,    30,     0,     0,     0,    63,     0,    60,    61,    62,
       0,     0,    97,   118,    69,     0,     0,     0,    72,     0,
      85,   110,   103,   104,   102,     0,     0,    45,    46,    47,
      48,    49,    51,     0,     0,    68,     0,    64,    66,    67,
      58,     0,     0,    60,     0,   127,   129,   130,   131,   132,
     133,   134,   135,     0,     0,     0,   128,     0,   117,     0,
      73,    70,     0,    73,     0,    86,     0,     0,   116,   112,
      40,     0,     0,     0,    52,    43,    34,    36,     0,    65,
       0,     0,     0,     0,     0,   137,     0,   136,     0,   120,
     118,     0,    71,     0,    75,     0,    79,     0,   142,    41,
      39,     0,    53,     0,     0,    36,    58,    55,   125,     0,
     138,   139,     0,   140,     0,   119,    76,    73,   160,   110,
      79,     0,   150,    51,    35,    36,     0,     0,    59,     0,
       0,     0,   126,   123,     0,     0,     0,   140,    74,   111,
       0,     0,     0,    78,    42,    37,    33,     0,    57,    54,
      58,   140,   121,   124,     0,     0,   144,     0,    32,     0,
     141,   122,   118,     0,   146,   154,   152,    55,   114,   144,
       0,   143,   155,     0,   156,     0,   151,    56,     0,   113,
     145,     0,   157,   152,     0,     0,     0,   158,   159,   153,
      79,   148,     0,     0,   147,     0,     0,   118,     0,   114,
     148,   115,   149
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,  -295,
    -295,  -295,  -295,  -295,   153,  -295,  -220,  -295,  -295,   150,
     207,   158,  -295,  -295,   112,  -295,    70,  -295,  -223,  -295,
    -137,  -295,  -295,  -295,  -189,   216,  -295,   -56,  -122,  -295,
    -295,   -89,   -33,   -38,    25,   -55,  -107,  -289,  -295,   115,
    -295,    40,  -111,  -221,  -191,  -294,   229,  -228,  -253,  -295,
      73,  -295,    36,  -295,    57,    72,  -295
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   217,   265,   244,    30,    31,   166,
     137,   134,   172,   138,   215,    32,   270,   271,   221,    71,
     150,    33,    34,   118,   158,   119,    35,    36,   102,    37,
      72,    97,   151,    74,    75,    76,    77,    78,    79,   208,
     209,   319,   116,   198,   153,   195,   185,   253,   275,   262,
     304,   311,   334,   283,   316,   306,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     135,   160,    93,   161,    73,   180,   230,   156,   152,   255,
      95,   232,     5,   127,   234,   212,   312,   122,   200,    92,
      94,   321,   327,   268,   294,   267,   277,   326,    45,    46,
      59,    60,    61,    62,    63,    42,    44,    43,   300,   206,
      47,     5,   338,   313,   336,   285,   291,   175,   103,   104,
     130,   131,   176,    49,    94,   199,   177,   178,    48,   213,
     179,   214,    50,   123,    64,   103,   104,   299,   278,    65,
     314,   205,    82,    67,    68,    69,   328,    70,   207,   224,
     225,   308,   132,   246,   213,   133,   214,    69,    51,   251,
     152,    95,    39,   175,    40,    41,   257,   238,   176,    52,
     175,    53,   177,   178,   302,   176,   179,   105,   106,   177,
     178,    54,   100,   179,   259,   101,   339,   251,   186,   187,
     188,   189,   190,   191,   192,   222,   227,   228,   128,   129,
     325,    55,    57,    80,   290,    56,    58,   251,   280,    81,
      83,    84,    85,   231,   337,    86,    87,    59,    60,    61,
      62,    63,   186,   187,   188,   189,   190,   191,   192,   193,
      88,    90,   229,    89,   194,    96,    91,   249,    98,   107,
     252,   108,    99,   110,   296,   111,   143,   109,   112,   113,
     144,   145,   115,   114,   117,   120,   146,   121,   152,   331,
     147,   148,    69,   124,   149,   125,   309,   126,   276,    58,
     136,   340,   140,   142,   141,   154,    92,   139,   332,   155,
      59,    60,    61,    62,    63,   157,   159,    59,    60,    61,
      62,    63,    58,   167,   168,   169,   170,   171,   152,   162,
     163,   164,   173,    59,    60,    61,    62,    63,    59,    60,
      61,    62,    63,   165,    64,   181,   174,   182,   -68,    65,
      66,    64,   -64,    67,    68,    69,    65,    70,   -66,   -67,
      67,    68,    69,   184,    70,   197,   201,    64,   202,   211,
      92,   204,    65,   218,   220,    92,    67,    68,    69,   216,
      70,    59,    60,    61,    62,    63,    59,    60,    61,    62,
      63,   219,     5,   223,   -65,   226,   233,   237,   235,   236,
     240,   133,   242,   243,   247,   248,   250,   254,   258,   256,
     260,   263,   261,   266,   264,    64,   282,   269,   272,   273,
      64,   274,   281,   286,    67,    68,    69,   287,    70,   183,
      68,    69,     2,    70,   288,    69,     3,     4,   289,   292,
     293,   295,     5,     6,     7,     8,     9,    10,    11,   297,
     298,   301,    12,    13,    14,   303,   305,   307,   310,   315,
     239,   318,   322,   324,   335,   330,   227,   333,    15,    16,
     241,   245,   210,   203,   279,   284,   342,   317,    17,   341,
     329,   196,   320,     0,     0,     0,     0,   323
};

static const yytype_int16 yycheck[] =
{
     107,   123,    58,   125,    37,   142,   197,   118,   115,   230,
      65,   200,    10,   102,   203,    17,    11,    18,   155,    17,
      58,   310,    11,   246,   277,   245,   254,   321,     7,     8,
      28,    29,    30,    31,    32,     6,    73,     8,   291,    19,
       3,    10,   336,    38,   333,   265,   274,    62,    66,    67,
     105,   106,    67,    41,    92,    17,    71,    72,    39,    61,
      75,    63,    73,    96,    62,    66,    67,   290,   257,    67,
      65,   160,     8,    71,    72,    73,    65,    75,    58,    61,
      62,   302,    68,   220,    61,    71,    63,    73,     3,   226,
     197,   146,     6,    62,     8,     9,   233,   208,    67,     3,
      62,     3,    71,    72,   295,    67,    75,    68,    69,    71,
      72,     3,    70,    75,   236,    73,   337,   254,    49,    50,
      51,    52,    53,    54,    55,   181,    55,    56,   103,   104,
      61,     3,     3,    73,   271,    47,    17,   274,   260,    73,
      73,    73,     3,   199,   335,     3,    41,    28,    29,    30,
      31,    32,    49,    50,    51,    52,    53,    54,    55,    56,
      73,    44,   195,    73,    61,    19,    48,   223,    38,    17,
     226,    17,    41,    73,   281,     3,    57,    45,     3,    73,
      61,    62,    42,    40,    73,    75,    67,    18,   295,   326,
      71,    72,    73,    73,    75,    73,   303,    73,   254,    17,
      73,   338,    45,    17,     3,     3,    17,    73,   330,    49,
      28,    29,    30,    31,    32,    19,    39,    28,    29,    30,
      31,    32,    17,    23,    24,    25,    26,    27,   335,    18,
      18,    18,    17,    28,    29,    30,    31,    32,    28,    29,
      30,    31,    32,    19,    62,    17,    73,    57,    60,    67,
      68,    62,    60,    71,    72,    73,    67,    75,    60,    60,
      71,    72,    73,    60,    75,    43,     3,    62,    73,    18,
      17,     6,    67,    17,    19,    17,    71,    72,    73,    73,
      75,    28,    29,    30,    31,    32,    28,    29,    30,    31,
      32,    71,    10,    17,    60,    17,    49,    59,    73,    73,
       3,    71,    62,    19,    18,    18,    62,    17,     3,    18,
      73,    18,    33,    18,    73,    62,    64,    19,    18,    18,
      62,    19,    34,     3,    71,    72,    73,    18,    75,    71,
      72,    73,     0,    75,    17,    73,     4,     5,     3,    18,
      18,    45,    10,    11,    12,    13,    14,    15,    16,    34,
       3,    18,    20,    21,    22,    19,    73,    18,    35,    19,
     210,    58,    73,    59,    45,    73,    55,    43,    36,    37,
     212,   218,   165,   157,   259,   263,   340,   307,    46,   339,
     323,   152,   309,    -1,    -1,    -1,    -1,   315
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    78,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    36,    37,    46,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      94,    95,   102,   108,   109,   113,   114,   116,   143,     6,
       8,     9,     6,     8,    73,     7,     8,     3,    39,    41,
      73,     3,     3,     3,     3,     3,    47,     3,    17,    28,
      29,    30,    31,    32,    62,    67,    68,    71,    72,    73,
      75,   106,   117,   119,   120,   121,   122,   123,   124,   125,
      73,    73,     8,    73,    73,     3,     3,    41,    73,    73,
      44,    48,    17,   114,   120,   122,    19,   118,    38,    41,
      70,    73,   115,    66,    67,    68,    69,    17,    17,    45,
      73,     3,     3,    73,    40,    42,   129,    73,   110,   112,
      75,    18,    18,   119,    73,    73,    73,   118,   121,   121,
     122,   122,    68,    71,    98,   123,    73,    97,   100,    73,
      45,     3,    17,    57,    61,    62,    67,    71,    72,    75,
     107,   119,   123,   131,     3,    49,   129,    19,   111,    39,
     115,   115,    18,    18,    18,    19,    96,    23,    24,    25,
      26,    27,    99,    17,    73,    62,    67,    71,    72,    75,
     107,    17,    57,    71,    60,   133,    49,    50,    51,    52,
      53,    54,    55,    56,    61,   132,   133,    43,   130,    17,
     107,     3,    73,   112,     6,   118,    19,    58,   126,   127,
      97,    18,    17,    61,    63,   101,    73,    91,    17,    71,
      19,   105,   114,    17,    61,    62,    17,    55,    56,   119,
     131,   114,   111,    49,   111,    73,    73,    59,   129,    96,
       3,    98,    62,    19,    93,    91,   107,    18,    18,   114,
      62,   107,   114,   134,    17,   130,    18,   107,     3,   115,
      73,    33,   136,    18,    73,    92,    18,    93,   105,    19,
     103,   104,    18,    18,    19,   135,   114,   134,   111,   126,
     115,    34,    64,   140,   101,    93,     3,    18,    17,     3,
     107,   134,    18,    18,   135,    45,   123,    34,     3,   105,
     135,    18,   131,    19,   137,    73,   142,    18,   130,   123,
      35,   138,    11,    38,    65,    19,   141,   103,    58,   128,
     137,   124,    73,   142,    59,    61,   132,    11,    65,   141,
      73,   107,   115,    43,   139,    45,   124,   131,   132,   130,
     107,   128,   139
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    78,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    90,    91,    92,    93,    93,    94,    95,
      96,    96,    97,    97,    98,    99,    99,    99,    99,    99,
     100,   101,   101,   101,   102,   103,   103,   104,   105,   105,
     106,   106,   106,   106,   107,   107,   107,   107,   107,   108,
     109,   110,   110,   111,   111,   111,   112,   113,   114,   115,
     115,   115,   116,   117,   117,   118,   118,   119,   119,   120,
     120,   120,   121,   121,   121,   121,   122,   122,   122,   122,
     123,   123,   124,   124,   124,   125,   125,   125,   125,   125,
     126,   126,   126,   127,   128,   128,   129,   129,   130,   130,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   133,   133,   134,
     135,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     140,   140,   141,   141,   142,   142,   142,   142,   142,   142,
     143
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
       6,     4,     2,     0,     5,     3,     5,     2,     9,     0,
       2,     1,     1,     2,     3,     0,     4,     1,     3,     3,
       3,     1,     3,     3,     2,     1,     3,     1,     1,     1,
       1,     3,     4,     4,     4,     1,     1,     1,     1,     1,
       0,     4,     1,     8,     0,     8,     0,     3,     0,     3,
       3,     6,     7,     5,     6,     4,     5,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     1,
       0,     3,     0,     5,     0,     3,     0,     5,     0,     5,
       0,     4,     0,     3,     1,     2,     2,     3,     4,     4,
       8
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
#line 218 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1538 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 223 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1546 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 228 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1554 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 234 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1562 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 240 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1570 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 246 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1578 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 252 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1587 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 258 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1595 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 264 "yacc_sql.y"
                                 {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1604 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 271 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1613 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 279 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1623 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 285 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1633 "yacc_sql.tab.c"
    break;

  case 34: /* attrone: ID  */
#line 293 "yacc_sql.y"
        {
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1641 "yacc_sql.tab.c"
    break;

  case 35: /* attr_index: ID  */
#line 299 "yacc_sql.y"
        {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, (yyvsp[0].string));
		CONTEXT->attr_num++;
	}
#line 1650 "yacc_sql.tab.c"
    break;

  case 37: /* attr_index_list: COMMA attr_index attr_index_list  */
#line 307 "yacc_sql.y"
        {

	}
#line 1658 "yacc_sql.tab.c"
    break;

  case 38: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 314 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1667 "yacc_sql.tab.c"
    break;

  case 39: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 321 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1679 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 331 "yacc_sql.y"
                                   {    }
#line 1685 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 335 "yacc_sql.y"
                                              {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
    }
#line 1697 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type nullable  */
#line 342 "yacc_sql.y"
                           {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4 + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
	}
#line 1709 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 350 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1715 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 353 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1721 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 354 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 1727 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 355 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1733 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 356 "yacc_sql.y"
              { (yyval.number) = FLOATS; }
#line 1739 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 357 "yacc_sql.y"
             { (yyval.number) = DATES; }
#line 1745 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 360 "yacc_sql.y"
       {
        char *temp=(yyvsp[0].string);
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1754 "yacc_sql.tab.c"
    break;

  case 51: /* nullable: %empty  */
#line 365 "yacc_sql.y"
                  { (yyval.number) = false; }
#line 1760 "yacc_sql.tab.c"
    break;

  case 52: /* nullable: NULLABLE  */
#line 366 "yacc_sql.y"
               { (yyval.number) = true; }
#line 1766 "yacc_sql.tab.c"
    break;

  case 53: /* nullable: NOT NULL_TOKEN  */
#line 367 "yacc_sql.y"
                         { (yyval.number) = false; }
#line 1772 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE v_list SEMICOLON  */
#line 372 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_INSERT;
		CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
		CONTEXT->every_group_count=0;
        CONTEXT->group_num = CONTEXT->group_num + 1;

		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->insert_groups, CONTEXT->group_num);

		//临时变量清零
		CONTEXT->value_length=0;
    }
#line 1788 "yacc_sql.tab.c"
    break;

  case 56: /* v_list: node value value_list RBRACE v_list  */
#line 386 "yacc_sql.y"
    {
    }
#line 1795 "yacc_sql.tab.c"
    break;

  case 57: /* node: COMMA LBRACE  */
#line 391 "yacc_sql.y"
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    }
#line 1806 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 400 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1814 "yacc_sql.tab.c"
    break;

  case 60: /* expr_value: NUMBER  */
#line 405 "yacc_sql.y"
             {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1824 "yacc_sql.tab.c"
    break;

  case 61: /* expr_value: FLOAT  */
#line 410 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1834 "yacc_sql.tab.c"
    break;

  case 62: /* expr_value: SSS  */
#line 415 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1845 "yacc_sql.tab.c"
    break;

  case 63: /* expr_value: NULL_TOKEN  */
#line 421 "yacc_sql.y"
                 {
         value_init_null(&CONTEXT->values[CONTEXT->value_length]);
         (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
         CONTEXT->every_group_count++;
     }
#line 1855 "yacc_sql.tab.c"
    break;

  case 64: /* value: NUMBER  */
#line 427 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1865 "yacc_sql.tab.c"
    break;

  case 65: /* value: MINUS NUMBER  */
#line 432 "yacc_sql.y"
                   {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], -(yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1875 "yacc_sql.tab.c"
    break;

  case 66: /* value: FLOAT  */
#line 437 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
	}
#line 1885 "yacc_sql.tab.c"
    break;

  case 67: /* value: SSS  */
#line 442 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1896 "yacc_sql.tab.c"
    break;

  case 68: /* value: NULL_TOKEN  */
#line 448 "yacc_sql.y"
                 {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1906 "yacc_sql.tab.c"
    break;

  case 69: /* delete: DELETE FROM ID where SEMICOLON  */
#line 455 "yacc_sql.y"
                                   {
        CONTEXT->ssql->flag = SCF_DELETE;//"delete";
        deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
        deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->conditions[CONTEXT->select_length],
                CONTEXT->condition_length[CONTEXT->select_length]);
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
#line 1918 "yacc_sql.tab.c"
    break;

  case 70: /* update: UPDATE ID SET update_attr where SEMICOLON  */
#line 465 "yacc_sql.y"
                                              {
        CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), CONTEXT->conditions[CONTEXT->select_length],
		        CONTEXT->condition_length[CONTEXT->select_length]);
		CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
#line 1929 "yacc_sql.tab.c"
    break;

  case 71: /* update_attr: ID EQ value update_attr_list  */
#line 472 "yacc_sql.y"
                                 {
		updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1937 "yacc_sql.tab.c"
    break;

  case 72: /* update_attr: update_unit update_attr_list  */
#line 475 "yacc_sql.y"
                                   {

    }
#line 1945 "yacc_sql.tab.c"
    break;

  case 74: /* update_attr_list: COMMA ID EQ value update_attr_list  */
#line 480 "yacc_sql.y"
                                         {
        updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1953 "yacc_sql.tab.c"
    break;

  case 75: /* update_attr_list: COMMA update_unit update_attr_list  */
#line 483 "yacc_sql.y"
                                         {

    }
#line 1961 "yacc_sql.tab.c"
    break;

  case 76: /* update_unit: ID EQ LBRACE select_unit RBRACE  */
#line 487 "yacc_sql.y"
                                    {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), (yyvsp[-1]._select));
    }
#line 1969 "yacc_sql.tab.c"
    break;

  case 77: /* select: select_unit SEMICOLON  */
#line 492 "yacc_sql.y"
                          {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[1];
    }
#line 1978 "yacc_sql.tab.c"
    break;

  case 78: /* select_unit: select_begin select_attr FROM ID alias rel_list where group_by order_by  */
#line 497 "yacc_sql.y"
                                                                            {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length],
                CONTEXT->conditions[CONTEXT->select_length], CONTEXT->condition_length[CONTEXT->select_length]);
        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 1992 "yacc_sql.tab.c"
    break;

  case 79: /* alias: %empty  */
#line 509 "yacc_sql.y"
    {
        (yyval.string) = NULL;
    }
#line 2000 "yacc_sql.tab.c"
    break;

  case 80: /* alias: AS ID  */
#line 512 "yacc_sql.y"
           {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2008 "yacc_sql.tab.c"
    break;

  case 81: /* alias: ID  */
#line 515 "yacc_sql.y"
        {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2016 "yacc_sql.tab.c"
    break;

  case 82: /* select_begin: SELECT  */
#line 521 "yacc_sql.y"
           {
        CONTEXT->select_length++;
        memset(&CONTEXT->selects[CONTEXT->select_length], 0, sizeof(Selects));
    }
#line 2025 "yacc_sql.tab.c"
    break;

  case 83: /* select_attr: STAR select_attr_list  */
#line 527 "yacc_sql.y"
                           {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], &attr);
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], &CONTEXT->exprs[CONTEXT->expr_length++], NULL);
    }
#line 2036 "yacc_sql.tab.c"
    break;

  case 84: /* select_attr: expr alias select_attr_list  */
#line 533 "yacc_sql.y"
                                  {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2044 "yacc_sql.tab.c"
    break;

  case 86: /* select_attr_list: COMMA expr alias select_attr_list  */
#line 538 "yacc_sql.y"
                                        {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2052 "yacc_sql.tab.c"
    break;

  case 87: /* expr: add_expr  */
#line 542 "yacc_sql.y"
             {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2060 "yacc_sql.tab.c"
    break;

  case 88: /* expr: LBRACE select_unit RBRACE  */
#line 545 "yacc_sql.y"
                                {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2069 "yacc_sql.tab.c"
    break;

  case 89: /* add_expr: add_expr PLUS mul_expr  */
#line 550 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_PLUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2078 "yacc_sql.tab.c"
    break;

  case 90: /* add_expr: add_expr MINUS mul_expr  */
#line 554 "yacc_sql.y"
                              {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MINUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2087 "yacc_sql.tab.c"
    break;

  case 91: /* add_expr: mul_expr  */
#line 558 "yacc_sql.y"
               {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2095 "yacc_sql.tab.c"
    break;

  case 92: /* mul_expr: mul_expr STAR primary_expr  */
#line 562 "yacc_sql.y"
                               {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MULTIPLY, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2104 "yacc_sql.tab.c"
    break;

  case 93: /* mul_expr: mul_expr DIVIDE primary_expr  */
#line 566 "yacc_sql.y"
                                   {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_DIVIDE, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2113 "yacc_sql.tab.c"
    break;

  case 94: /* mul_expr: MINUS primary_expr  */
#line 570 "yacc_sql.y"
                         {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_NEGATIVE, (yyvsp[0]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2122 "yacc_sql.tab.c"
    break;

  case 95: /* mul_expr: primary_expr  */
#line 574 "yacc_sql.y"
                   {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2130 "yacc_sql.tab.c"
    break;

  case 96: /* primary_expr: LBRACE add_expr RBRACE  */
#line 578 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_BRACE, (yyvsp[-1]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2139 "yacc_sql.tab.c"
    break;

  case 97: /* primary_expr: attr  */
#line 582 "yacc_sql.y"
           {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2148 "yacc_sql.tab.c"
    break;

  case 98: /* primary_expr: aggr_attr  */
#line 586 "yacc_sql.y"
                {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2157 "yacc_sql.tab.c"
    break;

  case 99: /* primary_expr: expr_value  */
#line 590 "yacc_sql.y"
                 {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2166 "yacc_sql.tab.c"
    break;

  case 100: /* attr: ID  */
#line 596 "yacc_sql.y"
       {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2176 "yacc_sql.tab.c"
    break;

  case 101: /* attr: ID DOT ID  */
#line 601 "yacc_sql.y"
                {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2186 "yacc_sql.tab.c"
    break;

  case 102: /* aggr_attr: aggr_type LBRACE attr RBRACE  */
#line 607 "yacc_sql.y"
                                   {
        relation_attr_aggr((yyvsp[-1]._attr), (yyvsp[-3].number));
        (yyval._attr) = (yyvsp[-1]._attr);
    }
#line 2195 "yacc_sql.tab.c"
    break;

  case 103: /* aggr_attr: aggr_type LBRACE STAR RBRACE  */
#line 611 "yacc_sql.y"
                                   {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2206 "yacc_sql.tab.c"
    break;

  case 104: /* aggr_attr: aggr_type LBRACE number RBRACE  */
#line 617 "yacc_sql.y"
                                     {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        if ((yyvsp[-1].number) != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2220 "yacc_sql.tab.c"
    break;

  case 105: /* aggr_type: MAX  */
#line 627 "yacc_sql.y"
          { (yyval.number) = AGGR_MAX; }
#line 2226 "yacc_sql.tab.c"
    break;

  case 106: /* aggr_type: MIN  */
#line 628 "yacc_sql.y"
          { (yyval.number) = AGGR_MIN; }
#line 2232 "yacc_sql.tab.c"
    break;

  case 107: /* aggr_type: COUNT  */
#line 629 "yacc_sql.y"
            { (yyval.number) = AGGR_COUNT; }
#line 2238 "yacc_sql.tab.c"
    break;

  case 108: /* aggr_type: AVG  */
#line 630 "yacc_sql.y"
          { (yyval.number) = AGGR_AVG; }
#line 2244 "yacc_sql.tab.c"
    break;

  case 109: /* aggr_type: SUM  */
#line 631 "yacc_sql.y"
          { (yyval.number) = AGGR_SUM; }
#line 2250 "yacc_sql.tab.c"
    break;

  case 111: /* rel_list: COMMA ID alias rel_list  */
#line 636 "yacc_sql.y"
                              {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2].string), (yyvsp[-1].string));
    }
#line 2258 "yacc_sql.tab.c"
    break;

  case 112: /* rel_list: join  */
#line 639 "yacc_sql.y"
           {
    }
#line 2265 "yacc_sql.tab.c"
    break;

  case 113: /* join: INNER JOIN ID alias ON condition condition_list join_list  */
#line 643 "yacc_sql.y"
                                                                  {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2273 "yacc_sql.tab.c"
    break;

  case 115: /* join_list: INNER JOIN ID alias ON condition condition_list join_list  */
#line 648 "yacc_sql.y"
                                                                     {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2281 "yacc_sql.tab.c"
    break;

  case 117: /* where: WHERE condition condition_list  */
#line 654 "yacc_sql.y"
                                     {}
#line 2287 "yacc_sql.tab.c"
    break;

  case 119: /* condition_list: AND condition condition_list  */
#line 658 "yacc_sql.y"
                                   {}
#line 2293 "yacc_sql.tab.c"
    break;

  case 120: /* condition: expr comOp expr  */
#line 662 "yacc_sql.y"
                    {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
    }
#line 2302 "yacc_sql.tab.c"
    break;

  case 121: /* condition: expr IN LBRACE condition_value condition_value_list RBRACE  */
#line 666 "yacc_sql.y"
                                                                 {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2311 "yacc_sql.tab.c"
    break;

  case 122: /* condition: expr NOT IN LBRACE condition_value condition_value_list RBRACE  */
#line 670 "yacc_sql.y"
                                                                     {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_IN_OP, (yyvsp[-6]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2320 "yacc_sql.tab.c"
    break;

  case 123: /* condition: expr IN LBRACE select_unit RBRACE  */
#line 674 "yacc_sql.y"
                                         {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                IN_OP, (yyvsp[-4]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2330 "yacc_sql.tab.c"
    break;

  case 124: /* condition: expr NOT IN LBRACE select_unit RBRACE  */
#line 679 "yacc_sql.y"
                                            {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2340 "yacc_sql.tab.c"
    break;

  case 125: /* condition: EXISTS LBRACE select_unit RBRACE  */
#line 684 "yacc_sql.y"
                                       {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2350 "yacc_sql.tab.c"
    break;

  case 126: /* condition: NOT EXISTS LBRACE select_unit RBRACE  */
#line 689 "yacc_sql.y"
                                           {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2360 "yacc_sql.tab.c"
    break;

  case 127: /* condition: value null_comOp  */
#line 694 "yacc_sql.y"
                           {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
#line 2375 "yacc_sql.tab.c"
    break;

  case 128: /* condition: attr null_comOp  */
#line 704 "yacc_sql.y"
                          {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._attr));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
#line 2390 "yacc_sql.tab.c"
    break;

  case 129: /* comOp: EQ  */
#line 716 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2396 "yacc_sql.tab.c"
    break;

  case 130: /* comOp: LT  */
#line 717 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2402 "yacc_sql.tab.c"
    break;

  case 131: /* comOp: GT  */
#line 718 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2408 "yacc_sql.tab.c"
    break;

  case 132: /* comOp: LE  */
#line 719 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2414 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: GE  */
#line 720 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2420 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: NE  */
#line 721 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2426 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: LIKE  */
#line 722 "yacc_sql.y"
           { (yyval.number) = LIKE_OP; }
#line 2432 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: NOT LIKE  */
#line 723 "yacc_sql.y"
               { (yyval.number) = NOT_LIKE_OP; }
#line 2438 "yacc_sql.tab.c"
    break;

  case 137: /* null_comOp: IS NULL_TOKEN  */
#line 726 "yacc_sql.y"
                    { (yyval.number) = IS_NULL; }
#line 2444 "yacc_sql.tab.c"
    break;

  case 138: /* null_comOp: IS NOT NULL_TOKEN  */
#line 727 "yacc_sql.y"
                        { (yyval.number) = IS_NOT_NULL; }
#line 2450 "yacc_sql.tab.c"
    break;

  case 139: /* condition_value: value  */
#line 730 "yacc_sql.y"
          {
        expr_append_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
    }
#line 2458 "yacc_sql.tab.c"
    break;

  case 141: /* condition_value_list: COMMA condition_value condition_value_list  */
#line 735 "yacc_sql.y"
                                                 {

    }
#line 2466 "yacc_sql.tab.c"
    break;

  case 143: /* group_by: GROUP BY attr group_list having  */
#line 741 "yacc_sql.y"
                                      {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._attr));
    }
#line 2474 "yacc_sql.tab.c"
    break;

  case 145: /* group_list: COMMA attr group_list  */
#line 746 "yacc_sql.y"
                            {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
    }
#line 2482 "yacc_sql.tab.c"
    break;

  case 147: /* having: HAVING aggr_attr comOp value having_list  */
#line 751 "yacc_sql.y"
                                               {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2495 "yacc_sql.tab.c"
    break;

  case 149: /* having_list: AND aggr_attr comOp value having_list  */
#line 761 "yacc_sql.y"
                                            {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2508 "yacc_sql.tab.c"
    break;

  case 151: /* order_by: ORDER BY order order_list  */
#line 772 "yacc_sql.y"
                                {
    }
#line 2515 "yacc_sql.tab.c"
    break;

  case 153: /* order_list: COMMA order order_list  */
#line 777 "yacc_sql.y"
                            {
    }
#line 2522 "yacc_sql.tab.c"
    break;

  case 154: /* order: ID  */
#line 781 "yacc_sql.y"
      {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, "");
    }
#line 2530 "yacc_sql.tab.c"
    break;

  case 155: /* order: ID DESC  */
#line 784 "yacc_sql.y"
             {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, "");
    }
#line 2538 "yacc_sql.tab.c"
    break;

  case 156: /* order: ID ASC  */
#line 787 "yacc_sql.y"
            {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, "");
    }
#line 2546 "yacc_sql.tab.c"
    break;

  case 157: /* order: ID DOT ID  */
#line 790 "yacc_sql.y"
               {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, (yyvsp[-2].string));
    }
#line 2554 "yacc_sql.tab.c"
    break;

  case 158: /* order: ID DOT ID DESC  */
#line 793 "yacc_sql.y"
                    {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, (yyvsp[-3].string));
    }
#line 2562 "yacc_sql.tab.c"
    break;

  case 159: /* order: ID DOT ID ASC  */
#line 796 "yacc_sql.y"
                   {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, (yyvsp[-3].string));
    }
#line 2570 "yacc_sql.tab.c"
    break;

  case 160: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 802 "yacc_sql.y"
                                                 {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
    }
#line 2579 "yacc_sql.tab.c"
    break;


#line 2583 "yacc_sql.tab.c"

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

#line 807 "yacc_sql.y"

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
