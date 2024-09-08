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
#line 2 "parser.y"

    #include<bits/stdc++.h>
    #include <fstream>
    using namespace std;
    void yyerror(const char * s);
    int yylex();
    extern int yylineno;
    extern FILE* yyin;
    #define YYERROR_VERBOSE 1
    int nodes = 0;
    map<int, string> node_entities;
    vector<pair<int,string>> parent_entities, child_entities;
    string temp_str;
    map <int, string> edges;

#line 87 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_STRING = 3,                     /* STRING  */
  YYSYMBOL_INDENT = 4,                     /* INDENT  */
  YYSYMBOL_DEDENT = 5,                     /* DEDENT  */
  YYSYMBOL_DOUBLE_QUOTE = 6,               /* DOUBLE_QUOTE  */
  YYSYMBOL_SINGLE_QUOTE = 7,               /* SINGLE_QUOTE  */
  YYSYMBOL_BREAK = 8,                      /* BREAK  */
  YYSYMBOL_CONTINUE = 9,                   /* CONTINUE  */
  YYSYMBOL_RETURN = 10,                    /* RETURN  */
  YYSYMBOL_GLOBAL = 11,                    /* GLOBAL  */
  YYSYMBOL_ASSERT = 12,                    /* ASSERT  */
  YYSYMBOL_CLASS = 13,                     /* CLASS  */
  YYSYMBOL_DEF = 14,                       /* DEF  */
  YYSYMBOL_IF = 15,                        /* IF  */
  YYSYMBOL_ELIF = 16,                      /* ELIF  */
  YYSYMBOL_ELSE = 17,                      /* ELSE  */
  YYSYMBOL_WHILE = 18,                     /* WHILE  */
  YYSYMBOL_FOR = 19,                       /* FOR  */
  YYSYMBOL_IN = 20,                        /* IN  */
  YYSYMBOL_NONE = 21,                      /* NONE  */
  YYSYMBOL_TRUE = 22,                      /* TRUE  */
  YYSYMBOL_FALSE = 23,                     /* FALSE  */
  YYSYMBOL_OR = 24,                        /* OR  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_IS = 27,                        /* IS  */
  YYSYMBOL_OPEN_ROUND_BRACKET = 28,        /* OPEN_ROUND_BRACKET  */
  YYSYMBOL_ARROW = 29,                     /* ARROW  */
  YYSYMBOL_SEMICOLON = 30,                 /* SEMICOLON  */
  YYSYMBOL_COLON = 31,                     /* COLON  */
  YYSYMBOL_EQUAL = 32,                     /* EQUAL  */
  YYSYMBOL_PLUS_EQUAL = 33,                /* PLUS_EQUAL  */
  YYSYMBOL_MINUS_EQUAL = 34,               /* MINUS_EQUAL  */
  YYSYMBOL_STAR_EQUAL = 35,                /* STAR_EQUAL  */
  YYSYMBOL_SLASH_EQUAL = 36,               /* SLASH_EQUAL  */
  YYSYMBOL_PERCENTAGE_EQUAL = 37,          /* PERCENTAGE_EQUAL  */
  YYSYMBOL_AND_EQUAL = 38,                 /* AND_EQUAL  */
  YYSYMBOL_OR_EQUAL = 39,                  /* OR_EQUAL  */
  YYSYMBOL_XOR_EQUAL = 40,                 /* XOR_EQUAL  */
  YYSYMBOL_LEFT_SHIFT_EQUAL = 41,          /* LEFT_SHIFT_EQUAL  */
  YYSYMBOL_RIGHT_SHIFT_EQUAL = 42,         /* RIGHT_SHIFT_EQUAL  */
  YYSYMBOL_DOUBLE_STAR_EQUAL = 43,         /* DOUBLE_STAR_EQUAL  */
  YYSYMBOL_DOUBLE_SLASH_EQUAL = 44,        /* DOUBLE_SLASH_EQUAL  */
  YYSYMBOL_COMMA = 45,                     /* COMMA  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_STAR = 47,                      /* STAR  */
  YYSYMBOL_SLASH = 48,                     /* SLASH  */
  YYSYMBOL_DOUBLE_STAR = 49,               /* DOUBLE_STAR  */
  YYSYMBOL_OR_OP = 50,                     /* OR_OP  */
  YYSYMBOL_PLUS = 51,                      /* PLUS  */
  YYSYMBOL_MINUS = 52,                     /* MINUS  */
  YYSYMBOL_OPEN_SQUARE_BRACKET = 53,       /* OPEN_SQUARE_BRACKET  */
  YYSYMBOL_COLON_EQUAL = 54,               /* COLON_EQUAL  */
  YYSYMBOL_DOUBLE_EQUAL = 55,              /* DOUBLE_EQUAL  */
  YYSYMBOL_NOT_EQUAL = 56,                 /* NOT_EQUAL  */
  YYSYMBOL_LESSER_EQUAL = 57,              /* LESSER_EQUAL  */
  YYSYMBOL_LESSER = 58,                    /* LESSER  */
  YYSYMBOL_GREATER_EQUAL = 59,             /* GREATER_EQUAL  */
  YYSYMBOL_GREATER = 60,                   /* GREATER  */
  YYSYMBOL_XOR = 61,                       /* XOR  */
  YYSYMBOL_AND_OP = 62,                    /* AND_OP  */
  YYSYMBOL_LEFT_SHIFT = 63,                /* LEFT_SHIFT  */
  YYSYMBOL_RIGHT_SHIFT = 64,               /* RIGHT_SHIFT  */
  YYSYMBOL_DOUBLE_SLASH = 65,              /* DOUBLE_SLASH  */
  YYSYMBOL_PERCENTAGE = 66,                /* PERCENTAGE  */
  YYSYMBOL_NOT_OP = 67,                    /* NOT_OP  */
  YYSYMBOL_NAME = 68,                      /* NAME  */
  YYSYMBOL_NEWLINE = 69,                   /* NEWLINE  */
  YYSYMBOL_NUMBER = 70,                    /* NUMBER  */
  YYSYMBOL_CLOSE_ROUND_BRACKET = 71,       /* CLOSE_ROUND_BRACKET  */
  YYSYMBOL_CLOSE_SQUARE_BRACKET = 72,      /* CLOSE_SQUARE_BRACKET  */
  YYSYMBOL_YYACCEPT = 73,                  /* $accept  */
  YYSYMBOL_unit = 74,                      /* unit  */
  YYSYMBOL_file_input = 75,                /* file_input  */
  YYSYMBOL_funcdef = 76,                   /* funcdef  */
  YYSYMBOL_Opt_arrow_test = 77,            /* Opt_arrow_test  */
  YYSYMBOL_parameters = 78,                /* parameters  */
  YYSYMBOL_Opt_typedargslist = 79,         /* Opt_typedargslist  */
  YYSYMBOL_typedargslist = 80,             /* typedargslist  */
  YYSYMBOL_Multi_tfpdef = 81,              /* Multi_tfpdef  */
  YYSYMBOL_tfpdef = 82,                    /* tfpdef  */
  YYSYMBOL_Opt_colon_test = 83,            /* Opt_colon_test  */
  YYSYMBOL_stmt = 84,                      /* stmt  */
  YYSYMBOL_simple_stmt = 85,               /* simple_stmt  */
  YYSYMBOL_Multi_small_stmt = 86,          /* Multi_small_stmt  */
  YYSYMBOL_small_stmt = 87,                /* small_stmt  */
  YYSYMBOL_expr_stmt = 88,                 /* expr_stmt  */
  YYSYMBOL_Test_dash = 89,                 /* Test_dash  */
  YYSYMBOL_augassign = 90,                 /* augassign  */
  YYSYMBOL_flow_stmt = 91,                 /* flow_stmt  */
  YYSYMBOL_Opt_test = 92,                  /* Opt_test  */
  YYSYMBOL_global_stmt = 93,               /* global_stmt  */
  YYSYMBOL_Multi_name = 94,                /* Multi_name  */
  YYSYMBOL_assert_stmt = 95,               /* assert_stmt  */
  YYSYMBOL_Opt_comma_test = 96,            /* Opt_comma_test  */
  YYSYMBOL_compound_stmt = 97,             /* compound_stmt  */
  YYSYMBOL_if_stmt = 98,                   /* if_stmt  */
  YYSYMBOL_Multi_elif = 99,                /* Multi_elif  */
  YYSYMBOL_Opt_else = 100,                 /* Opt_else  */
  YYSYMBOL_while_stmt = 101,               /* while_stmt  */
  YYSYMBOL_for_stmt = 102,                 /* for_stmt  */
  YYSYMBOL_suite = 103,                    /* suite  */
  YYSYMBOL_Nonzero_stmt = 104,             /* Nonzero_stmt  */
  YYSYMBOL_test = 105,                     /* test  */
  YYSYMBOL_Opt_if_else = 106,              /* Opt_if_else  */
  YYSYMBOL_or_test = 107,                  /* or_test  */
  YYSYMBOL_and_test = 108,                 /* and_test  */
  YYSYMBOL_not_test = 109,                 /* not_test  */
  YYSYMBOL_comparison = 110,               /* comparison  */
  YYSYMBOL_comp_op = 111,                  /* comp_op  */
  YYSYMBOL_expr = 112,                     /* expr  */
  YYSYMBOL_xor_expr = 113,                 /* xor_expr  */
  YYSYMBOL_and_expr = 114,                 /* and_expr  */
  YYSYMBOL_shift_expr = 115,               /* shift_expr  */
  YYSYMBOL_arith_expr = 116,               /* arith_expr  */
  YYSYMBOL_term = 117,                     /* term  */
  YYSYMBOL_factor = 118,                   /* factor  */
  YYSYMBOL_power = 119,                    /* power  */
  YYSYMBOL_atom_expr = 120,                /* atom_expr  */
  YYSYMBOL_Multi_trailer = 121,            /* Multi_trailer  */
  YYSYMBOL_atom = 122,                     /* atom  */
  YYSYMBOL_Opt_testlist = 123,             /* Opt_testlist  */
  YYSYMBOL_Multi_string = 124,             /* Multi_string  */
  YYSYMBOL_trailer = 125,                  /* trailer  */
  YYSYMBOL_Opt_arglist = 126,              /* Opt_arglist  */
  YYSYMBOL_testlist = 127,                 /* testlist  */
  YYSYMBOL_Multi_test = 128,               /* Multi_test  */
  YYSYMBOL_classdef = 129,                 /* classdef  */
  YYSYMBOL_Opt_round_bracket_opt_arglist = 130, /* Opt_round_bracket_opt_arglist  */
  YYSYMBOL_arglist = 131,                  /* arglist  */
  YYSYMBOL_Multi_argument = 132,           /* Multi_argument  */
  YYSYMBOL_argument = 133,                 /* argument  */
  YYSYMBOL_func_body_suite = 134           /* func_body_suite  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  75
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   342

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  62
/* YYNRULES -- Number of rules.  */
#define YYNRULES  148
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  240

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   327


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
      65,    66,    67,    68,    69,    70,    71,    72
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   183,   183,   192,   196,   218,   237,   278,   281,   297,
     329,   332,   355,   392,   395,   424,   449,   452,   470,   473,
     478,   502,   505,   535,   538,   541,   544,   549,   573,   592,
     603,   610,   623,   668,   679,   690,   701,   712,   723,   734,
     745,   756,   767,   778,   789,   802,   814,   826,   852,   855,
     860,   883,   886,   924,   944,   947,   964,   967,   970,   973,
     976,   981,  1018,  1021,  1052,  1055,  1079,  1110,  1153,  1156,
    1185,  1188,  1201,  1219,  1222,  1246,  1249,  1296,  1300,  1345,
    1359,  1365,  1370,  1403,  1414,  1425,  1436,  1447,  1458,  1469,
    1480,  1496,  1508,  1526,  1529,  1577,  1581,  1626,  1630,  1675,
    1678,  1690,  1762,  1766,  1778,  1873,  1876,  1888,  1901,  1914,
    2039,  2053,  2067,  2081,  2086,  2089,  2121,  2139,  2142,  2161,
    2183,  2206,  2218,  2230,  2251,  2263,  2275,  2289,  2292,  2298,
    2311,  2336,  2358,  2378,  2398,  2401,  2406,  2425,  2428,  2458,
    2493,  2496,  2520,  2538,  2541,  2571,  2574,  2594,  2598
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "STRING", "INDENT",
  "DEDENT", "DOUBLE_QUOTE", "SINGLE_QUOTE", "BREAK", "CONTINUE", "RETURN",
  "GLOBAL", "ASSERT", "CLASS", "DEF", "IF", "ELIF", "ELSE", "WHILE", "FOR",
  "IN", "NONE", "TRUE", "FALSE", "OR", "AND", "NOT", "IS",
  "OPEN_ROUND_BRACKET", "ARROW", "SEMICOLON", "COLON", "EQUAL",
  "PLUS_EQUAL", "MINUS_EQUAL", "STAR_EQUAL", "SLASH_EQUAL",
  "PERCENTAGE_EQUAL", "AND_EQUAL", "OR_EQUAL", "XOR_EQUAL",
  "LEFT_SHIFT_EQUAL", "RIGHT_SHIFT_EQUAL", "DOUBLE_STAR_EQUAL",
  "DOUBLE_SLASH_EQUAL", "COMMA", "DOT", "STAR", "SLASH", "DOUBLE_STAR",
  "OR_OP", "PLUS", "MINUS", "OPEN_SQUARE_BRACKET", "COLON_EQUAL",
  "DOUBLE_EQUAL", "NOT_EQUAL", "LESSER_EQUAL", "LESSER", "GREATER_EQUAL",
  "GREATER", "XOR", "AND_OP", "LEFT_SHIFT", "RIGHT_SHIFT", "DOUBLE_SLASH",
  "PERCENTAGE", "NOT_OP", "NAME", "NEWLINE", "NUMBER",
  "CLOSE_ROUND_BRACKET", "CLOSE_SQUARE_BRACKET", "$accept", "unit",
  "file_input", "funcdef", "Opt_arrow_test", "parameters",
  "Opt_typedargslist", "typedargslist", "Multi_tfpdef", "tfpdef",
  "Opt_colon_test", "stmt", "simple_stmt", "Multi_small_stmt",
  "small_stmt", "expr_stmt", "Test_dash", "augassign", "flow_stmt",
  "Opt_test", "global_stmt", "Multi_name", "assert_stmt", "Opt_comma_test",
  "compound_stmt", "if_stmt", "Multi_elif", "Opt_else", "while_stmt",
  "for_stmt", "suite", "Nonzero_stmt", "test", "Opt_if_else", "or_test",
  "and_test", "not_test", "comparison", "comp_op", "expr", "xor_expr",
  "and_expr", "shift_expr", "arith_expr", "term", "factor", "power",
  "atom_expr", "Multi_trailer", "atom", "Opt_testlist", "Multi_string",
  "trailer", "Opt_arglist", "testlist", "Multi_test", "classdef",
  "Opt_round_bracket_opt_arglist", "arglist", "Multi_argument", "argument",
  "func_body_suite", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-185)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      14,    15,  -185,  -185,   229,   -47,   229,   -34,   -12,   229,
     229,   272,  -185,  -185,  -185,   229,   229,   272,   272,   229,
     272,  -185,    14,  -185,    58,  -185,  -185,    14,  -185,    31,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,   128,
      39,    45,  -185,    -7,    29,    24,    26,     9,    42,    21,
    -185,  -185,    41,    11,  -185,    15,  -185,  -185,  -185,    53,
      59,    75,    83,    81,    82,    10,  -185,    43,  -185,  -185,
      70,    47,  -185,  -185,  -185,  -185,  -185,   250,    48,   229,
     229,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,   229,   229,   229,  -185,   229,  -185,   100,
      95,  -185,  -185,  -185,  -185,  -185,  -185,   272,   272,   272,
     272,   272,   272,   272,   272,   272,   272,   272,   272,   272,
     229,    55,   229,  -185,    11,  -185,    57,  -185,   229,  -185,
     229,    91,    60,    98,   196,   196,   229,  -185,   229,  -185,
    -185,    31,  -185,    97,  -185,    99,  -185,    54,    45,  -185,
    -185,  -185,    29,    24,    26,     9,    42,    42,    21,    21,
    -185,  -185,  -185,  -185,  -185,   103,    65,  -185,    85,  -185,
      74,  -185,    53,  -185,    66,   196,   116,    79,  -185,   109,
     229,   124,   153,  -185,   157,   158,   143,    70,  -185,   229,
     229,   229,  -185,   229,  -185,  -185,  -185,  -185,  -185,   229,
    -185,  -185,    60,  -185,  -185,   217,   130,   229,   158,   146,
    -185,   196,  -185,  -185,  -185,  -185,    85,  -185,   109,   174,
    -185,  -185,   130,   175,   148,  -185,   196,   158,  -185,  -185,
     130,  -185,  -185,   196,  -185,  -185,   179,   157,  -185,  -185
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,   129,    45,    46,    48,     0,     0,     0,     0,     0,
       0,     0,   124,   125,   126,     0,    48,     0,     0,   127,
       0,   121,     3,   122,     0,     2,    59,     3,    18,    21,
      23,    30,    24,    25,    26,    19,    56,    57,    58,    32,
      73,    75,    77,    80,    81,    93,    95,    97,    99,   102,
     105,   113,   114,   117,    60,   129,   123,    47,    49,    51,
      54,   140,     0,     0,     0,     0,    79,     0,   110,   111,
     137,     0,   128,   112,     4,     1,     5,     0,     0,     0,
       0,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,     0,     0,     0,    72,     0,    89,     0,
      91,    85,    88,    87,    83,    86,    84,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     134,     0,     0,   116,   117,   130,     0,    50,     0,    53,
     134,     0,    10,     7,     0,     0,     0,   119,     0,   136,
     120,    21,    20,    28,    31,    32,    29,     0,    76,    78,
      90,    92,    82,    94,    96,    98,   100,   101,   103,   104,
     106,   107,   109,   108,   115,   145,     0,   135,   143,   133,
       0,   118,    51,    55,     0,     0,    16,     0,    11,    13,
       0,     0,     0,    68,    62,    64,     0,   137,    22,     0,
       0,     0,   131,     0,   142,   132,    52,   141,   139,     0,
      15,     9,     0,    12,     8,     0,     0,     0,    64,     0,
      66,     0,   138,    27,    74,   146,   143,    17,    13,     0,
     147,     6,    70,     0,     0,    61,     0,    64,   144,    14,
       0,    71,    69,     0,    65,    67,     0,    62,   148,    63
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -185,  -185,   -11,  -185,  -185,  -185,  -185,  -185,   -30,    -9,
    -185,  -175,  -131,    49,   114,  -185,   112,  -185,  -185,   178,
    -185,    30,  -185,  -185,  -185,  -185,   -41,  -165,  -185,  -185,
    -134,  -184,    -4,  -185,   107,   115,    -6,  -185,  -185,     3,
     101,   102,   104,   -15,   -13,   -10,  -185,  -185,    88,  -185,
    -185,   160,  -185,    86,   -77,    34,  -185,  -185,  -185,    -3,
      37,  -185
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    24,    25,    26,   181,   133,   177,   178,   203,   179,
     200,    27,    28,    78,    29,    30,    31,    93,    32,    57,
      33,   127,    34,   129,    35,    36,   208,   210,    37,    38,
     184,   223,    39,    96,    40,    41,    42,    43,   107,    44,
      45,    46,    47,    48,    49,    50,    51,    52,   123,    53,
      71,    56,   124,   166,    72,   139,    54,   131,   167,   194,
     168,   221
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,   185,    60,   183,   183,    63,    64,    68,    69,    66,
      73,    74,    58,    98,    65,    70,    76,     1,    55,    99,
     100,    59,     2,     3,     4,     5,     6,     7,     8,     9,
     136,   222,    10,    11,    61,    12,    13,    14,   231,   120,
      15,   198,    16,   225,   183,   170,   236,   222,   101,   102,
     103,   104,   105,   106,    94,   222,    62,   121,    75,   186,
     108,    77,   235,    95,   122,    17,    18,    19,   115,   116,
      97,   190,   111,   112,   220,   143,   145,   227,    95,   108,
     183,    20,    21,    22,    23,   109,   117,   118,   110,   146,
     119,   149,   234,   113,   114,   183,   156,   157,   126,   237,
     158,   159,   183,   130,   128,   160,   161,   162,   163,   164,
     152,   132,   134,   135,   137,   138,   165,   142,    70,   140,
     150,   151,   175,   169,   173,   172,   165,   180,   176,   189,
     193,    80,    70,     1,   187,   191,   192,   197,     2,     3,
       4,     5,     6,     7,     8,     9,   195,   199,    10,    11,
     201,    12,    13,    14,   202,   205,    15,   206,    16,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   207,   211,   209,   204,   226,   230,   233,
     232,    17,    18,    19,   238,   213,   214,   215,   229,   165,
     188,   141,   144,   218,    67,   217,   239,    20,    21,     1,
      23,   147,   196,   224,     2,     3,     4,     5,     6,   153,
     148,   154,   171,   228,   155,   125,   174,    12,    13,    14,
       1,   212,    15,     0,    16,     2,     3,     4,     5,     6,
     216,     0,     1,     0,     0,     0,     0,     0,    12,    13,
      14,     0,     0,    15,     0,    16,     0,    17,    18,    19,
      12,    13,    14,     1,     0,    15,     0,    16,     2,     3,
       4,     5,     6,    20,    21,   182,    23,     0,    17,    18,
      19,    12,    13,    14,     0,     1,    15,     0,    16,     0,
      17,    18,    19,     0,    20,    21,   219,    23,     0,     0,
       0,     0,     0,    12,    13,    14,    20,    21,     0,    23,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,    21,     0,
      23,     0,     0,    17,    18,    19,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      21,     0,    23
};

