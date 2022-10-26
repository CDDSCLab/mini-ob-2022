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
  size_t condition_length;
  size_t from_length;
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
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
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


#line 141 "yacc_sql.tab.c"

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
  YYSYMBOL_NOT = 56,                       /* NOT  */
  YYSYMBOL_NUMBER = 57,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 58,                     /* FLOAT  */
  YYSYMBOL_ID = 59,                        /* ID  */
  YYSYMBOL_PATH = 60,                      /* PATH  */
  YYSYMBOL_SSS = 61,                       /* SSS  */
  YYSYMBOL_STAR = 62,                      /* STAR  */
  YYSYMBOL_STRING_V = 63,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 64,                  /* $accept  */
  YYSYMBOL_commands = 65,                  /* commands  */
  YYSYMBOL_command = 66,                   /* command  */
  YYSYMBOL_exit = 67,                      /* exit  */
  YYSYMBOL_help = 68,                      /* help  */
  YYSYMBOL_sync = 69,                      /* sync  */
  YYSYMBOL_begin = 70,                     /* begin  */
  YYSYMBOL_commit = 71,                    /* commit  */
  YYSYMBOL_rollback = 72,                  /* rollback  */
  YYSYMBOL_drop_table = 73,                /* drop_table  */
  YYSYMBOL_show_tables = 74,               /* show_tables  */
  YYSYMBOL_show_index = 75,                /* show_index  */
  YYSYMBOL_desc_table = 76,                /* desc_table  */
  YYSYMBOL_create_index = 77,              /* create_index  */
  YYSYMBOL_attrone = 78,                   /* attrone  */
  YYSYMBOL_attr_index = 79,                /* attr_index  */
  YYSYMBOL_attr_index_list = 80,           /* attr_index_list  */
  YYSYMBOL_drop_index = 81,                /* drop_index  */
  YYSYMBOL_create_table = 82,              /* create_table  */
  YYSYMBOL_attr_def_list = 83,             /* attr_def_list  */
  YYSYMBOL_attr_def = 84,                  /* attr_def  */
  YYSYMBOL_number = 85,                    /* number  */
  YYSYMBOL_type = 86,                      /* type  */
  YYSYMBOL_ID_get = 87,                    /* ID_get  */
  YYSYMBOL_insert = 88,                    /* insert  */
  YYSYMBOL_v_list = 89,                    /* v_list  */
  YYSYMBOL_node = 90,                      /* node  */
  YYSYMBOL_value_list = 91,                /* value_list  */
  YYSYMBOL_value = 92,                     /* value  */
  YYSYMBOL_delete = 93,                    /* delete  */
  YYSYMBOL_update = 94,                    /* update  */
  YYSYMBOL_select = 95,                    /* select  */
  YYSYMBOL_select_attr = 96,               /* select_attr  */
  YYSYMBOL_select_attr_list = 97,          /* select_attr_list  */
  YYSYMBOL_attr = 98,                      /* attr  */
  YYSYMBOL_aggr_attr = 99,                 /* aggr_attr  */
  YYSYMBOL_aggr_type = 100,                /* aggr_type  */
  YYSYMBOL_rel_list = 101,                 /* rel_list  */
  YYSYMBOL_where = 102,                    /* where  */
  YYSYMBOL_condition_list = 103,           /* condition_list  */
  YYSYMBOL_condition = 104,                /* condition  */
  YYSYMBOL_comOp = 105,                    /* comOp  */
  YYSYMBOL_group = 106,                    /* group  */
  YYSYMBOL_group_list = 107,               /* group_list  */
  YYSYMBOL_having = 108,                   /* having  */
  YYSYMBOL_having_list = 109,              /* having_list  */
  YYSYMBOL_load_data = 110                 /* load_data  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   216

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  64
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  230

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   318


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
      55,    56,    57,    58,    59,    60,    61,    62,    63
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   163,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   188,   193,   198,   204,   210,   216,   222,   228,
     234,   241,   248,   254,   262,   268,   274,   276,   283,   290,
     299,   301,   305,   316,   329,   332,   333,   334,   335,   336,
     339,   346,   359,   360,   365,   373,   375,   380,   384,   388,
     396,   406,   417,   434,   439,   443,   447,   449,   453,   458,
     463,   469,   473,   479,   489,   490,   491,   492,   493,   496,
     498,   502,   504,   508,   510,   515,   525,   533,   543,   552,
     561,   571,   583,   584,   585,   586,   587,   588,   589,   590,
     593,   595,   599,   601,   605,   607,   615,   617,   627
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
  "GE", "NE", "LIKE", "NOT", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "show_index", "desc_table", "create_index", "attrone", "attr_index",
  "attr_index_list", "drop_index", "create_table", "attr_def_list",
  "attr_def", "number", "type", "ID_get", "insert", "v_list", "node",
  "value_list", "value", "delete", "update", "select", "select_attr",
  "select_attr_list", "attr", "aggr_attr", "aggr_type", "rel_list",
  "where", "condition_list", "condition", "comOp", "group", "group_list",
  "having", "having_list", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-163)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -163,     4,  -163,   121,    30,    -1,   -52,    15,    10,    -6,
       2,   -14,    48,    51,    64,    65,    96,    61,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,    45,    50,   103,
      54,    58,  -163,  -163,  -163,  -163,  -163,    31,   107,    81,
     107,   107,   114,   129,   130,    93,  -163,    77,    78,    94,
    -163,  -163,  -163,  -163,  -163,    91,   123,    98,    82,   141,
     142,    87,    34,  -163,    88,  -163,  -163,   -20,  -163,  -163,
      89,   109,   108,    92,    95,    99,   100,   110,  -163,  -163,
    -163,   107,   107,   134,  -163,   136,   139,   143,   157,   145,
      -2,   160,   115,   126,  -163,   147,    56,   150,   111,  -163,
    -163,   112,   108,  -163,  -163,  -163,  -163,    67,  -163,  -163,
      22,  -163,    36,   125,  -163,    67,   163,    99,   154,  -163,
    -163,  -163,  -163,  -163,   156,   116,   159,   134,   144,   155,
     119,  -163,  -163,  -163,  -163,  -163,  -163,  -163,   124,    44,
      57,    -2,  -163,   108,   122,   147,   177,   127,  -163,   164,
     116,  -163,   148,   182,    67,   168,    36,  -163,  -163,  -163,
     149,  -163,   125,   185,   186,  -163,  -163,   172,   132,   174,
     164,   135,  -163,   155,   176,    62,   137,  -163,  -163,  -163,
    -163,  -163,   164,   190,   179,   180,  -163,   181,   197,    67,
     165,  -163,  -163,  -163,  -163,   198,   135,   167,  -163,  -163,
     155,   146,  -163,   180,    66,  -163,   188,  -163,  -163,    36,
     176,    67,  -163,   161,    66,  -163,    36,    67,   161,  -163
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    21,
      20,    15,    16,    17,    18,     9,    10,    11,    12,    13,
      14,     8,     5,     7,     6,     4,    19,     0,     0,     0,
       0,     0,    74,    75,    76,    77,    78,    69,    66,     0,
      66,    66,     0,     0,     0,     0,    24,     0,     0,     0,
      25,    26,    27,    23,    22,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,    64,    65,     0,    31,    29,
       0,     0,    81,     0,     0,     0,     0,     0,    28,    38,
      70,    66,    66,    79,    44,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    40,     0,     0,     0,    67,
      68,     0,    81,    72,    73,    71,    30,     0,    57,    58,
       0,    59,     0,    83,    60,     0,     0,     0,     0,    45,
      46,    47,    48,    49,    43,     0,     0,    79,   100,    55,
       0,    92,    93,    94,    95,    96,    97,    98,     0,     0,
       0,     0,    82,    81,     0,    40,     0,     0,    34,    36,
       0,    80,     0,     0,     0,     0,     0,    99,    87,    85,
      88,    86,    83,     0,     0,    41,    39,     0,     0,     0,
      36,     0,    62,    55,    52,     0,     0,    84,    61,   108,
      42,    35,    36,     0,     0,   102,    56,     0,     0,     0,
       0,    89,    90,    37,    33,     0,     0,   104,    54,    51,
      55,     0,    32,   102,     0,   101,     0,    91,   103,     0,
      52,     0,    53,   106,     0,   105,     0,     0,   106,   107
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,    47,  -163,  -148,  -163,  -163,    53,
      83,    52,  -163,  -163,  -163,    -9,  -163,  -162,  -115,  -163,
    -163,  -163,  -163,   -39,   -71,   -72,  -163,    75,  -107,    41,
      63,  -119,  -163,     3,  -163,   -13,  -163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   159,   192,   179,    30,    31,   128,
     105,    96,   134,   106,    32,   198,   199,   165,   122,    33,
      34,    35,    49,    73,    50,    51,    52,   112,   101,   152,
     123,   149,   163,   207,   215,   225,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      92,    91,   139,   150,     2,   138,    97,    53,     3,     4,
     153,    75,    76,    56,     5,     6,     7,     8,     9,    10,
      11,   196,    54,    55,    12,    13,    14,    42,    43,    44,
      45,    46,   194,    57,   169,   171,    40,    94,    41,    47,
      15,    16,    95,    58,   203,    59,   173,   185,   216,   183,
      17,    60,   109,   110,    61,   118,   119,   120,    47,   121,
     140,    48,    42,    43,    44,    45,    46,    62,    63,    71,
     201,   141,   142,   143,   144,   145,   146,   147,   148,   129,
     130,   131,   132,   133,   210,   141,   142,   143,   144,   145,
     146,   147,   148,    47,    42,    43,    44,    45,    46,    64,
     221,   118,   119,   168,    66,   121,   223,   227,    65,    67,
     195,    68,   228,    69,   118,   119,   170,    70,   121,   118,
     119,   200,    74,   121,   118,   119,    72,    37,   121,    38,
      39,    77,    78,    79,    80,   213,    81,    82,    83,    84,
      85,    87,   219,    86,    88,    89,    90,    93,    98,    99,
     100,   102,   226,   111,   113,   108,   103,   114,   104,   107,
     116,   115,   117,   124,   125,   126,   127,   135,   151,   154,
     136,   137,   156,   157,   164,   158,   160,   162,   166,   167,
     176,   174,   181,   178,    94,   182,   184,   186,   188,   189,
     190,   191,   193,   204,    47,   197,   202,   205,   208,   206,
     209,   212,   214,   211,   224,   217,   220,   180,   175,   177,
     155,   222,   161,   187,   172,   229,   218
};

static const yytype_uint8 yycheck[] =
{
      72,    72,   117,   122,     0,   112,    77,    59,     4,     5,
     125,    50,    51,     3,    10,    11,    12,    13,    14,    15,
      16,   183,     7,     8,    20,    21,    22,    28,    29,    30,
      31,    32,   180,    39,   149,   150,     6,    57,     8,    59,
      36,    37,    62,    41,   192,    59,   153,   166,   210,   164,
      46,     3,    91,    92,     3,    57,    58,    59,    59,    61,
      38,    62,    28,    29,    30,    31,    32,     3,     3,    38,
     185,    49,    50,    51,    52,    53,    54,    55,    56,    23,
      24,    25,    26,    27,   199,    49,    50,    51,    52,    53,
      54,    55,    56,    59,    28,    29,    30,    31,    32,     3,
     219,    57,    58,    59,    59,    61,   221,   226,    47,    59,
     181,     8,   227,    59,    57,    58,    59,    59,    61,    57,
      58,    59,    41,    61,    57,    58,    19,     6,    61,     8,
       9,    17,     3,     3,    41,   206,    59,    59,    44,    48,
      17,    59,   214,    45,     3,     3,    59,    59,    59,    40,
      42,    59,   224,    19,    18,    45,    61,    18,    59,    59,
       3,    18,    17,     3,    49,    39,    19,    17,    43,     6,
      59,    59,    18,    17,    19,    59,    17,    33,    59,    55,
       3,    59,    34,    19,    57,     3,    18,    38,     3,     3,
      18,    59,    18,     3,    59,    19,    59,    18,    17,    19,
       3,     3,    35,    38,    43,    59,    18,   160,   155,   157,
     127,   220,   137,   172,   151,   228,   213
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    65,     0,     4,     5,    10,    11,    12,    13,    14,
      15,    16,    20,    21,    22,    36,    37,    46,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      81,    82,    88,    93,    94,    95,   110,     6,     8,     9,
       6,     8,    28,    29,    30,    31,    32,    59,    62,    96,
      98,    99,   100,    59,     7,     8,     3,    39,    41,    59,
       3,     3,     3,     3,     3,    47,    59,    59,     8,    59,
      59,    38,    19,    97,    41,    97,    97,    17,     3,     3,
      41,    59,    59,    44,    48,    17,    45,    59,     3,     3,
      59,    98,    99,    59,    57,    62,    85,    98,    59,    40,
      42,   102,    59,    61,    59,    84,    87,    59,    45,    97,
      97,    19,   101,    18,    18,    18,     3,    17,    57,    58,
      59,    61,    92,   104,     3,    49,    39,    19,    83,    23,
      24,    25,    26,    27,    86,    17,    59,    59,   102,    92,
      38,    49,    50,    51,    52,    53,    54,    55,    56,   105,
     105,    43,   103,    92,     6,    84,    18,    17,    59,    78,
      17,   101,    33,   106,    19,    91,    59,    55,    59,    92,
      59,    92,   104,   102,    59,    83,     3,    85,    19,    80,
      78,    34,     3,    92,    18,   105,    38,   103,     3,     3,
      18,    59,    79,    18,    80,    98,    91,    19,    89,    90,
      59,    92,    59,    80,     3,    18,    19,   107,    17,     3,
      92,    38,     3,    98,    35,   108,    91,    59,   107,    99,
      18,   105,    89,    92,    43,   109,    99,   105,    92,   109
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    64,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    77,    78,    79,    80,    80,    81,    82,
      83,    83,    84,    84,    85,    86,    86,    86,    86,    86,
      87,    88,    89,    89,    90,    91,    91,    92,    92,    92,
      93,    94,    95,    96,    96,    96,    97,    97,    97,    98,
      98,    99,    99,    99,   100,   100,   100,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   104,   104,   104,
     104,   104,   105,   105,   105,   105,   105,   105,   105,   105,
     106,   106,   107,   107,   108,   108,   109,   109,   110
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     2,     2,     2,     4,     3,
       5,     3,    11,    10,     1,     1,     0,     3,     4,     8,
       0,     3,     5,     2,     1,     1,     1,     1,     1,     1,
       1,    10,     0,     5,     2,     0,     3,     1,     1,     1,
       5,     8,     8,     2,     2,     2,     0,     3,     3,     1,
       3,     4,     4,     4,     1,     1,     1,     1,     1,     0,
       3,     0,     3,     0,     3,     3,     3,     3,     3,     5,
       5,     7,     1,     1,     1,     1,     1,     1,     1,     2,
       0,     5,     0,     3,     0,     5,     0,     5,     8
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
#line 188 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1401 "yacc_sql.tab.c"
    break;

  case 23: /* help: HELP SEMICOLON  */
