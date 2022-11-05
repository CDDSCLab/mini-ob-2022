/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

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
  YYSYMBOL_SET = 47,                       /* SET  */
  YYSYMBOL_ON = 48,                        /* ON  */
  YYSYMBOL_LOAD = 49,                      /* LOAD  */
  YYSYMBOL_DATA = 50,                      /* DATA  */
  YYSYMBOL_INFILE = 51,                    /* INFILE  */
  YYSYMBOL_EQ = 52,                        /* EQ  */
  YYSYMBOL_LT = 53,                        /* LT  */
  YYSYMBOL_GT = 54,                        /* GT  */
  YYSYMBOL_LE = 55,                        /* LE  */
  YYSYMBOL_GE = 56,                        /* GE  */
  YYSYMBOL_NE = 57,                        /* NE  */
  YYSYMBOL_LIKE = 58,                      /* LIKE  */
  YYSYMBOL_IN = 59,                        /* IN  */
  YYSYMBOL_EXISTS = 60,                    /* EXISTS  */
  YYSYMBOL_INNER = 61,                     /* INNER  */
  YYSYMBOL_JOIN = 62,                      /* JOIN  */
  YYSYMBOL_IS = 63,                        /* IS  */
  YYSYMBOL_NOT = 64,                       /* NOT  */
  YYSYMBOL_NULL_TOKEN = 65,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 66,                  /* NULLABLE  */
  YYSYMBOL_ORDER = 67,                     /* ORDER  */
  YYSYMBOL_ASC = 68,                       /* ASC  */
  YYSYMBOL_PLUS = 69,                      /* PLUS  */
  YYSYMBOL_MINUS = 70,                     /* MINUS  */
  YYSYMBOL_STAR = 71,                      /* STAR  */
  YYSYMBOL_DIVIDE = 72,                    /* DIVIDE  */
  YYSYMBOL_AS = 73,                        /* AS  */
  YYSYMBOL_NUMBER = 74,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 75,                     /* FLOAT  */
  YYSYMBOL_ID = 76,                        /* ID  */
  YYSYMBOL_PATH = 77,                      /* PATH  */
  YYSYMBOL_SSS = 78,                       /* SSS  */
  YYSYMBOL_STRING_V = 79,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 80,                  /* $accept  */
  YYSYMBOL_commands = 81,                  /* commands  */
  YYSYMBOL_command = 82,                   /* command  */
  YYSYMBOL_exit = 83,                      /* exit  */
  YYSYMBOL_help = 84,                      /* help  */
  YYSYMBOL_sync = 85,                      /* sync  */
  YYSYMBOL_begin = 86,                     /* begin  */
  YYSYMBOL_commit = 87,                    /* commit  */
  YYSYMBOL_rollback = 88,                  /* rollback  */
  YYSYMBOL_drop_table = 89,                /* drop_table  */
  YYSYMBOL_show_tables = 90,               /* show_tables  */
  YYSYMBOL_show_index = 91,                /* show_index  */
  YYSYMBOL_desc_table = 92,                /* desc_table  */
  YYSYMBOL_create_index = 93,              /* create_index  */
  YYSYMBOL_attrone = 94,                   /* attrone  */
  YYSYMBOL_attr_index = 95,                /* attr_index  */
  YYSYMBOL_attr_index_list = 96,           /* attr_index_list  */
  YYSYMBOL_drop_index = 97,                /* drop_index  */
  YYSYMBOL_create_table = 98,              /* create_table  */
  YYSYMBOL_attr_def_list = 99,             /* attr_def_list  */
  YYSYMBOL_attr_def = 100,                 /* attr_def  */
  YYSYMBOL_number = 101,                   /* number  */
  YYSYMBOL_type = 102,                     /* type  */
  YYSYMBOL_ID_get = 103,                   /* ID_get  */
  YYSYMBOL_nullable = 104,                 /* nullable  */
  YYSYMBOL_insert = 105,                   /* insert  */
  YYSYMBOL_v_list = 106,                   /* v_list  */
  YYSYMBOL_node = 107,                     /* node  */
  YYSYMBOL_value_list = 108,               /* value_list  */
  YYSYMBOL_expr_value = 109,               /* expr_value  */
  YYSYMBOL_value = 110,                    /* value  */
  YYSYMBOL_delete = 111,                   /* delete  */
  YYSYMBOL_update = 112,                   /* update  */
  YYSYMBOL_update_attr = 113,              /* update_attr  */
  YYSYMBOL_update_attr_list = 114,         /* update_attr_list  */
  YYSYMBOL_update_unit = 115,              /* update_unit  */
  YYSYMBOL_select = 116,                   /* select  */
  YYSYMBOL_select_unit = 117,              /* select_unit  */
  YYSYMBOL_func_attr_list = 118,           /* func_attr_list  */
  YYSYMBOL_func_attr = 119,                /* func_attr  */
  YYSYMBOL_func_type_1 = 120,              /* func_type_1  */
  YYSYMBOL_func_type_2 = 121,              /* func_type_2  */
  YYSYMBOL_alias = 122,                    /* alias  */
  YYSYMBOL_select_begin = 123,             /* select_begin  */
  YYSYMBOL_select_attr = 124,              /* select_attr  */
  YYSYMBOL_select_attr_list = 125,         /* select_attr_list  */
  YYSYMBOL_expr = 126,                     /* expr  */
  YYSYMBOL_add_expr = 127,                 /* add_expr  */
  YYSYMBOL_mul_expr = 128,                 /* mul_expr  */
  YYSYMBOL_primary_expr = 129,             /* primary_expr  */
  YYSYMBOL_attr = 130,                     /* attr  */
  YYSYMBOL_aggr_attr = 131,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 132,                /* aggr_type  */
  YYSYMBOL_rel_list = 133,                 /* rel_list  */
  YYSYMBOL_join = 134,                     /* join  */
  YYSYMBOL_join_list = 135,                /* join_list  */
  YYSYMBOL_where = 136,                    /* where  */
  YYSYMBOL_condition_list = 137,           /* condition_list  */
  YYSYMBOL_condition = 138,                /* condition  */
  YYSYMBOL_comOp = 139,                    /* comOp  */
  YYSYMBOL_null_comOp = 140,               /* null_comOp  */
  YYSYMBOL_condition_value = 141,          /* condition_value  */
  YYSYMBOL_condition_value_list = 142,     /* condition_value_list  */
  YYSYMBOL_group_by = 143,                 /* group_by  */
  YYSYMBOL_group_list = 144,               /* group_list  */
  YYSYMBOL_having = 145,                   /* having  */
  YYSYMBOL_having_list = 146,              /* having_list  */
  YYSYMBOL_order_by = 147,                 /* order_by  */
  YYSYMBOL_order_list = 148,               /* order_list  */
  YYSYMBOL_order = 149,                    /* order  */
  YYSYMBOL_load_data = 150                 /* load_data  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYLAST   418

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  175
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  374

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   334


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
      75,    76,    77,    78,    79
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   197,   197,   199,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,   224,   229,   234,   240,   246,   252,   258,   264,
     270,   277,   284,   290,   298,   304,   310,   312,   319,   326,
     335,   337,   341,   348,   356,   359,   360,   361,   362,   363,
     366,   371,   372,   373,   377,   390,   391,   396,   404,   406,
     411,   416,   421,   427,   433,   438,   443,   448,   454,   461,
     471,   478,   481,   484,   486,   489,   493,   498,   503,   511,
     521,   522,   528,   532,   536,   542,   544,   545,   550,   553,
     556,   562,   568,   571,   583,   586,   588,   591,   595,   598,
     603,   607,   611,   615,   619,   623,   627,   631,   635,   639,
     643,   649,   654,   659,   665,   669,   675,   685,   686,   687,
     688,   689,   692,   694,   697,   701,   704,   706,   710,   712,
     714,   716,   720,   724,   728,   732,   736,   740,   744,   749,
     754,   763,   772,   782,   794,   795,   796,   797,   798,   799,
     800,   801,   804,   805,   808,   811,   813,   817,   819,   822,
     824,   827,   829,   837,   839,   848,   850,   853,   855,   859,
     862,   865,   868,   871,   874,   880
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
  "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON", "LOAD", "DATA",
  "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "LIKE", "IN", "EXISTS",
  "INNER", "JOIN", "IS", "NOT", "NULL_TOKEN", "NULLABLE", "ORDER", "ASC",
  "PLUS", "MINUS", "STAR", "DIVIDE", "AS", "NUMBER", "FLOAT", "ID", "PATH",
  "SSS", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "show_index", "desc_table", "create_index", "attrone", "attr_index",
  "attr_index_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "nullable", "insert", "v_list",
  "node", "value_list", "expr_value", "value", "delete", "update",
  "update_attr", "update_attr_list", "update_unit", "select",
  "select_unit", "func_attr_list", "func_attr", "func_type_1",
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

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334
};
#endif

#define YYPACT_NINF (-315)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-96)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -315,   338,  -315,    23,    65,  -315,   -38,    95,    43,    30,
      55,    -2,    86,   107,   116,   136,   149,   115,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,   167,   179,  -315,    96,
      97,   163,    99,   100,   174,   178,   140,  -315,   109,   111,
     141,  -315,  -315,  -315,  -315,  -315,   142,  -315,     5,  -315,
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,   256,   172,
    -315,  -315,   156,  -315,  -315,   -34,   182,   184,   159,   -34,
      54,    66,  -315,  -315,  -315,   188,   189,   170,   143,   218,
     225,  -315,  -315,   153,   196,   186,   162,   154,   230,   222,
      27,  -315,   205,  -315,    11,   169,  -315,    22,   256,   256,
     176,   172,   230,   230,   256,   256,    17,   180,   187,   198,
    -315,  -315,   245,   247,   104,   262,   214,   186,   248,   226,
    -315,  -315,   -34,   -34,  -315,  -315,  -315,   205,  -315,  -315,
     251,   125,   -34,  -315,    66,    66,  -315,  -315,   253,  -315,
     254,   259,  -315,   255,   103,   277,   200,  -315,    42,   279,
     237,   235,   261,   236,   238,   239,   240,   258,   102,   240,
     263,  -315,   -10,   304,   241,  -315,   312,   172,   172,   -34,
    -315,  -315,   256,     6,  -315,  -315,  -315,   180,   301,  -315,
    -315,  -315,  -315,  -315,    -5,   244,   306,  -315,   250,  -315,
    -315,  -315,   308,   315,   311,   266,    81,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,  -315,   275,   205,   323,    91,   205,
    -315,   104,  -315,   315,   248,  -315,   289,   248,   268,  -315,
    -315,    22,   327,   270,   285,   186,  -315,   255,   352,   282,
     292,  -315,  -315,  -315,   342,   244,  -315,    42,   344,   345,
     315,   299,  -315,  -315,  -315,  -315,    20,   348,  -315,  -315,
     263,   349,  -315,   -10,  -315,   363,  -315,  -315,   -34,   293,
     335,  -315,  -315,   353,  -315,   294,   354,   342,   308,   355,
    -315,   357,  -315,  -315,   358,   360,    20,  -315,  -315,   248,
    -315,     6,   -34,   339,   313,    45,  -315,   342,   378,   364,
    -315,   366,   381,    42,  -315,  -315,    42,   367,   368,   360,
    -315,  -315,   340,   314,   359,  -315,  -315,  -315,  -315,   386,
    -315,  -315,   308,   360,  -315,  -315,   373,   104,   375,   316,
    -315,   377,  -315,  -315,   263,   314,   361,     8,   379,   355,
     336,   375,   195,  -315,  -315,   324,  -315,   316,  -315,  -315,
     337,  -315,  -315,   258,     9,   379,   325,    42,  -315,  -315,
    -315,   -34,   356,   362,   195,  -315,   104,   258,   263,    42,
     336,   356,  -315,  -315
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
      66,    67,    58,     0,     0,    60,     0,   142,   144,   145,
     146,   147,   148,   149,   150,     0,     0,     0,     0,     0,
     143,     0,   129,     0,    73,    70,     0,    73,     0,    97,
      96,    80,     0,     0,     0,   128,   124,    40,     0,     0,
       0,    52,    43,    34,    36,     0,    65,     0,     0,     0,
       0,     0,   152,   151,   133,   134,     0,     0,   135,   132,
     130,     0,    71,     0,    75,     0,    81,    83,    88,     0,
     157,    41,    39,     0,    53,     0,     0,    36,    58,    55,
     140,     0,   153,   154,     0,   155,     0,   131,    76,    73,
     175,   122,    88,     0,   165,    51,    35,    36,     0,     0,
      59,     0,     0,     0,   141,   138,     0,     0,     0,   155,
      74,   123,     0,     0,     0,    79,    42,    37,    33,     0,
      57,    54,    58,   155,   136,   139,     0,     0,   159,     0,
      32,     0,   156,   137,   130,     0,   161,   169,   167,    55,
     126,   159,     0,   158,   170,     0,   171,     0,   166,    56,
       0,   125,   160,     0,   172,   167,     0,     0,   173,   174,
     168,    88,   163,     0,     0,   162,     0,     0,   130,     0,
     126,   163,   127,   164
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,  -315,
    -315,  -315,  -315,  -315,   158,  -315,  -254,  -315,  -315,   168,
     217,   173,  -315,  -315,   112,  -315,    67,  -315,  -260,  -315,
    -155,  -315,  -315,  -315,  -203,   234,  -315,   -56,   183,   -33,
    -315,  -315,   -79,  -315,  -315,   -63,   -24,   -42,    50,   -57,
    -115,  -314,  -315,   118,  -315,    41,  -113,  -250,  -213,  -163,
     246,  -259,  -283,  -315,    72,  -315,    46,  -315,    61,    71,
    -315
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   244,   297,   276,    30,    31,   188,
     153,   150,   194,   154,   242,    32,   302,   303,   248,    74,
     166,    33,    34,   127,   175,   128,    35,    36,   138,   167,
      76,    77,   107,    37,    78,   229,   168,    80,    81,    82,
      83,    84,    85,   235,   236,   351,   125,   222,   170,   216,
     207,   285,   307,   294,   336,   343,   365,   315,   348,   338,
      38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     111,   151,    99,   202,    75,   219,   103,   223,   260,   169,
     287,   101,   239,    79,   173,     5,   100,   224,   300,   344,
     358,   262,    98,   299,   264,   233,   326,   309,   353,    39,
       5,    40,    41,    59,    60,    61,    62,    63,    44,   105,
     332,   137,   106,   317,   139,   131,    47,   323,   143,   345,
     367,   140,   141,   177,   178,   197,   100,   146,   147,   240,
     198,   241,   331,   183,   199,   200,   -95,   234,   201,   132,
      67,    42,    48,    43,    50,    68,   346,   359,   133,    70,
      71,    72,   134,    73,   340,   197,   310,   135,   148,    51,
     198,   149,   278,    72,   199,   200,   112,   113,   201,    49,
     231,   283,    45,    46,   179,   101,   169,   197,   289,   240,
      52,   241,   198,   133,   334,   230,   199,   200,   370,    53,
     201,    58,   270,   112,   113,   232,   189,   190,   191,   192,
     193,   283,    59,    60,    61,    62,    63,   114,   115,    54,
      64,    65,    66,   181,   182,   251,   252,   249,   322,   253,
     257,   283,    55,   368,   208,   209,   210,   211,   212,   213,
     214,   217,   144,   145,   159,    56,   218,   261,   160,   161,
      57,    88,    86,    87,   162,    89,    90,    91,   163,   164,
      72,    92,   165,   254,    93,    94,   258,    95,    96,   291,
     357,   102,   255,    97,   281,   259,    58,   104,   328,   108,
     284,   109,   362,   110,   369,   116,   117,    59,    60,    61,
      62,    63,   169,   312,   371,    64,    65,    66,   118,   119,
     341,   120,    58,    59,    60,    61,    62,    63,   121,   122,
     308,   124,   129,    59,    60,    61,    62,    63,   126,   123,
     130,    64,    65,    66,    67,   136,   156,    98,   157,    68,
      69,   169,   142,    70,    71,    72,   152,    73,    59,    60,
      61,    62,    63,   155,   158,   171,   172,   174,   176,   180,
      67,   184,   185,    98,   187,    68,   196,   186,    98,    70,
      71,    72,   363,    73,    59,    60,    61,    62,    63,    59,
      60,    61,    62,    63,   195,    67,   203,   204,   -68,   -64,
      68,   -66,   -67,   206,    70,    71,    72,   225,    73,   221,
     208,   209,   210,   211,   212,   213,   214,   226,   228,   238,
     243,    67,   215,   245,   246,     5,    67,   247,   250,   -65,
      70,    71,    72,   253,    73,   205,    71,    72,     2,    73,
     256,   263,     3,     4,   265,   267,   268,   269,     5,     6,
       7,     8,     9,    10,    11,   272,   149,   274,    12,    13,
      14,   275,   279,   280,   282,   286,   290,   288,   293,   292,
     296,   295,   298,   313,   301,   304,   305,    15,    16,   306,
     314,   318,   319,   320,   321,   324,   325,    17,   327,   330,
      72,   333,   337,   329,   335,   339,   342,   350,   347,   356,
     354,   361,   364,   277,   237,   271,   349,   316,   227,   311,
     366,   372,   273,   352,   266,   220,   360,   373,   355
};

static const yytype_int16 yycheck[] =
{
      79,   116,    58,   158,    37,   168,    69,    17,   221,   124,
     260,    68,    17,    37,   127,    10,    58,   172,   278,    11,
      11,   224,    17,   277,   227,    19,   309,   286,   342,     6,
      10,     8,     9,    28,    29,    30,    31,    32,    76,    73,
     323,    19,    76,   297,   107,    18,     3,   306,   111,    41,
     364,   108,   109,   132,   133,    65,    98,   114,   115,    64,
      70,    66,   322,   142,    74,    75,    44,    61,    78,   102,
      65,     6,    42,     8,    76,    70,    68,    68,   102,    74,
      75,    76,    71,    78,   334,    65,   289,    76,    71,     3,
      70,    74,   247,    76,    74,    75,    69,    70,    78,    44,
     179,   256,     7,     8,   137,   162,   221,    65,   263,    64,
       3,    66,    70,   137,   327,   178,    74,    75,   368,     3,
      78,    17,   235,    69,    70,   182,    23,    24,    25,    26,
      27,   286,    28,    29,    30,    31,    32,    71,    72,     3,
      36,    37,    38,    18,    19,    64,    65,   203,   303,    58,
      59,   306,     3,   366,    52,    53,    54,    55,    56,    57,
      58,    59,   112,   113,    60,    50,    64,   223,    64,    65,
       3,     8,    76,    76,    70,    76,    76,     3,    74,    75,
      76,     3,    78,   216,    44,    76,   219,    76,    47,   268,
     353,    19,   216,    51,   250,   219,    17,    41,   313,    17,
     256,    17,   357,    44,   367,    17,    17,    28,    29,    30,
      31,    32,   327,   292,   369,    36,    37,    38,    48,    76,
     335,     3,    17,    28,    29,    30,    31,    32,     3,    76,
     286,    45,    78,    28,    29,    30,    31,    32,    76,    43,
      18,    36,    37,    38,    65,    76,    48,    17,     3,    70,
      71,   366,    76,    74,    75,    76,    76,    78,    28,    29,
      30,    31,    32,    76,    17,     3,    52,    19,    42,    18,
      65,    18,    18,    17,    19,    70,    76,    18,    17,    74,
      75,    76,   361,    78,    28,    29,    30,    31,    32,    28,
      29,    30,    31,    32,    17,    65,    17,    60,    63,    63,
      70,    63,    63,    63,    74,    75,    76,     3,    78,    46,
      52,    53,    54,    55,    56,    57,    58,    76,     6,    18,
      76,    65,    64,    17,    74,    10,    65,    19,    17,    63,
      74,    75,    76,    58,    78,    74,    75,    76,     0,    78,
      17,    52,     4,     5,    76,    18,    76,    62,    10,    11,
      12,    13,    14,    15,    16,     3,    74,    65,    20,    21,
      22,    19,    18,    18,    65,    17,     3,    18,    33,    76,
      76,    18,    18,    34,    19,    18,    18,    39,    40,    19,
      67,     3,    18,    17,     3,    18,    18,    49,    48,     3,
      76,    18,    76,    34,    19,    18,    35,    61,    19,    62,
      76,    76,    46,   245,   187,   237,   339,   295,   174,   291,
      48,   370,   239,   341,   231,   169,   355,   371,   347
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    81,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    39,    40,    49,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      97,    98,   105,   111,   112,   116,   117,   123,   150,     6,
       8,     9,     6,     8,    76,     7,     8,     3,    42,    44,
      76,     3,     3,     3,     3,     3,    50,     3,    17,    28,
      29,    30,    31,    32,    36,    37,    38,    65,    70,    71,
      74,    75,    76,    78,   109,   119,   120,   121,   124,   126,
     127,   128,   129,   130,   131,   132,    76,    76,     8,    76,
      76,     3,     3,    44,    76,    76,    47,    51,    17,   117,
     127,   129,    19,   125,    41,    73,    76,   122,    17,    17,
      44,   122,    69,    70,    71,    72,    17,    17,    48,    76,
       3,     3,    76,    43,    45,   136,    76,   113,   115,    78,
      18,    18,   119,   126,    71,    76,    76,    19,   118,   125,
     129,   129,    76,   125,   128,   128,   129,   129,    71,    74,
     101,   130,    76,   100,   103,    76,    48,     3,    17,    60,
      64,    65,    70,    74,    75,    78,   110,   119,   126,   130,
     138,     3,    52,   136,    19,   114,    42,   122,   122,   119,
      18,    18,    19,   122,    18,    18,    18,    19,    99,    23,
      24,    25,    26,    27,   102,    17,    76,    65,    70,    74,
      75,    78,   110,    17,    60,    74,    63,   140,    52,    53,
      54,    55,    56,    57,    58,    64,   139,    59,    64,   139,
     140,    46,   137,    17,   110,     3,    76,   115,     6,   125,
     125,   122,   129,    19,    61,   133,   134,   100,    18,    17,
      64,    66,   104,    76,    94,    17,    74,    19,   108,   117,
      17,    64,    65,    58,   119,   126,    17,    59,   119,   126,
     138,   117,   114,    52,   114,    76,   118,    18,    76,    62,
     136,    99,     3,   101,    65,    19,    96,    94,   110,    18,
      18,   117,    65,   110,   117,   141,    17,   137,    18,   110,
       3,   122,    76,    33,   143,    18,    76,    95,    18,    96,
     108,    19,   106,   107,    18,    18,    19,   142,   117,   141,
     114,   133,   122,    34,    67,   147,   104,    96,     3,    18,
      17,     3,   110,   141,    18,    18,   142,    48,   130,    34,
       3,   108,   142,    18,   138,    19,   144,    76,   149,    18,
     137,   130,    35,   145,    11,    41,    68,    19,   148,   106,
      61,   135,   144,   131,    76,   149,    62,   139,    11,    68,
     148,    76,   110,   122,    46,   146,    48,   131,   138,   139,
     137,   110,   135,   146
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    80,    81,    81,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    93,    94,    95,    96,    96,    97,    98,
      99,    99,   100,   100,   101,   102,   102,   102,   102,   102,
     103,   104,   104,   104,   105,   106,   106,   107,   108,   108,
     109,   109,   109,   109,   110,   110,   110,   110,   110,   111,
     112,   113,   113,   114,   114,   114,   115,   116,   117,   117,
     118,   118,   119,   119,   119,   120,   121,   121,   122,   122,
     122,   123,   124,   124,   124,   125,   125,   125,   126,   126,
     127,   127,   127,   128,   128,   128,   128,   129,   129,   129,
     129,   130,   130,   130,   131,   131,   131,   132,   132,   132,
     132,   132,   133,   133,   133,   134,   135,   135,   136,   136,
     137,   137,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   139,   140,   140,   141,   142,   142,   143,   143,   144,
     144,   145,   145,   146,   146,   147,   147,   148,   148,   149,
     149,   149,   149,   149,   149,   150
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
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
       0,     3,     3,     3,     3,     3,     6,     7,     5,     6,
       4,     5,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     1,     0,     3,     0,     5,     0,
       3,     0,     5,     0,     5,     0,     4,     0,     3,     1,
       2,     2,     3,     4,     4,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


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
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
#line 224 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1568 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 229 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1576 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 234 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1584 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 240 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1592 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 246 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1600 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 252 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1608 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 258 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1617 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 264 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1625 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 270 "yacc_sql.y"
                                 {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1634 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 277 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1643 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 285 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1653 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 291 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1663 "yacc_sql.tab.c"
    break;

  case 34: /* attrone: ID  */
