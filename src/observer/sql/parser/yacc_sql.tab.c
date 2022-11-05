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
  YYSYMBOL_select = 115,                   /* select  */
  YYSYMBOL_select_unit = 116,              /* select_unit  */
  YYSYMBOL_func_attr = 117,                /* func_attr  */
  YYSYMBOL_func_type_1 = 118,              /* func_type_1  */
  YYSYMBOL_func_type_2 = 119,              /* func_type_2  */
  YYSYMBOL_alias = 120,                    /* alias  */
  YYSYMBOL_select_begin = 121,             /* select_begin  */
  YYSYMBOL_select_attr = 122,              /* select_attr  */
  YYSYMBOL_select_attr_list = 123,         /* select_attr_list  */
  YYSYMBOL_expr = 124,                     /* expr  */
  YYSYMBOL_add_expr = 125,                 /* add_expr  */
  YYSYMBOL_mul_expr = 126,                 /* mul_expr  */
  YYSYMBOL_primary_expr = 127,             /* primary_expr  */
  YYSYMBOL_attr = 128,                     /* attr  */
  YYSYMBOL_aggr_attr = 129,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 130,                /* aggr_type  */
  YYSYMBOL_rel_list = 131,                 /* rel_list  */
  YYSYMBOL_join = 132,                     /* join  */
  YYSYMBOL_join_list = 133,                /* join_list  */
  YYSYMBOL_where = 134,                    /* where  */
  YYSYMBOL_condition_list = 135,           /* condition_list  */
  YYSYMBOL_condition = 136,                /* condition  */
  YYSYMBOL_comOp = 137,                    /* comOp  */
  YYSYMBOL_null_comOp = 138,               /* null_comOp  */
  YYSYMBOL_group_by = 139,                 /* group_by  */
  YYSYMBOL_group_list = 140,               /* group_list  */
  YYSYMBOL_having = 141,                   /* having  */
  YYSYMBOL_having_list = 142,              /* having_list  */
  YYSYMBOL_order_by = 143,                 /* order_by  */
  YYSYMBOL_order_list = 144,               /* order_list  */
  YYSYMBOL_order = 145,                    /* order  */
  YYSYMBOL_load_data = 146                 /* load_data  */
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
#define YYLAST   388

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  80
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  67
/* YYNRULES -- Number of rules.  */
#define YYNRULES  161
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  351

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
     471,   478,   481,   484,   486,   489,   494,   499,   507,   516,
     527,   531,   537,   539,   540,   545,   548,   551,   557,   560,
     566,   569,   571,   575,   578,   583,   587,   591,   595,   599,
     603,   607,   611,   614,   618,   622,   629,   634,   640,   644,
     650,   660,   661,   662,   663,   664,   667,   669,   672,   676,
     679,   681,   685,   687,   689,   691,   695,   699,   704,   709,
     714,   719,   729,   741,   742,   743,   744,   745,   746,   747,
     748,   751,   752,   755,   757,   760,   762,   765,   767,   775,
     777,   786,   788,   791,   793,   797,   800,   803,   806,   809,
     812,   818
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
  "update_attr", "update_attr_list", "select", "select_unit", "func_attr",
  "func_type_1", "func_type_2", "alias", "select_begin", "select_attr",
  "select_attr_list", "expr", "add_expr", "mul_expr", "primary_expr",
  "attr", "aggr_attr", "aggr_type", "rel_list", "join", "join_list",
  "where", "condition_list", "condition", "comOp", "null_comOp",
  "group_by", "group_list", "having", "having_list", "order_by",
  "order_list", "order", "load_data", YY_NULLPTR
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