#line 193 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1409 "yacc_sql.tab.c"
    break;

  case 24: /* sync: SYNC SEMICOLON  */
#line 198 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1417 "yacc_sql.tab.c"
    break;

  case 25: /* begin: TRX_BEGIN SEMICOLON  */
#line 204 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1425 "yacc_sql.tab.c"
    break;

  case 26: /* commit: TRX_COMMIT SEMICOLON  */
#line 210 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1433 "yacc_sql.tab.c"
    break;

  case 27: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 216 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1441 "yacc_sql.tab.c"
    break;

  case 28: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 222 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1450 "yacc_sql.tab.c"
    break;

  case 29: /* show_tables: SHOW TABLES SEMICOLON  */
#line 228 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1458 "yacc_sql.tab.c"
    break;

  case 30: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 234 "yacc_sql.y"
                                 {
      CONTEXT->ssql->flag = SCF_SHOW_INDEX;
	  show_index_init(&CONTEXT->ssql->sstr.show_index, (yyvsp[-1].string));
    }
#line 1467 "yacc_sql.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 241 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1476 "yacc_sql.tab.c"
    break;

  case 32: /* create_index: CREATE UNIQUE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 249 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 1, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1486 "yacc_sql.tab.c"
    break;

  case 33: /* create_index: CREATE INDEX ID ON ID LBRACE attrone attr_index_list RBRACE SEMICOLON  */
