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


#line 140 "yacc_sql.tab.c"

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
  YYSYMBOL_INNER = 56,                     /* INNER  */
  YYSYMBOL_JOIN = 57,                      /* JOIN  */
  YYSYMBOL_IS = 58,                        /* IS  */
  YYSYMBOL_NOT = 59,                       /* NOT  */
  YYSYMBOL_NULL_TOKEN = 60,                /* NULL_TOKEN  */
  YYSYMBOL_NULLABLE = 61,                  /* NULLABLE  */
  YYSYMBOL_ORDER = 62,                     /* ORDER  */
  YYSYMBOL_ASC = 63,                       /* ASC  */
  YYSYMBOL_NUMBER = 64,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 65,                     /* FLOAT  */
  YYSYMBOL_ID = 66,                        /* ID  */
  YYSYMBOL_PATH = 67,                      /* PATH  */
  YYSYMBOL_SSS = 68,                       /* SSS  */
  YYSYMBOL_STAR = 69,                      /* STAR  */
  YYSYMBOL_STRING_V = 70,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 71,                  /* $accept  */
  YYSYMBOL_commands = 72,                  /* commands  */
  YYSYMBOL_command = 73,                   /* command  */
  YYSYMBOL_exit = 74,                      /* exit  */
  YYSYMBOL_help = 75,                      /* help  */
  YYSYMBOL_sync = 76,                      /* sync  */
  YYSYMBOL_begin = 77,                     /* begin  */
  YYSYMBOL_commit = 78,                    /* commit  */
  YYSYMBOL_rollback = 79,                  /* rollback  */
  YYSYMBOL_drop_table = 80,                /* drop_table  */
  YYSYMBOL_show_tables = 81,               /* show_tables  */
  YYSYMBOL_show_index = 82,                /* show_index  */
  YYSYMBOL_desc_table = 83,                /* desc_table  */
  YYSYMBOL_create_index = 84,              /* create_index  */
  YYSYMBOL_attrone = 85,                   /* attrone  */
  YYSYMBOL_attr_index = 86,                /* attr_index  */
  YYSYMBOL_attr_index_list = 87,           /* attr_index_list  */
  YYSYMBOL_drop_index = 88,                /* drop_index  */
  YYSYMBOL_create_table = 89,              /* create_table  */
  YYSYMBOL_attr_def_list = 90,             /* attr_def_list  */
  YYSYMBOL_attr_def = 91,                  /* attr_def  */
  YYSYMBOL_number = 92,                    /* number  */
  YYSYMBOL_type = 93,                      /* type  */
  YYSYMBOL_ID_get = 94,                    /* ID_get  */
  YYSYMBOL_nullable = 95,                  /* nullable  */
  YYSYMBOL_insert = 96,                    /* insert  */
  YYSYMBOL_v_list = 97,                    /* v_list  */
  YYSYMBOL_node = 98,                      /* node  */
  YYSYMBOL_value_list = 99,                /* value_list  */
  YYSYMBOL_value = 100,                    /* value  */
  YYSYMBOL_delete = 101,                   /* delete  */
  YYSYMBOL_update = 102,                   /* update  */
  YYSYMBOL_update_attr = 103,              /* update_attr  */
  YYSYMBOL_update_attr_list = 104,         /* update_attr_list  */
  YYSYMBOL_select = 105,                   /* select  */
  YYSYMBOL_select_unit = 106,              /* select_unit  */
  YYSYMBOL_select_attr = 107,              /* select_attr  */
  YYSYMBOL_select_attr_list = 108,         /* select_attr_list  */
  YYSYMBOL_attr = 109,                     /* attr  */
  YYSYMBOL_aggr_attr = 110,                /* aggr_attr  */
  YYSYMBOL_aggr_type = 111,                /* aggr_type  */
  YYSYMBOL_rel_list = 112,                 /* rel_list  */
  YYSYMBOL_join = 113,                     /* join  */
  YYSYMBOL_join_list = 114,                /* join_list  */
  YYSYMBOL_where = 115,                    /* where  */
  YYSYMBOL_condition_list = 116,           /* condition_list  */
  YYSYMBOL_condition = 117,                /* condition  */
  YYSYMBOL_comOp = 118,                    /* comOp  */
  YYSYMBOL_null_comOp = 119,               /* null_comOp  */
  YYSYMBOL_group_by = 120,                 /* group_by  */
  YYSYMBOL_group_list = 121,               /* group_list  */
  YYSYMBOL_having = 122,                   /* having  */
  YYSYMBOL_having_list = 123,              /* having_list  */
  YYSYMBOL_order_by = 124,                 /* order_by  */
  YYSYMBOL_order_list = 125,               /* order_list  */
  YYSYMBOL_order = 126,                    /* order  */
  YYSYMBOL_load_data = 127                 /* load_data  */
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
#define YYLAST   289

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  71
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  57
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  289

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   325


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
      65,    66,    67,    68,    69,    70
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   171,   171,   173,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   198,   203,   208,   214,   220,   226,   232,   238,
     244,   251,   258,   264,   272,   278,   284,   286,   293,   300,
     309,   311,   315,   322,   330,   333,   334,   335,   336,   337,
     340,   345,   346,   347,   351,   364,   365,   370,   378,   380,
     385,   390,   395,   401,   408,   418,   424,   427,   430,   432,
     435,   440,   445,   456,   461,   465,   469,   471,   475,   480,
     485,   491,   495,   501,   511,   512,   513,   514,   515,   518,
     520,   523,   527,   530,   532,   536,   538,   542,   544,   549,
     559,   567,   577,   586,   595,   605,   615,   625,   636,   649,
     650,   651,   652,   653,   654,   655,   656,   659,   660,   663,
     665,   669,   671,   675,   677,   685,   687,   696,   698,   701,
     703,   707,   710,   713,   716,   719,   722,   728
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
  "GE", "NE", "LIKE", "INNER", "JOIN", "IS", "NOT", "NULL_TOKEN",
  "NULLABLE", "ORDER", "ASC", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "show_index", "desc_table", "create_index", "attrone", "attr_index",
  "attr_index_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "nullable", "insert", "v_list",
  "node", "value_list", "value", "delete", "update", "update_attr",
  "update_attr_list", "select", "select_unit", "select_attr",
  "select_attr_list", "attr", "aggr_attr", "aggr_type", "rel_list", "join",
  "join_list", "where", "condition_list", "condition", "comOp",
  "null_comOp", "group_by", "group_list", "having", "having_list",
  "order_by", "order_list", "order", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-206)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -206,   113,  -206,    80,    32,    -8,   -47,    73,    34,    12,
      19,     3,    60,    68,    84,    92,   101,    36,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,   107,  -206,    46,    49,
     108,    53,    55,  -206,  -206,  -206,  -206,  -206,    94,   103,
      89,   103,   103,   120,   133,   135,    98,  -206,    75,    88,
     111,  -206,  -206,  -206,  -206,  -206,   109,  -206,   146,   132,
      99,   172,   182,   126,    18,  -206,   127,  -206,  -206,    13,
    -206,  -206,   131,   164,   144,   139,   138,   142,   143,   165,
    -206,  -206,  -206,   103,   103,    -3,  -206,   193,   194,   195,
     211,   198,    96,   213,   168,   144,   179,  -206,   200,     6,
     203,   155,  -206,  -206,   156,   166,   144,  -206,  -206,  -206,
    -206,  -206,    43,  -206,  -206,  -206,    47,  -206,    93,   181,
    -206,     8,   222,   220,   142,   209,  -206,  -206,  -206,  -206,
    -206,    -7,   162,   212,    -3,   167,   197,   215,   169,  -206,
    -206,  -206,  -206,  -206,  -206,  -206,    33,   176,   116,  -206,
     123,  -206,    96,  -206,   226,   218,  -206,   173,   200,   229,
     174,   180,  -206,  -206,  -206,   223,   162,  -206,   196,   210,
     183,    43,   225,    93,   186,  -206,  -206,  -206,  -206,   214,
    -206,   181,   230,   184,  -206,   244,  -206,  -206,   231,  -206,
     185,   235,   223,    96,   188,   221,  -206,   215,   237,   130,
    -206,  -206,   191,  -206,   218,   216,  -206,   -17,  -206,   223,
     255,   241,   181,   242,   201,  -206,   243,   259,    43,   228,
    -206,  -206,  -206,    10,  -206,  -206,  -206,   260,   208,   188,
     233,    -4,   250,  -206,  -206,   215,   204,   226,   218,  -206,
     217,  -206,   242,   171,  -206,  -206,   205,  -206,   201,  -206,
     254,  -206,   257,  -206,   207,  -206,   119,     4,   250,   237,
     218,   232,    43,  -206,  -206,  -206,  -206,  -206,    96,   236,
     181,   171,  -206,   208,   119,  -206,    43,   236,  -206
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
       0,     0,     0,    84,    85,    86,    87,    88,    79,    76,
       0,    76,    76,     0,     0,     0,     0,    24,     0,     0,
       0,    25,    26,    27,    23,    22,     0,    71,     0,     0,
       0,     0,     0,     0,     0,    73,     0,    74,    75,     0,
      31,    29,     0,     0,    95,     0,     0,     0,     0,     0,
      28,    38,    80,    76,    76,    89,    44,     0,     0,     0,
       0,     0,     0,     0,     0,    95,     0,    50,    40,     0,
       0,     0,    77,    78,     0,     0,    95,    91,    82,    83,
      81,    30,     0,    63,    60,    61,     0,    62,     0,    97,
      64,     0,     0,     0,     0,     0,    45,    46,    47,    48,
      49,    51,     0,     0,    89,     0,   119,    58,     0,   109,
     110,   111,   112,   113,   114,   115,     0,     0,     0,   107,
       0,   106,     0,    96,     0,    68,    65,     0,    40,     0,
       0,     0,    52,    43,    34,    36,     0,    90,     0,     0,
     127,     0,     0,     0,     0,   117,   116,   101,    99,   102,
     100,    97,     0,     0,    66,     0,    41,    39,     0,    53,
       0,     0,    36,     0,     0,     0,    72,    58,    55,     0,
     108,   118,     0,    98,    68,     0,   137,    51,    35,    36,
       0,     0,    97,   121,     0,    59,     0,     0,     0,     0,
     103,   104,    67,     0,    42,    37,    33,     0,    93,     0,
     123,   131,   129,    57,    54,    58,     0,     0,    68,    32,
       0,    92,   121,     0,   120,   132,     0,   133,     0,   128,
       0,   105,     0,    69,     0,   122,     0,   134,   129,    55,
      68,     0,     0,   135,   136,   130,    56,    70,     0,   125,
      97,     0,   124,    93,     0,    94,     0,   125,   126
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,  -206,
    -206,  -206,  -206,  -206,   100,  -206,  -184,  -206,  -206,   110,
     147,   112,  -206,  -206,    63,  -206,    14,  -206,  -181,  -119,
    -206,  -206,  -206,  -205,  -206,  -156,  -206,   -38,   -73,   -74,
    -206,   140,  -206,     2,   -88,  -186,  -158,  -126,  -117,  -206,
      35,  -206,    -1,  -206,    20,    31,  -206
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   175,   219,   201,    30,    31,   135,
     108,    98,   141,   109,   173,    32,   227,   228,   182,   128,
      33,    34,   105,   194,    35,    36,    50,    75,    51,    52,
      53,   116,   117,   251,   103,   163,   129,   158,   159,   180,
     240,   254,   282,   206,   259,   242,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      94,    93,   160,   147,   191,   213,    99,   255,   192,   232,
     170,   161,   165,    77,    78,   273,   114,   132,   221,    54,
      43,    44,    45,    46,    47,   164,   225,   247,   146,   136,
     137,   138,   139,   140,   256,   235,   238,    57,    41,   188,
      42,   190,   171,   263,   172,   222,    43,    44,    45,    46,
      47,    58,   171,   115,   172,   112,   113,   209,    48,   257,
      59,    49,   207,    61,   260,   277,   210,   274,   123,    60,
     123,    62,   124,   125,   124,   125,   127,    96,   127,    48,
      55,    56,    97,    66,    48,   148,    38,    63,    39,    40,
     230,   262,   184,   185,   283,    64,   149,   150,   151,   152,
     153,   154,   155,   123,    65,   156,   157,   124,   125,   245,
      67,   127,    68,     2,   248,    69,    70,     3,     4,    71,
     280,    72,    74,     5,     6,     7,     8,     9,    10,    11,
      76,   223,    73,    12,    13,    14,    80,    79,    81,    82,
     272,    83,   149,   150,   151,   152,   153,   154,   155,    15,
      16,   156,   157,   279,    84,    85,   123,    86,   286,    17,
     124,   125,   126,    87,   127,    89,   252,   287,   149,   150,
     151,   152,   153,   154,   155,    90,   123,    88,   157,   266,
     124,   125,   187,   123,   127,    91,   102,   124,   125,   189,
     123,   127,    92,    95,   124,   125,   229,   100,   127,    43,
      44,    45,    46,    47,   101,   104,   106,   284,   107,   110,
     111,   118,   119,   120,   121,   122,   130,   131,   133,   134,
     142,   143,   144,   145,   162,   166,   167,   169,   174,   176,
     179,   186,   197,   178,   181,   183,     5,   193,    96,   195,
     199,   203,   200,   208,   204,   205,   211,   216,   214,   217,
     215,   218,   212,   220,    48,   224,   226,   231,   236,   237,
     243,   239,   244,   249,   250,   233,   246,   241,   253,   258,
     261,   267,   269,   271,   264,   270,   202,   278,   196,   281,
     234,   168,   198,   276,   177,   285,   288,   265,   275,   268
};

