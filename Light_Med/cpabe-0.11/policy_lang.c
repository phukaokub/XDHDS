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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "policy_lang.y"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <glib.h>
#include <pbc.h>

#include "common.h"
#include "policy_lang.h"

typedef struct
{
	uint64_t value;
	int bits; /* zero if this is a flexint */
}
sized_integer_t;

typedef struct
{
	int k;               /* one if leaf, otherwise threshold */
	char* attr;          /* attribute string if leaf, otherwise null */
	GPtrArray* children; /* pointers to bswabe_policy_t's, len == 0 for leaves */
}
cpabe_policy_t;

cpabe_policy_t* final_policy = 0;

int yylex();
void yyerror( const char* s );
sized_integer_t* expint( uint64_t value, uint64_t bits );
sized_integer_t* flexint( uint64_t value );
cpabe_policy_t* leaf_policy( char* attr );
cpabe_policy_t* kof2_policy( int k, cpabe_policy_t* l, cpabe_policy_t* r );
cpabe_policy_t* kof_policy( int k, GPtrArray* list );
cpabe_policy_t* eq_policy( sized_integer_t* n, char* attr );
cpabe_policy_t* lt_policy( sized_integer_t* n, char* attr );
cpabe_policy_t* gt_policy( sized_integer_t* n, char* attr );
cpabe_policy_t* le_policy( sized_integer_t* n, char* attr );
cpabe_policy_t* ge_policy( sized_integer_t* n, char* attr );

#line 114 "policy_lang.c"

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
    TAG = 258,                     /* TAG  */
    INTLIT = 259,                  /* INTLIT  */
    OR = 260,                      /* OR  */
    AND = 261,                     /* AND  */
    OF = 262,                      /* OF  */
    LEQ = 263,                     /* LEQ  */
    GEQ = 264                      /* GEQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 45 "policy_lang.y"

	char* str;
	uint64_t nat;
  sized_integer_t* sint;
	cpabe_policy_t* tree;
	GPtrArray* list;

#line 178 "policy_lang.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TAG = 3,                        /* TAG  */
  YYSYMBOL_INTLIT = 4,                     /* INTLIT  */
  YYSYMBOL_OR = 5,                         /* OR  */
  YYSYMBOL_AND = 6,                        /* AND  */
  YYSYMBOL_OF = 7,                         /* OF  */
  YYSYMBOL_LEQ = 8,                        /* LEQ  */
  YYSYMBOL_GEQ = 9,                        /* GEQ  */
  YYSYMBOL_10_ = 10,                       /* '#'  */
  YYSYMBOL_11_ = 11,                       /* '('  */
  YYSYMBOL_12_ = 12,                       /* ')'  */
  YYSYMBOL_13_ = 13,                       /* '='  */
  YYSYMBOL_14_ = 14,                       /* '<'  */
  YYSYMBOL_15_ = 15,                       /* '>'  */
  YYSYMBOL_16_ = 16,                       /* ','  */
  YYSYMBOL_YYACCEPT = 17,                  /* $accept  */
  YYSYMBOL_result = 18,                    /* result  */
  YYSYMBOL_number = 19,                    /* number  */
  YYSYMBOL_policy = 20,                    /* policy  */
  YYSYMBOL_arg_list = 21                   /* arg_list  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   45

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  17
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  5
/* YYNRULES -- Number of rules.  */
#define YYNRULES  21
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  44

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   264


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
       2,     2,     2,     2,     2,    10,     2,     2,     2,     2,
      11,    12,     2,     2,    16,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      14,    13,    15,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    67,    67,    69,    70,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      88,    90
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
  "\"end of file\"", "error", "\"invalid token\"", "TAG", "INTLIT", "OR",
  "AND", "OF", "LEQ", "GEQ", "'#'", "'('", "')'", "'='", "'<'", "'>'",
  "','", "$accept", "result", "number", "policy", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-5)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -2,    -1,    -4,    -2,     4,     2,    17,     1,     1,     1,
       1,     1,    13,    29,    15,    -5,    32,    33,    34,    37,
      38,    -2,    -2,    35,    -5,    -5,    -5,    -5,    -5,    -2,
      -5,    -5,    -5,    -5,    -5,    -5,    -5,    19,    -5,    17,
      22,    -5,    -2,    17
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     4,     0,     0,     0,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     4,    12,    13,     9,    10,    11,     0,
       3,    19,    17,    18,    14,    15,    16,     6,     7,    20,
       0,     8,     0,    21
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -5,    -5,    21,    -3,    -5
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    40
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      14,     1,     2,    12,    15,    23,    13,     7,     8,     3,
      16,    17,     9,    10,    11,    18,    19,    20,    37,    38,
      21,    22,    21,    22,    29,    22,    39,    31,    24,    25,
      26,    27,    28,    30,    41,    32,    33,    34,    42,    43,
      35,    36,     0,     0,     0,    13
};