#line 255 "yacc_sql.y"
        {
		CONTEXT->ssql->flag = SCF_CREATE_INDEX;
		create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), 0, CONTEXT->attr_num+1);
		CONTEXT->attr_num = 0;
	}
#line 1496 "yacc_sql.tab.c"
    break;

  case 34: /* attrone: ID  */
#line 263 "yacc_sql.y"
        {
		create_index_first_attr(&CONTEXT->ssql->sstr.create_index, (yyvsp[0].string));
	}
#line 1504 "yacc_sql.tab.c"
    break;

  case 35: /* attr_index: ID  */
#line 269 "yacc_sql.y"
        {
		create_index_append_attr(&CONTEXT->ssql->sstr.create_index, CONTEXT->attr_num, (yyvsp[0].string));
		CONTEXT->attr_num++;
	}
#line 1513 "yacc_sql.tab.c"
    break;

  case 37: /* attr_index_list: COMMA attr_index attr_index_list  */
#line 277 "yacc_sql.y"
        {

	}
#line 1521 "yacc_sql.tab.c"
    break;

  case 38: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 284 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1530 "yacc_sql.tab.c"
    break;

  case 39: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 291 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1542 "yacc_sql.tab.c"
    break;

  case 41: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 301 "yacc_sql.y"
                                   {    }