static const yytype_int16 yycheck[] =
{
      74,    74,   128,   122,   162,   191,    79,    11,   164,   214,
      17,   128,   131,    51,    52,    11,    19,   105,   202,    66,
      28,    29,    30,    31,    32,    17,   207,    17,   116,    23,
      24,    25,    26,    27,    38,   219,   222,     3,     6,   158,
       8,   160,    59,   248,    61,   203,    28,    29,    30,    31,
      32,    39,    59,    56,    61,    93,    94,   183,    66,    63,
      41,    69,   181,     3,   245,   270,   183,    63,    60,    66,
      60,     3,    64,    65,    64,    65,    68,    64,    68,    66,
       7,     8,    69,    47,    66,    38,     6,     3,     8,     9,
     209,   247,    59,    60,   280,     3,    49,    50,    51,    52,
      53,    54,    55,    60,     3,    58,    59,    64,    65,   228,
       3,    68,    66,     0,   233,    66,     8,     4,     5,    66,
     278,    66,    19,    10,    11,    12,    13,    14,    15,    16,
      41,   204,    38,    20,    21,    22,     3,    17,     3,    41,
     266,    66,    49,    50,    51,    52,    53,    54,    55,    36,
      37,    58,    59,   272,    66,    44,    60,    48,   284,    46,
      64,    65,    66,    17,    68,    66,   239,   286,    49,    50,
      51,    52,    53,    54,    55,     3,    60,    45,    59,   253,
      64,    65,    66,    60,    68,     3,    42,    64,    65,    66,
      60,    68,    66,    66,    64,    65,    66,    66,    68,    28,
      29,    30,    31,    32,    40,    66,    68,   281,    66,    66,
      45,    18,    18,    18,     3,    17,     3,    49,    39,    19,
      17,    66,    66,    57,    43,     3,     6,    18,    66,    17,
      33,    55,     3,    66,    19,    66,    10,    19,    64,    66,
      60,    45,    19,    18,    34,    62,    60,     3,    18,    18,
      66,    66,    38,    18,    66,    34,    19,    66,     3,    18,
      17,    19,     3,     3,    56,    49,    38,    66,    35,    19,
      66,    66,    18,    66,    57,    18,   176,    45,   168,    43,
     217,   134,   170,   269,   144,   283,   287,   252,   268,   258
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    72,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    36,    37,    46,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      88,    89,    96,   101,   102,   105,   106,   127,     6,     8,
       9,     6,     8,    28,    29,    30,    31,    32,    66,    69,
     107,   109,   110,   111,    66,     7,     8,     3,    39,    41,
      66,     3,     3,     3,     3,     3,    47,     3,    66,    66,
       8,    66,    66,    38,    19,   108,    41,   108,   108,    17,
       3,     3,    41,    66,    66,    44,    48,    17,    45,    66,
       3,     3,    66,   109,   110,    66,    64,    69,    92,   109,
      66,    40,    42,   115,    66,   103,    68,    66,    91,    94,
      66,    45,   108,   108,    19,    56,   112,   113,    18,    18,
      18,     3,    17,    60,    64,    65,    66,    68,   100,   117,
       3,    49,   115,    39,    19,    90,    23,    24,    25,    26,
      27,    93,    17,    66,    66,    57,   115,   100,    38,    49,
      50,    51,    52,    53,    54,    55,    58,    59,   118,   119,
     118,   119,    43,   116,    17,   100,     3,     6,    91,    18,
      17,    59,    61,    95,    66,    85,    17,   112,    66,    33,
     120,    19,    99,    66,    59,    60,    55,    66,   100,    66,
     100,   117,   106,    19,   104,    66,    90,     3,    92,    60,
      19,    87,    85,    45,    34,    62,   124,   100,    18,   118,
     119,    60,    38,   116,    18,    66,     3,    18,    66,    86,
      18,    87,   117,   109,    34,    99,    19,    97,    98,    66,
     100,    66,   104,    49,    95,    87,     3,    18,   116,    19,
     121,    66,   126,    17,     3,   100,    38,    17,   100,     3,
      56,   114,   109,    35,   122,    11,    38,    63,    19,   125,
      99,    66,   106,   104,    57,   121,   110,    66,   126,    18,
      18,    66,   118,    11,    63,   125,    97,   104,    45,   100,
     117,    43,   123,   116,   110,   114,   118,   100,   123
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      73,    73,    73,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    84,    85,    86,    87,    87,    88,    89,
      90,    90,    91,    91,    92,    93,    93,    93,    93,    93,
      94,    95,    95,    95,    96,    97,    97,    98,    99,    99,
     100,   100,   100,   100,   101,   102,   103,   103,   104,   104,
     104,   105,   106,   107,   107,   107,   108,   108,   108,   109,
     109,   110,   110,   110,   111,   111,   111,   111,   111,   112,
     112,   112,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   118,
     118,   118,   118,   118,   118,   118,   118,   119,   119,   120,
     120,   121,   121,   122,   122,   123,   123,   124,   124,   125,
     125,   126,   126,   126,   126,   126,   126,   127
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
       1,     1,     1,     1,     5,     6,     4,     6,     0,     5,
       7,     2,     8,     2,     2,     2,     0,     3,     3,     1,
       3,     4,     4,     4,     1,     1,     1,     1,     1,     0,
       3,     1,     7,     0,     7,     0,     3,     0,     3,     3,
       3,     3,     3,     5,     5,     7,     2,     2,     4,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     0,
       5,     0,     3,     0,     5,     0,     5,     0,     4,     0,
       3,     1,     2,     2,     3,     4,     4,     8
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
#line 198 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1464 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 203 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1472 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 208 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1480 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 214 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1488 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 220 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1496 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 226 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1504 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 232 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1513 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 238 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1521 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 244 "yacc_sql.y"
                                 {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1530 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 251 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1539 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 259 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1549 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 265 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1559 "yacc_sql.tab.c"
    break;

  case 34: /* attrone: ID  */
#line 273 "yacc_sql.y"
        {
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1567 "yacc_sql.tab.c"
    break;

  case 35: /* attr_index: ID  */
#line 279 "yacc_sql.y"
        {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, (yyvsp[0].string));
		CONTEXT->attr_num++;
	}
#line 1576 "yacc_sql.tab.c"
    break;

  case 37: /* attr_index_list: COMMA attr_index attr_index_list  */
#line 287 "yacc_sql.y"
        {

	}
#line 1584 "yacc_sql.tab.c"
    break;

  case 38: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 294 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1593 "yacc_sql.tab.c"
    break;

  case 39: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 301 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1605 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 311 "yacc_sql.y"
                                   {    }
#line 1611 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE nullable  */
#line 315 "yacc_sql.y"
                                              {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-4].number), (yyvsp[-2].number) + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
    }
