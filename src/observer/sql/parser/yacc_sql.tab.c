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
  size_t condition_length;
  size_t value_length;
  size_t attr_length;
  size_t expr_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
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


#line 143 "yacc_sql.tab.c"

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
  YYSYMBOL_NUMBER = 70,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 71,                     /* FLOAT  */
  YYSYMBOL_ID = 72,                        /* ID  */
  YYSYMBOL_PATH = 73,                      /* PATH  */
  YYSYMBOL_SSS = 74,                       /* SSS  */
  YYSYMBOL_STRING_V = 75,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_commands = 77,                  /* commands  */
  YYSYMBOL_command = 78,                   /* command  */
  YYSYMBOL_exit = 79,                      /* exit  */
  YYSYMBOL_help = 80,                      /* help  */
  YYSYMBOL_sync = 81,                      /* sync  */
  YYSYMBOL_begin = 82,                     /* begin  */
  YYSYMBOL_commit = 83,                    /* commit  */
  YYSYMBOL_rollback = 84,                  /* rollback  */
  YYSYMBOL_drop_table = 85,                /* drop_table  */
  YYSYMBOL_show_tables = 86,               /* show_tables  */
  YYSYMBOL_show_index = 87,                /* show_index  */
  YYSYMBOL_desc_table = 88,                /* desc_table  */
  YYSYMBOL_create_index = 89,              /* create_index  */
  YYSYMBOL_attrone = 90,                   /* attrone  */
  YYSYMBOL_attr_index = 91,                /* attr_index  */
  YYSYMBOL_attr_index_list = 92,           /* attr_index_list  */
  YYSYMBOL_drop_index = 93,                /* drop_index  */
  YYSYMBOL_create_table = 94,              /* create_table  */
  YYSYMBOL_attr_def_list = 95,             /* attr_def_list  */
  YYSYMBOL_attr_def = 96,                  /* attr_def  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_ID_get = 99,                    /* ID_get  */
  YYSYMBOL_nullable = 100,                 /* nullable  */
  YYSYMBOL_insert = 101,                   /* insert  */
  YYSYMBOL_v_list = 102,                   /* v_list  */
  YYSYMBOL_node = 103,                     /* node  */
  YYSYMBOL_value_list = 104,               /* value_list  */
  YYSYMBOL_expr_value = 105,               /* expr_value  */
  YYSYMBOL_value = 106,                    /* value  */
  YYSYMBOL_delete = 107,                   /* delete  */
  YYSYMBOL_update = 108,                   /* update  */
  YYSYMBOL_update_attr = 109,              /* update_attr  */
  YYSYMBOL_update_attr_list = 110,         /* update_attr_list  */
  YYSYMBOL_select = 111,                   /* select  */
  YYSYMBOL_select_unit = 112,              /* select_unit  */
  YYSYMBOL_select_attr = 113,              /* select_attr  */
  YYSYMBOL_select_attr_list = 114,         /* select_attr_list  */
  YYSYMBOL_expr = 115,                     /* expr  */
  YYSYMBOL_add_expr = 116,                 /* add_expr  */
  YYSYMBOL_mul_expr = 117,                 /* mul_expr  */
  YYSYMBOL_primary_expr = 118,             /* primary_expr  */
  YYSYMBOL_attr = 119,                     /* attr  */
  YYSYMBOL_aggr_attr = 120,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 121,                /* aggr_type  */
  YYSYMBOL_rel_list = 122,                 /* rel_list  */
  YYSYMBOL_join = 123,                     /* join  */
  YYSYMBOL_join_list = 124,                /* join_list  */
  YYSYMBOL_where = 125,                    /* where  */
  YYSYMBOL_condition_list = 126,           /* condition_list  */
  YYSYMBOL_condition = 127,                /* condition  */
  YYSYMBOL_comOp = 128,                    /* comOp  */
  YYSYMBOL_null_comOp = 129,               /* null_comOp  */
  YYSYMBOL_group_by = 130,                 /* group_by  */
  YYSYMBOL_group_list = 131,               /* group_list  */
  YYSYMBOL_having = 132,                   /* having  */
  YYSYMBOL_having_list = 133,              /* having_list  */
  YYSYMBOL_order_by = 134,                 /* order_by  */
  YYSYMBOL_order_list = 135,               /* order_list  */
  YYSYMBOL_order = 136,                    /* order  */
  YYSYMBOL_load_data = 137                 /* load_data  */
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
#define YYLAST   358

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  321

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
      75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   187,   187,   189,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   214,   219,   224,   230,   236,   242,   248,   254,
     260,   267,   274,   280,   288,   294,   300,   302,   309,   316,
     325,   327,   331,   338,   346,   349,   350,   351,   352,   353,
     356,   361,   362,   363,   367,   380,   381,   386,   394,   396,
     401,   406,   411,   418,   423,   428,   433,   439,   446,   456,
     462,   465,   468,   470,   473,   478,   483,   494,   500,   503,
     505,   509,   512,   517,   521,   525,   529,   533,   537,   541,
     545,   548,   552,   556,   562,   567,   573,   577,   583,   593,
     594,   595,   596,   597,   600,   602,   605,   609,   612,   614,
     618,   620,   624,   626,   632,   637,   643,   649,   655,   661,
     672,   685,   686,   687,   688,   689,   690,   691,   692,   695,
     696,   699,   701,   704,   706,   709,   711,   719,   721,   730,
     732,   735,   737,   741,   744,   747,   750,   753,   756,   762
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
  "DIVIDE", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STRING_V", "$accept",
  "commands", "command", "exit", "help", "sync", "begin", "commit",
  "rollback", "drop_table", "show_tables", "show_index", "desc_table",
  "create_index", "attrone", "attr_index", "attr_index_list", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "nullable", "insert", "v_list", "node", "value_list", "expr_value",
  "value", "delete", "update", "update_attr", "update_attr_list", "select",
  "select_unit", "select_attr", "select_attr_list", "expr", "add_expr",
  "mul_expr", "primary_expr", "attr", "aggr_attr", "aggr_type", "rel_list",
  "join", "join_list", "where", "condition_list", "condition", "comOp",
  "null_comOp", "group_by", "group_list", "having", "having_list",
  "order_by", "order_list", "order", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-269)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-67)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -269,   228,  -269,    88,    93,    75,   -19,   111,    24,    30,
      36,     8,    90,   106,   113,   117,   130,    39,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,  -269,  -269,   141,  -269,    53,    55,
     140,    79,    91,     4,  -269,  -269,  -269,  -269,  -269,    11,
     150,  -269,  -269,   137,  -269,  -269,   144,   150,    57,    67,
    -269,  -269,  -269,   170,   187,   194,   158,  -269,   128,   131,
     160,  -269,  -269,  -269,  -269,  -269,   157,  -269,   190,   163,
     142,   208,   209,    83,   206,    -8,  -269,   100,  -269,   154,
     155,  -269,    83,    83,    11,    11,    19,  -269,  -269,   159,
     189,   192,   164,   156,   173,   174,   214,  -269,  -269,  -269,
    -269,   150,  -269,    12,    67,    67,  -269,  -269,   229,  -269,
     242,   243,   232,   245,    -6,   270,   226,   192,   237,  -269,
     258,   135,   262,   210,  -269,   211,   221,   192,  -269,  -269,
    -269,  -269,  -269,   124,   264,   227,  -269,   151,   225,   230,
     231,   233,   202,   233,   244,  -269,   122,   283,   282,   173,
     271,  -269,  -269,  -269,  -269,  -269,    27,   220,   277,    12,
     223,   263,   234,  -269,  -269,  -269,   278,   288,   284,   239,
      76,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,    -4,
     247,   100,  -269,    -6,  -269,   288,   281,  -269,   235,   258,
     300,   236,   246,  -269,  -269,  -269,   286,   220,  -269,   265,
     275,   248,  -269,   124,   293,   295,   288,   252,  -269,   288,
     298,  -269,  -269,   244,   299,   249,  -269,   313,  -269,  -269,
     301,  -269,   250,   302,   286,    -6,   251,   290,  -269,   278,
     306,  -269,   308,  -269,   309,   288,  -269,   281,   269,  -269,
      47,  -269,   286,   325,   311,   244,   312,   260,  -269,   316,
     327,   124,  -269,  -269,   317,  -269,   139,  -269,  -269,  -269,
     331,   279,   251,   303,     7,   320,  -269,  -269,   278,  -269,
     288,   281,  -269,   285,  -269,   312,   188,  -269,  -269,   268,
    -269,   260,  -269,   318,   323,  -269,   273,  -269,   217,    -2,
     320,   306,   281,   297,   124,  -269,  -269,  -269,  -269,  -269,
      -6,   304,   244,   188,  -269,   279,   217,  -269,   124,   304,
    -269
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,     0,    19,     0,     0,
       0,     0,     0,     0,    99,   100,   101,   102,   103,     0,
      79,    60,    61,    94,    62,    93,     0,    79,    81,    85,
      89,    91,    92,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    75,     0,     0,
       0,     0,     0,     0,     0,     0,    88,     0,    77,     0,
       0,    78,     0,     0,     0,     0,     0,    31,    29,     0,
       0,   110,     0,     0,     0,     0,     0,    28,    38,    82,
      90,    79,    95,   104,    83,    84,    86,    87,     0,    44,
       0,     0,     0,     0,     0,     0,     0,   110,     0,    50,
      40,     0,     0,     0,    80,     0,     0,   110,   106,    97,
      98,    96,    30,     0,     0,     0,    67,     0,    60,    61,
      62,     0,     0,    91,   112,    68,     0,     0,     0,     0,
       0,    45,    46,    47,    48,    49,    51,     0,     0,   104,
       0,   131,     0,    63,    65,    66,    58,     0,     0,    60,
       0,   119,   121,   122,   123,   124,   125,   126,   127,     0,
       0,     0,   120,     0,   111,     0,    72,    69,     0,    40,
       0,     0,     0,    52,    43,    34,    36,     0,   105,     0,
       0,   139,    64,     0,     0,     0,     0,     0,   129,     0,
       0,   128,   114,   112,     0,     0,    70,     0,    41,    39,
       0,    53,     0,     0,    36,     0,     0,     0,    76,    58,
      55,   117,     0,   130,     0,     0,   113,    72,     0,   149,
      51,    35,    36,     0,     0,   112,   133,     0,    59,     0,
       0,     0,   118,   115,     0,    71,     0,    42,    37,    33,
       0,   108,     0,   135,   143,   141,    57,    54,    58,   116,
       0,    72,    32,     0,   107,   133,     0,   132,   144,     0,
     145,     0,   140,     0,     0,    73,     0,   134,     0,   146,
     141,    55,    72,     0,     0,   147,   148,   142,    56,    74,
       0,   137,   112,     0,   136,   108,     0,   109,     0,   137,
     138
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,  -269,
    -269,  -269,  -269,  -269,   136,  -269,  -215,  -269,  -269,   147,
     191,   148,  -269,  -269,    98,  -269,    50,  -269,  -224,  -269,
    -140,  -269,  -269,  -269,  -235,  -269,   -43,  -269,   -49,    -3,
     -23,    73,   -45,   -95,  -234,  -269,   183,  -269,    38,  -120,
    -217,  -188,  -268,   201,  -269,    70,  -269,    37,  -269,    58,
      66,  -269
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   206,   252,   233,    30,    31,   160,
     130,   120,   166,   131,   204,    32,   260,   261,   214,    55,
     151,    33,    34,   127,   226,    35,    36,    56,    88,   152,
      58,    59,    60,    61,    62,    63,   137,   138,   284,   125,
     194,   154,   191,   181,   211,   273,   287,   314,   238,   292,
     275,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      84,   121,    57,   176,    86,   223,   246,   157,    91,   305,
     110,    43,   265,   219,     5,   258,   196,   171,   288,   254,
      85,    83,    44,    45,    46,    47,    48,    67,    83,   153,
     304,   135,    44,    45,    46,    47,    48,   268,   271,    44,
      45,    46,    47,    48,   201,   289,   295,   255,   318,   116,
     117,   144,   298,    64,   293,   145,   146,   220,    92,    93,
      85,   147,   134,   306,   148,   149,    53,   309,   150,    68,
     136,    49,   290,   239,    51,    52,    53,    69,    54,   316,
      70,    51,    52,    53,   111,    54,    76,   118,   202,   119,
     203,    53,    43,    71,    38,   315,    39,    40,   153,    41,
      83,    42,    86,    44,    45,    46,    47,    48,   202,    72,
     203,    44,    45,    46,    47,    48,    73,    43,    65,    66,
      74,   278,   312,    92,    93,    78,   281,    79,    44,    45,
      46,    47,    48,    75,   215,    94,    95,   217,   218,   195,
     153,   256,    49,    50,    77,    51,    52,    53,    80,    54,
      49,    81,   224,    51,    52,    53,   280,    54,   161,   162,
     163,   164,   165,    82,   311,   114,   115,    49,    83,    87,
      51,    52,    53,   242,    54,    89,   244,   285,   319,    44,
      45,    46,    47,    48,   146,    90,   146,    96,   222,   172,
      97,   172,   173,   174,   173,   174,   175,    98,   175,    99,
     100,   146,   264,   101,   102,   103,   172,   104,   105,   173,
     174,   107,   108,   175,   106,   153,    44,    45,    46,    47,
      48,   179,    52,    53,   109,    54,   112,   113,     2,   123,
     128,   122,     3,     4,   124,   142,   126,   294,     5,     6,
       7,     8,     9,    10,    11,   129,   132,   139,    12,    13,
      14,   182,   183,   184,   185,   186,   187,   188,   189,   133,
     140,   141,   143,   190,    15,    16,   182,   183,   184,   185,
     186,   187,   188,   155,    17,   156,   158,   159,   190,   167,
     170,   177,   168,   169,   178,   -63,   197,   193,   198,   200,
     -65,   -66,   205,   180,   207,   209,   210,   213,     5,   -64,
     225,   216,   221,   229,   212,   232,   119,   227,   231,   236,
     235,   240,   237,   241,   243,   245,   249,   247,   266,   250,
     253,   248,   251,    53,   257,   259,   262,   263,   269,   270,
     277,   272,   274,   276,   282,   279,   301,   283,   286,   291,
     299,   302,   310,   234,   296,   303,   228,   313,   267,   230,
     199,   308,   208,   317,   192,   297,   320,   300,   307
};