#line 1548 "yacc_sql.tab.c"
    break;

  case 42: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 306 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1563 "yacc_sql.tab.c"
    break;

  case 43: /* attr_def: ID_get type  */
#line 317 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1578 "yacc_sql.tab.c"
    break;

  case 44: /* number: NUMBER  */
#line 329 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 1584 "yacc_sql.tab.c"
    break;

  case 45: /* type: INT_T  */
#line 332 "yacc_sql.y"
          { (yyval.number) = INTS; }
#line 1590 "yacc_sql.tab.c"
    break;

  case 46: /* type: STRING_T  */
#line 333 "yacc_sql.y"
               { (yyval.number) = CHARS; }
#line 1596 "yacc_sql.tab.c"
    break;

  case 47: /* type: TEXT_T  */
#line 334 "yacc_sql.y"
             { (yyval.number)=TEXTS; }
#line 1602 "yacc_sql.tab.c"
    break;

  case 48: /* type: FLOAT_T  */
#line 335 "yacc_sql.y"
              { (yyval.number) = FLOATS; }
#line 1608 "yacc_sql.tab.c"
    break;

  case 49: /* type: DATE_T  */
#line 336 "yacc_sql.y"
             { (yyval.number) = DATES; }
#line 1614 "yacc_sql.tab.c"
    break;

  case 50: /* ID_get: ID  */