#line 1623 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type nullable  */
#line 322 "yacc_sql.y"
                           {
        AttrInfo attribute;
        // 属性占用字节多一个用于表示是否为 NULL
        attr_info_init(&attribute, CONTEXT->id, (yyvsp[-1].number), 4 + 1, (yyvsp[0].number));
        create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
        CONTEXT->value_length++;
	}
#line 1635 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 330 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1641 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 333 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1647 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 334 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 1653 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 335 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1659 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 336 "yacc_sql.y"
              { (yyval.number) = FLOATS; }
#line 1665 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 337 "yacc_sql.y"
             { (yyval.number) = DATES; }
#line 1671 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 340 "yacc_sql.y"
       {
        char *temp=(yyvsp[0].string);
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1680 "yacc_sql.tab.c"
    break;

  case 51: /* nullable: %empty  */
#line 345 "yacc_sql.y"
                  { (yyval.number) = false; }
#line 1686 "yacc_sql.tab.c"
    break;

  case 52: /* nullable: NULLABLE  */
#line 346 "yacc_sql.y"
               { (yyval.number) = true; }
#line 1692 "yacc_sql.tab.c"
    break;

  case 53: /* nullable: NOT NULL_TOKEN  */
#line 347 "yacc_sql.y"
                         { (yyval.number) = false; }
#line 1698 "yacc_sql.tab.c"
    break;

  case 54: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE v_list SEMICOLON  */
#line 352 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_INSERT;
		CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
		CONTEXT->every_group_count=0;
        CONTEXT->group_num = CONTEXT->group_num + 1;

		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->insert_groups, CONTEXT->group_num);

		//临时变量清零
		CONTEXT->value_length=0;
    }