#define YYPACT_NINF (-299)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-69)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -299,   279,  -299,    84,    17,  -299,   -62,    49,    41,    11,
       7,     6,    83,    97,    99,   101,   114,    30,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,   116,    77,  -299,    12,
      50,   121,    58,    65,   119,   134,   112,  -299,    69,    91,
     122,  -299,  -299,  -299,  -299,  -299,   120,  -299,     1,  -299,
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,     9,   151,
    -299,  -299,   131,  -299,  -299,   -49,   159,   162,   137,   -49,
      -1,    61,  -299,  -299,  -299,   168,   171,   143,   124,   189,
     195,  -299,  -299,   125,   177,   157,   145,   144,   180,   205,
      -5,  -299,   196,  -299,   167,   170,  -299,   200,     9,     9,
     172,   151,   180,   180,     9,     9,    27,   173,   175,   204,
    -299,  -299,   254,   236,   129,   257,   210,   157,   221,  -299,
    -299,   -49,  -299,  -299,   188,   247,   249,   -49,  -299,    61,
      61,  -299,  -299,   251,  -299,   255,   263,  -299,   256,   139,
     265,   209,  -299,    53,   269,   227,   225,   202,   233,   234,
     235,   248,   250,   248,   264,  -299,    46,   309,   307,   151,
    -299,  -299,     9,    -2,  -299,  -299,  -299,   173,   297,  -299,
    -299,  -299,  -299,  -299,    25,   240,   300,  -299,   246,  -299,
    -299,  -299,   302,   312,   306,   261,    75,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,  -299,   308,    85,   196,  -299,   129,
    -299,   312,   310,  -299,   258,  -299,   313,   259,   268,   157,
    -299,   256,   323,   253,   267,  -299,  -299,  -299,   314,   240,
    -299,    53,   318,   319,   312,   273,  -299,   312,  -299,   322,
    -299,   264,   324,   270,  -299,   337,  -299,   -49,   271,   311,
    -299,  -299,   325,  -299,   272,   327,   314,   302,   330,  -299,
     332,  -299,   333,   312,  -299,   310,   289,  -299,    -2,   -49,
     320,   285,   -30,  -299,   314,   350,   338,  -299,   340,   352,
      53,  -299,  -299,   341,  -299,   108,  -299,   315,   282,   326,
    -299,  -299,  -299,  -299,   358,  -299,  -299,   302,  -299,   312,
     310,   129,   343,   288,  -299,   347,   348,  -299,   264,   282,
     334,     4,   349,   330,   310,   316,   343,   186,  -299,  -299,
     291,  -299,   288,  -299,  -299,  -299,   317,  -299,  -299,   183,
      10,   349,   294,   328,    53,  -299,  -299,  -299,   -49,   329,
     335,   186,  -299,   129,   183,   264,    53,   316,   329,  -299,
    -299
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,    88,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    76,     0,   111,
     112,   113,   114,   115,    82,    83,    84,    63,     0,    91,
      60,    61,   106,    62,   105,    85,     0,     0,     0,    85,
      93,    97,   101,   103,   104,     0,     0,     0,     0,     0,
       0,    31,    29,     0,     0,   122,     0,     0,     0,     0,
       0,   100,     0,    89,     0,     0,    87,    77,     0,     0,
       0,    91,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    38,     0,     0,     0,     0,     0,   122,     0,    94,
     102,    85,   107,    86,     0,     0,     0,    85,    90,    95,
      96,    98,    99,     0,    44,     0,     0,    50,    40,     0,
       0,     0,    30,     0,     0,     0,    63,     0,    60,    61,
      62,     0,     0,   103,   124,    69,     0,     0,     0,    91,
      78,    80,     0,   116,   109,   110,   108,     0,     0,    45,
      46,    47,    48,    49,    51,     0,     0,    68,     0,    64,
      66,    67,    58,     0,     0,    60,     0,   131,   133,   134,
     135,   136,   137,   138,   139,     0,     0,     0,   132,     0,
     123,     0,    73,    70,     0,    92,     0,     0,     0,   122,
     118,    40,     0,     0,     0,    52,    43,    34,    36,     0,
      65,     0,     0,     0,     0,     0,   141,     0,   140,     0,
     126,   124,     0,     0,    71,     0,    81,    85,     0,   143,
      41,    39,     0,    53,     0,     0,    36,    58,    55,   129,
       0,   142,     0,     0,   125,    73,     0,   161,   116,    85,
       0,   151,    51,    35,    36,     0,     0,    59,     0,     0,
       0,   130,   127,     0,    72,     0,   117,     0,     0,     0,
      79,    42,    37,    33,     0,    57,    54,    58,   128,     0,
      73,     0,   145,     0,    32,     0,     0,    74,   124,     0,
     147,   155,   153,    55,    73,   120,   145,     0,   144,   156,
       0,   157,     0,   152,    56,    75,     0,   119,   146,     0,
     158,   153,     0,     0,     0,   159,   160,   154,    85,   149,
       0,     0,   148,     0,     0,   124,     0,   120,   149,   121,
     150
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,  -299,
    -299,  -299,  -299,  -299,   142,  -299,  -228,  -299,  -299,   152,
     197,   149,  -299,  -299,   104,  -299,    67,  -299,  -237,  -299,
    -150,  -299,  -299,  -299,  -253,  -299,   -57,  -299,  -299,  -299,
     -79,  -299,  -299,  -102,   -32,   -36,    37,   -60,  -114,  -298,
    -299,   110,  -299,    34,  -120,  -235,  -205,  -294,   219,  -299,
      68,  -299,    39,  -299,    54,    66,  -299
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   228,   274,   255,    30,    31,   178,
     148,   145,   184,   149,   226,    32,   279,   280,   232,    74,
     161,    33,    34,   127,   244,    35,    36,    75,    76,    77,
     107,    37,    78,   103,   162,    80,    81,    82,    83,    84,
      85,   219,   220,   327,   125,   210,   164,   207,   197,   271,
     310,   318,   342,   290,   323,   312,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     111,    99,   146,   192,   241,    79,   264,   167,   101,   138,
     163,     5,   284,   130,    44,   319,   212,   217,    98,   329,
     277,   335,   100,    42,   105,    43,    98,   106,   276,    59,
      60,    61,    62,    63,   224,   334,   225,    59,    60,    61,
      62,    63,   223,   344,    47,   320,   292,   307,   135,   136,
     346,    49,   169,    48,   141,   142,    45,    46,   173,   218,
     305,   325,   100,   211,   112,   113,    67,   215,   112,   113,
     131,    68,   321,   315,    67,    70,    71,    72,   336,    73,
      56,   257,    50,    70,    71,    72,    51,    73,    86,   224,
      39,   225,    40,    41,    58,   163,   308,   101,   143,   249,
      52,   144,    53,    72,    54,    59,    60,    61,    62,    63,
     347,   187,   216,    64,    65,    66,   188,    55,   187,    57,
     189,   190,    91,   188,   191,   299,    87,   189,   190,    88,
     297,   191,   114,   115,    89,   300,   233,    92,   345,   235,
     236,    90,    67,   238,   239,    94,    58,    68,    69,   139,
     140,    70,    71,    72,   242,    73,    93,    59,    60,    61,
      62,    63,   179,   180,   181,   182,   183,    95,   268,    96,
     102,    97,   104,   187,   302,   240,   108,   260,   188,   109,
     262,   110,   189,   190,   339,   116,   191,   163,   117,   154,
     287,   118,   120,   155,   156,   316,   348,    98,   121,   157,
     119,   122,   124,   158,   159,    72,   283,   160,    59,    60,
      61,    62,    63,    58,    59,    60,    61,    62,    63,    98,
     123,   126,   128,   129,    59,    60,    61,    62,    63,   163,
      59,    60,    61,    62,    63,   198,   199,   200,   201,   202,
     203,   204,   306,   132,   134,    67,   133,   333,   137,   147,
      68,   150,   151,   153,    70,    71,    72,   152,    73,   340,
     165,    67,   166,   168,   170,   171,    68,    67,   172,   174,
      70,    71,    72,   175,    73,   177,   195,    71,    72,     2,
      73,   176,   185,     3,     4,   186,   193,   194,   -68,     5,
       6,     7,     8,     9,    10,    11,   -64,   -66,   -67,    12,
      13,    14,   198,   199,   200,   201,   202,   203,   204,   205,
     209,   196,   213,   214,   206,   222,   227,   229,    15,    16,
     230,   231,     5,   234,   -65,   237,   251,   144,    17,   243,
     248,   246,   253,   254,   245,   247,   258,   259,   261,   263,
     267,   285,   265,   272,   270,   275,   266,   269,   273,   278,
     281,   282,   289,   293,   288,   296,   294,   295,    72,   298,
     303,   304,   309,   301,   311,   313,   314,   330,   322,   317,
     338,   256,   252,   250,   221,   341,   291,   326,   286,   332,
     324,   349,   208,   343,   328,   337,   238,   350,   331
};