static const yytype_int16 yycheck[] =
{
      43,    96,     5,   143,    49,   193,   223,   127,    57,    11,
      18,    17,   247,    17,    10,   239,   156,   137,    11,   234,
      43,    17,    28,    29,    30,    31,    32,     3,    17,   124,
     298,    19,    28,    29,    30,    31,    32,   252,   255,    28,
      29,    30,    31,    32,    17,    38,   281,   235,   316,    94,
      95,    57,   286,    72,   278,    61,    62,    61,    66,    67,
      83,    67,   111,    65,    70,    71,    72,   302,    74,    39,
      58,    67,    65,   213,    70,    71,    72,    41,    74,   313,
      72,    70,    71,    72,    87,    74,    47,    68,    61,    70,
      63,    72,    17,     3,     6,   312,     8,     9,   193,     6,
      17,     8,   147,    28,    29,    30,    31,    32,    61,     3,
      63,    28,    29,    30,    31,    32,     3,    17,     7,     8,
       3,   261,   310,    66,    67,    72,   266,    72,    28,    29,
      30,    31,    32,     3,   177,    68,    69,    61,    62,    17,
     235,   236,    67,    68,     3,    70,    71,    72,     8,    74,
      67,    72,   195,    70,    71,    72,    17,    74,    23,    24,
      25,    26,    27,    72,   304,    92,    93,    67,    17,    19,
      70,    71,    72,   216,    74,    38,   219,   272,   318,    28,
      29,    30,    31,    32,    62,    41,    62,    17,   191,    67,
       3,    67,    70,    71,    70,    71,    74,     3,    74,    41,
      72,    62,   245,    72,    44,    48,    67,    17,    45,    70,
      71,     3,     3,    74,    72,   310,    28,    29,    30,    31,
      32,    70,    71,    72,    18,    74,    72,    72,     0,    40,
      74,    72,     4,     5,    42,     3,    72,   280,    10,    11,
      12,    13,    14,    15,    16,    72,    72,    18,    20,    21,
      22,    49,    50,    51,    52,    53,    54,    55,    56,    45,
      18,    18,    17,    61,    36,    37,    49,    50,    51,    52,
      53,    54,    55,     3,    46,    49,    39,    19,    61,    17,
      59,    17,    72,    72,    57,    60,     3,    43,     6,    18,
      60,    60,    72,    60,    17,    72,    33,    19,    10,    60,
      19,    17,    55,     3,    70,    19,    70,    72,    62,    34,
      45,    18,    64,    18,    62,    17,     3,    18,    49,    18,
      18,    72,    72,    72,    34,    19,    18,    18,     3,    18,
       3,    19,    72,    17,     3,    18,    18,    58,    35,    19,
      72,    18,    45,   207,    59,    72,   199,    43,   250,   201,
     159,   301,   169,   315,   153,   285,   319,   291,   300
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    77,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    36,    37,    46,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      93,    94,   101,   107,   108,   111,   112,   137,     6,     8,
       9,     6,     8,    17,    28,    29,    30,    31,    32,    67,
      68,    70,    71,    72,    74,   105,   113,   115,   116,   117,
     118,   119,   120,   121,    72,     7,     8,     3,    39,    41,
      72,     3,     3,     3,     3,     3,    47,     3,    72,    72,
       8,    72,    72,    17,   112,   116,   118,    19,   114,    38,
      41,   114,    66,    67,    68,    69,    17,     3,     3,    41,
      72,    72,    44,    48,    17,    45,    72,     3,     3,    18,
      18,   115,    72,    72,   117,   117,   118,   118,    68,    70,
      97,   119,    72,    40,    42,   125,    72,   109,    74,    72,
      96,    99,    72,    45,   114,    19,    58,   122,   123,    18,
      18,    18,     3,    17,    57,    61,    62,    67,    70,    71,
      74,   106,   115,   119,   127,     3,    49,   125,    39,    19,
      95,    23,    24,    25,    26,    27,    98,    17,    72,    72,
      59,   125,    67,    70,    71,    74,   106,    17,    57,    70,
      60,   129,    49,    50,    51,    52,    53,    54,    55,    56,
      61,   128,   129,    43,   126,    17,   106,     3,     6,    96,
      18,    17,    61,    63,   100,    72,    90,    17,   122,    72,
      33,   130,    70,    19,   104,   112,    17,    61,    62,    17,
      61,    55,   115,   127,   112,    19,   110,    72,    95,     3,
      97,    62,    19,    92,    90,    45,    34,    64,   134,   106,
      18,    18,   112,    62,   112,    17,   126,    18,    72,     3,
      18,    72,    91,    18,    92,   127,   119,    34,   104,    19,
     102,   103,    18,    18,   112,   110,    49,   100,    92,     3,
      18,   126,    19,   131,    72,   136,    17,     3,   106,    18,
      17,   106,     3,    58,   124,   119,    35,   132,    11,    38,
      65,    19,   135,   104,   112,   110,    59,   131,   120,    72,
     136,    18,    18,    72,   128,    11,    65,   135,   102,   110,
      45,   106,   127,    43,   133,   126,   120,   124,   128,   106,
     133
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    77,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    89,    90,    91,    92,    92,    93,    94,
      95,    95,    96,    96,    97,    98,    98,    98,    98,    98,
      99,   100,   100,   100,   101,   102,   102,   103,   104,   104,
     105,   105,   105,   106,   106,   106,   106,   106,   107,   108,
     109,   109,   110,   110,   110,   111,   112,   113,   113,   114,
     114,   115,   115,   116,   116,   116,   117,   117,   117,   117,
     118,   118,   118,   118,   119,   119,   120,   120,   120,   121,
     121,   121,   121,   121,   122,   122,   122,   123,   124,   124,
     125,   125,   126,   126,   127,   127,   127,   127,   127,   127,
     127,   128,   128,   128,   128,   128,   128,   128,   128,   129,
     129,   130,   130,   131,   131,   132,   132,   133,   133,   134,
     134,   135,   135,   136,   136,   136,   136,   136,   136,   137
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
       1,     1,     1,     1,     2,     1,     1,     1,     5,     6,
       4,     6,     0,     5,     7,     2,     8,     2,     2,     0,
       3,     1,     3,     3,     3,     1,     3,     3,     2,     1,
       3,     1,     1,     1,     1,     3,     4,     4,     4,     1,
       1,     1,     1,     1,     0,     3,     1,     7,     0,     7,
       0,     3,     0,     3,     3,     5,     6,     4,     5,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     0,     5,     0,     3,     0,     5,     0,     5,     0,
       4,     0,     3,     1,     2,     2,     3,     4,     4,     8
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
#line 214 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1510 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 219 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1518 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 224 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1526 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 230 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1534 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 236 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1542 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 242 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1550 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 248 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1559 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 254 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1567 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 260 "yacc_sql.y"
                                 {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1576 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 267 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1585 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 275 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1595 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 281 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1605 "yacc_sql.tab.c"
    break;

  case 34: /* attrone: ID  */
#line 289 "yacc_sql.y"
        {
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1613 "yacc_sql.tab.c"
    break;

  case 35: /* attr_index: ID  */
#line 295 "yacc_sql.y"
        {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, (yyvsp[0].string));
		CONTEXT->attr_num++;
	}
#line 1622 "yacc_sql.tab.c"
    break;

  case 37: /* attr_index_list: COMMA attr_index attr_index_list  */
#line 303 "yacc_sql.y"
        {

	}
#line 1630 "yacc_sql.tab.c"
    break;

  case 38: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 310 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1639 "yacc_sql.tab.c"
    break;

  case 39: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 317 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1651 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 327 "yacc_sql.y"
                                   {    }
#line 1657 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 331 "yacc_sql.y"
                                              {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
    }
#line 1669 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type nullable  */
#line 338 "yacc_sql.y"
                           {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4 + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
	}
#line 1681 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 346 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1687 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 349 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1693 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 350 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 1699 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 351 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1705 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 352 "yacc_sql.y"
              { (yyval.number) = FLOATS; }
#line 1711 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 353 "yacc_sql.y"
             { (yyval.number) = DATES; }
#line 1717 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 356 "yacc_sql.y"
       {
        char *temp=(yyvsp[0].string);
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1726 "yacc_sql.tab.c"
    break;

  case 51: /* nullable: %empty  */
#line 361 "yacc_sql.y"
                  { (yyval.number) = false; }
#line 1732 "yacc_sql.tab.c"
    break;

  case 52: /* nullable: NULLABLE  */
#line 362 "yacc_sql.y"
               { (yyval.number) = true; }
#line 1738 "yacc_sql.tab.c"
    break;

  case 53: /* nullable: NOT NULL_TOKEN  */
#line 363 "yacc_sql.y"
                         { (yyval.number) = false; }
#line 1744 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE v_list SEMICOLON  */
#line 368 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_INSERT;
		CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
		CONTEXT->every_group_count=0;
        CONTEXT->group_num = CONTEXT->group_num + 1;

		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->insert_groups, CONTEXT->group_num);

		//临时变量清零
		CONTEXT->value_length=0;
    }
#line 1760 "yacc_sql.tab.c"
    break;

  case 56: /* v_list: node value value_list RBRACE v_list  */
#line 382 "yacc_sql.y"
    {
    }
#line 1767 "yacc_sql.tab.c"
    break;

  case 57: /* node: COMMA LBRACE  */
#line 387 "yacc_sql.y"
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    }
#line 1778 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 396 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1786 "yacc_sql.tab.c"
    break;

  case 60: /* expr_value: NUMBER  */