#line 1714 "yacc_sql.tab.c"
    break;

  case 56: /* v_list: node value value_list RBRACE v_list  */
#line 366 "yacc_sql.y"
    {
    }
#line 1721 "yacc_sql.tab.c"
    break;

  case 57: /* node: COMMA LBRACE  */
#line 371 "yacc_sql.y"
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    }
#line 1732 "yacc_sql.tab.c"
    break;

  case 59: /* value_list: COMMA value value_list  */
#line 380 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1740 "yacc_sql.tab.c"
    break;

  case 60: /* value: NUMBER  */
#line 385 "yacc_sql.y"
           {
        value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length - 1];
        CONTEXT->every_group_count++;
    }
#line 1750 "yacc_sql.tab.c"
    break;

  case 61: /* value: FLOAT  */
#line 390 "yacc_sql.y"
            {
        value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length - 1];
        CONTEXT->every_group_count++;
	}
#line 1760 "yacc_sql.tab.c"
    break;

  case 62: /* value: SSS  */
#line 395 "yacc_sql.y"
          {
        (yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
        value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length - 1];
        CONTEXT->every_group_count++;
    }
#line 1771 "yacc_sql.tab.c"
    break;

  case 63: /* value: NULL_TOKEN  */
#line 401 "yacc_sql.y"
                 {
        value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
        (yyval._value) = &CONTEXT->values[CONTEXT->value_length - 1];
        CONTEXT->every_group_count++;
    }