static const yytype_int16 yycheck[] =
{
      79,    58,   116,   153,   209,    37,   241,   127,    68,   111,
     124,    10,   265,    18,    76,    11,   166,    19,    17,   317,
     257,    11,    58,     6,    73,     8,    17,    76,   256,    28,
      29,    30,    31,    32,    64,   329,    66,    28,    29,    30,
      31,    32,    17,   341,     3,    41,   274,   300,   108,   109,
     344,    44,   131,    42,   114,   115,     7,     8,   137,    61,
     297,   314,    98,    17,    69,    70,    65,   169,    69,    70,
     102,    70,    68,   308,    65,    74,    75,    76,    68,    78,
      50,   231,    76,    74,    75,    76,     3,    78,    76,    64,
       6,    66,     8,     9,    17,   209,   301,   157,    71,   219,
       3,    74,     3,    76,     3,    28,    29,    30,    31,    32,
     345,    65,   172,    36,    37,    38,    70,     3,    65,     3,
      74,    75,     3,    70,    78,    17,    76,    74,    75,     8,
     280,    78,    71,    72,    76,   285,   193,     3,   343,    64,
      65,    76,    65,    58,    59,    76,    17,    70,    71,   112,
     113,    74,    75,    76,   211,    78,    44,    28,    29,    30,
      31,    32,    23,    24,    25,    26,    27,    76,   247,    47,
      19,    51,    41,    65,   288,   207,    17,   234,    70,    17,
     237,    44,    74,    75,   334,    17,    78,   301,    17,    60,
     269,    48,     3,    64,    65,   309,   346,    17,     3,    70,
      76,    76,    45,    74,    75,    76,   263,    78,    28,    29,
      30,    31,    32,    17,    28,    29,    30,    31,    32,    17,
      43,    76,    78,    18,    28,    29,    30,    31,    32,   343,
      28,    29,    30,    31,    32,    52,    53,    54,    55,    56,
      57,    58,   299,    76,    44,    65,    76,    64,    76,    76,
      70,    76,    48,    17,    74,    75,    76,     3,    78,   338,
       3,    65,    52,    42,    76,    18,    70,    65,    19,    18,
      74,    75,    76,    18,    78,    19,    74,    75,    76,     0,
      78,    18,    17,     4,     5,    76,    17,    60,    63,    10,
      11,    12,    13,    14,    15,    16,    63,    63,    63,    20,
      21,    22,    52,    53,    54,    55,    56,    57,    58,    59,
      46,    63,     3,     6,    64,    18,    76,    17,    39,    40,
      74,    19,    10,    17,    63,    17,     3,    74,    49,    19,
      62,    18,    65,    19,    76,    76,    18,    18,    65,    17,
       3,    52,    18,    18,    33,    18,    76,    76,    76,    19,
      18,    18,    67,     3,    34,     3,    18,    17,    76,    18,
      34,     3,    19,    48,    76,    18,    18,    76,    19,    35,
      76,   229,   223,   221,   177,    46,   272,    61,   268,    62,
     313,   347,   163,    48,   316,   331,    58,   348,   322
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    81,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    39,    40,    49,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      97,    98,   105,   111,   112,   115,   116,   121,   146,     6,
       8,     9,     6,     8,    76,     7,     8,     3,    42,    44,
      76,     3,     3,     3,     3,     3,    50,     3,    17,    28,
      29,    30,    31,    32,    36,    37,    38,    65,    70,    71,
      74,    75,    76,    78,   109,   117,   118,   119,   122,   124,
     125,   126,   127,   128,   129,   130,    76,    76,     8,    76,
      76,     3,     3,    44,    76,    76,    47,    51,    17,   116,
     125,   127,    19,   123,    41,    73,    76,   120,    17,    17,
      44,   120,    69,    70,    71,    72,    17,    17,    48,    76,
       3,     3,    76,    43,    45,   134,    76,   113,    78,    18,
      18,   124,    76,    76,    44,   127,   127,    76,   123,   126,
     126,   127,   127,    71,    74,   101,   128,    76,   100,   103,
      76,    48,     3,    17,    60,    64,    65,    70,    74,    75,
      78,   110,   124,   128,   136,     3,    52,   134,    42,   120,
      76,    18,    19,   120,    18,    18,    18,    19,    99,    23,
      24,    25,    26,    27,   102,    17,    76,    65,    70,    74,
      75,    78,   110,    17,    60,    74,    63,   138,    52,    53,
      54,    55,    56,    57,    58,    59,    64,   137,   138,    46,
     135,    17,   110,     3,     6,   123,   127,    19,    61,   131,
     132,   100,    18,    17,    64,    66,   104,    76,    94,    17,
      74,    19,   108,   116,    17,    64,    65,    17,    58,    59,
     124,   136,   116,    19,   114,    76,    18,    76,    62,   134,
      99,     3,   101,    65,    19,    96,    94,   110,    18,    18,
     116,    65,   116,    17,   135,    18,    76,     3,   120,    76,
      33,   139,    18,    76,    95,    18,    96,   108,    19,   106,
     107,    18,    18,   116,   114,    52,   131,   120,    34,    67,
     143,   104,    96,     3,    18,    17,     3,   110,    18,    17,
     110,    48,   128,    34,     3,   108,   116,   114,   136,    19,
     140,    76,   145,    18,    18,   135,   128,    35,   141,    11,
      41,    68,    19,   144,   106,   114,    61,   133,   140,   129,
      76,   145,    62,    64,   137,    11,    68,   144,    76,   110,
     120,    46,   142,    48,   129,   136,   137,   135,   110,   133,
     142
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
     112,   113,   113,   114,   114,   114,   115,   116,   116,   116,
     117,   117,   118,   119,   119,   120,   120,   120,   121,   122,
     122,   123,   123,   124,   124,   125,   125,   125,   126,   126,
     126,   126,   127,   127,   127,   127,   128,   128,   129,   129,
     129,   130,   130,   130,   130,   130,   131,   131,   131,   132,
     133,   133,   134,   134,   135,   135,   136,   136,   136,   136,
     136,   136,   136,   137,   137,   137,   137,   137,   137,   137,
     137,   138,   138,   139,   139,   140,   140,   141,   141,   142,
     142,   143,   143,   144,   144,   145,   145,   145,   145,   145,
     145,   146
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
       6,     4,     6,     0,     5,     7,     2,     3,     5,     9,
       4,     6,     1,     1,     1,     0,     2,     1,     1,     2,
       3,     0,     4,     1,     3,     3,     3,     1,     3,     3,
       2,     1,     3,     1,     1,     1,     1,     3,     4,     4,
       4,     1,     1,     1,     1,     1,     0,     4,     1,     8,
       0,     8,     0,     3,     0,     3,     3,     5,     6,     4,
       5,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     3,     0,     5,     0,     3,     0,     5,     0,
       5,     0,     4,     0,     3,     1,     2,     2,     3,     4,
       4,     8
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
#line 1546 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 229 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1554 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 234 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1562 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 240 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1570 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 246 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1578 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 252 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1586 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 258 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1595 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 264 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1603 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 270 "yacc_sql.y"
                                 {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1612 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 277 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1621 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 285 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1631 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 291 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1641 "yacc_sql.tab.c"
    break;

  case 34: /* attrone: ID  */
#line 299 "yacc_sql.y"
        {
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1649 "yacc_sql.tab.c"
    break;

  case 35: /* attr_index: ID  */
#line 305 "yacc_sql.y"
        {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, (yyvsp[0].string));
		CONTEXT->attr_num++;
	}
#line 1658 "yacc_sql.tab.c"
    break;

  case 37: /* attr_index_list: COMMA attr_index attr_index_list  */
#line 313 "yacc_sql.y"
        {

	}
#line 1666 "yacc_sql.tab.c"
    break;

  case 38: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 320 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1675 "yacc_sql.tab.c"
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
#line 1687 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 337 "yacc_sql.y"
                                   {    }
#line 1693 "yacc_sql.tab.c"
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
#line 1705 "yacc_sql.tab.c"
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
#line 1717 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 356 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1723 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 359 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1729 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 360 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 1735 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 361 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1741 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 362 "yacc_sql.y"
              { (yyval.number) = FLOATS; }
#line 1747 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 363 "yacc_sql.y"
             { (yyval.number) = DATES; }
#line 1753 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 366 "yacc_sql.y"
       {
        char *temp=(yyvsp[0].string);
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1762 "yacc_sql.tab.c"
    break;

  case 51: /* nullable: %empty  */
#line 371 "yacc_sql.y"
                  { (yyval.number) = false; }
#line 1768 "yacc_sql.tab.c"
    break;

  case 52: /* nullable: NULLABLE  */
#line 372 "yacc_sql.y"
               { (yyval.number) = true; }
#line 1774 "yacc_sql.tab.c"
    break;

  case 53: /* nullable: NOT NULL_TOKEN  */
#line 373 "yacc_sql.y"
                         { (yyval.number) = false; }
#line 1780 "yacc_sql.tab.c"
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
#line 1796 "yacc_sql.tab.c"
    break;

  case 56: /* v_list: node value value_list RBRACE v_list  */
#line 392 "yacc_sql.y"
    {
    }
#line 1803 "yacc_sql.tab.c"
    break;

  case 57: /* node: COMMA LBRACE  */
#line 397 "yacc_sql.y"
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    }
#line 1814 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 406 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1822 "yacc_sql.tab.c"
    break;

  case 60: /* expr_value: NUMBER  */
#line 411 "yacc_sql.y"
             {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1832 "yacc_sql.tab.c"
    break;

  case 61: /* expr_value: FLOAT  */
#line 416 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1842 "yacc_sql.tab.c"
    break;

  case 62: /* expr_value: SSS  */
#line 421 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1853 "yacc_sql.tab.c"
    break;

  case 63: /* expr_value: NULL_TOKEN  */
#line 427 "yacc_sql.y"
                 {
         value_init_null(&CONTEXT->values[CONTEXT->value_length]);
         (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
         CONTEXT->every_group_count++;
     }
#line 1863 "yacc_sql.tab.c"
    break;

  case 64: /* value: NUMBER  */
#line 433 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1873 "yacc_sql.tab.c"
    break;

  case 65: /* value: MINUS NUMBER  */
#line 438 "yacc_sql.y"
                   {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], -(yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1883 "yacc_sql.tab.c"
    break;

  case 66: /* value: FLOAT  */
#line 443 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
	}
#line 1893 "yacc_sql.tab.c"
    break;

  case 67: /* value: SSS  */
#line 448 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1904 "yacc_sql.tab.c"
    break;

  case 68: /* value: NULL_TOKEN  */
#line 454 "yacc_sql.y"
                 {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1914 "yacc_sql.tab.c"
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
#line 1926 "yacc_sql.tab.c"
    break;

  case 70: /* update: UPDATE ID SET update_attr where SEMICOLON  */
#line 471 "yacc_sql.y"
                                              {
        CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), CONTEXT->conditions[CONTEXT->select_length],
		        CONTEXT->condition_length[CONTEXT->select_length]);
		CONTEXT->condition_length[CONTEXT->select_length] = 0;
    }
#line 1937 "yacc_sql.tab.c"
    break;

  case 71: /* update_attr: ID EQ value update_attr_list  */
#line 478 "yacc_sql.y"
                                 {
		updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1945 "yacc_sql.tab.c"
    break;

  case 72: /* update_attr: ID EQ LBRACE select_unit RBRACE update_attr_list  */
#line 481 "yacc_sql.y"
                                                       {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), (yyvsp[-2]._select));
    }
#line 1953 "yacc_sql.tab.c"
    break;

  case 74: /* update_attr_list: COMMA ID EQ value update_attr_list  */
#line 486 "yacc_sql.y"
                                         {
        updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1961 "yacc_sql.tab.c"
    break;

  case 75: /* update_attr_list: COMMA ID EQ LBRACE select_unit RBRACE update_attr_list  */
#line 489 "yacc_sql.y"
                                                             {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), (yyvsp[-2]._select));
    }
#line 1969 "yacc_sql.tab.c"
    break;

  case 76: /* select: select_unit SEMICOLON  */
#line 494 "yacc_sql.y"
                          {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[1];
    }
#line 1978 "yacc_sql.tab.c"
    break;

  case 77: /* select_unit: select_begin func_attr alias  */
#line 499 "yacc_sql.y"
                                 {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._expr), (yyvsp[0].string));

        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 1991 "yacc_sql.tab.c"
    break;

  case 78: /* select_unit: select_begin func_attr alias FROM ID  */