#line 401 "yacc_sql.y"
             {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1796 "yacc_sql.tab.c"
    break;

  case 61: /* expr_value: FLOAT  */
#line 406 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1806 "yacc_sql.tab.c"
    break;

  case 62: /* expr_value: SSS  */
#line 411 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1817 "yacc_sql.tab.c"
    break;

  case 63: /* value: NUMBER  */
#line 418 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1827 "yacc_sql.tab.c"
    break;

  case 64: /* value: MINUS NUMBER  */
#line 423 "yacc_sql.y"
                   {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length], -(yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1837 "yacc_sql.tab.c"
    break;

  case 65: /* value: FLOAT  */
#line 428 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
	}
#line 1847 "yacc_sql.tab.c"
    break;

  case 66: /* value: SSS  */
#line 433 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1858 "yacc_sql.tab.c"
    break;

  case 67: /* value: NULL_TOKEN  */
#line 439 "yacc_sql.y"
                 {
        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length++];
        CONTEXT->every_group_count++;
    }
#line 1868 "yacc_sql.tab.c"
    break;

  case 68: /* delete: DELETE FROM ID where SEMICOLON  */
#line 447 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1879 "yacc_sql.tab.c"
    break;

  case 69: /* update: UPDATE ID SET update_attr where SEMICOLON  */