#line 1781 "yacc_sql.tab.c"
    break;

  case 64: /* delete: DELETE FROM ID where SEMICOLON  */
#line 409 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1792 "yacc_sql.tab.c"
    break;

  case 65: /* update: UPDATE ID SET update_attr where SEMICOLON  */
#line 418 "yacc_sql.y"
                                              {
		CONTEXT->ssql->flag = SCF_UPDATE;
		updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-4].string), CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->condition_length = 0;
    }
#line 1802 "yacc_sql.tab.c"
    break;

  case 66: /* update_attr: ID EQ value update_attr_list  */
#line 424 "yacc_sql.y"
                                 {
		updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1810 "yacc_sql.tab.c"
    break;

  case 67: /* update_attr: ID EQ LBRACE select_unit RBRACE update_attr_list  */
#line 427 "yacc_sql.y"
                                                       {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), (yyvsp[-2]._select));
    }
#line 1818 "yacc_sql.tab.c"
    break;

  case 69: /* update_attr_list: COMMA ID EQ value update_attr_list  */
#line 432 "yacc_sql.y"
                                         {
        updates_append_attr(&CONTEXT->ssql->sstr.update, (yyvsp[-3].string), (yyvsp[-1]._value));
    }
#line 1826 "yacc_sql.tab.c"
    break;

  case 70: /* update_attr_list: COMMA ID EQ LBRACE select_unit RBRACE update_attr_list  */