#line 339 "yacc_sql.y"
       {
        char *temp=(yyvsp[0].string);
        snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
    }
#line 1623 "yacc_sql.tab.c"
    break;

  case 51: /* insert: INSERT INTO ID VALUES LBRACE value value_list RBRACE v_list SEMICOLON  */
#line 347 "yacc_sql.y"
        {
		CONTEXT->ssql->flag=SCF_INSERT;
		CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
		CONTEXT->every_group_count=0;
        CONTEXT->group_num = CONTEXT->group_num + 1;

		inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-7].string), CONTEXT->values, CONTEXT->insert_groups, CONTEXT->group_num);

		//临时变量清零
		CONTEXT->value_length=0;
    }
#line 1639 "yacc_sql.tab.c"
    break;

  case 53: /* v_list: node value value_list RBRACE v_list  */
#line 361 "yacc_sql.y"
    {
    }
#line 1646 "yacc_sql.tab.c"
    break;

  case 54: /* node: COMMA LBRACE  */
#line 366 "yacc_sql.y"
    {
		// 每进来一次，表明已经有一个括号的值，放入了values，也就是卓这里处理的是前一个括号的属性
    	CONTEXT->insert_groups[CONTEXT->group_num] = CONTEXT->every_group_count;
    	CONTEXT->every_group_count=0;
    	CONTEXT->group_num = CONTEXT->group_num + 1;
    }
#line 1657 "yacc_sql.tab.c"
    break;

  case 56: /* value_list: COMMA value value_list  */
#line 375 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1665 "yacc_sql.tab.c"
    break;

  case 57: /* value: NUMBER  */
#line 380 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		CONTEXT->every_group_count++;
		}
#line 1674 "yacc_sql.tab.c"
    break;

  case 58: /* value: FLOAT  */
#line 384 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		CONTEXT->every_group_count++;
		}
#line 1683 "yacc_sql.tab.c"
    break;

  case 59: /* value: SSS  */
