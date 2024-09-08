/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
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
    STRING = 258,                  /* STRING  */
    INDENT = 259,                  /* INDENT  */
    DEDENT = 260,                  /* DEDENT  */
    DOUBLE_QUOTE = 261,            /* DOUBLE_QUOTE  */
    SINGLE_QUOTE = 262,            /* SINGLE_QUOTE  */
    BREAK = 263,                   /* BREAK  */
    CONTINUE = 264,                /* CONTINUE  */
    RETURN = 265,                  /* RETURN  */
    GLOBAL = 266,                  /* GLOBAL  */
    ASSERT = 267,                  /* ASSERT  */
    CLASS = 268,                   /* CLASS  */
    DEF = 269,                     /* DEF  */
    IF = 270,                      /* IF  */
    ELIF = 271,                    /* ELIF  */
    ELSE = 272,                    /* ELSE  */
    WHILE = 273,                   /* WHILE  */
    FOR = 274,                     /* FOR  */
    IN = 275,                      /* IN  */
    NONE = 276,                    /* NONE  */
    TRUE = 277,                    /* TRUE  */
    FALSE = 278,                   /* FALSE  */
    OR = 279,                      /* OR  */
    AND = 280,                     /* AND  */
    NOT = 281,                     /* NOT  */
    IS = 282,                      /* IS  */
    OPEN_ROUND_BRACKET = 283,      /* OPEN_ROUND_BRACKET  */
    ARROW = 284,                   /* ARROW  */
    SEMICOLON = 285,               /* SEMICOLON  */
    COLON = 286,                   /* COLON  */
    EQUAL = 287,                   /* EQUAL  */
    PLUS_EQUAL = 288,              /* PLUS_EQUAL  */
    MINUS_EQUAL = 289,             /* MINUS_EQUAL  */
    STAR_EQUAL = 290,              /* STAR_EQUAL  */
    SLASH_EQUAL = 291,             /* SLASH_EQUAL  */
    PERCENTAGE_EQUAL = 292,        /* PERCENTAGE_EQUAL  */
    AND_EQUAL = 293,               /* AND_EQUAL  */
    OR_EQUAL = 294,                /* OR_EQUAL  */
    XOR_EQUAL = 295,               /* XOR_EQUAL  */
    LEFT_SHIFT_EQUAL = 296,        /* LEFT_SHIFT_EQUAL  */
    RIGHT_SHIFT_EQUAL = 297,       /* RIGHT_SHIFT_EQUAL  */
    DOUBLE_STAR_EQUAL = 298,       /* DOUBLE_STAR_EQUAL  */
    DOUBLE_SLASH_EQUAL = 299,      /* DOUBLE_SLASH_EQUAL  */
    COMMA = 300,                   /* COMMA  */
    DOT = 301,                     /* DOT  */
    STAR = 302,                    /* STAR  */
    SLASH = 303,                   /* SLASH  */
    DOUBLE_STAR = 304,             /* DOUBLE_STAR  */
    OR_OP = 305,                   /* OR_OP  */
    PLUS = 306,                    /* PLUS  */
    MINUS = 307,                   /* MINUS  */
    OPEN_SQUARE_BRACKET = 308,     /* OPEN_SQUARE_BRACKET  */
    COLON_EQUAL = 309,             /* COLON_EQUAL  */
    DOUBLE_EQUAL = 310,            /* DOUBLE_EQUAL  */
    NOT_EQUAL = 311,               /* NOT_EQUAL  */
    LESSER_EQUAL = 312,            /* LESSER_EQUAL  */
    LESSER = 313,                  /* LESSER  */
    GREATER_EQUAL = 314,           /* GREATER_EQUAL  */
    GREATER = 315,                 /* GREATER  */
    XOR = 316,                     /* XOR  */
    AND_OP = 317,                  /* AND_OP  */
    LEFT_SHIFT = 318,              /* LEFT_SHIFT  */
    RIGHT_SHIFT = 319,             /* RIGHT_SHIFT  */
    DOUBLE_SLASH = 320,            /* DOUBLE_SLASH  */
    PERCENTAGE = 321,              /* PERCENTAGE  */
    NOT_OP = 322,                  /* NOT_OP  */
    NAME = 323,                    /* NAME  */
    NEWLINE = 324,                 /* NEWLINE  */
    NUMBER = 325,                  /* NUMBER  */
    CLOSE_ROUND_BRACKET = 326,     /* CLOSE_ROUND_BRACKET  */
    CLOSE_SQUARE_BRACKET = 327     /* CLOSE_SQUARE_BRACKET  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser.y"

  struct {
    int token_num;
    char token_lex[1000];
  } token_attr;
  int nt_num;
  // char nt_lex[1000];

#line 145 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