static const yytype_int16 yycheck[] =
{
       4,   135,     6,   134,   135,     9,    10,    17,    18,    15,
      20,    22,    16,    20,    11,    19,    27,     3,     3,    26,
      27,    68,     8,     9,    10,    11,    12,    13,    14,    15,
      20,   206,    18,    19,    68,    21,    22,    23,   222,    28,
      26,   175,    28,   208,   175,   122,   230,   222,    55,    56,
      57,    58,    59,    60,    15,   230,    68,    46,     0,   136,
      50,    30,   227,    24,    53,    51,    52,    53,    47,    48,
      25,    17,    63,    64,   205,    79,    80,   211,    24,    50,
     211,    67,    68,    69,    70,    61,    65,    66,    62,    93,
      49,    97,   226,    51,    52,   226,   111,   112,    45,   233,
     113,   114,   233,    28,    45,   115,   116,   117,   118,   119,
     107,    28,    31,    31,    71,    45,   120,    69,   122,    72,
      20,    26,    31,    68,   128,    68,   130,    29,    68,    32,
      45,    32,   136,     3,   138,    32,    71,    71,     8,     9,
      10,    11,    12,    13,    14,    15,    72,    31,    18,    19,
      71,    21,    22,    23,    45,    31,    26,     4,    28,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    16,    31,    17,   180,    31,     4,    31,
       5,    51,    52,    53,     5,   189,   190,   191,   218,   193,
     141,    77,    80,   202,    16,   199,   237,    67,    68,     3,
      70,    94,   172,   207,     8,     9,    10,    11,    12,   108,
      95,   109,   124,   216,   110,    55,   130,    21,    22,    23,
       3,   187,    26,    -1,    28,     8,     9,    10,    11,    12,
     193,    -1,     3,    -1,    -1,    -1,    -1,    -1,    21,    22,
      23,    -1,    -1,    26,    -1,    28,    -1,    51,    52,    53,
      21,    22,    23,     3,    -1,    26,    -1,    28,     8,     9,
      10,    11,    12,    67,    68,    69,    70,    -1,    51,    52,
      53,    21,    22,    23,    -1,     3,    26,    -1,    28,    -1,
      51,    52,    53,    -1,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    21,    22,    23,    67,    68,    -1,    70,
      28,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    -1,
      70,    -1,    -1,    51,    52,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,
      68,    -1,    70
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,     9,    10,    11,    12,    13,    14,    15,
      18,    19,    21,    22,    23,    26,    28,    51,    52,    53,
      67,    68,    69,    70,    74,    75,    76,    84,    85,    87,
      88,    89,    91,    93,    95,    97,    98,   101,   102,   105,
     107,   108,   109,   110,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   122,   129,     3,   124,    92,   105,    68,
     105,    68,    68,   105,   105,   112,   109,    92,   118,   118,
     105,   123,   127,   118,    75,     0,    75,    30,    86,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    90,    15,    24,   106,    25,    20,    26,
      27,    55,    56,    57,    58,    59,    60,   111,    50,    61,
      62,    63,    64,    51,    52,    47,    48,    65,    66,    49,
      28,    46,    53,   121,   125,   124,    45,    94,    45,    96,
      28,   130,    28,    78,    31,    31,    20,    71,    45,   128,
      72,    87,    69,   105,    89,   105,   105,   107,   108,   109,
      20,    26,   112,   113,   114,   115,   116,   116,   117,   117,
     118,   118,   118,   118,   118,   105,   126,   131,   133,    68,
     127,   121,    68,   105,   126,    31,    68,    79,    80,    82,
      29,    77,    69,    85,   103,   103,   127,   105,    86,    32,
      17,    32,    71,    45,   132,    72,    94,    71,   103,    31,
      83,    71,    45,    81,   105,    31,     4,    16,    99,    17,
     100,    31,   128,   105,   105,   105,   133,   105,    82,    69,
      85,   134,    84,   104,   105,   100,    31,   103,   132,    81,
       4,   104,     5,    31,   103,   100,   104,   103,     5,    99
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    75,    75,    76,    77,    77,    78,
      79,    79,    80,    81,    81,    82,    83,    83,    84,    84,
      85,    86,    86,    87,    87,    87,    87,    88,    88,    88,
      88,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    91,    91,    91,    92,    92,
      93,    94,    94,    95,    96,    96,    97,    97,    97,    97,
      97,    98,    99,    99,   100,   100,   101,   102,   103,   103,
     104,   104,   105,   106,   106,   107,   107,   108,   108,   109,
     109,   110,   110,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   115,   116,   116,   116,   117,   117,   117,   117,   117,
     118,   118,   118,   118,   119,   119,   120,   121,   121,   122,
     122,   122,   122,   122,   122,   122,   122,   123,   123,   124,
     124,   125,   125,   125,   126,   126,   127,   128,   128,   129,
     130,   130,   131,   132,   132,   133,   133,   134,   134
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     6,     0,     2,     3,
       0,     1,     2,     0,     3,     2,     0,     2,     1,     1,
       3,     0,     3,     1,     1,     1,     1,     5,     3,     3,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     0,     1,
       3,     0,     3,     3,     0,     2,     1,     1,     1,     1,
       1,     6,     0,     5,     0,     3,     5,     7,     1,     4,
       1,     2,     2,     0,     4,     1,     3,     1,     3,     2,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     2,     1,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       2,     2,     2,     1,     1,     3,     2,     0,     2,     3,
       3,     1,     1,     2,     1,     1,     1,     0,     1,     0,
       2,     3,     3,     2,     0,     1,     2,     0,     3,     5,
       0,     3,     2,     0,     3,     1,     3,     1,     4
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* unit: file_input  */
#line 183 "parser.y"
            {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "unit";
  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  // edges[parent_entities.size()-1] = "ghfdk";
}
#line 1693 "parser.tab.c"
    break;

  case 3: /* file_input: %empty  */
#line 192 "parser.y"
                          {
  // cout<<"hi\n";
  (yyval.nt_num) = -1;
}
#line 1702 "parser.tab.c"
    break;

  case 4: /* file_input: NEWLINE file_input  */
#line 196 "parser.y"
                          {
  // cout<<"hii\n";
  if((yyvsp[0].nt_num) == -1){
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "NEWLINE";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "file_input";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "NEWLINE";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 1729 "parser.tab.c"
    break;

  case 5: /* file_input: stmt file_input  */
#line 218 "parser.y"
                         {
  // cout<<"hiii\n";
  if((yyvsp[0].nt_num) == -1){
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "file_input";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));


    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 1751 "parser.tab.c"
    break;

  case 6: /* funcdef: DEF NAME parameters Opt_arrow_test COLON func_body_suite  */
#line 237 "parser.y"
                                                              {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "funcdef";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "DEF("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-4].token_attr)).token_num = nodes++;
  temp_str = "NAME("+string((char*)((yyvsp[-4].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-4].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-4].token_attr)).token_num, node_entities[((yyvsp[-4].token_attr)).token_num]));
  edges[parent_entities.size()-1]="def";

  if((yyvsp[-3].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-3].nt_num), node_entities[(yyvsp[-3].nt_num)]));
  }

  if((yyvsp[-2].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));
    edges[parent_entities.size()-1]="return type";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($5).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($5).token_lex)+")";
  // node_entities[($5).token_num] = temp_str;
  // child_entities.push_back(make_pair(($5).token_num, node_entities[($5).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  edges[parent_entities.size()-1]="function body";

}
#line 1795 "parser.tab.c"
    break;

  case 7: /* Opt_arrow_test: %empty  */