#line 299 "yacc_sql.y"
        {
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1671 "yacc_sql.tab.c"
    break;

  case 35: /* attr_index: ID  */
#line 305 "yacc_sql.y"
        {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, (yyvsp[0].string));
		CONTEXT->attr_num++;
	}
#line 1680 "yacc_sql.tab.c"
    break;

  case 37: /* attr_index_list: COMMA attr_index attr_index_list  */
#line 313 "yacc_sql.y"
        {

	}
#line 1688 "yacc_sql.tab.c"
    break;

  case 38: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 320 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1697 "yacc_sql.tab.c"
    break;

  case 39: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 327 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1709 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 337 "yacc_sql.y"
                                   {    }
#line 1715 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 341 "yacc_sql.y"
                                              {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
    }
#line 1727 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type nullable  */
#line 348 "yacc_sql.y"
                           {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4 + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
	}
#line 1739 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 356 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1745 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 359 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1751 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 360 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 1757 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 361 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1763 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 362 "yacc_sql.y"
              { (yyval.number) = FLOATS; }
#line 1769 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 363 "yacc_sql.y"
             { (yyval.number) = DATES; }
#line 1775 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 366 "yacc_sql.y"
       {
        char *temp=(yyvsp[0].string);
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1784 "yacc_sql.tab.c"
    break;

  case 51: /* nullable: %empty  */
#line 371 "yacc_sql.y"
                  { (yyval.number) = false; }
#line 1790 "yacc_sql.tab.c"
    break;

  case 52: /* nullable: NULLABLE  */
#line 372 "yacc_sql.y"
               { (yyval.number) = true; }
#line 1796 "yacc_sql.tab.c"
    break;

  case 53: /* nullable: NOT NULL_TOKEN  */
#line 373 "yacc_sql.y"
                         { (yyval.number) = false; }
#line 1802 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE v_list SEMICOLON  */
#line 378 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_INSERT;
		CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
		CONTEXT->every_group_count=0;
        CONTEXT->group_num = CONTEXT->group_num + 1;

		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->insert_groups, CONTEXT->group_num);

		//临时变量清零
		CONTEXT->value_length=0;
    }