static const yytype_int8 yycheck[] =
{
       3,     3,     4,     7,     0,     4,    10,     8,     9,    11,
       8,     9,    13,    14,    15,    13,    14,    15,    21,    22,
       5,     6,     5,     6,    11,     6,    29,    12,     7,     8,
       9,    10,    11,     4,    12,     3,     3,     3,    16,    42,
       3,     3,    -1,    -1,    -1,    10
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,    11,    18,    19,    20,     8,     9,    13,
      14,    15,     7,    10,    20,     0,     8,     9,    13,    14,
      15,     5,     6,     4,    19,    19,    19,    19,    19,    11,
       4,    12,     3,     3,     3,     3,     3,    20,    20,    20,
      21,    12,    16,    20
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    17,    18,    19,    19,    20,    20,    20,    20,    20,
      20,    20,    20,    20,    20,    20,    20,    20,    20,    20,
      21,    21
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     3,     1,     1,     3,     3,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3
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
        yyerror (YY_("syntax error: cannot back up")); \
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
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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
      yychar = yylex ();
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
  case 2: /* result: policy  */
#line 67 "policy_lang.y"
               { final_policy = (yyvsp[0].tree) ;}
#line 1192 "policy_lang.c"
    break;

  case 3: /* number: INTLIT '#' INTLIT  */
#line 69 "policy_lang.y"
                                     { (yyval.sint) = expint((yyvsp[-2].nat), (yyvsp[0].nat)); }
#line 1198 "policy_lang.c"
    break;

  case 4: /* number: INTLIT  */
#line 70 "policy_lang.y"
                                     { (yyval.sint) = flexint((yyvsp[0].nat));    }
#line 1204 "policy_lang.c"
    break;

  case 5: /* policy: TAG  */
#line 72 "policy_lang.y"
                                     { (yyval.tree) = leaf_policy((yyvsp[0].str));        }
#line 1210 "policy_lang.c"
    break;

  case 6: /* policy: policy OR policy  */
#line 73 "policy_lang.y"
                                     { (yyval.tree) = kof2_policy(1, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1216 "policy_lang.c"
    break;

  case 7: /* policy: policy AND policy  */
#line 74 "policy_lang.y"
                                     { (yyval.tree) = kof2_policy(2, (yyvsp[-2].tree), (yyvsp[0].tree)); }
#line 1222 "policy_lang.c"
    break;

  case 8: /* policy: INTLIT OF '(' arg_list ')'  */
#line 75 "policy_lang.y"
                                     { (yyval.tree) = kof_policy((yyvsp[-4].nat), (yyvsp[-1].list));     }
#line 1228 "policy_lang.c"
    break;

  case 9: /* policy: TAG '=' number  */
#line 76 "policy_lang.y"
                                     { (yyval.tree) = eq_policy((yyvsp[0].sint), (yyvsp[-2].str));      }
#line 1234 "policy_lang.c"
    break;

  case 10: /* policy: TAG '<' number  */
#line 77 "policy_lang.y"
                                     { (yyval.tree) = lt_policy((yyvsp[0].sint), (yyvsp[-2].str));      }
#line 1240 "policy_lang.c"
    break;

  case 11: /* policy: TAG '>' number  */
#line 78 "policy_lang.y"
                                     { (yyval.tree) = gt_policy((yyvsp[0].sint), (yyvsp[-2].str));      }
#line 1246 "policy_lang.c"
    break;

  case 12: /* policy: TAG LEQ number  */
#line 79 "policy_lang.y"
                                     { (yyval.tree) = le_policy((yyvsp[0].sint), (yyvsp[-2].str));      }
#line 1252 "policy_lang.c"
    break;

  case 13: /* policy: TAG GEQ number  */
#line 80 "policy_lang.y"
                                     { (yyval.tree) = ge_policy((yyvsp[0].sint), (yyvsp[-2].str));      }
#line 1258 "policy_lang.c"
    break;

  case 14: /* policy: number '=' TAG  */
#line 81 "policy_lang.y"
                                     { (yyval.tree) = eq_policy((yyvsp[-2].sint), (yyvsp[0].str));      }
#line 1264 "policy_lang.c"
    break;

  case 15: /* policy: number '<' TAG  */
#line 82 "policy_lang.y"
                                     { (yyval.tree) = gt_policy((yyvsp[-2].sint), (yyvsp[0].str));      }
#line 1270 "policy_lang.c"
    break;

  case 16: /* policy: number '>' TAG  */
#line 83 "policy_lang.y"
                                     { (yyval.tree) = lt_policy((yyvsp[-2].sint), (yyvsp[0].str));      }
#line 1276 "policy_lang.c"
    break;

  case 17: /* policy: number LEQ TAG  */
#line 84 "policy_lang.y"
                                     { (yyval.tree) = ge_policy((yyvsp[-2].sint), (yyvsp[0].str));      }
#line 1282 "policy_lang.c"
    break;

  case 18: /* policy: number GEQ TAG  */
#line 85 "policy_lang.y"
                                     { (yyval.tree) = le_policy((yyvsp[-2].sint), (yyvsp[0].str));      }
#line 1288 "policy_lang.c"
    break;

  case 19: /* policy: '(' policy ')'  */
#line 86 "policy_lang.y"
                                     { (yyval.tree) = (yyvsp[-1].tree);                     }
#line 1294 "policy_lang.c"
    break;

  case 20: /* arg_list: policy  */
#line 88 "policy_lang.y"
                                     { (yyval.list) = g_ptr_array_new();
                                       g_ptr_array_add((yyval.list), (yyvsp[0].tree)); }
#line 1301 "policy_lang.c"
    break;

  case 21: /* arg_list: arg_list ',' policy  */
#line 90 "policy_lang.y"
                                     { (yyval.list) = (yyvsp[-2].list);
                                       g_ptr_array_add((yyval.list), (yyvsp[0].tree)); }
#line 1308 "policy_lang.c"
    break;


#line 1312 "policy_lang.c"

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
      yyerror (YY_("syntax error"));
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
                      yytoken, &yylval);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 94 "policy_lang.y"


sized_integer_t*
expint( uint64_t value, uint64_t bits )
{
	sized_integer_t* s;

	if( bits == 0 )
		die("error parsing policy: zero-length integer \"%llub%llu\"\n",
				value, bits);
	else if( bits > 64 )
		die("error parsing policy: no more than 64 bits allowed \"%llub%llu\"\n",
				value, bits);

	s = malloc(sizeof(sized_integer_t));
	s->value = value;
	s->bits = bits;

	return s;
}

sized_integer_t*
flexint( uint64_t value )
{
	sized_integer_t* s;

	s = malloc(sizeof(sized_integer_t));
	s->value = value;
	s->bits = 0;

	return s;
}

void
policy_free( cpabe_policy_t* p )
{
	int i;

	if( p->attr )
		free(p->attr);

	for( i = 0; i < p->children->len; i++ )
		policy_free(g_ptr_array_index(p->children, i));
	g_ptr_array_free(p->children, 1);

	free(p);
}

cpabe_policy_t*
leaf_policy( char* attr )
{
	cpabe_policy_t* p;

	p = (cpabe_policy_t*) malloc(sizeof(cpabe_policy_t));
	p->k = 1;
	p->attr = attr;
	p->children = g_ptr_array_new();

	return p;
}

cpabe_policy_t*
kof2_policy( int k, cpabe_policy_t* l, cpabe_policy_t* r )
{
	cpabe_policy_t* p;

	p = (cpabe_policy_t*) malloc(sizeof(cpabe_policy_t));
	p->k = k;
	p->attr = 0;
	p->children = g_ptr_array_new();
	g_ptr_array_add(p->children, l);
	g_ptr_array_add(p->children, r);

	return p;
}

cpabe_policy_t*
kof_policy( int k, GPtrArray* list )
{
	cpabe_policy_t* p;

	if( k < 1 )
		die("error parsing policy: trivially satisfied operator \"%dof\"\n", k);
	else if( k > list->len )
		die("error parsing policy: unsatisfiable operator \"%dof\" (only %d operands)\n",
				k, list->len);
	else if( list->len == 1 )
		die("error parsing policy: identity operator \"%dof\" (only one operand)\n", k);

	p = (cpabe_policy_t*) malloc(sizeof(cpabe_policy_t));
	p->k = k;
	p->attr = 0;
	p->children = list;

	return p;
}

char*
bit_marker( char* base, char* tplate, int bit, char val )
{
	char* lx;
	char* rx;
	char* s;

 	lx = g_strnfill(64 - bit - 1, 'x');
	rx = g_strnfill(bit, 'x');
	s = g_strdup_printf(tplate, base, lx, !!val, rx);
	free(lx);
	free(rx);

	return s;
}

cpabe_policy_t*
eq_policy( sized_integer_t* n, char* attr )
{
	if( n->bits == 0 )
		return leaf_policy
			(g_strdup_printf("%s_flexint_%llu", attr, n->value));
	else
		return leaf_policy
			(g_strdup_printf("%s_expint%02d_%llu", attr, n->bits, n->value));

	return 0;
}

cpabe_policy_t*
bit_marker_list( int gt, char* attr, char* tplate, int bits, uint64_t value )
{
	cpabe_policy_t* p;
	int i;

	i = 0;
	while( gt ? (((uint64_t)1)<<i & value) : !(((uint64_t)1)<<i & value) )
		i++;

	p = leaf_policy(bit_marker(attr, tplate, i, gt));
	for( i = i + 1; i < bits; i++ )
		if( gt )
			p = kof2_policy(((uint64_t)1<<i & value) ? 2 : 1, p,
											leaf_policy(bit_marker(attr, tplate, i, gt)));
		else
			p = kof2_policy(((uint64_t)1<<i & value) ? 1 : 2, p,
											leaf_policy(bit_marker(attr, tplate, i, gt)));

	return p;
}

cpabe_policy_t*
flexint_leader( int gt, char* attr, uint64_t value )
{
	cpabe_policy_t* p;
	int k;

	p = (cpabe_policy_t*) malloc(sizeof(cpabe_policy_t));
	p->attr = 0;
	p->children = g_ptr_array_new();

	for( k = 2; k <= 32; k *= 2 )
		if( ( gt && ((uint64_t)1<<k) >  value) ||
				(!gt && ((uint64_t)1<<k) >= value) )
			g_ptr_array_add
				(p->children, leaf_policy
				 (g_strdup_printf(gt ? "%s_ge_2^%02d" : "%s_lt_2^%02d", attr, k)));

	p->k = gt ? 1 : p->children->len;

	if( p->children->len == 0 )
	{
		policy_free(p);
		p = 0;
	}
	else if( p->children->len == 1 )
	{
		cpabe_policy_t* t;
		
		t = g_ptr_array_remove_index(p->children, 0);
		policy_free(p);
		p = t;
	}
	
	return p;
}

cpabe_policy_t*
cmp_policy( sized_integer_t* n, int gt, char* attr )
{
	cpabe_policy_t* p;
	char* tplate;

	/* some error checking */

	if( gt && n->value >= ((uint64_t)1<<(n->bits ? n->bits : 64)) - 1 )
		die("error parsing policy: unsatisfiable integer comparison %s > %llu\n"
				"(%d-bits are insufficient to satisfy)\n", attr, n->value,
				n->bits ? n->bits : 64);
	else if( !gt && n->value == 0 )
		die("error parsing policy: unsatisfiable integer comparison %s < 0\n"
				"(all numerical attributes are unsigned)\n", attr);
	else if( !gt && n->value > ((uint64_t)1<<(n->bits ? n->bits : 64)) - 1 )
		die("error parsing policy: trivially satisfied integer comparison %s < %llu\n"
				"(any %d-bit number will satisfy)\n", attr, n->value,
				n->bits ? n->bits : 64);

	/* create it */

	/* horrible */
	tplate = n->bits ?
		g_strdup_printf("%%s_expint%02d_%%s%%d%%s", n->bits) :
		strdup("%s_flexint_%s%d%s");
	p = bit_marker_list(gt, attr, tplate, n->bits ? n->bits :
											(n->value >= ((uint64_t)1<<32) ? 64 :
											 n->value >= ((uint64_t)1<<16) ? 32 :
											 n->value >= ((uint64_t)1<< 8) ? 16 :
											 n->value >= ((uint64_t)1<< 4) ?  8 :
											 n->value >= ((uint64_t)1<< 2) ?  4 : 2), n->value);
	free(tplate);

	if( !n->bits )
	{
		cpabe_policy_t* l;
		
		l = flexint_leader(gt, attr, n->value);
		if( l )
			p = kof2_policy(gt ? 1 : 2, l, p);
	}

	return p;
}

cpabe_policy_t*
lt_policy( sized_integer_t* n, char* attr )
{
	return cmp_policy(n, 0, attr);
}

cpabe_policy_t*
gt_policy( sized_integer_t* n, char* attr )
{
	return cmp_policy(n, 1, attr);
}

cpabe_policy_t*
le_policy( sized_integer_t* n, char* attr )
{
	n->value++;
	return cmp_policy(n, 0, attr);
}

cpabe_policy_t*
ge_policy( sized_integer_t* n, char* attr )
{
	n->value--;
	return cmp_policy(n, 1, attr);
}

char* cur_string = 0;

#define PEEK_CHAR ( *cur_string ? *cur_string     : EOF )
#define NEXT_CHAR ( *cur_string ? *(cur_string++) : EOF )

int
yylex()
{
  int c;
	int r;

  while( isspace(c = NEXT_CHAR) );

	r = 0;
  if( c == EOF )
    r = 0;
	else if( c == '&' )
		r = AND;
	else if( c == '|' )
		r = OR;
	else if( strchr("(),=#", c) || (strchr("<>", c) && PEEK_CHAR != '=') )
		r = c;
	else if( c == '<' && PEEK_CHAR == '=' )
	{
		NEXT_CHAR;
		r = LEQ;
	}
	else if( c == '>' && PEEK_CHAR == '=' )
	{
		NEXT_CHAR;
		r = GEQ;
	}
	else if( isdigit(c) )
	{
		GString* s;

		s = g_string_new("");
		g_string_append_c(s, c);
		while( isdigit(PEEK_CHAR) )
			g_string_append_c(s, NEXT_CHAR);

		sscanf(s->str, "%llu", &(yylval.nat));

		g_string_free(s, 1);
		r = INTLIT;
	}
	else if( isalpha(c) )
	{
		GString* s;

		s = g_string_new("");
		g_string_append_c(s, c);

		while( isalnum(PEEK_CHAR) || PEEK_CHAR == '_' )
			g_string_append_c(s, NEXT_CHAR);

		if( !strcmp(s->str, "and") )
		{
			g_string_free(s, 1);
			r = AND;
		}
		else if( !strcmp(s->str, "or") )
		{
			g_string_free(s, 1);
			r = OR;
		}
		else if( !strcmp(s->str, "of") )
		{
			g_string_free(s, 1);
			r = OF;
		}
		else
		{
			yylval.str = s->str;
			g_string_free(s, 0);
			r = TAG;
		}
	}
	else
		die("syntax error at \"%c%s\"\n", c, cur_string);

	return r;
}

void
yyerror( const char* s )
{
  die("error parsing policy: %s\n", s);
}

#define POLICY_IS_OR(p)  (((cpabe_policy_t*)(p))->k == 1 && ((cpabe_policy_t*)(p))->children->len)
#define POLICY_IS_AND(p) (((cpabe_policy_t*)(p))->k == ((cpabe_policy_t*)(p))->children->len)

void
merge_child( cpabe_policy_t* p, int i )
{
	int j;
	cpabe_policy_t* c;

	c = g_ptr_array_index(p->children, i);
	if( POLICY_IS_AND(p) )
	{
		p->k += c->k;
		p->k--;
	}

	g_ptr_array_remove_index_fast(p->children, i);
	for( j = 0; j < c->children->len; j++ )
		g_ptr_array_add(p->children, g_ptr_array_index(c->children, j));

	g_ptr_array_free(c->children, 0);
	free(c);
}

void
simplify( cpabe_policy_t* p )
{
	int i;

	for( i = 0; i < p->children->len; i++ )
		simplify(g_ptr_array_index(p->children, i));

	if( POLICY_IS_OR(p) )
		for( i = 0; i < p->children->len; i++ )
			if( POLICY_IS_OR(g_ptr_array_index(p->children, i)) )
				merge_child(p, i);

	if( POLICY_IS_AND(p) )
		for( i = 0; i < p->children->len; i++ )
			if( POLICY_IS_AND(g_ptr_array_index(p->children, i)) )
				merge_child(p, i);
}

int
cmp_tidy( const void* a, const void* b )
{
	cpabe_policy_t* pa;
	cpabe_policy_t* pb;

	pa = *((cpabe_policy_t**) a);
	pb = *((cpabe_policy_t**) b);

	if(      pa->children->len >  0 && pb->children->len == 0 )
		return -1;
	else if( pa->children->len == 0 && pb->children->len >  0 )
		return 1;
	else if( pa->children->len == 0 && pb->children->len == 0 )
		return strcmp(pa->attr, pb->attr);
	else
		return 0;	
}

void
tidy( cpabe_policy_t* p )
{
	int i;

	for( i = 0; i < p->children->len; i++ )
		tidy(g_ptr_array_index(p->children, i));

	if( p->children->len > 0 )
		qsort(p->children->pdata, p->children->len,
					sizeof(cpabe_policy_t*), cmp_tidy);
}

char*
format_policy_postfix( cpabe_policy_t* p )
{
	int i;
	char* r;
	char* s;
	char* t;

	if( p->children->len == 0 )
		return strdup(p->attr);

	r = format_policy_postfix(g_ptr_array_index(p->children, 0));
	for( i = 1; i < p->children->len; i++ )
	{
		s = format_policy_postfix(g_ptr_array_index(p->children, i));
		t = g_strjoin(" ", r, s, (char*) 0);
		free(r);
		free(s);
		r = t;
	}
	
	t = g_strdup_printf("%s %dof%d", r, p->k, p->children->len);
 	free(r);

	return t;
}

/*
	Crufty.
*/
int
actual_bits( uint64_t value )
{
	int i;

	for( i = 32; i >= 1; i /= 2 )
		if( value >= ((uint64_t)1<<i) )
			return i * 2;

	return 1;
}

/*
	It is pretty crufty having this here since it is only used in
	keygen. Maybe eventually there will be a separate .c file with the
	policy_lang module.
*/
void
parse_attribute( GSList** l, char* a )
{
	if( !strchr(a, '=') )
		*l = g_slist_append(*l, a);
	else
	{
		int i;
		char* s;
		char* tplate;
		uint64_t value;
		int bits;

		s = malloc(sizeof(char) * strlen(a));

		if( sscanf(a, " %s = %llu # %u ", s, &value, &bits) == 3 )
		{
			/* expint */

			if( bits > 64 )
				die("error parsing attribute \"%s\": 64 bits is the maximum allowed\n",
						a, value, bits);

			if( value >= ((uint64_t)1<<bits) )
				die("error parsing attribute \"%s\": value %llu too big for %d bits\n",
						a, value, bits);

			tplate = g_strdup_printf("%%s_expint%02d_%%s%%d%%s", bits);
			for( i = 0; i < bits; i++ )
				*l = g_slist_append
					(*l, bit_marker(s, tplate, i, !!((uint64_t)1<<i & value)));
			free(tplate);

			*l = g_slist_append
				(*l, g_strdup_printf("%s_expint%02d_%llu", s, bits, value));
		}
		else if( sscanf(a, " %s = %llu ", s, &value) == 2 )
		{
			/* flexint */

			for( i = 2; i <= 32; i *= 2 )
				*l = g_slist_append
					(*l, g_strdup_printf
					 (value < ((uint64_t)1<<i) ? "%s_lt_2^%02d" : "%s_ge_2^%02d", s, i));

			for( i = 0; i < 64; i++ )
				*l = g_slist_append
					(*l, bit_marker(s, "%s_flexint_%s%d%s", i, !!((uint64_t)1<<i & value)));

			*l = g_slist_append
				(*l, g_strdup_printf("%s_flexint_%llu", s, value));
		}
		else
			die("error parsing attribute \"%s\"\n"
					"(note that numerical attributes are unsigned integers)\n",	a);

 		free(s);
	}	
}

char*
parse_policy_lang( char* s )
{
	char* parsed_policy;

	cur_string = s;

	yyparse();
 	simplify(final_policy);
 	tidy(final_policy);
	parsed_policy = format_policy_postfix(final_policy);

	policy_free(final_policy);

	return parsed_policy;
}