#line 507 "yacc_sql.y"
                                          {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-3]._expr), (yyvsp[-2].string));
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), NULL);

        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 2005 "yacc_sql.tab.c"
    break;

  case 79: /* select_unit: select_begin select_attr FROM ID alias rel_list where group_by order_by  */
#line 516 "yacc_sql.y"
                                                                              {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length],
                CONTEXT->conditions[CONTEXT->select_length], CONTEXT->condition_length[CONTEXT->select_length]);
        // 临时变量清零
        CONTEXT->condition_length[CONTEXT->select_length] = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length--];
    }
#line 2019 "yacc_sql.tab.c"
    break;

  case 80: /* func_attr: func_type_1 LBRACE primary_expr RBRACE  */
#line 527 "yacc_sql.y"
                                                 {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-3].number), (yyvsp[-1]._expr), NULL);
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2028 "yacc_sql.tab.c"
    break;

  case 81: /* func_attr: func_type_2 LBRACE primary_expr COMMA primary_expr RBRACE  */
#line 531 "yacc_sql.y"
                                                                {
		expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-5].number), (yyvsp[-3]._expr), (yyvsp[-1]._expr));
		(yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
	}
#line 2037 "yacc_sql.tab.c"
    break;

  case 82: /* func_type_1: LENGTH  */