#line 278 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 1803 "parser.tab.c"
    break;

  case 8: /* Opt_arrow_test: ARROW test  */
#line 281 "parser.y"
                  {
  // $$ = nodes++;
  // node_entities[$$] = "Opt_arrow_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "ARROW("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 1822 "parser.tab.c"
    break;

  case 9: /* parameters: OPEN_ROUND_BRACKET Opt_typedargslist CLOSE_ROUND_BRACKET  */
#line 297 "parser.y"
                                                              {
  
  

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if((yyvsp[-1].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "parameters";
    
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
    edges[parent_entities.size()-1]="( )";
  }

  else{
    (yyval.nt_num) = -1;
  }


  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
#line 1857 "parser.tab.c"
    break;

  case 10: /* Opt_typedargslist: %empty  */
#line 329 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 1865 "parser.tab.c"
    break;

  case 11: /* Opt_typedargslist: typedargslist  */
#line 332 "parser.y"
                     {
  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 1874 "parser.tab.c"
    break;

  case 12: /* typedargslist: tfpdef Multi_tfpdef  */
#line 355 "parser.y"
                          {

  if((yyvsp[0].nt_num) == -1){
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }
  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "typedargslist";

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));

      parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
      child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 1895 "parser.tab.c"
    break;

  case 13: /* Multi_tfpdef: %empty  */
#line 392 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 1903 "parser.tab.c"
    break;

  case 14: /* Multi_tfpdef: COMMA tfpdef Multi_tfpdef  */
#line 395 "parser.y"
                                 {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_tfpdef";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if((yyvsp[0].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "argslist";

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
  else{
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }
}
#line 1935 "parser.tab.c"
    break;

  case 15: /* tfpdef: NAME Opt_colon_test  */
#line 424 "parser.y"
                          {
  if((yyvsp[0].nt_num) == -1){
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "NAME("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "arg";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "NAME("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
    edges[parent_entities.size()-1] = "parameter type";
  }

}
#line 1963 "parser.tab.c"
    break;

  case 16: /* Opt_colon_test: %empty  */
#line 449 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 1971 "parser.tab.c"
    break;

  case 17: /* Opt_colon_test: COLON test  */
#line 452 "parser.y"
                  {
  // $$ = nodes++;
  // node_entities[$$] = "Opt_colon_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 1992 "parser.tab.c"
    break;

  case 18: /* stmt: simple_stmt  */
#line 470 "parser.y"
                 {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2000 "parser.tab.c"
    break;

  case 19: /* stmt: compound_stmt  */
#line 473 "parser.y"
                     {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2008 "parser.tab.c"
    break;

  case 20: /* simple_stmt: small_stmt Multi_small_stmt NEWLINE  */
#line 478 "parser.y"
                                         {
  
  if((yyvsp[-1].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "simple_stmt";

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
  }
  else{
    (yyval.nt_num) = (yyvsp[-2].nt_num);
  }
  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++; 
  // temp_str = "NEWLINE";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

}
#line 2035 "parser.tab.c"
    break;

  case 21: /* Multi_small_stmt: %empty  */
#line 502 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 2043 "parser.tab.c"
    break;

  case 22: /* Multi_small_stmt: SEMICOLON small_stmt Multi_small_stmt  */
#line 505 "parser.y"
                                             {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_small_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "SEMICOLON("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if((yyvsp[0].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "Multi_small_stmt";

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }

  else {
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }
}
#line 2076 "parser.tab.c"
    break;

  case 23: /* small_stmt: expr_stmt  */
#line 535 "parser.y"
               {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2084 "parser.tab.c"
    break;

  case 24: /* small_stmt: flow_stmt  */
#line 538 "parser.y"
                 {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2092 "parser.tab.c"
    break;

  case 25: /* small_stmt: global_stmt  */
#line 541 "parser.y"
                   {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2100 "parser.tab.c"
    break;

  case 26: /* small_stmt: assert_stmt  */
#line 544 "parser.y"
                   {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2108 "parser.tab.c"
    break;

  case 27: /* expr_stmt: test COLON test EQUAL test  */
#line 549 "parser.y"
                                {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "EQUAL("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
  
  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-4].nt_num), node_entities[(yyvsp[-4].nt_num)]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($2).token_lex)+")";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));
  edges[parent_entities.size()-1]="type";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

  
}
#line 2137 "parser.tab.c"
    break;

  case 28: /* expr_stmt: test COLON test  */
#line 573 "parser.y"
                          {
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "expr_stmt";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($2).token_lex)+")";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  edges[parent_entities.size()-1]="type";


}
#line 2161 "parser.tab.c"
    break;

  case 29: /* expr_stmt: test augassign test  */
#line 592 "parser.y"
                      {
  (yyval.nt_num) = (yyvsp[-1].nt_num);

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));


}
#line 2177 "parser.tab.c"
    break;

  case 30: /* expr_stmt: Test_dash  */
#line 603 "parser.y"
            {
  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 2186 "parser.tab.c"
    break;

  case 31: /* Test_dash: test EQUAL Test_dash  */
#line 610 "parser.y"
                     {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "EQUAL("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 2204 "parser.tab.c"
    break;

  case 32: /* Test_dash: test  */
#line 623 "parser.y"
        {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2212 "parser.tab.c"
    break;

  case 33: /* augassign: PLUS_EQUAL  */
#line 668 "parser.y"
                {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "PLUS_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2228 "parser.tab.c"
    break;

  case 34: /* augassign: MINUS_EQUAL  */
#line 679 "parser.y"
                   {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "MINUS_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2244 "parser.tab.c"
    break;

  case 35: /* augassign: STAR_EQUAL  */
#line 690 "parser.y"
                  {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "STAR_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2260 "parser.tab.c"
    break;

  case 36: /* augassign: SLASH_EQUAL  */
#line 701 "parser.y"
                   {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "SLASH_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2276 "parser.tab.c"
    break;

  case 37: /* augassign: PERCENTAGE_EQUAL  */
#line 712 "parser.y"
                        {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "PERCENTAGE_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2292 "parser.tab.c"
    break;

  case 38: /* augassign: AND_EQUAL  */
#line 723 "parser.y"
                 {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "AND_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2308 "parser.tab.c"
    break;

  case 39: /* augassign: OR_EQUAL  */
#line 734 "parser.y"
                {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "OR_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2324 "parser.tab.c"
    break;

  case 40: /* augassign: XOR_EQUAL  */
#line 745 "parser.y"
                 {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "XOR_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2340 "parser.tab.c"
    break;

  case 41: /* augassign: LEFT_SHIFT_EQUAL  */
#line 756 "parser.y"
                        {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "LEFT_SHIFT_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2356 "parser.tab.c"
    break;

  case 42: /* augassign: RIGHT_SHIFT_EQUAL  */
#line 767 "parser.y"
                         {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "RIGHT_SHIFT_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2372 "parser.tab.c"
    break;

  case 43: /* augassign: DOUBLE_STAR_EQUAL  */
#line 778 "parser.y"
                         {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "DOUBLE_STAR_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2388 "parser.tab.c"
    break;

  case 44: /* augassign: DOUBLE_SLASH_EQUAL  */
#line 789 "parser.y"
                          {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "DOUBLE_SLASH_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2404 "parser.tab.c"
    break;

  case 45: /* flow_stmt: BREAK  */
#line 802 "parser.y"
           {
  // $$ = nodes++;
  // node_entities[$$] = "flow_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "BREAK("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2421 "parser.tab.c"
    break;

  case 46: /* flow_stmt: CONTINUE  */
#line 814 "parser.y"
                {
  // $$ = nodes++;
  // node_entities[$$] = "flow_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "CONTINUE("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 2438 "parser.tab.c"
    break;

  case 47: /* flow_stmt: RETURN Opt_test  */
#line 826 "parser.y"
                       {

  if((yyvsp[0].nt_num) == -1){
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "RETURN("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "flow_stmt";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "RETURN("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }

  
}
#line 2467 "parser.tab.c"
    break;

  case 48: /* Opt_test: %empty  */
#line 852 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 2475 "parser.tab.c"
    break;

  case 49: /* Opt_test: test  */
#line 855 "parser.y"
            {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2483 "parser.tab.c"
    break;

  case 50: /* global_stmt: GLOBAL NAME Multi_name  */
#line 860 "parser.y"
                            {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "global_stmt";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-2].token_attr)).token_num = nodes++;
  temp_str = "GLOBAL("+string((char*)((yyvsp[-2].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-2].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-2].token_attr)).token_num, node_entities[((yyvsp[-2].token_attr)).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "NAME("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

  if((yyvsp[0].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }   
}
#line 2509 "parser.tab.c"
    break;

  case 51: /* Multi_name: %empty  */
#line 883 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 2517 "parser.tab.c"
    break;

  case 52: /* Multi_name: COMMA NAME Multi_name  */
#line 886 "parser.y"
                             {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_name";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++;
  // temp_str = "NAME("+string((char*)($2).token_lex)+")";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  if((yyvsp[0].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "Multi_name";  

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "NAME("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  } 
  else{
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "NAME("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
  }
}
#line 2558 "parser.tab.c"
    break;

  case 53: /* assert_stmt: ASSERT test Opt_comma_test  */
#line 924 "parser.y"
                                {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "assert_stmt";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-2].token_attr)).token_num = nodes++;
  temp_str = "ASSERT("+string((char*)((yyvsp[-2].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-2].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-2].token_attr)).token_num, node_entities[((yyvsp[-2].token_attr)).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)])); 
  
  if((yyvsp[0].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  } 
}
#line 2581 "parser.tab.c"
    break;

  case 54: /* Opt_comma_test: %empty  */
#line 944 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 2589 "parser.tab.c"
    break;

  case 55: /* Opt_comma_test: COMMA test  */
#line 947 "parser.y"
                   {
  // $$ = nodes++;
  // node_entities[$$] = "Opt_comma_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2])); 

  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2609 "parser.tab.c"
    break;

  case 56: /* compound_stmt: if_stmt  */
#line 964 "parser.y"
             {
  (yyval.nt_num) = (yyvsp[0].nt_num); 
}
#line 2617 "parser.tab.c"
    break;

  case 57: /* compound_stmt: while_stmt  */
#line 967 "parser.y"
                  {
  (yyval.nt_num) = (yyvsp[0].nt_num); 
}
#line 2625 "parser.tab.c"
    break;

  case 58: /* compound_stmt: for_stmt  */
#line 970 "parser.y"
                {
  (yyval.nt_num) = (yyvsp[0].nt_num); 
}
#line 2633 "parser.tab.c"
    break;

  case 59: /* compound_stmt: funcdef  */
#line 973 "parser.y"
               {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2641 "parser.tab.c"
    break;

  case 60: /* compound_stmt: classdef  */
#line 976 "parser.y"
                {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2649 "parser.tab.c"
    break;

  case 61: /* if_stmt: IF test COLON suite Multi_elif Opt_else  */
#line 981 "parser.y"
                                             {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "if_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "IF("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-4].nt_num), node_entities[(yyvsp[-4].nt_num)]));
  edges[parent_entities.size()-1]="if";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));
  edges[parent_entities.size()-1]="then";

  if((yyvsp[-1].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
  }

  if((yyvsp[0].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
    edges[parent_entities.size()-1]="else";
  }
}
#line 2689 "parser.tab.c"
    break;

  case 62: /* Multi_elif: %empty  */
#line 1018 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 2697 "parser.tab.c"
    break;

  case 63: /* Multi_elif: ELIF test COLON suite Multi_elif  */
#line 1021 "parser.y"
                                        {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "Multi_elif";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "ELIF("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-3].nt_num), node_entities[(yyvsp[-3].nt_num)]));
  edges[parent_entities.size()-1]="elif";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
  edges[parent_entities.size()-1]="then";

  if((yyvsp[0].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 2731 "parser.tab.c"
    break;

  case 64: /* Opt_else: %empty  */
#line 1052 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 2739 "parser.tab.c"
    break;

  case 65: /* Opt_else: ELSE COLON suite  */
#line 1055 "parser.y"
                        {
  // $$ = nodes++;
  // node_entities[$$] = "Opt_else";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "ELSE("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($2).token_lex)+")";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));
  
  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($3, node_entities[$3]));
  // edges[parent_entities.size()-1]="else";
  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 2766 "parser.tab.c"
    break;

  case 66: /* while_stmt: WHILE test COLON suite Opt_else  */
#line 1079 "parser.y"
                                     {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "while_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "WHILE("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-3].nt_num), node_entities[(yyvsp[-3].nt_num)]));
  edges[parent_entities.size()-1] = "while";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
  edges[parent_entities.size()-1] = "body";

  if((yyvsp[0].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 2800 "parser.tab.c"
    break;

  case 67: /* for_stmt: FOR expr IN testlist COLON suite Opt_else  */
#line 1110 "parser.y"
                                                {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "for_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "FOR("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-5].nt_num), node_entities[(yyvsp[-5].nt_num)]));
  edges[parent_entities.size()-1] = "for";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "IN("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-3].nt_num), node_entities[(yyvsp[-3].nt_num)]));
  edges[parent_entities.size()-1] = "in";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($5).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($5).token_lex)+")";
  // node_entities[($5).token_num] = temp_str;
  // child_entities.push_back(make_pair(($5).token_num, node_entities[($5).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
  edges[parent_entities.size()-1] = "body";

  if((yyvsp[0].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
  
}
#line 2845 "parser.tab.c"
    break;

  case 68: /* suite: simple_stmt  */
#line 1153 "parser.y"
                 {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2853 "parser.tab.c"
    break;

  case 69: /* suite: NEWLINE INDENT Nonzero_stmt DEDENT  */
#line 1156 "parser.y"
                                          {
  // $$ = nodes++;
  // node_entities[$$] = "suite";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++; 
  // temp_str = "NEWLINE";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++; 
  // temp_str = "INDENT";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($3, node_entities[$3]));

  (yyval.nt_num) = (yyvsp[-1].nt_num);

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($4).token_num = nodes++; 
  // temp_str = "DEDENT";
  // node_entities[($4).token_num] = temp_str;
  // child_entities.push_back(make_pair(($4).token_num, node_entities[($4).token_num]));
}
#line 2885 "parser.tab.c"
    break;

  case 70: /* Nonzero_stmt: stmt  */
#line 1185 "parser.y"
          {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2893 "parser.tab.c"
    break;

  case 71: /* Nonzero_stmt: stmt Nonzero_stmt  */
#line 1188 "parser.y"
                         {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "stmts";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 2909 "parser.tab.c"
    break;

  case 72: /* test: or_test Opt_if_else  */
#line 1201 "parser.y"
                         {
  if((yyvsp[0].nt_num) == -1){
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "test";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));


    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 2930 "parser.tab.c"
    break;

  case 73: /* Opt_if_else: %empty  */
#line 1219 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 2938 "parser.tab.c"
    break;

  case 74: /* Opt_if_else: IF or_test ELSE test  */
#line 1222 "parser.y"
                            {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "Opt_if_else";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-3].token_attr)).token_num = nodes++;
  temp_str = "IF("+string((char*)((yyvsp[-3].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-3].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-3].token_attr)).token_num, node_entities[((yyvsp[-3].token_attr)).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "ELSE("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 2965 "parser.tab.c"
    break;

  case 75: /* or_test: and_test  */
#line 1246 "parser.y"
               {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 2973 "parser.tab.c"
    break;

  case 76: /* or_test: or_test OR and_test  */
#line 1249 "parser.y"
                      {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "OR("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  

}
#line 2992 "parser.tab.c"
    break;

  case 77: /* and_test: not_test  */
#line 1296 "parser.y"
              {
  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 3001 "parser.tab.c"
    break;

  case 78: /* and_test: and_test AND not_test  */
#line 1300 "parser.y"
                        {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "AND("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3018 "parser.tab.c"
    break;

  case 79: /* not_test: NOT not_test  */
#line 1345 "parser.y"
                  {
  // $$ = nodes++;
  // node_entities[$$] = "not_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "NOT("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3037 "parser.tab.c"
    break;

  case 80: /* not_test: comparison  */
#line 1359 "parser.y"
                  {
  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 3046 "parser.tab.c"
    break;

  case 81: /* comparison: expr  */
#line 1365 "parser.y"
           {
  (yyval.nt_num) = (yyvsp[0].nt_num);
  

}
#line 3056 "parser.tab.c"
    break;

  case 82: /* comparison: comparison comp_op expr  */
#line 1370 "parser.y"
                          {

  (yyval.nt_num) = (yyvsp[-1].nt_num);

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 3072 "parser.tab.c"
    break;

  case 83: /* comp_op: LESSER  */
#line 1403 "parser.y"
            {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "LESSER("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3088 "parser.tab.c"
    break;

  case 84: /* comp_op: GREATER  */
#line 1414 "parser.y"
               {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "GREATER("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3104 "parser.tab.c"
    break;

  case 85: /* comp_op: DOUBLE_EQUAL  */
#line 1425 "parser.y"
                    {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "DOUBLE_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3120 "parser.tab.c"
    break;

  case 86: /* comp_op: GREATER_EQUAL  */
#line 1436 "parser.y"
                     {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "GREATER_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3136 "parser.tab.c"
    break;

  case 87: /* comp_op: LESSER_EQUAL  */
#line 1447 "parser.y"
                    {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "LESSER_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3152 "parser.tab.c"
    break;

  case 88: /* comp_op: NOT_EQUAL  */
#line 1458 "parser.y"
                 {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "NOT_EQUAL("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3168 "parser.tab.c"
    break;

  case 89: /* comp_op: IN  */
#line 1469 "parser.y"
          {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "IN("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3184 "parser.tab.c"
    break;

  case 90: /* comp_op: NOT IN  */
#line 1480 "parser.y"
              {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "comp_op";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "NOT("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "IN("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[0].token_attr)).token_num, node_entities[((yyvsp[0].token_attr)).token_num]));
}
#line 3205 "parser.tab.c"
    break;

  case 91: /* comp_op: IS  */
#line 1496 "parser.y"
          {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "IS("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3222 "parser.tab.c"
    break;

  case 92: /* comp_op: IS NOT  */
#line 1508 "parser.y"
              {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "comp_op";

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "IS("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "NOT("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[0].token_attr)).token_num, node_entities[((yyvsp[0].token_attr)).token_num]));
}
#line 3243 "parser.tab.c"
    break;

  case 93: /* expr: xor_expr  */
#line 1526 "parser.y"
              {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 3251 "parser.tab.c"
    break;

  case 94: /* expr: expr OR_OP xor_expr  */
#line 1529 "parser.y"
                      {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "BITWISE_OR("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3268 "parser.tab.c"
    break;

  case 95: /* xor_expr: and_expr  */
#line 1577 "parser.y"
            {
  (yyval.nt_num) = (yyvsp[0].nt_num);
  
}
#line 3277 "parser.tab.c"
    break;

  case 96: /* xor_expr: xor_expr XOR and_expr  */
#line 1581 "parser.y"
                        {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "BITWISE_XOR("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3294 "parser.tab.c"
    break;

  case 97: /* and_expr: shift_expr  */
#line 1626 "parser.y"
              {
  (yyval.nt_num) = (yyvsp[0].nt_num);
  
}
#line 3303 "parser.tab.c"
    break;

  case 98: /* and_expr: and_expr AND_OP shift_expr  */
#line 1630 "parser.y"
                             {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "BITWISE_AND("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3320 "parser.tab.c"
    break;

  case 99: /* shift_expr: arith_expr  */
#line 1675 "parser.y"
               {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 3328 "parser.tab.c"
    break;

  case 100: /* shift_expr: shift_expr LEFT_SHIFT arith_expr  */
#line 1678 "parser.y"
                                   {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "LEFT_SHIFT("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3345 "parser.tab.c"
    break;

  case 101: /* shift_expr: shift_expr RIGHT_SHIFT arith_expr  */
#line 1690 "parser.y"
                                    {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "RIGHT_SHIFT("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 3363 "parser.tab.c"
    break;

  case 102: /* arith_expr: term  */
#line 1762 "parser.y"
         {
  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 3372 "parser.tab.c"
    break;

  case 103: /* arith_expr: arith_expr PLUS term  */
#line 1766 "parser.y"
                       {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "PLUS("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3389 "parser.tab.c"
    break;

  case 104: /* arith_expr: arith_expr MINUS term  */
#line 1778 "parser.y"
                        {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "MINUS("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 3407 "parser.tab.c"
    break;

  case 105: /* term: factor  */
#line 1873 "parser.y"
             {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 3415 "parser.tab.c"
    break;

  case 106: /* term: term STAR factor  */
#line 1876 "parser.y"
                   {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "STAR("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3432 "parser.tab.c"
    break;

  case 107: /* term: term SLASH factor  */
#line 1888 "parser.y"
                    {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "SLASH("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 3450 "parser.tab.c"
    break;

  case 108: /* term: term PERCENTAGE factor  */
#line 1901 "parser.y"
                         {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "PERCENTAGE("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 3468 "parser.tab.c"
    break;

  case 109: /* term: term DOUBLE_SLASH factor  */
#line 1914 "parser.y"
                           {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "DOUBLE_SLASH("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));

}
#line 3486 "parser.tab.c"
    break;

  case 110: /* factor: PLUS factor  */
#line 2039 "parser.y"
                 {
  // $$ = nodes++;
  // node_entities[$$] = "factor";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "PLUS("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3505 "parser.tab.c"
    break;

  case 111: /* factor: MINUS factor  */
#line 2053 "parser.y"
                    {
  // $$ = nodes++;
  // node_entities[$$] = "factor";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "MINUS("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3524 "parser.tab.c"
    break;

  case 112: /* factor: NOT_OP factor  */
#line 2067 "parser.y"
                     {
  // $$ = nodes++;
  // node_entities[$$] = "factor";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "BITWISE_NOT("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3543 "parser.tab.c"
    break;

  case 113: /* factor: power  */
#line 2081 "parser.y"
             {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 3551 "parser.tab.c"
    break;

  case 114: /* power: atom_expr  */
#line 2086 "parser.y"
                {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 3559 "parser.tab.c"
    break;

  case 115: /* power: atom_expr DOUBLE_STAR factor  */
#line 2089 "parser.y"
                               {
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "DOUBLE_STAR("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
}
#line 3576 "parser.tab.c"
    break;

  case 116: /* atom_expr: atom Multi_trailer  */
#line 2121 "parser.y"
                        {
  if((yyvsp[0].nt_num) == -1){
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "atom_expr";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));


    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 3597 "parser.tab.c"
    break;

  case 117: /* Multi_trailer: %empty  */
#line 2139 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 3605 "parser.tab.c"
    break;

  case 118: /* Multi_trailer: trailer Multi_trailer  */
#line 2142 "parser.y"
                             {

  if((yyvsp[0].nt_num) == -1){
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "Multi_trailer";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));


    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 3627 "parser.tab.c"
    break;

  case 119: /* atom: OPEN_ROUND_BRACKET Opt_test CLOSE_ROUND_BRACKET  */
#line 2161 "parser.y"
                                                     {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if((yyvsp[-1].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
    edges[parent_entities.size()-1] = "( )";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
#line 3654 "parser.tab.c"
    break;

  case 120: /* atom: OPEN_SQUARE_BRACKET Opt_testlist CLOSE_SQUARE_BRACKET  */
#line 2183 "parser.y"
                                                             {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_SQUARE_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if((yyvsp[-1].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
    edges[parent_entities.size()-1] = "[ ]";

  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_SQUARE_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
#line 3682 "parser.tab.c"
    break;

  case 121: /* atom: NAME  */
#line 2206 "parser.y"
            {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "NAME("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3699 "parser.tab.c"
    break;

  case 122: /* atom: NUMBER  */
#line 2218 "parser.y"
              {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "NUMBER("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3716 "parser.tab.c"
    break;

  case 123: /* atom: STRING Multi_string  */
#line 2230 "parser.y"
                          {
    if((yyvsp[0].nt_num) != -1){
      (yyval.nt_num) = nodes++;
      node_entities[(yyval.nt_num)] = "atom";

      parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
      ((yyvsp[-1].token_attr)).token_num = nodes++;
      temp_str = "STRING("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
      node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
      child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

      parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
      child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
    }
    else{
      ((yyvsp[-1].token_attr)).token_num = nodes++;
      temp_str = "STRING("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
      node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
      (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
    }
}
#line 3742 "parser.tab.c"
    break;

  case 124: /* atom: NONE  */
#line 2251 "parser.y"
            {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "NONE("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3759 "parser.tab.c"
    break;

  case 125: /* atom: TRUE  */
#line 2263 "parser.y"
            {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "TRUE("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3776 "parser.tab.c"
    break;

  case 126: /* atom: FALSE  */
#line 2275 "parser.y"
             {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "FALSE("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  (yyval.nt_num) = ((yyvsp[0].token_attr)).token_num;
}
#line 3793 "parser.tab.c"
    break;

  case 127: /* Opt_testlist: %empty  */
#line 2289 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 3801 "parser.tab.c"
    break;

  case 128: /* Opt_testlist: testlist  */
#line 2292 "parser.y"
                {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 3809 "parser.tab.c"
    break;

  case 129: /* Multi_string: %empty  */
#line 2298 "parser.y"
            {
  // // $$ = nodes++;
  // // node_entities[$$] = "Nonzero_string";

  // // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "STRING("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // $$ = ($1).token_num;
  (yyval.nt_num) = -1;
}
#line 3827 "parser.tab.c"
    break;

  case 130: /* Multi_string: STRING Multi_string  */
#line 2311 "parser.y"
                           {

  if((yyvsp[0].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "Multi_string";

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "STRING("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
  else{
    ((yyvsp[-1].token_attr)).token_num = nodes++;
    temp_str = "STRING("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
    node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
    (yyval.nt_num) = ((yyvsp[-1].token_attr)).token_num;
  }
  
}
#line 3855 "parser.tab.c"
    break;

  case 131: /* trailer: OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET  */
#line 2336 "parser.y"
                                                        {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "trailer";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if((yyvsp[-1].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
    edges[parent_entities.size()-1] = "( )";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
#line 3882 "parser.tab.c"
    break;

  case 132: /* trailer: OPEN_SQUARE_BRACKET testlist CLOSE_SQUARE_BRACKET  */
#line 2358 "parser.y"
                                                         {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "trailer";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_SQUARE_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
  edges[parent_entities.size()-1] = "[ ]";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_SQUARE_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
#line 3907 "parser.tab.c"
    break;

  case 133: /* trailer: DOT NAME  */
#line 2378 "parser.y"
                {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "trailer";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "DOT("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[0].token_attr)).token_num = nodes++;
  temp_str = "NAME("+string((char*)((yyvsp[0].token_attr)).token_lex)+")";
  node_entities[((yyvsp[0].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[0].token_attr)).token_num, node_entities[((yyvsp[0].token_attr)).token_num]));

  edges[parent_entities.size()-1] = ".";
}
#line 3930 "parser.tab.c"
    break;

  case 134: /* Opt_arglist: %empty  */
#line 2398 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 3938 "parser.tab.c"
    break;

  case 135: /* Opt_arglist: arglist  */
#line 2401 "parser.y"
               {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 3946 "parser.tab.c"
    break;

  case 136: /* testlist: test Multi_test  */
#line 2406 "parser.y"
                      {
  if((yyvsp[0].nt_num) == -1){
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "testlist";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));


    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }

}
#line 3968 "parser.tab.c"
    break;

  case 137: /* Multi_test: %empty  */
#line 2425 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 3976 "parser.tab.c"
    break;

  case 138: /* Multi_test: COMMA test Multi_test  */
#line 2428 "parser.y"
                             {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if((yyvsp[0].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "Multi_test";

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
  else{
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }

}
#line 4009 "parser.tab.c"
    break;

  case 139: /* classdef: CLASS NAME Opt_round_bracket_opt_arglist COLON suite  */
#line 2458 "parser.y"
                                                          {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "classdef";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "CLASS("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-3].token_attr)).token_num = nodes++;
  temp_str = "NAME("+string((char*)((yyvsp[-3].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-3].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-3].token_attr)).token_num, node_entities[((yyvsp[-3].token_attr)).token_num]));
  edges[parent_entities.size()-1] = "class";

  if((yyvsp[-2].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($4).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($4).token_lex)+")";
  // node_entities[($4).token_num] = temp_str;
  // child_entities.push_back(make_pair(($4).token_num, node_entities[($4).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  edges[parent_entities.size()-1] = "class body";

}
#line 4047 "parser.tab.c"
    break;

  case 140: /* Opt_round_bracket_opt_arglist: %empty  */
#line 2493 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 4055 "parser.tab.c"
    break;

  case 141: /* Opt_round_bracket_opt_arglist: OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET  */
#line 2496 "parser.y"
                                                          {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "class parameters";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if((yyvsp[-1].nt_num) != -1){
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));
    edges[parent_entities.size()-1] = "( )";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
#line 4082 "parser.tab.c"
    break;

  case 142: /* arglist: argument Multi_argument  */
#line 2520 "parser.y"
                              {
  if((yyvsp[0].nt_num) == -1){
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }

  else{
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "arglist";
    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));


    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
}
#line 4103 "parser.tab.c"
    break;

  case 143: /* Multi_argument: %empty  */
#line 2538 "parser.y"
                   {
  (yyval.nt_num) = -1;
}
#line 4111 "parser.tab.c"
    break;

  case 144: /* Multi_argument: COMMA argument Multi_argument  */
#line 2541 "parser.y"
                                     {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_argument";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if((yyvsp[0].nt_num) != -1){
    (yyval.nt_num) = nodes++;
    node_entities[(yyval.nt_num)] = "Multi_argument";

    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[-1].nt_num), node_entities[(yyvsp[-1].nt_num)]));


    parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
    child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));
  }
  else{
    (yyval.nt_num) = (yyvsp[-1].nt_num);
  }
}
#line 4144 "parser.tab.c"
    break;

  case 145: /* argument: test  */
#line 2571 "parser.y"
          {
  (yyval.nt_num) = (yyvsp[0].nt_num);
}
#line 4152 "parser.tab.c"
    break;

  case 146: /* argument: test EQUAL test  */
#line 2574 "parser.y"
                       {
  (yyval.nt_num) = nodes++;
  node_entities[(yyval.nt_num)] = "argument";
  
  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[-2].nt_num), node_entities[(yyvsp[-2].nt_num)]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  ((yyvsp[-1].token_attr)).token_num = nodes++;
  temp_str = "EQUAL("+string((char*)((yyvsp[-1].token_attr)).token_lex)+")";
  node_entities[((yyvsp[-1].token_attr)).token_num] = temp_str;
  child_entities.push_back(make_pair(((yyvsp[-1].token_attr)).token_num, node_entities[((yyvsp[-1].token_attr)).token_num]));

  parent_entities.push_back(make_pair((yyval.nt_num), node_entities[(yyval.nt_num)]));
  child_entities.push_back(make_pair((yyvsp[0].nt_num), node_entities[(yyvsp[0].nt_num)]));


}
#line 4175 "parser.tab.c"
    break;

  case 147: /* func_body_suite: simple_stmt  */
#line 2594 "parser.y"
                 {
  (yyval.nt_num) = (yyvsp[0].nt_num);

}
#line 4184 "parser.tab.c"
    break;

  case 148: /* func_body_suite: NEWLINE INDENT Nonzero_stmt DEDENT  */
#line 2598 "parser.y"
                                          {
  // $$ = nodes++;
  // node_entities[$$] = "func_body_suite";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++; 
  // temp_str = "NEWLINE";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++; 
  // temp_str = "INDENT";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  (yyval.nt_num) = (yyvsp[-1].nt_num);

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($3, node_entities[$3]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($4).token_num = nodes++; 
  // temp_str = "DEDENT";
  // node_entities[($4).token_num] = temp_str;
  // child_entities.push_back(make_pair(($4).token_num, node_entities[($4).token_num]));
}
#line 4216 "parser.tab.c"
    break;


#line 4220 "parser.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 2626 "parser.y"


int main(int argc, char *argv[])
{
  string exec_file_name(argv[0]);
  argc--, argv++;
  if(argc != 3) {
    cerr << exec_file_name << ": Error: Incorrect arguments given\n";
    exit(1);
  }
  char *input_file_name = argv[0], *output_filename = argv[1];
  int verbose = atoi(argv[2]);
  if(verbose) yydebug = 1;
  yyin = fopen(input_file_name, "r");
  if(yyin == NULL) {
    cerr << exec_file_name << ": Error: Input file " << input_file_name << " is missing\n";
    exit(1);
  }
  yyparse();
  /* cout<<parent_entities.size()<<child_entities.size(); */
  ofstream fout(output_filename);
  fout<<"digraph G {"<<endl;
  fout<<"node [ordering=out]\n";
  for(auto it : node_entities){
    if(it.second.size() >= 8 && it.second[7]=='\"'){
      fout<<it.first<<" [label=\"" ;
      for(auto j: it.second){
        if(j=='\"') fout<<"\\\"";
        else fout<<j;
      }
      fout<<"\"]" << endl;
    }
    else
    fout<<it.first<<" [label=\"" << it.second << "\"]" << endl;
  }
  for(int i=0; i<nodes-1; ++i){
    fout<<parent_entities[i].first<<" -> "<<child_entities[i].first<<" ";
    auto it = edges.find(i);
    if(it != edges.end()){
      fout<<"[label=\""<< edges[i] <<"\"]";
    }
    fout<<"\n";
  }
  fout<<"}"<<endl;
  // cout<<parent_entities.size()<<" "<<child_entities.size()<<"\n";
  return 0;
}

void yyerror(const char * s)
{
  cout<<"Error in line " << yylineno << " : " << s << endl;
  exit(0);
}