#line 435 "yacc_sql.y"
                                                             {
        updates_append_select(&CONTEXT->ssql->sstr.update, (yyvsp[-5].string), (yyvsp[-2]._select));
    }
#line 1834 "yacc_sql.tab.c"
    break;

  case 71: /* select: select_unit SEMICOLON  */
#line 440 "yacc_sql.y"
                          {
        CONTEXT->ssql->flag = SCF_SELECT;
        CONTEXT->ssql->sstr.selection = CONTEXT->selects[CONTEXT->select_length - 1];
    }
#line 1843 "yacc_sql.tab.c"
    break;

  case 72: /* select_unit: SELECT select_attr FROM ID rel_list where group_by order_by  */
#line 445 "yacc_sql.y"
                                                                {
        selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
        selects_append_conditions(&CONTEXT->selects[CONTEXT->select_length], CONTEXT->conditions, CONTEXT->condition_length);

        // 临时变量清零
        CONTEXT->condition_length = 0;
        CONTEXT->value_length = 0;
        (yyval._select) = &CONTEXT->selects[CONTEXT->select_length++];
    }
#line 1857 "yacc_sql.tab.c"
    break;

  case 73: /* select_attr: STAR select_attr_list  */
#line 456 "yacc_sql.y"
                          {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], &attr);
    }
#line 1867 "yacc_sql.tab.c"
    break;

  case 74: /* select_attr: attr select_attr_list  */