#line 537 "yacc_sql.y"
                  { (yyval.number) = EXPR_LENGTH; }
#line 2043 "yacc_sql.tab.c"
    break;

  case 83: /* func_type_2: ROUND  */
#line 539 "yacc_sql.y"
                 { (yyval.number) = EXPR_ROUND; }
#line 2049 "yacc_sql.tab.c"
    break;

  case 84: /* func_type_2: DATE_FORMAT  */
#line 540 "yacc_sql.y"
                       { (yyval.number) = EXPR_DATE_FORMAT; }
#line 2055 "yacc_sql.tab.c"
    break;

  case 85: /* alias: %empty  */
#line 545 "yacc_sql.y"
    {
        (yyval.string) = NULL;
    }
#line 2063 "yacc_sql.tab.c"
    break;

  case 86: /* alias: AS ID  */
#line 548 "yacc_sql.y"
           {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2071 "yacc_sql.tab.c"
    break;

  case 87: /* alias: ID  */
#line 551 "yacc_sql.y"
        {
        (yyval.string) = (yyvsp[0].string);
    }
#line 2079 "yacc_sql.tab.c"
    break;

  case 88: /* select_begin: SELECT  */
#line 557 "yacc_sql.y"
           { CONTEXT->select_length++; }
#line 2085 "yacc_sql.tab.c"
    break;

  case 89: /* select_attr: STAR select_attr_list  */
#line 560 "yacc_sql.y"
                           {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], &attr);
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], &CONTEXT->exprs[CONTEXT->expr_length++], NULL);
    }