#line 1818 "yacc_sql.tab.c"
    break;

  case 56: /* v_list: node value value_list RBRACE v_list  */
#line 392 "yacc_sql.y"
    {
    }
#line 1825 "yacc_sql.tab.c"
    break;

  case 57: /* node: COMMA LBRACE  */
#line 397 "yacc_sql.y"
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    }
#line 1836 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 406 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1844 "yacc_sql.tab.c"
    break;

  case 60: /* expr_value: NUMBER  */
#line 411 "yacc_sql.y"
             {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1854 "yacc_sql.tab.c"
    break;

  case 61: /* expr_value: FLOAT  */
#line 416 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1864 "yacc_sql.tab.c"
    break;

  case 62: /* expr_value: SSS  */
#line 421 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1875 "yacc_sql.tab.c"
    break;

  case 63: /* expr_value: NULL_TOKEN  */
#line 427 "yacc_sql.y"
                 {
         value_init_null(&CONTEXT->values[CONTEXT->value_length]);
         (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
         CONTEXT->every_group_count++;
     }
#line 1885 "yacc_sql.tab.c"
    break;

  case 64: /* value: NUMBER  */
#line 433 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1895 "yacc_sql.tab.c"
    break;

  case 65: /* value: MINUS NUMBER  */
#line 438 "yacc_sql.y"
                   {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], -(yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1905 "yacc_sql.tab.c"
    break;

  case 66: /* value: FLOAT  */
#line 443 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
	}
#line 1915 "yacc_sql.tab.c"
    break;

  case 67: /* value: SSS  */
#line 448 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1926 "yacc_sql.tab.c"
    break;

  case 68: /* value: NULL_TOKEN  */
#line 454 "yacc_sql.y"
                 {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1936 "yacc_sql.tab.c"
    break;

  case 69: /* delete: DELETE FROM ID where SEMICOLON  */
#line 461 "yacc_sql.y"
                                   {
        CONTEXT->ssql->flag = SCF_DELETE;//"delete";
        deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
        deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->conditions[CONTEXT->select_length],
                CONTEXT->condition_length[CONTEXT->select_length]);
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
#line 1948 "yacc_sql.tab.c"
    break;

  case 70: /* update: UPDATE ID SET update_attr where SEMICOLON  */
#line 471 "yacc_sql.y"
                                              {
        CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), CONTEXT->conditions[CONTEXT->select_length],
		        CONTEXT->condition_length[CONTEXT->select_length]);
		CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
#line 1959 "yacc_sql.tab.c"
    break;

  case 71: /* update_attr: ID EQ value update_attr_list  */
#line 478 "yacc_sql.y"
                                 {
		updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1967 "yacc_sql.tab.c"
    break;

  case 72: /* update_attr: update_unit update_attr_list  */
#line 481 "yacc_sql.y"
                                   {

    }
#line 1975 "yacc_sql.tab.c"
    break;

  case 74: /* update_attr_list: COMMA ID EQ value update_attr_list  */
#line 486 "yacc_sql.y"
                                         {
        updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1983 "yacc_sql.tab.c"
    break;

  case 75: /* update_attr_list: COMMA update_unit update_attr_list  */
#line 489 "yacc_sql.y"
                                         {

    }
#line 1991 "yacc_sql.tab.c"
    break;

  case 76: /* update_unit: ID EQ LBRACE select_unit RBRACE  */
#line 493 "yacc_sql.y"
                                    {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), (yyvsp[-1]._select));
    }
#line 1999 "yacc_sql.tab.c"
    break;

  case 77: /* select: select_unit SEMICOLON  */
#line 498 "yacc_sql.y"
                          {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[1];
    }
#line 2008 "yacc_sql.tab.c"
    break;

  case 78: /* select_unit: select_begin func_attr alias func_attr_list  */
#line 503 "yacc_sql.y"
                                                {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));

        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 2021 "yacc_sql.tab.c"
    break;

  case 79: /* select_unit: select_begin select_attr FROM ID alias rel_list where group_by order_by  */
#line 511 "yacc_sql.y"
                                                                              {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length],
                CONTEXT->conditions[CONTEXT->select_length], CONTEXT->condition_length[CONTEXT->select_length]);
        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 2035 "yacc_sql.tab.c"
    break;

  case 81: /* func_attr_list: COMMA func_attr alias func_attr_list  */