#line 456 "yacc_sql.y"
                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
    }
#line 1889 "yacc_sql.tab.c"
    break;

  case 70: /* update_attr: ID EQ value update_attr_list  */
#line 462 "yacc_sql.y"
                                 {
		updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1897 "yacc_sql.tab.c"
    break;

  case 71: /* update_attr: ID EQ LBRACE select_unit RBRACE update_attr_list  */
#line 465 "yacc_sql.y"
                                                       {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), (yyvsp[-2]._select));
    }
#line 1905 "yacc_sql.tab.c"
    break;

  case 73: /* update_attr_list: COMMA ID EQ value update_attr_list  */
#line 470 "yacc_sql.y"
                                         {
        updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1913 "yacc_sql.tab.c"
    break;

  case 74: /* update_attr_list: COMMA ID EQ LBRACE select_unit RBRACE update_attr_list  */
#line 473 "yacc_sql.y"
                                                             {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), (yyvsp[-2]._select));
    }
#line 1921 "yacc_sql.tab.c"
    break;

  case 75: /* select: select_unit SEMICOLON  */
#line 478 "yacc_sql.y"
                          {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[CONTEXT->select_length - 1];
    }
#line 1930 "yacc_sql.tab.c"
    break;

  case 76: /* select_unit: SELECT select_attr FROM ID rel_list where group_by order_by  */