#line 388 "yacc_sql.y"
         {
		(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  		value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		CONTEXT->every_group_count++;
		}
#line 1693 "yacc_sql.tab.c"
    break;

  case 60: /* delete: DELETE FROM ID where SEMICOLON  */
#line 397 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1705 "yacc_sql.tab.c"
    break;

  case 61: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 407 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1717 "yacc_sql.tab.c"
    break;

  case 62: /* select: SELECT select_attr FROM ID rel_list where group SEMICOLON  */
#line 417 "yacc_sql.y"
                                                              {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-4].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1737 "yacc_sql.tab.c"
    break;

  case 63: /* select_attr: STAR select_attr_list  */
#line 434 "yacc_sql.y"
                          {
        RelAttr attr;
        relation_attr_init(&attr, NULL, "*");
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
    }
#line 1747 "yacc_sql.tab.c"
    break;

  case 64: /* select_attr: attr select_attr_list  */
#line 439 "yacc_sql.y"
                            {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1756 "yacc_sql.tab.c"
    break;

  case 65: /* select_attr: aggr_attr select_attr_list  */
#line 443 "yacc_sql.y"
                                 {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1765 "yacc_sql.tab.c"
    break;

  case 67: /* select_attr_list: COMMA attr select_attr_list  */
#line 449 "yacc_sql.y"
                                  {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1774 "yacc_sql.tab.c"
    break;

  case 68: /* select_attr_list: COMMA aggr_attr select_attr_list  */
#line 453 "yacc_sql.y"
                                       {
        selects_append_attribute(&CONTEXT->ssql->sstr.selection, (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 1783 "yacc_sql.tab.c"
    break;

  case 69: /* attr: ID  */
#line 458 "yacc_sql.y"
       {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, NULL, (yyvsp[0].string));
        (yyval._attr) = attr;
    }
#line 1793 "yacc_sql.tab.c"
    break;

  case 70: /* attr: ID DOT ID  */
#line 463 "yacc_sql.y"
                {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, NULL, (yyvsp[-2].string));
        (yyval._attr) = attr;
    }
#line 1803 "yacc_sql.tab.c"
    break;

  case 71: /* aggr_attr: aggr_type LBRACE attr RBRACE  */
#line 469 "yacc_sql.y"
                                   {
        relation_attr_aggr((yyvsp[-1]._attr), (yyvsp[-3].number));
        (yyval._attr) = (yyvsp[-1]._attr);
    }
#line 1812 "yacc_sql.tab.c"
    break;

  case 72: /* aggr_attr: aggr_type LBRACE STAR RBRACE  */
#line 473 "yacc_sql.y"
                                   {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        relation_attr_init(attr, NULL, "*");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 1823 "yacc_sql.tab.c"
    break;

  case 73: /* aggr_attr: aggr_type LBRACE number RBRACE  */
#line 479 "yacc_sql.y"
                                     {
        RelAttr *attr = (RelAttr *)(malloc(sizeof(RelAttr)));
        if ((yyvsp[-1].number) != 1) {
            YYERROR;
        }
        relation_attr_init(attr, NULL, "1");
        relation_attr_aggr(attr, (yyvsp[-3].number));
        (yyval._attr) = attr;
    }
#line 1837 "yacc_sql.tab.c"
    break;

  case 74: /* aggr_type: MAX  */
#line 489 "yacc_sql.y"
          { (yyval.number) = AGGR_MAX; }
#line 1843 "yacc_sql.tab.c"
    break;

  case 75: /* aggr_type: MIN  */
#line 490 "yacc_sql.y"
          { (yyval.number) = AGGR_MIN; }
#line 1849 "yacc_sql.tab.c"
    break;

  case 76: /* aggr_type: COUNT  */
#line 491 "yacc_sql.y"
            { (yyval.number) = AGGR_COUNT; }
#line 1855 "yacc_sql.tab.c"
    break;

  case 77: /* aggr_type: AVG  */
#line 492 "yacc_sql.y"
          { (yyval.number) = AGGR_AVG; }
#line 1861 "yacc_sql.tab.c"
    break;

  case 78: /* aggr_type: SUM  */
#line 493 "yacc_sql.y"
          { (yyval.number) = AGGR_SUM; }
#line 1867 "yacc_sql.tab.c"
    break;

  case 80: /* rel_list: COMMA ID rel_list  */
#line 498 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1875 "yacc_sql.tab.c"
    break;

  case 82: /* where: WHERE condition condition_list  */
#line 504 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1883 "yacc_sql.tab.c"
    break;

  case 84: /* condition_list: AND condition condition_list  */
#line 510 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 1891 "yacc_sql.tab.c"
    break;

  case 85: /* condition: ID comOp value  */
#line 515 "yacc_sql.y"
                   {
        RelAttr left_attr;
        relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 1906 "yacc_sql.tab.c"
    break;

  case 86: /* condition: value comOp value  */
#line 525 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 1919 "yacc_sql.tab.c"
    break;

  case 87: /* condition: ID comOp ID  */
#line 533 "yacc_sql.y"
                      {
		RelAttr left_attr;
		relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 1934 "yacc_sql.tab.c"
    break;

  case 88: /* condition: value comOp ID  */
#line 543 "yacc_sql.y"
                     {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
		RelAttr right_attr;
		relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
	}
#line 1948 "yacc_sql.tab.c"
    break;

  case 89: /* condition: ID DOT ID comOp value  */
#line 552 "yacc_sql.y"
                            {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
		Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 1962 "yacc_sql.tab.c"
    break;

  case 90: /* condition: value comOp ID DOT ID  */
#line 561 "yacc_sql.y"
                            {
		Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 1977 "yacc_sql.tab.c"
    break;

  case 91: /* condition: ID DOT ID comOp ID DOT ID  */
#line 571 "yacc_sql.y"
                                {
		RelAttr left_attr;
		relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
		RelAttr right_attr;
		relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

		Condition condition;
		condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
		CONTEXT->conditions[CONTEXT->condition_length++] = condition;
    }
#line 1992 "yacc_sql.tab.c"
    break;

  case 92: /* comOp: EQ  */
#line 583 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 1998 "yacc_sql.tab.c"
    break;

  case 93: /* comOp: LT  */
#line 584 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2004 "yacc_sql.tab.c"
    break;

  case 94: /* comOp: GT  */
#line 585 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2010 "yacc_sql.tab.c"
    break;

  case 95: /* comOp: LE  */
#line 586 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2016 "yacc_sql.tab.c"
    break;

  case 96: /* comOp: GE  */
#line 587 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2022 "yacc_sql.tab.c"
    break;

  case 97: /* comOp: NE  */
#line 588 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2028 "yacc_sql.tab.c"
    break;

  case 98: /* comOp: LIKE  */
#line 589 "yacc_sql.y"
           { CONTEXT->comp = LIKE_OP; }
#line 2034 "yacc_sql.tab.c"
    break;

  case 99: /* comOp: NOT LIKE  */
#line 590 "yacc_sql.y"
               { CONTEXT->comp = NOT_LIKE_OP; }
#line 2040 "yacc_sql.tab.c"
    break;

  case 101: /* group: GROUP BY attr group_list having  */
#line 595 "yacc_sql.y"
                                      {
        selects_append_groups(&CONTEXT->ssql->sstr.selection, (yyvsp[-2]._attr));
        free((yyvsp[-2]._attr));
    }
#line 2049 "yacc_sql.tab.c"
    break;

  case 103: /* group_list: COMMA attr group_list  */
#line 601 "yacc_sql.y"
                            {
        selects_append_groups(&CONTEXT->ssql->sstr.selection, (yyvsp[-1]._attr));
        free((yyvsp[-1]._attr));
    }
#line 2058 "yacc_sql.tab.c"
    break;

  case 105: /* having: HAVING aggr_attr comOp value having_list  */
#line 607 "yacc_sql.y"
                                               {
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

        Condition condition;
        condition_init(&condition, CONTEXT->comp, 1, (yyvsp[-3]._attr), NULL, 0, NULL, right_value);
        free((yyvsp[-3]._attr));
        selects_append_having(&CONTEXT->ssql->sstr.selection, &condition);
    }
#line 2071 "yacc_sql.tab.c"
    break;

  case 107: /* having_list: AND aggr_attr comOp value having_list  */
#line 617 "yacc_sql.y"
                                            {
        Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

        Condition condition;
        condition_init(&condition, CONTEXT->comp, 1, (yyvsp[-3]._attr), NULL, 0, NULL, right_value);
        free((yyvsp[-3]._attr));
        selects_append_having(&CONTEXT->ssql->sstr.selection, &condition);
    }
#line 2084 "yacc_sql.tab.c"
    break;

  case 108: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 627 "yacc_sql.y"
                                                 {
        CONTEXT->ssql->flag = SCF_LOAD_DATA;
        load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
    }
#line 2093 "yacc_sql.tab.c"
    break;


#line 2097 "yacc_sql.tab.c"

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

#line 632 "yacc_sql.y"

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