#line 522 "yacc_sql.y"
                                          {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2043 "yacc_sql.tab.c"
    break;

  case 82: /* func_attr: func_type_1 LBRACE primary_expr RBRACE  */
#line 528 "yacc_sql.y"
                                                 {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-3].number), (yyvsp[-1]._expr), NULL);
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2052 "yacc_sql.tab.c"
    break;

  case 83: /* func_attr: func_type_2 LBRACE primary_expr COMMA primary_expr RBRACE  */
#line 532 "yacc_sql.y"
                                                                {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-5].number), (yyvsp[-3]._expr), (yyvsp[-1]._expr));
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2061 "yacc_sql.tab.c"
    break;

  case 84: /* func_attr: func_type_2 LBRACE primary_expr RBRACE  */
#line 536 "yacc_sql.y"
                                             {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-3].number), (yyvsp[-1]._expr), NULL);
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2070 "yacc_sql.tab.c"
    break;

  case 85: /* func_type_1: LENGTH  */
#line 542 "yacc_sql.y"
                  { (yyval.number) = EXPR_LENGTH; }
#line 2076 "yacc_sql.tab.c"
    break;

  case 86: /* func_type_2: ROUND  */
#line 544 "yacc_sql.y"
                 { (yyval.number) = EXPR_ROUND; }