#line 483 "yacc_sql.y"
                                                                {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions, CONTEXT->condition_length);

        // 临时变量清零
        CONTEXT->condition_length = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length++];
    }
#line 1944 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr: STAR select_attr_list  */
#line 494 "yacc_sql.y"
                           {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], &attr);
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], &CONTEXT->exprs[CONTEXT->expr_length++]);
    }
#line 1955 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr: expr select_attr_list  */
#line 500 "yacc_sql.y"
                            {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._expr));
    }
#line 1963 "yacc_sql.tab.c"
    break;

  case 80: /* select_attr_list: COMMA expr select_attr_list  */
#line 505 "yacc_sql.y"
                                  {
        selects_append_expr(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._expr));
    }
#line 1971 "yacc_sql.tab.c"
    break;

  case 81: /* expr: add_expr  */
#line 509 "yacc_sql.y"
             {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 1979 "yacc_sql.tab.c"
    break;

  case 82: /* expr: LBRACE select_unit RBRACE  */
#line 512 "yacc_sql.y"
                                {
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 1988 "yacc_sql.tab.c"
    break;

  case 83: /* add_expr: add_expr PLUS mul_expr  */
#line 517 "yacc_sql.y"
                           {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_PLUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 1997 "yacc_sql.tab.c"
    break;

  case 84: /* add_expr: add_expr MINUS mul_expr  */
#line 521 "yacc_sql.y"
                              {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MINUS, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2006 "yacc_sql.tab.c"
    break;

  case 85: /* add_expr: mul_expr  */
#line 525 "yacc_sql.y"
               {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2014 "yacc_sql.tab.c"
    break;

  case 86: /* mul_expr: mul_expr STAR primary_expr  */
#line 529 "yacc_sql.y"
                               {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_MULTIPLY, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2023 "yacc_sql.tab.c"
    break;

  case 87: /* mul_expr: mul_expr DIVIDE primary_expr  */
#line 533 "yacc_sql.y"
                                   {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_DIVIDE, (yyvsp[-2]._expr), (yyvsp[0]._expr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2032 "yacc_sql.tab.c"
    break;

  case 88: /* mul_expr: MINUS primary_expr  */
#line 537 "yacc_sql.y"
                         {
        expr_init_expr(&CONTEXT->exprs[CONTEXT->expr_length], EXPR_NEGATIVE, (yyvsp[0]._expr), NULL);
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2041 "yacc_sql.tab.c"
    break;

  case 89: /* mul_expr: primary_expr  */
#line 541 "yacc_sql.y"
                   {
        (yyval._expr) = (yyvsp[0]._expr);
    }
#line 2049 "yacc_sql.tab.c"
    break;

  case 90: /* primary_expr: LBRACE add_expr RBRACE  */
#line 545 "yacc_sql.y"
                           {
        (yyval._expr) = (yyvsp[-1]._expr);
    }
#line 2057 "yacc_sql.tab.c"
    break;

  case 91: /* primary_expr: attr  */
#line 548 "yacc_sql.y"
           {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2066 "yacc_sql.tab.c"
    break;

  case 92: /* primary_expr: aggr_attr  */
#line 552 "yacc_sql.y"
                {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._attr));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2075 "yacc_sql.tab.c"
    break;

  case 93: /* primary_expr: expr_value  */
#line 556 "yacc_sql.y"
                 {
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[0]._value));
        (yyval._expr) = &CONTEXT->exprs[CONTEXT->expr_length++];
    }
#line 2084 "yacc_sql.tab.c"
    break;

  case 94: /* attr: ID  */
#line 562 "yacc_sql.y"
       {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2094 "yacc_sql.tab.c"
    break;

  case 95: /* attr: ID DOT ID  */
#line 567 "yacc_sql.y"
                {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 2104 "yacc_sql.tab.c"
    break;

  case 96: /* aggr_attr: aggr_type LBRACE attr RBRACE  */
#line 573 "yacc_sql.y"
                                   {
        relation_attr_aggr((yyvsp[-1]._attr), (yyvsp[-3].number));
        (yyval._attr) = (yyvsp[-1]._attr);
    }
#line 2113 "yacc_sql.tab.c"
    break;

  case 97: /* aggr_attr: aggr_type LBRACE STAR RBRACE  */
#line 577 "yacc_sql.y"
                                   {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2124 "yacc_sql.tab.c"
    break;

  case 98: /* aggr_attr: aggr_type LBRACE number RBRACE  */
#line 583 "yacc_sql.y"
                                     {
        RelAttr *attr = &CONTEXT->attrs[CONTEXT->attr_length++];
        if ((yyvsp[-1].number) != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 2138 "yacc_sql.tab.c"
    break;

  case 99: /* aggr_type: MAX  */
#line 593 "yacc_sql.y"
          { (yyval.number) = AGGR_MAX; }
#line 2144 "yacc_sql.tab.c"
    break;

  case 100: /* aggr_type: MIN  */
#line 594 "yacc_sql.y"
          { (yyval.number) = AGGR_MIN; }
#line 2150 "yacc_sql.tab.c"
    break;

  case 101: /* aggr_type: COUNT  */
#line 595 "yacc_sql.y"
            { (yyval.number) = AGGR_COUNT; }
#line 2156 "yacc_sql.tab.c"
    break;

  case 102: /* aggr_type: AVG  */
#line 596 "yacc_sql.y"
          { (yyval.number) = AGGR_AVG; }
#line 2162 "yacc_sql.tab.c"
    break;

  case 103: /* aggr_type: SUM  */
#line 597 "yacc_sql.y"
          { (yyval.number) = AGGR_SUM; }
#line 2168 "yacc_sql.tab.c"
    break;

  case 105: /* rel_list: COMMA ID rel_list  */
#line 602 "yacc_sql.y"
                        {
            selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
    }
#line 2176 "yacc_sql.tab.c"
    break;

  case 106: /* rel_list: join  */
#line 605 "yacc_sql.y"
           {
    }
#line 2183 "yacc_sql.tab.c"
    break;

  case 107: /* join: INNER JOIN ID ON condition condition_list join_list  */
#line 609 "yacc_sql.y"
                                                            {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2191 "yacc_sql.tab.c"
    break;

  case 109: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 614 "yacc_sql.y"
                                                               {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2199 "yacc_sql.tab.c"
    break;

  case 111: /* where: WHERE condition condition_list  */
#line 620 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2207 "yacc_sql.tab.c"
    break;

  case 113: /* condition_list: AND condition condition_list  */
#line 626 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2215 "yacc_sql.tab.c"
    break;

  case 114: /* condition: expr comOp expr  */
#line 632 "yacc_sql.y"
                    {
        Condition condition;
        condition_init(&condition, (yyvsp[-1].number), (yyvsp[-2]._expr), (yyvsp[0]._expr));
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2225 "yacc_sql.tab.c"
    break;

  case 115: /* condition: expr IN LBRACE select_unit RBRACE  */
#line 637 "yacc_sql.y"
                                         {
        Condition condition;
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&condition, IN_OP, (yyvsp[-4]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2236 "yacc_sql.tab.c"
    break;

  case 116: /* condition: expr IN NOT LBRACE select_unit RBRACE  */
#line 643 "yacc_sql.y"
                                            {
        Condition condition;
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&condition, NOT_IN_OP, (yyvsp[-5]._expr), &CONTEXT->exprs[CONTEXT->expr_length++]);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2247 "yacc_sql.tab.c"
    break;

  case 117: /* condition: EXISTS LBRACE select_unit RBRACE  */
#line 649 "yacc_sql.y"
                                       {
        Condition condition;
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&condition, EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2258 "yacc_sql.tab.c"
    break;

  case 118: /* condition: NOT EXISTS LBRACE select_unit RBRACE  */
#line 655 "yacc_sql.y"
                                           {
        Condition condition;
        expr_init_select(&CONTEXT->exprs[CONTEXT->expr_length], (yyvsp[-1]._select));
        condition_init(&condition, NOT_EXISTS_OP, NULL, &CONTEXT->exprs[CONTEXT->expr_length++]);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2269 "yacc_sql.tab.c"
    break;

  case 119: /* condition: value null_comOp  */
#line 661 "yacc_sql.y"
                           {
        Condition condition;
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&condition, (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2285 "yacc_sql.tab.c"
    break;

  case 120: /* condition: attr null_comOp  */
#line 672 "yacc_sql.y"
                          {
        Condition condition;
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._attr));

        value_init_null(&CONTEXT->values[CONTEXT->value_length]);
        Value *right_value = &CONTEXT->values[CONTEXT->value_length++];
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], right_value);

        condition_init(&condition, (yyvsp[0].number), &CONTEXT->exprs[CONTEXT->expr_length - 2], &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2301 "yacc_sql.tab.c"
    break;

  case 121: /* comOp: EQ  */
#line 685 "yacc_sql.y"
             { (yyval.number) = EQUAL_TO; }
#line 2307 "yacc_sql.tab.c"
    break;

  case 122: /* comOp: LT  */
#line 686 "yacc_sql.y"
         { (yyval.number) = LESS_THAN; }
#line 2313 "yacc_sql.tab.c"
    break;

  case 123: /* comOp: GT  */
#line 687 "yacc_sql.y"
         { (yyval.number) = GREAT_THAN; }
#line 2319 "yacc_sql.tab.c"
    break;

  case 124: /* comOp: LE  */
#line 688 "yacc_sql.y"
         { (yyval.number) = LESS_EQUAL; }
#line 2325 "yacc_sql.tab.c"
    break;

  case 125: /* comOp: GE  */
#line 689 "yacc_sql.y"
         { (yyval.number) = GREAT_EQUAL; }
#line 2331 "yacc_sql.tab.c"
    break;

  case 126: /* comOp: NE  */
#line 690 "yacc_sql.y"
         { (yyval.number) = NOT_EQUAL; }
#line 2337 "yacc_sql.tab.c"
    break;

  case 127: /* comOp: LIKE  */
#line 691 "yacc_sql.y"
           { (yyval.number) = LIKE_OP; }
#line 2343 "yacc_sql.tab.c"
    break;

  case 128: /* comOp: NOT LIKE  */
#line 692 "yacc_sql.y"
               { (yyval.number) = NOT_LIKE_OP; }
#line 2349 "yacc_sql.tab.c"
    break;

  case 129: /* null_comOp: IS NULL_TOKEN  */
#line 695 "yacc_sql.y"
                    { (yyval.number) = IS_NULL; }
#line 2355 "yacc_sql.tab.c"
    break;

  case 130: /* null_comOp: IS NOT NULL_TOKEN  */
#line 696 "yacc_sql.y"
                        { (yyval.number) = IS_NOT_NULL; }
#line 2361 "yacc_sql.tab.c"
    break;

  case 132: /* group_by: GROUP BY attr group_list having  */
#line 701 "yacc_sql.y"
                                      {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._attr));
    }
#line 2369 "yacc_sql.tab.c"
    break;

  case 134: /* group_list: COMMA attr group_list  */
#line 706 "yacc_sql.y"
                            {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
    }
#line 2377 "yacc_sql.tab.c"
    break;

  case 136: /* having: HAVING aggr_attr comOp value having_list  */
#line 711 "yacc_sql.y"
                                               {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2390 "yacc_sql.tab.c"
    break;

  case 138: /* having_list: AND aggr_attr comOp value having_list  */
#line 721 "yacc_sql.y"
                                            {
        expr_init_attr(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-3]._attr));
        expr_init_value(&CONTEXT->exprs[CONTEXT->expr_length++], (yyvsp[-1]._value));
        Condition condition;
        condition_init(&condition, (yyvsp[-2].number), &CONTEXT->exprs[CONTEXT->expr_length - 2],
                &CONTEXT->exprs[CONTEXT->expr_length - 1]);
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2403 "yacc_sql.tab.c"
    break;

  case 140: /* order_by: ORDER BY order order_list  */
#line 732 "yacc_sql.y"
                                {
    }
#line 2410 "yacc_sql.tab.c"
    break;

  case 142: /* order_list: COMMA order order_list  */
#line 737 "yacc_sql.y"
                            {
    }
#line 2417 "yacc_sql.tab.c"
    break;

  case 143: /* order: ID  */
#line 741 "yacc_sql.y"
      {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, "");
    }
#line 2425 "yacc_sql.tab.c"
    break;

  case 144: /* order: ID DESC  */
#line 744 "yacc_sql.y"
             {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, "");
    }
#line 2433 "yacc_sql.tab.c"
    break;

  case 145: /* order: ID ASC  */
#line 747 "yacc_sql.y"
            {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, "");
    }
#line 2441 "yacc_sql.tab.c"
    break;

  case 146: /* order: ID DOT ID  */
#line 750 "yacc_sql.y"
               {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, (yyvsp[-2].string));
    }
#line 2449 "yacc_sql.tab.c"
    break;

  case 147: /* order: ID DOT ID DESC  */
#line 753 "yacc_sql.y"
                    {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, (yyvsp[-3].string));
    }
#line 2457 "yacc_sql.tab.c"
    break;

  case 148: /* order: ID DOT ID ASC  */
#line 756 "yacc_sql.y"
                   {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, (yyvsp[-3].string));
    }
#line 2465 "yacc_sql.tab.c"
    break;

  case 149: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 762 "yacc_sql.y"
                                                 {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
    }
#line 2474 "yacc_sql.tab.c"
    break;


#line 2478 "yacc_sql.tab.c"

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

#line 767 "yacc_sql.y"

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