#line 2096 "yacc_sql.tab.c"
    break;

  case 90: /* select_attr: expr alias select_attr_list  */
#line 566 "yacc_sql.y"
                                  {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2104 "yacc_sql.tab.c"
    break;

  case 92: /* select_attr_list: COMMA expr alias select_attr_list  */
#line 571 "yacc_sql.y"
                                        {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._expr), (yyvsp[-1].string));
    }
#line 2112 "yacc_sql.tab.c"
    break;

  case 93: /* expr: add_expr  */
#line 575 "yacc_sql.y"
             {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2120 "yacc_sql.tab.c"
    break;

  case 94: /* expr: LBRACE select_unit RBRACE  */
#line 578 "yacc_sql.y"
                                {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2129 "yacc_sql.tab.c"
    break;

  case 95: /* add_expr: add_expr PLUS mul_expr  */
#line 583 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_PLUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2138 "yacc_sql.tab.c"
    break;

  case 96: /* add_expr: add_expr MINUS mul_expr  */
#line 587 "yacc_sql.y"
                              {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MINUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2147 "yacc_sql.tab.c"
    break;

  case 97: /* add_expr: mul_expr  */
#line 591 "yacc_sql.y"
               {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2155 "yacc_sql.tab.c"
    break;

  case 98: /* mul_expr: mul_expr STAR primary_expr  */
#line 595 "yacc_sql.y"
                               {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MULTIPLY, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2164 "yacc_sql.tab.c"
    break;

  case 99: /* mul_expr: mul_expr DIVIDE primary_expr  */
#line 599 "yacc_sql.y"
                                   {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_DIVIDE, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2173 "yacc_sql.tab.c"
    break;

  case 100: /* mul_expr: MINUS primary_expr  */
#line 603 "yacc_sql.y"
                         {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_NEGATIVE, (yyvsp[0]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2182 "yacc_sql.tab.c"
    break;

  case 101: /* mul_expr: primary_expr  */
#line 607 "yacc_sql.y"
                   {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2190 "yacc_sql.tab.c"
    break;

  case 102: /* primary_expr: LBRACE add_expr RBRACE  */
#line 611 "yacc_sql.y"
                           {
        (yyval._expr) = (yyvsp[-1]._expr);
    }
#line 2198 "yacc_sql.tab.c"
    break;

  case 103: /* primary_expr: attr  */
#line 614 "yacc_sql.y"
           {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2207 "yacc_sql.tab.c"
    break;

  case 104: /* primary_expr: aggr_attr  */
#line 618 "yacc_sql.y"
                {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2216 "yacc_sql.tab.c"
    break;

  case 105: /* primary_expr: expr_value  */
#line 622 "yacc_sql.y"
                 {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2225 "yacc_sql.tab.c"
    break;

  case 106: /* attr: ID  */
#line 629 "yacc_sql.y"
       {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2235 "yacc_sql.tab.c"
    break;

  case 107: /* attr: ID DOT ID  */
#line 634 "yacc_sql.y"
                {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2245 "yacc_sql.tab.c"
    break;

  case 108: /* aggr_attr: aggr_type LBRACE attr RBRACE  */
#line 640 "yacc_sql.y"
                                   {
        relation_attr_aggr((yyvsp[-1]._attr), (yyvsp[-3].number));
        (yyval._attr) = (yyvsp[-1]._attr);
    }
#line 2254 "yacc_sql.tab.c"
    break;

  case 109: /* aggr_attr: aggr_type LBRACE STAR RBRACE  */
#line 644 "yacc_sql.y"
                                   {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2265 "yacc_sql.tab.c"
    break;

  case 110: /* aggr_attr: aggr_type LBRACE number RBRACE  */
#line 650 "yacc_sql.y"
                                     {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        if ((yyvsp[-1].number) != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2279 "yacc_sql.tab.c"
    break;

  case 111: /* aggr_type: MAX  */
#line 660 "yacc_sql.y"
          { (yyval.number) = AGGR_MAX; }
#line 2285 "yacc_sql.tab.c"
    break;

  case 112: /* aggr_type: MIN  */
#line 661 "yacc_sql.y"
          { (yyval.number) = AGGR_MIN; }
#line 2291 "yacc_sql.tab.c"
    break;

  case 113: /* aggr_type: COUNT  */
#line 662 "yacc_sql.y"
            { (yyval.number) = AGGR_COUNT; }
#line 2297 "yacc_sql.tab.c"
    break;

  case 114: /* aggr_type: AVG  */
#line 663 "yacc_sql.y"
          { (yyval.number) = AGGR_AVG; }
#line 2303 "yacc_sql.tab.c"
    break;

  case 115: /* aggr_type: SUM  */
#line 664 "yacc_sql.y"
          { (yyval.number) = AGGR_SUM; }
#line 2309 "yacc_sql.tab.c"
    break;

  case 117: /* rel_list: COMMA ID alias rel_list  */
#line 669 "yacc_sql.y"
                              {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2].string), (yyvsp[-1].string));
    }
#line 2317 "yacc_sql.tab.c"
    break;

  case 118: /* rel_list: join  */
#line 672 "yacc_sql.y"
           {
    }
#line 2324 "yacc_sql.tab.c"
    break;

  case 119: /* join: INNER JOIN ID alias ON condition condition_list join_list  */
#line 676 "yacc_sql.y"
                                                                  {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2332 "yacc_sql.tab.c"
    break;

  case 121: /* join_list: INNER JOIN ID alias ON condition condition_list join_list  */
#line 681 "yacc_sql.y"
                                                                     {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-5].string), (yyvsp[-4].string));
	}
#line 2340 "yacc_sql.tab.c"
    break;

  case 123: /* where: WHERE condition condition_list  */
#line 687 "yacc_sql.y"
                                     {}
#line 2346 "yacc_sql.tab.c"
    break;

  case 125: /* condition_list: AND condition condition_list  */
#line 691 "yacc_sql.y"
                                   {}
#line 2352 "yacc_sql.tab.c"
    break;

  case 126: /* condition: expr comOp expr  */
#line 695 "yacc_sql.y"
                    {
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]++],
                (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
    }
#line 2361 "yacc_sql.tab.c"
    break;

  case 127: /* condition: expr IN LBRACE select_unit RBRACE  */
#line 699 "yacc_sql.y"
                                         {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                IN_OP, (yyvsp[-4]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2371 "yacc_sql.tab.c"
    break;

  case 128: /* condition: expr NOT IN LBRACE select_unit RBRACE  */
#line 704 "yacc_sql.y"
                                            {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                NOT_IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2381 "yacc_sql.tab.c"
    break;

  case 129: /* condition: EXISTS LBRACE select_unit RBRACE  */
#line 709 "yacc_sql.y"
                                       {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2391 "yacc_sql.tab.c"
    break;

  case 130: /* condition: NOT EXISTS LBRACE select_unit RBRACE  */
#line 714 "yacc_sql.y"
                                           {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                NOT_EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 2401 "yacc_sql.tab.c"
    break;

  case 131: /* condition: value null_comOp  */
#line 719 "yacc_sql.y"
                           {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
#line 2416 "yacc_sql.tab.c"
    break;

  case 132: /* condition: attr null_comOp  */
#line 729 "yacc_sql.y"
                          {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._attr));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&CONTEXT->conditions[CONTEXT->select_length][CONTEXT->condition_length[CONTEXT->select_length]],
                (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
	}
#line 2431 "yacc_sql.tab.c"
    break;

  case 133: /* comOp: EQ  */
#line 741 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2437 "yacc_sql.tab.c"
    break;

  case 134: /* comOp: LT  */
#line 742 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2443 "yacc_sql.tab.c"
    break;

  case 135: /* comOp: GT  */
#line 743 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2449 "yacc_sql.tab.c"
    break;

  case 136: /* comOp: LE  */
#line 744 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2455 "yacc_sql.tab.c"
    break;

  case 137: /* comOp: GE  */
#line 745 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2461 "yacc_sql.tab.c"
    break;

  case 138: /* comOp: NE  */
#line 746 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2467 "yacc_sql.tab.c"
    break;

  case 139: /* comOp: LIKE  */
#line 747 "yacc_sql.y"
           { (yyval.number) = LIKE_OP; }
#line 2473 "yacc_sql.tab.c"
    break;

  case 140: /* comOp: NOT LIKE  */
#line 748 "yacc_sql.y"
               { (yyval.number) = NOT_LIKE_OP; }
#line 2479 "yacc_sql.tab.c"
    break;

  case 141: /* null_comOp: IS NULL_TOKEN  */
#line 751 "yacc_sql.y"
                    { (yyval.number) = IS_NULL; }
#line 2485 "yacc_sql.tab.c"
    break;

  case 142: /* null_comOp: IS NOT NULL_TOKEN  */
#line 752 "yacc_sql.y"
                        { (yyval.number) = IS_NOT_NULL; }
#line 2491 "yacc_sql.tab.c"
    break;

  case 144: /* group_by: GROUP BY attr group_list having  */
#line 757 "yacc_sql.y"
                                      {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._attr));
    }
#line 2499 "yacc_sql.tab.c"
    break;

  case 146: /* group_list: COMMA attr group_list  */
#line 762 "yacc_sql.y"
                            {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
    }
#line 2507 "yacc_sql.tab.c"
    break;

  case 148: /* having: HAVING aggr_attr comOp value having_list  */
#line 767 "yacc_sql.y"
                                               {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2520 "yacc_sql.tab.c"
    break;

  case 150: /* having_list: AND aggr_attr comOp value having_list  */
#line 777 "yacc_sql.y"
                                            {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2533 "yacc_sql.tab.c"
    break;

  case 152: /* order_by: ORDER BY order order_list  */
#line 788 "yacc_sql.y"
                                {
    }
#line 2540 "yacc_sql.tab.c"
    break;

  case 154: /* order_list: COMMA order order_list  */
#line 793 "yacc_sql.y"
                            {
    }
#line 2547 "yacc_sql.tab.c"
    break;

  case 155: /* order: ID  */
#line 797 "yacc_sql.y"
      {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, "");
    }
#line 2555 "yacc_sql.tab.c"
    break;

  case 156: /* order: ID DESC  */
#line 800 "yacc_sql.y"
             {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, "");
    }
#line 2563 "yacc_sql.tab.c"
    break;

  case 157: /* order: ID ASC  */
#line 803 "yacc_sql.y"
            {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, "");
    }
#line 2571 "yacc_sql.tab.c"
    break;

  case 158: /* order: ID DOT ID  */
#line 806 "yacc_sql.y"
               {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, (yyvsp[-2].string));
    }
#line 2579 "yacc_sql.tab.c"
    break;

  case 159: /* order: ID DOT ID DESC  */
#line 809 "yacc_sql.y"
                    {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, (yyvsp[-3].string));
    }
#line 2587 "yacc_sql.tab.c"
    break;

  case 160: /* order: ID DOT ID ASC  */
#line 812 "yacc_sql.y"
                   {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, (yyvsp[-3].string));
    }
#line 2595 "yacc_sql.tab.c"
    break;

  case 161: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 818 "yacc_sql.y"
                                                 {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
    }
#line 2604 "yacc_sql.tab.c"
    break;


#line 2608 "yacc_sql.tab.c"

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

#line 823 "yacc_sql.y"

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