#line 2082 "yacc_sql.tab.c"
    break;

  case 87: /* func_type_2: DATE_FORMAT  */
#line 545 "yacc_sql.y"
                       { (yyval.number) = EXPR_DATE_FORMAT; }
#line 2088 "yacc_sql.tab.c"
    break;

  case 88: /* alias: %empty  */
#line 550 "yacc_sql.y"
    {
        (yyval.string) = NULL;
    }
#line 2096 "yacc_sql.tab.c"
    break;

  case 89: /* alias: AS ID  */
#line 553 "yacc_sql.y"
           {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2104 "yacc_sql.tab.c"
    break;

  case 90: /* alias: ID  */
#line 556 "yacc_sql.y"
        {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2112 "yacc_sql.tab.c"
    break;

  case 91: /* select_begin: SELECT  */
#line 562 "yacc_sql.y"
           {
        CONTEXT->select_length++;
        memset(&CONTEXT->selects[CONTEXT->select_length], 0, sizeof(Selects));
    }
#line 2121 "yacc_sql.tab.c"
    break;

  case 92: /* select_attr: func_attr alias select_attr_list  */
#line 568 "yacc_sql.y"
                                    {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2129 "yacc_sql.tab.c"
    break;

  case 93: /* select_attr: STAR select_attr_list  */
#line 571 "yacc_sql.y"
                            {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], &attr);
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], &CONTEXT->exprs[CONTEXT->expr_length++], NULL);
    }