#line 461 "yacc_sql.y"
                            {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1876 "yacc_sql.tab.c"
    break;

  case 75: /* select_attr: aggr_attr select_attr_list  */
#line 465 "yacc_sql.y"
                                 {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1885 "yacc_sql.tab.c"
    break;

  case 77: /* select_attr_list: COMMA attr select_attr_list  */
#line 471 "yacc_sql.y"
                                  {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1894 "yacc_sql.tab.c"
    break;

  case 78: /* select_attr_list: COMMA aggr_attr select_attr_list  */
#line 475 "yacc_sql.y"
                                       {
        selects_append_attribute(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1903 "yacc_sql.tab.c"
    break;

  case 79: /* attr: ID  */
#line 480 "yacc_sql.y"
       {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 1913 "yacc_sql.tab.c"
    break;

  case 80: /* attr: ID DOT ID  */
#line 485 "yacc_sql.y"
                {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, (yyvsp[-2].string), (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 1923 "yacc_sql.tab.c"
    break;

  case 81: /* aggr_attr: aggr_type LBRACE attr RBRACE  */
#line 491 "yacc_sql.y"
                                   {
        relation_attr_aggr((yyvsp[-1]._attr), (yyvsp[-3].number));
        (yyval._attr) = (yyvsp[-1]._attr);
    }
#line 1932 "yacc_sql.tab.c"
    break;

  case 82: /* aggr_attr: aggr_type LBRACE STAR RBRACE  */
#line 495 "yacc_sql.y"
                                   {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 1943 "yacc_sql.tab.c"
    break;

  case 83: /* aggr_attr: aggr_type LBRACE number RBRACE  */
#line 501 "yacc_sql.y"
                                     {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        if ((yyvsp[-1].number) != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 1957 "yacc_sql.tab.c"
    break;

  case 84: /* aggr_type: MAX  */
#line 511 "yacc_sql.y"
          { (yyval.number) = AGGR_MAX; }
#line 1963 "yacc_sql.tab.c"
    break;

  case 85: /* aggr_type: MIN  */
#line 512 "yacc_sql.y"
          { (yyval.number) = AGGR_MIN; }
#line 1969 "yacc_sql.tab.c"
    break;

  case 86: /* aggr_type: COUNT  */
#line 513 "yacc_sql.y"
            { (yyval.number) = AGGR_COUNT; }
#line 1975 "yacc_sql.tab.c"
    break;

  case 87: /* aggr_type: AVG  */
#line 514 "yacc_sql.y"
          { (yyval.number) = AGGR_AVG; }
#line 1981 "yacc_sql.tab.c"
    break;

  case 88: /* aggr_type: SUM  */
#line 515 "yacc_sql.y"
          { (yyval.number) = AGGR_SUM; }
#line 1987 "yacc_sql.tab.c"
    break;

  case 90: /* rel_list: COMMA ID rel_list  */
#line 520 "yacc_sql.y"
                        {
            selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string));
    }
#line 1995 "yacc_sql.tab.c"
    break;

  case 91: /* rel_list: join  */
#line 523 "yacc_sql.y"
           {
    }
#line 2002 "yacc_sql.tab.c"
    break;

  case 92: /* join: INNER JOIN ID ON condition condition_list join_list  */
#line 527 "yacc_sql.y"
                                                            {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2010 "yacc_sql.tab.c"
    break;

  case 94: /* join_list: INNER JOIN ID ON condition condition_list join_list  */
#line 532 "yacc_sql.y"
                                                               {
		selects_append_relation(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-4].string));
	}
#line 2018 "yacc_sql.tab.c"
    break;

  case 96: /* where: WHERE condition condition_list  */
#line 538 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2026 "yacc_sql.tab.c"
    break;

  case 98: /* condition_list: AND condition condition_list  */
#line 544 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2034 "yacc_sql.tab.c"
    break;

  case 99: /* condition: ID comOp value  */
#line 549 "yacc_sql.y"
                   {
        RelAttr left_attr;
        relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2049 "yacc_sql.tab.c"
    break;

  case 100: /* condition: value comOp value  */
#line 559 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2062 "yacc_sql.tab.c"
    break;

  case 101: /* condition: ID comOp ID  */
#line 567 "yacc_sql.y"
                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2077 "yacc_sql.tab.c"
    break;

  case 102: /* condition: value comOp ID  */
#line 577 "yacc_sql.y"
                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2091 "yacc_sql.tab.c"
    break;

  case 103: /* condition: ID DOT ID comOp value  */
#line 586 "yacc_sql.y"
                            {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2105 "yacc_sql.tab.c"
    break;

  case 104: /* condition: value comOp ID DOT ID  */
#line 595 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2120 "yacc_sql.tab.c"
    break;

  case 105: /* condition: ID DOT ID comOp ID DOT ID  */
#line 605 "yacc_sql.y"
                                {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 2135 "yacc_sql.tab.c"
    break;

  case 106: /* condition: value null_comOp  */
#line 615 "yacc_sql.y"
                           {
		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);

		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2150 "yacc_sql.tab.c"
    break;

  case 107: /* condition: ID null_comOp  */
#line 625 "yacc_sql.y"
                        {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-1].string));

		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2166 "yacc_sql.tab.c"
    break;

  case 108: /* condition: ID DOT ID null_comOp  */
#line 636 "yacc_sql.y"
                               {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-3].string), (yyvsp[-1].string));

		value_init_null(&CONTEXT->values[CONTEXT->value_length++]);
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 2182 "yacc_sql.tab.c"
    break;

  case 109: /* comOp: EQ  */
#line 649 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2188 "yacc_sql.tab.c"
    break;

  case 110: /* comOp: LT  */
#line 650 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2194 "yacc_sql.tab.c"
    break;

  case 111: /* comOp: GT  */
#line 651 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2200 "yacc_sql.tab.c"
    break;

  case 112: /* comOp: LE  */
#line 652 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2206 "yacc_sql.tab.c"
    break;

  case 113: /* comOp: GE  */
#line 653 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2212 "yacc_sql.tab.c"
    break;

  case 114: /* comOp: NE  */
#line 654 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2218 "yacc_sql.tab.c"
    break;

  case 115: /* comOp: LIKE  */
#line 655 "yacc_sql.y"
           { CONTEXT->comp = LIKE_OP; }
#line 2224 "yacc_sql.tab.c"
    break;

  case 116: /* comOp: NOT LIKE  */
#line 656 "yacc_sql.y"
               { CONTEXT->comp = NOT_LIKE_OP; }
#line 2230 "yacc_sql.tab.c"
    break;

  case 117: /* null_comOp: IS NULL_TOKEN  */
#line 659 "yacc_sql.y"
                    { CONTEXT->comp = IS_NULL; }
#line 2236 "yacc_sql.tab.c"
    break;

  case 118: /* null_comOp: IS NOT NULL_TOKEN  */
#line 660 "yacc_sql.y"
                        { CONTEXT->comp = IS_NOT_NULL; }
#line 2242 "yacc_sql.tab.c"
    break;

  case 120: /* group_by: GROUP BY attr group_list having  */
#line 665 "yacc_sql.y"
                                      {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-2]._attr));
        free((yyvsp[-2]._attr));
    }
#line 2251 "yacc_sql.tab.c"
    break;

  case 122: /* group_list: COMMA attr group_list  */
#line 671 "yacc_sql.y"
                            {
        selects_append_groups(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 2260 "yacc_sql.tab.c"
    break;

  case 124: /* having: HAVING aggr_attr comOp value having_list  */
#line 677 "yacc_sql.y"
                                               {
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

        Condition condition;
        condition_init(&condition, CONTEXT->comp, 1, (yyvsp[-3]._attr), NULL, 0, NULL, right_value);
        free((yyvsp[-3]._attr));
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2273 "yacc_sql.tab.c"
    break;

  case 126: /* having_list: AND aggr_attr comOp value having_list  */
#line 687 "yacc_sql.y"
                                            {
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

        Condition condition;
        condition_init(&condition, CONTEXT->comp, 1, (yyvsp[-3]._attr), NULL, 0, NULL, right_value);
        free((yyvsp[-3]._attr));
        selects_append_having(&CONTEXT->selects[CONTEXT->select_length], &condition);
    }
#line 2286 "yacc_sql.tab.c"
    break;

  case 128: /* order_by: ORDER BY order order_list  */
#line 698 "yacc_sql.y"
                                {
    }
#line 2293 "yacc_sql.tab.c"
    break;

  case 130: /* order_list: COMMA order order_list  */
#line 703 "yacc_sql.y"
                            {
    }
#line 2300 "yacc_sql.tab.c"
    break;

  case 131: /* order: ID  */
#line 707 "yacc_sql.y"
      {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, "");
    }
#line 2308 "yacc_sql.tab.c"
    break;

  case 132: /* order: ID DESC  */
#line 710 "yacc_sql.y"
             {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, "");
    }
#line 2316 "yacc_sql.tab.c"
    break;

  case 133: /* order: ID ASC  */
#line 713 "yacc_sql.y"
            {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, "");
    }
#line 2324 "yacc_sql.tab.c"
    break;

  case 134: /* order: ID DOT ID  */
#line 716 "yacc_sql.y"
               {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[0].string), 0, (yyvsp[-2].string));
    }
#line 2332 "yacc_sql.tab.c"
    break;

  case 135: /* order: ID DOT ID DESC  */
#line 719 "yacc_sql.y"
                    {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 1, (yyvsp[-3].string));
    }
#line 2340 "yacc_sql.tab.c"
    break;

  case 136: /* order: ID DOT ID ASC  */
#line 722 "yacc_sql.y"
                   {
        selects_append_order(&CONTEXT->selects[CONTEXT->select_length], (yyvsp[-1].string), 0, (yyvsp[-3].string));
    }
#line 2348 "yacc_sql.tab.c"
    break;

  case 137: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 728 "yacc_sql.y"
                                                 {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
    }
#line 2357 "yacc_sql.tab.c"
    break;


#line 2361 "yacc_sql.tab.c"

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

#line 733 "yacc_sql.y"

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