#line 2140 "yacc_sql.tab.c"
    break;

  case 94: /* select_attr: expr alias select_attr_list  */
#line 583 "yacc_sql.y"
                                  {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2148 "yacc_sql.tab.c"
    break;

  case 96: /* select_attr_list: COMMA expr alias select_attr_list  */
#line 588 "yacc_sql.y"
                                        {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2156 "yacc_sql.tab.c"
    break;

  case 97: /* select_attr_list: COMMA func_attr alias select_attr_list  */
#line 591 "yacc_sql.y"
                                             {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2164 "yacc_sql.tab.c"
    break;

  case 98: /* expr: add_expr  */
#line 595 "yacc_sql.y"
             {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2172 "yacc_sql.tab.c"
    break;

  case 99: /* expr: LBRACE select_unit RBRACE  */
#line 598 "yacc_sql.y"
                                {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2181 "yacc_sql.tab.c"
    break;

  case 100: /* add_expr: add_expr PLUS mul_expr  */
#line 603 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_PLUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2190 "yacc_sql.tab.c"
    break;

  case 101: /* add_expr: add_expr MINUS mul_expr  */
#line 607 "yacc_sql.y"
                              {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MINUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2199 "yacc_sql.tab.c"
    break;

  case 102: /* add_expr: mul_expr  */
#line 611 "yacc_sql.y"
               {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2207 "yacc_sql.tab.c"
    break;

  case 103: /* mul_expr: mul_expr STAR primary_expr  */
#line 615 "yacc_sql.y"
                               {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MULTIPLY, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2216 "yacc_sql.tab.c"
    break;

  case 104: /* mul_expr: mul_expr DIVIDE primary_expr  */
#line 619 "yacc_sql.y"
                                   {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_DIVIDE, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2225 "yacc_sql.tab.c"
    break;

  case 105: /* mul_expr: MINUS primary_expr  */
#line 623 "yacc_sql.y"
                         {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_NEGATIVE, (yyvsp[0]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2234 "yacc_sql.tab.c"
    break;

  case 106: /* mul_expr: primary_expr  */
#line 627 "yacc_sql.y"
                   {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2242 "yacc_sql.tab.c"
    break;

  case 107: /* primary_expr: LBRACE add_expr RBRACE  */
#line 631 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_BRACE, (yyvsp[-1]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2251 "yacc_sql.tab.c"
    break;

  case 108: /* primary_expr: attr  */
#line 635 "yacc_sql.y"
           {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2260 "yacc_sql.tab.c"
    break;

  case 109: /* primary_expr: aggr_attr  */
#line 639 "yacc_sql.y"
                {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2269 "yacc_sql.tab.c"
    break;

  case 110: /* primary_expr: expr_value  */
#line 643 "yacc_sql.y"
                 {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2278 "yacc_sql.tab.c"
    break;

  case 111: /* attr: ID  */
#line 649 "yacc_sql.y"
       {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2288 "yacc_sql.tab.c"
    break;

  case 112: /* attr: ID DOT ID  */
#line 654 "yacc_sql.y"
                {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2298 "yacc_sql.tab.c"
    break;

  case 113: /* attr: ID DOT STAR  */
#line 659 "yacc_sql.y"
                  {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, (yyvsp[-2].string), "*");
        (yyval._attr) = attr;
    }
#line 2308 "yacc_sql.tab.c"
    break;

  case 114: /* aggr_attr: aggr_type LBRACE attr RBRACE  */
#line 665 "yacc_sql.y"
                                   {
        relation_attr_aggr((yyvsp[-1]._attr), (yyvsp[-3].number));
        (yyval._attr) = (yyvsp[-1]._attr);
    }
#line 2317 "yacc_sql.tab.c"
    break;

  case 115: /* aggr_attr: aggr_type LBRACE STAR RBRACE  */
#line 669 "yacc_sql.y"
                                   {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2328 "yacc_sql.tab.c"
    break;

  case 116: /* aggr_attr: aggr_type LBRACE number RBRACE  */
#line 675 "yacc_sql.y"
                                     {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        if ((yyvsp[-1].number) != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2342 "yacc_sql.tab.c"
    break;

  case 117: /* aggr_type: MAX  */
#line 685 "yacc_sql.y"
          { (yyval.number) = AGGR_MAX; }
#line 2348 "yacc_sql.tab.c"
    break;

  case 118: /* aggr_type: MIN  */
#line 686 "yacc_sql.y"
          { (yyval.number) = AGGR_MIN; }
#line 2354 "yacc_sql.tab.c"
    break;

  case 119: /* aggr_type: COUNT  */
#line 687 "yacc_sql.y"
            { (yyval.number) = AGGR_COUNT; }
#line 2360 "yacc_sql.tab.c"
    break;

  case 120: /* aggr_type: AVG  */
#line 688 "yacc_sql.y"
          { (yyval.number) = AGGR_AVG; }
#line 2366 "yacc_sql.tab.c"
    break;

  case 121: /* aggr_type: SUM  */
#line 689 "yacc_sql.y"
          { (yyval.number) = AGGR_SUM; }
#line 2372 "yacc_sql.tab.c"
    break;

  case 123: /* rel_list: COMMA ID alias rel_list  */
#line 694 "yacc_sql.y"
                              {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2].string), (yyvsp[-1].string));
    }
#line 2380 "yacc_sql.tab.c"
    break;

  case 124: /* rel_list: join  */
#line 697 "yacc_sql.y"
           {
    }
#line 2387 "yacc_sql.tab.c"
    break;

  case 125: /* join: INNER JOIN ID alias ON condition condition_list join_list  */
#line 701 "yacc_sql.y"
                                                                  {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2395 "yacc_sql.tab.c"
    break;

  case 127: /* join_list: INNER JOIN ID alias ON condition condition_list join_list  */
#line 706 "yacc_sql.y"
                                                                     {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2403 "yacc_sql.tab.c"
    break;

  case 129: /* where: WHERE condition condition_list  */
#line 712 "yacc_sql.y"
                                     {}
#line 2409 "yacc_sql.tab.c"
    break;

  case 131: /* condition_list: AND condition condition_list  */
#line 716 "yacc_sql.y"
                                   {}
#line 2415 "yacc_sql.tab.c"
    break;

  case 132: /* condition: expr comOp expr  */
#line 720 "yacc_sql.y"
                    {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
    }
#line 2424 "yacc_sql.tab.c"
    break;

  case 133: /* condition: func_attr comOp func_attr  */
#line 724 "yacc_sql.y"
                                {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
    }
#line 2433 "yacc_sql.tab.c"
    break;

  case 134: /* condition: func_attr comOp expr  */
#line 728 "yacc_sql.y"
                           {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
    }
#line 2442 "yacc_sql.tab.c"
    break;

  case 135: /* condition: expr comOp func_attr  */
#line 732 "yacc_sql.y"
                           {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
    }
#line 2451 "yacc_sql.tab.c"
    break;

  case 136: /* condition: expr IN LBRACE condition_value condition_value_list RBRACE  */
#line 736 "yacc_sql.y"
                                                                 {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2460 "yacc_sql.tab.c"
    break;

  case 137: /* condition: expr NOT IN LBRACE condition_value condition_value_list RBRACE  */
#line 740 "yacc_sql.y"
                                                                     {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_IN_OP, (yyvsp[-6]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2469 "yacc_sql.tab.c"
    break;

  case 138: /* condition: expr IN LBRACE select_unit RBRACE  */
#line 744 "yacc_sql.y"
                                         {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                IN_OP, (yyvsp[-4]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2479 "yacc_sql.tab.c"
    break;

  case 139: /* condition: expr NOT IN LBRACE select_unit RBRACE  */
#line 749 "yacc_sql.y"
                                            {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2489 "yacc_sql.tab.c"
    break;

  case 140: /* condition: EXISTS LBRACE select_unit RBRACE  */
#line 754 "yacc_sql.y"
                                       {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *left_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], left_value);

        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                EXISTS_OP, &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
    }
#line 2503 "yacc_sql.tab.c"
    break;

  case 141: /* condition: NOT EXISTS LBRACE select_unit RBRACE  */
#line 763 "yacc_sql.y"
                                           {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *left_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], left_value);

        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                NOT_EXISTS_OP, &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
    }
#line 2517 "yacc_sql.tab.c"
    break;

  case 142: /* condition: value null_comOp  */
#line 772 "yacc_sql.y"
                           {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
#line 2532 "yacc_sql.tab.c"
    break;

  case 143: /* condition: attr null_comOp  */
#line 782 "yacc_sql.y"
                          {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._attr));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
#line 2547 "yacc_sql.tab.c"
    break;

  case 144: /* comOp: EQ  */
#line 794 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2553 "yacc_sql.tab.c"
    break;

  case 145: /* comOp: LT  */
#line 795 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2559 "yacc_sql.tab.c"
    break;

  case 146: /* comOp: GT  */
#line 796 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2565 "yacc_sql.tab.c"
    break;

  case 147: /* comOp: LE  */
#line 797 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2571 "yacc_sql.tab.c"
    break;

  case 148: /* comOp: GE  */
#line 798 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2577 "yacc_sql.tab.c"
    break;

  case 149: /* comOp: NE  */
#line 799 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2583 "yacc_sql.tab.c"
    break;

  case 150: /* comOp: LIKE  */
#line 800 "yacc_sql.y"
           { (yyval.number) = LIKE_OP; }
#line 2589 "yacc_sql.tab.c"
    break;

  case 151: /* comOp: NOT LIKE  */
#line 801 "yacc_sql.y"
               { (yyval.number) = NOT_LIKE_OP; }
#line 2595 "yacc_sql.tab.c"
    break;

  case 152: /* null_comOp: IS NULL_TOKEN  */
#line 804 "yacc_sql.y"
                    { (yyval.number) = IS_NULL; }
#line 2601 "yacc_sql.tab.c"
    break;

  case 153: /* null_comOp: IS NOT NULL_TOKEN  */
#line 805 "yacc_sql.y"
                        { (yyval.number) = IS_NOT_NULL; }
#line 2607 "yacc_sql.tab.c"
    break;

  case 154: /* condition_value: value  */
#line 808 "yacc_sql.y"
          {
        expr_append_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
    }
#line 2615 "yacc_sql.tab.c"
    break;

  case 156: /* condition_value_list: COMMA condition_value condition_value_list  */
#line 813 "yacc_sql.y"
                                                 {

    }
#line 2623 "yacc_sql.tab.c"
    break;

  case 158: /* group_by: GROUP BY attr group_list having  */
#line 819 "yacc_sql.y"
                                      {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._attr));
    }
#line 2631 "yacc_sql.tab.c"
    break;

  case 160: /* group_list: COMMA attr group_list  */
#line 824 "yacc_sql.y"
                            {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
    }
#line 2639 "yacc_sql.tab.c"
    break;

  case 162: /* having: HAVING aggr_attr comOp value having_list  */
#line 829 "yacc_sql.y"
                                               {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2652 "yacc_sql.tab.c"
    break;

  case 164: /* having_list: AND aggr_attr comOp value having_list  */
#line 839 "yacc_sql.y"
                                            {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2665 "yacc_sql.tab.c"
    break;

  case 166: /* order_by: ORDER BY order order_list  */
#line 850 "yacc_sql.y"
                                {
    }
#line 2672 "yacc_sql.tab.c"
    break;

  case 168: /* order_list: COMMA order order_list  */
#line 855 "yacc_sql.y"
                            {
    }
#line 2679 "yacc_sql.tab.c"
    break;

  case 169: /* order: ID  */
#line 859 "yacc_sql.y"
      {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, "");
    }
#line 2687 "yacc_sql.tab.c"
    break;

  case 170: /* order: ID DESC  */
#line 862 "yacc_sql.y"
             {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, "");
    }
#line 2695 "yacc_sql.tab.c"
    break;

  case 171: /* order: ID ASC  */
#line 865 "yacc_sql.y"
            {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, "");
    }
#line 2703 "yacc_sql.tab.c"
    break;

  case 172: /* order: ID DOT ID  */
#line 868 "yacc_sql.y"
               {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, (yyvsp[-2].string));
    }
#line 2711 "yacc_sql.tab.c"
    break;

  case 173: /* order: ID DOT ID DESC  */
#line 871 "yacc_sql.y"
                    {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, (yyvsp[-3].string));
    }
#line 2719 "yacc_sql.tab.c"
    break;

  case 174: /* order: ID DOT ID ASC  */
#line 874 "yacc_sql.y"
                   {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, (yyvsp[-3].string));
    }
#line 2727 "yacc_sql.tab.c"
    break;

  case 175: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 880 "yacc_sql.y"
                                                 {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
    }
#line 2736 "yacc_sql.tab.c"
    break;


#line 2740 "yacc_sql.tab.c"

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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
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

#line 885 "yacc_sql.y"

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
