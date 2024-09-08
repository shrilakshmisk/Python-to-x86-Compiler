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
#line 1 "parser.y"

    #include<bits/stdc++.h>
    #include <string>
    #include <fstream>
    using namespace std;
    void yyerror(const char * s);
    int yylex();
    extern int yylineno;
    extern FILE* yyin;
    #define YYERROR_VERBOSE 1

    map <string, int> all_global_vars;

    class Symbol_Table_Entry {
      public:
        string token;
        string type;
        int offset;
        string scopename;
        int line;
        string return_type;
        int numargs;
        int argnum;
        int width;
        int isinit;
        int listlen = 0;
        void *pointer;
        void* childtable;

        Symbol_Table_Entry(){ 
        }
        Symbol_Table_Entry(string token_, string type_, int offset_, string scopename_, int line_, int argnum_, int width_, int numargs_, int isinit_){
          token = token_;
          type = type_;
          offset = offset_;
          scopename = scopename_;
          line = line_;
          argnum = argnum_;
          width = width_;
          numargs = numargs_;
          isinit = isinit_;
        }
        void update_entry(void* childtable_){
          childtable =  childtable_;
        }
        void print_sym_entry(ostream& os){
          os << token << " " << type << " " << offset << " " << scopename << " " << line << " "<< numargs << " "<< argnum <<" " << width << " " << isinit << " " << endl;
        }
        void print_sym_entry(){
          cout << token << " " << type << " " << offset << " " << scopename << " " << line << " "<< numargs << " "<< argnum <<" " << width << " " << isinit << " " << endl;
        }

        void update_listlen(int listlen_){
          listlen = listlen_;
        }
    };
  class Symbol_Table {
    public:
      map <string, Symbol_Table_Entry> table;
      Symbol_Table* parent;
      int level_no;
      Symbol_Table_Entry* make_entry(string lexeme, string token, string type, int offset, string scopename, int line, int argnum, int width, int numargs, int isinit){
        if(table.find(lexeme) != table.end()){
              cerr << line << ": Error: Redeclaration of " << lexeme << endl; 
              exit(0); 
        }
        if(all_global_vars.find(lexeme) != all_global_vars.end()) {
          if(all_global_vars[lexeme] == 2){
            cerr <<  line << ": Error: Redeclaration of global variable " << lexeme << endl; 
            exit(0);
          }
          else{
            
            for(auto it=this; it!=NULL; it=it->parent){
              if(it->parent == NULL){
                 it->table[lexeme] = Symbol_Table_Entry(token, type, offset, scopename, line, argnum, width, numargs, isinit);
                 all_global_vars[lexeme] = 2;
                 return &(it->table[lexeme]);
              }
            }
          }
        }
        else{
          table[lexeme] = Symbol_Table_Entry(token, type, offset, scopename, line, argnum, width, numargs, isinit);
          return &(table[lexeme]);
        }

        return NULL;
        
      }

      // Symbol_Table_Entry* copy_entry(string lexeme, string token, string type, int offset, string scopename, int line, int argnum, int width, int numargs, int isinit, void* childpointer){
      //   if(table.find(lexeme) != table.end()){
      //         cerr << line << ": Error: Redeclaration of " << lexeme << endl; 
      //         exit(0); 
      //   }
      //   if(all_global_vars.find(lexeme) != all_global_vars.end()) {
      //     if(all_global_vars[lexeme] == 2){
      //       cerr <<  line << ": Error: Redeclaration of global variable " << lexeme << endl; 
      //       exit(0);
      //     }
      //     else{
            
      //       for(auto it=this; it!=NULL; it=it->parent){
      //         if(it->parent == NULL){
      //            it->table[lexeme] = Symbol_Table_Entry(token, type, offset, scopename, line, argnum, width, numargs, isinit);
      //            all_global_vars[lexeme] = 2;
      //            return &(it->table[lexeme]);
      //         }
      //       }
      //     }
      //   }
      //   else{
      //     table[lexeme] = Symbol_Table_Entry(token, type, offset, scopename, line, argnum, width, numargs, isinit);
      //     table[lexeme]->updatee
      //     return &(table[lexeme]);
      //   }

      //   return NULL;
        
      // }
      Symbol_Table(){}
      Symbol_Table(Symbol_Table* child){
          if(!child){
            level_no = 0;
            parent = NULL;
          }
          else{
            level_no = child->level_no + 1;
            parent = child;
          }
      }

      Symbol_Table_Entry lookup(string lexeme){
        for(auto it=this; it!=NULL; it=it->parent){
          if(it->table.find(lexeme) != it->table.end()){
            return it->table[lexeme];
          }
        }
        return Symbol_Table_Entry("null", "null", -1, "null", -1, -1, -1, -1, -1);
      }

      void modify_lookup(string lexeme, int isinit_){
        for(auto it=this; it!=NULL; it=it->parent){
          if(it->table.find(lexeme) != it->table.end()){
            it->table[lexeme].isinit = isinit_;
          }
        }
      }
      

      void print_sym_table(ostream& os){
        for(auto it=table.begin(); it!=table.end(); it++){
          os<<it->first<<": ";
          it->second.print_sym_entry(os);
        }
      }
  };

  int offset = 0;
  Symbol_Table* curr_table = new Symbol_Table(NULL);
  
  string curr_scope = "Global";
  stack <Symbol_Table*> table_stack;
  stack <int> offset_stack;
  stack <string> scope_stack;
  int size; 
  string type = "";
  vector <Symbol_Table*> vec_tables (1, curr_table);
  vector<pair<string,string>> func_param_vec;
  vector<pair<string,string>> func_arg_vec;
  vector<pair<string,string>> func_arg_temp_vec;
  vector <string> list_temps;
  // vector<string> testlist_types_vec;
  string func_return_type;
  int isreturning = 0;
  // map <string, int> class_size;
  int class_flag = 0; 
  map <string, Symbol_Table*> class_symbol_tables;
  string recent_class;
  unordered_set <string> all_types = {"int", "float", "str", "bool", "list@int", "list@float", "list@str", "list@bool"};
  stack <string> breakjumps;
  stack <string> continuejumps;
  vector <string> code_3ac; 
  map <string, string> child_to_parent_classes;
  stack<string> if_scopes;
  string range_start, range_end;
  int add_offset = 0;

  // all_types.insert("int");
  // all_types.insert("float");
  // all_types.insert("str");
  // all_types.insert("bool");


  int type_size(string s)
    {
      // have not handled size of an object
      int islist = 0;
      if(s.length() >= 5){
        string t = s.substr(0,5);
        if(t == "list@") islist = 1;
      }

      if(!islist){
        if(s == "int") return 4;
        else if(s == "float") return 4;
        else if(s == "bool") return 1;
        else if(s == "str") return 8;
        else return 8;
      }
      if(islist){
        string ns = s.substr(5);
        if(ns == "int") return 8;
        else if(ns == "float") return 8;
        else if(ns == "bool") return 8;
        else if(ns == "str") return 8;
        else return 8;
      }
      

      return 0;
    }

  string to_string(char* a)
{
    string s = a;
    return s;
}



int match_type(string a, string b){
  if(a == b){
    return 1;
  }
  else if(a == "bool" && b == "int"){
    return 1;
  }
  else if(a == "int" && b == "bool"){
    return 1;
  }
  else if(a == "float" && b == "int"){
    return 1;
  }
  else if (a == "int" && b == "float"){
    return 1;
  }
  // else if(a == "list@bool" && b == "list@int"){
  //   return 1;
  // }
  // else if(a == "list@int" && b == "list@bool"){
  //   return 1;
  // }
  // else if(a == "list@float" && b == "list@int"){
  //   return 1;
  // }
  // else if (a == "list@int" && b == "list@float"){
  //   return 1;
  // }
  else{
    if (child_to_parent_classes.find(b) != child_to_parent_classes.end()) {
        if(a == child_to_parent_classes[b]){
          return 1;
        }
    }
    return 0;
  }
}

void gen(string line_3ac){
  code_3ac.push_back(line_3ac);
}

// }
long long t_count = 0;
long long L_count = 0;

string t_new(){
  string temp_var = "t"+to_string(t_count++);
  return temp_var;
}
string L_new(){
  string temp_var = "L"+to_string(L_count++);
  return temp_var;
}


#line 360 "parser.tab.c"

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
  YYSYMBOL_77_1 = 77,                      /* $@1  */
  YYSYMBOL_78_2 = 78,                      /* $@2  */
  YYSYMBOL_parameters = 79,                /* parameters  */
  YYSYMBOL_typedargslist = 80,             /* typedargslist  */
  YYSYMBOL_Multi_tfpdef = 81,              /* Multi_tfpdef  */
  YYSYMBOL_tfpdef = 82,                    /* tfpdef  */
  YYSYMBOL_stmt = 83,                      /* stmt  */
  YYSYMBOL_simple_stmt = 84,               /* simple_stmt  */
  YYSYMBOL_Multi_small_stmt = 85,          /* Multi_small_stmt  */
  YYSYMBOL_small_stmt = 86,                /* small_stmt  */
  YYSYMBOL_expr_stmt = 87,                 /* expr_stmt  */
  YYSYMBOL_Lhs_init = 88,                  /* Lhs_init  */
  YYSYMBOL_Lhs_noninit = 89,               /* Lhs_noninit  */
  YYSYMBOL_flow_stmt = 90,                 /* flow_stmt  */
  YYSYMBOL_Opt_test = 91,                  /* Opt_test  */
  YYSYMBOL_global_stmt = 92,               /* global_stmt  */
  YYSYMBOL_Multi_name = 93,                /* Multi_name  */
  YYSYMBOL_compound_stmt = 94,             /* compound_stmt  */
  YYSYMBOL_if_stmt = 95,                   /* if_stmt  */
  YYSYMBOL_dummy_if_suit = 96,             /* dummy_if_suit  */
  YYSYMBOL_dummyifstmt = 97,               /* dummyifstmt  */
  YYSYMBOL_Multi_elif = 98,                /* Multi_elif  */
  YYSYMBOL_99_3 = 99,                      /* $@3  */
  YYSYMBOL_dummyelifstmt = 100,            /* dummyelifstmt  */
  YYSYMBOL_Opt_else = 101,                 /* Opt_else  */
  YYSYMBOL_dummyWhilestmt = 102,           /* dummyWhilestmt  */
  YYSYMBOL_dummyWhilestmt1 = 103,          /* dummyWhilestmt1  */
  YYSYMBOL_while_stmt = 104,               /* while_stmt  */
  YYSYMBOL_dummy_for_stmt = 105,           /* dummy_for_stmt  */
  YYSYMBOL_for_stmt = 106,                 /* for_stmt  */
  YYSYMBOL_suite = 107,                    /* suite  */
  YYSYMBOL_Nonzero_stmt = 108,             /* Nonzero_stmt  */
  YYSYMBOL_test = 109,                     /* test  */
  YYSYMBOL_or_test = 110,                  /* or_test  */
  YYSYMBOL_and_test = 111,                 /* and_test  */
  YYSYMBOL_not_test = 112,                 /* not_test  */
  YYSYMBOL_comparison = 113,               /* comparison  */
  YYSYMBOL_expr = 114,                     /* expr  */
  YYSYMBOL_xor_expr = 115,                 /* xor_expr  */
  YYSYMBOL_and_expr = 116,                 /* and_expr  */
  YYSYMBOL_shift_expr = 117,               /* shift_expr  */
  YYSYMBOL_arith_expr = 118,               /* arith_expr  */
  YYSYMBOL_term = 119,                     /* term  */
  YYSYMBOL_factor = 120,                   /* factor  */
  YYSYMBOL_power = 121,                    /* power  */
  YYSYMBOL_atom_expr = 122,                /* atom_expr  */
  YYSYMBOL_Multi_trailer = 123,            /* Multi_trailer  */
  YYSYMBOL_atom = 124,                     /* atom  */
  YYSYMBOL_trailer = 125,                  /* trailer  */
  YYSYMBOL_Opt_arglist = 126,              /* Opt_arglist  */
  YYSYMBOL_testlist = 127,                 /* testlist  */
  YYSYMBOL_Multi_test = 128,               /* Multi_test  */
  YYSYMBOL_classdef = 129,                 /* classdef  */
  YYSYMBOL_130_4 = 130,                    /* $@4  */
  YYSYMBOL_131_5 = 131,                    /* $@5  */
  YYSYMBOL_arglist = 132,                  /* arglist  */
  YYSYMBOL_Multi_argument = 133,           /* Multi_argument  */
  YYSYMBOL_argument = 134,                 /* argument  */
  YYSYMBOL_func_body_suite = 135           /* func_body_suite  */
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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  63
/* YYNRULES -- Number of rules.  */
#define YYNRULES  147
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  259

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
       0,   493,   493,   498,   501,   504,   509,   509,   607,   607,
     697,   703,   711,   718,   721,   727,   733,   745,   748,   753,
     758,   761,   767,   770,   773,   784,   874,   901,  1078,  1242,
    1246,  1322,  1419,  1505,  1593,  1681,  1769,  1847,  1924,  2001,
    2078,  2155,  2240,  2333,  2338,  2361,  2373,  2416,  2459,  2515,
    2519,  2523,  2553,  2586,  2589,  2594,  2607,  2610,  2622,  2625,
    2628,  2631,  2634,  2640,  2655,  2666,  2675,  2678,  2678,  2690,
    2700,  2703,  2735,  2744,  2754,  2763,  2804,  2814,  2817,  2823,
    2826,  2831,  2839,  2844,  2906,  2911,  2973,  2991,  2999,  3005,
    3063,  3121,  3179,  3238,  3297,  3356,  3362,  3368,  3412,  3418,
    3461,  3467,  3509,  3515,  3556,  3599,  3605,  3660,  3716,  3721,
    3775,  3830,  3883,  3940,  3967,  3995,  4017,  4024,  4031,  4091,
    4676,  4680,  4696,  4703,  4743,  4770,  4779,  4789,  4796,  4806,
    4818,  4826,  4843,  4854,  4857,  4862,  4871,  4874,  4880,  4880,
    4914,  4914,  4988,  4993,  4996,  5002,  5010,  5013
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
  "file_input", "funcdef", "$@1", "$@2", "parameters", "typedargslist",
  "Multi_tfpdef", "tfpdef", "stmt", "simple_stmt", "Multi_small_stmt",
  "small_stmt", "expr_stmt", "Lhs_init", "Lhs_noninit", "flow_stmt",
  "Opt_test", "global_stmt", "Multi_name", "compound_stmt", "if_stmt",
  "dummy_if_suit", "dummyifstmt", "Multi_elif", "$@3", "dummyelifstmt",
  "Opt_else", "dummyWhilestmt", "dummyWhilestmt1", "while_stmt",
  "dummy_for_stmt", "for_stmt", "suite", "Nonzero_stmt", "test", "or_test",
  "and_test", "not_test", "comparison", "expr", "xor_expr", "and_expr",
  "shift_expr", "arith_expr", "term", "factor", "power", "atom_expr",
  "Multi_trailer", "atom", "trailer", "Opt_arglist", "testlist",
  "Multi_test", "classdef", "$@4", "$@5", "arglist", "Multi_argument",
  "argument", "func_body_suite", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-216)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-125)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      44,  -216,  -216,  -216,   219,   -60,   -48,   -32,   219,  -216,
     -28,  -216,  -216,  -216,   219,   219,    -5,    44,  -216,    46,
    -216,  -216,    44,  -216,    14,  -216,    25,   293,  -216,  -216,
    -216,  -216,    33,   134,   219,    30,  -216,    40,  -216,  -216,
    -216,   219,   245,   245,   245,  -216,  -216,    74,    76,  -216,
     152,    52,    42,    43,   -13,    18,   101,  -216,  -216,    55,
     -15,    71,     6,    89,    87,    99,    57,  -216,    91,    60,
     219,    70,   219,  -216,  -216,  -216,   254,    77,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   130,   134,   146,  -216,  -216,  -216,   134,
     134,  -216,  -216,  -216,  -216,   219,   219,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,   245,   245,   245,   219,    83,   219,  -216,
     -15,    84,  -216,    85,  -216,   -26,   -17,  -216,   219,  -216,
     219,  -216,  -216,  -216,    88,  -216,   109,   -10,    92,    14,
    -216,   128,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,   132,   137,  -216,  -216,   112,
    -216,  -216,    76,  -216,    52,    52,    52,    52,    52,    52,
      52,    42,    43,   -13,    18,    18,   101,   101,  -216,  -216,
    -216,  -216,  -216,    90,  -216,   102,  -216,    71,   108,   134,
     142,  -216,   110,   138,   219,  -216,  -216,    91,  -216,   219,
    -216,   219,   219,  -216,  -216,   219,  -216,   134,    33,   112,
     179,  -216,  -216,  -216,   154,  -216,   219,  -216,   118,  -216,
     160,   167,  -216,   109,   121,   122,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,   138,  -216,   189,  -216,  -216,  -216,  -216,
    -216,   134,  -216,   167,   112,  -216,  -216,   191,  -216
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,   126,    49,    50,    51,     0,     0,     0,     0,    72,
       0,   127,   128,   129,    53,     0,    45,     3,   125,     0,
       2,    61,     3,    17,    20,    22,     0,     0,    23,    24,
      18,    58,    66,     0,     0,     0,    59,     0,    60,    29,
      62,     0,     0,     0,     0,   124,    52,    81,    82,    84,
      87,    88,    96,    98,   100,   102,   105,   108,   116,   117,
     120,    56,     0,     0,     0,     0,     0,    54,   136,     0,
     133,     0,     0,     4,     1,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    70,     0,     0,    77,    64,    73,     0,
       0,    86,   113,   114,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   133,     0,     0,   119,
     120,     0,    55,     0,   138,     0,     0,    65,     0,   122,
       0,   135,   123,   145,     0,   134,   143,    46,     0,    20,
      19,    26,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,     0,     0,    63,    67,     0,
      74,    76,    83,    85,    95,    91,    94,    93,    89,    92,
      90,    97,    99,   101,   103,   104,   106,   107,   109,   110,
     112,   111,   118,     0,   132,     0,   121,    56,     0,     0,
      16,    10,     0,    13,     0,     6,    75,   136,    27,     0,
     142,   133,     0,    47,    21,     0,    69,     0,    66,    79,
       0,   130,   131,    57,     0,   139,     0,    11,     0,    12,
       0,     0,   137,   143,     0,     0,    25,    71,    68,    80,
      78,   140,    15,    13,     8,     0,   146,     7,   144,    28,
      48,     0,    14,     0,     0,   141,     9,     0,   147
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,    10,  -216,  -216,  -216,  -216,  -216,   -46,   -30,
    -159,     2,    51,   125,  -216,  -216,  -216,  -216,  -216,  -216,
       9,  -216,  -216,  -216,  -216,    -4,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,   -93,  -215,     1,  -216,   113,   -38,
    -216,   192,   111,   100,   107,   -43,   -42,   -14,  -216,  -216,
      94,     0,  -216,  -115,  -216,    19,  -216,  -216,  -216,  -216,
      -3,    20,   -25
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,   231,   253,   136,   202,   229,   203,
      22,    96,    77,    24,    25,    26,    27,    28,    66,    29,
     132,    30,    31,    32,    33,    93,   218,    94,   167,    34,
      35,    36,    37,    38,    97,   220,   143,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
     129,    60,   130,   144,    69,   141,    40,   199,   251,   145,
     210,   146,   247
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      39,   168,    23,   101,   239,    46,   170,   171,    61,    64,
     219,   193,   204,   126,   205,    67,    68,    39,   211,    23,
      62,   -44,    39,    70,    23,  -124,   -43,    73,   102,   103,
     104,   127,    75,    39,   133,    98,    63,   134,   128,   257,
      65,    71,   200,   212,    76,   201,    74,     1,    72,    92,
     117,   118,     2,     3,     4,     5,    78,     6,     7,     8,
     219,    99,     9,    10,  -124,    11,    12,    13,   173,   119,
     120,   100,    14,   148,   184,   185,    39,   186,   187,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,    39,   219,   234,    15,   105,    39,
      39,   106,   114,   115,   125,   116,   225,   188,   189,   190,
     191,   192,    16,    17,    18,     1,   131,   135,   137,   138,
       2,     3,     4,     5,   237,     6,     7,     8,   139,   195,
       9,    10,   142,    11,    12,    13,   140,     1,   147,   206,
      14,   207,     2,     3,     4,     5,   150,   166,   121,   122,
     169,   194,   197,   198,   209,    11,    12,    13,   255,   208,
     215,   221,    14,   216,   213,    15,   123,   124,   217,    39,
       1,    23,   107,   226,   222,     2,     3,     4,     5,   224,
      16,   227,    18,   228,   240,   241,   200,    15,    11,    12,
      13,   244,   249,   254,   250,    14,   258,   252,   243,    39,
     214,   149,    16,    95,    18,   230,   223,   108,   109,   110,
     111,   112,   113,   235,   238,   182,   236,    39,   172,    39,
      15,    23,     1,   183,   196,   181,   232,   242,   256,   233,
     248,    39,     0,   246,     0,    16,   245,    18,     0,     0,
      11,    12,    13,     0,     0,    41,     0,    14,     1,     0,
       0,    39,     0,    39,    39,   246,    23,     1,     0,     0,
       0,     0,     2,     3,     4,     5,    11,    12,    13,     0,
      42,    43,    15,    14,     0,    11,    12,    13,     0,     0,
       0,     0,    14,     0,     0,     0,    44,    45,     0,    18,
       0,     0,     0,     0,     0,     0,    42,    43,    15,   174,
     175,   176,   177,   178,   179,   180,     0,    15,     0,     0,
       0,     0,    44,    45,     0,    18,     0,     0,     0,     0,
       0,     0,    16,     0,    18,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91
};

static const yytype_int16 yycheck[] =
{
       0,    94,     0,    41,   219,     4,    99,   100,    68,     8,
     169,   126,    29,    28,    31,    14,    15,    17,    28,    17,
      68,    31,    22,    28,    22,    30,    31,    17,    42,    43,
      44,    46,    22,    33,    28,    34,    68,    31,    53,   254,
      68,    46,    68,    53,    30,    71,     0,     3,    53,    16,
      63,    64,     8,     9,    10,    11,    31,    13,    14,    15,
     219,    31,    18,    19,    69,    21,    22,    23,   106,    51,
      52,    31,    28,    72,   117,   118,    76,   119,   120,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    94,   254,   211,    53,    24,    99,
     100,    25,    50,    61,    49,    62,   199,   121,   122,   123,
     124,   125,    68,    69,    70,     3,    45,    28,    31,    20,
       8,     9,    10,    11,   217,    13,    14,    15,    71,   128,
      18,    19,    72,    21,    22,    23,    45,     3,    68,   138,
      28,   140,     8,     9,    10,    11,    69,    17,    47,    48,
       4,    68,    68,    68,    45,    21,    22,    23,   251,    71,
      32,    71,    28,    31,    72,    53,    65,    66,    31,   169,
       3,   169,    20,    31,    72,     8,     9,    10,    11,    71,
      68,    71,    70,    45,     5,    31,    68,    53,    21,    22,
      23,    31,    71,     4,    72,    28,     5,   243,   228,   199,
     149,    76,    68,    69,    70,   204,   197,    55,    56,    57,
      58,    59,    60,   212,   218,   115,   215,   217,   105,   219,
      53,   219,     3,   116,   130,   114,   207,   226,   253,   209,
     233,   231,    -1,   231,    -1,    68,    69,    70,    -1,    -1,
      21,    22,    23,    -1,    -1,    26,    -1,    28,     3,    -1,
      -1,   251,    -1,   253,   254,   253,   254,     3,    -1,    -1,
      -1,    -1,     8,     9,    10,    11,    21,    22,    23,    -1,
      51,    52,    53,    28,    -1,    21,    22,    23,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    67,    68,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    51,    52,    53,   107,
     108,   109,   110,   111,   112,   113,    -1,    53,    -1,    -1,
      -1,    -1,    67,    68,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    -1,    70,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     8,     9,    10,    11,    13,    14,    15,    18,
      19,    21,    22,    23,    28,    53,    68,    69,    70,    74,
      75,    76,    83,    84,    86,    87,    88,    89,    90,    92,
      94,    95,    96,    97,   102,   103,   104,   105,   106,   124,
     129,    26,    51,    52,    67,    68,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     124,    68,    68,    68,   109,    68,    91,   109,   109,   127,
      28,    46,    53,    75,     0,    75,    30,    85,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    16,    98,   100,    69,    84,   107,   109,    31,
      31,   112,   120,   120,   120,    24,    25,    20,    55,    56,
      57,    58,    59,    60,    50,    61,    62,    63,    64,    51,
      52,    47,    48,    65,    66,    49,    28,    46,    53,   123,
     125,    45,    93,    28,    31,    28,    79,    31,    20,    71,
      45,   128,    72,   109,   126,   132,   134,    68,   109,    86,
      69,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,    17,   101,   107,     4,
     107,   107,   111,   112,   114,   114,   114,   114,   114,   114,
     114,   115,   116,   117,   118,   118,   119,   119,   120,   120,
     120,   120,   120,   126,    68,   109,   123,    68,    68,   130,
      68,    71,    80,    82,    29,    31,   109,   109,    71,    45,
     133,    28,    53,    72,    85,    32,    31,    31,    99,    83,
     108,    71,    72,    93,    71,   107,    31,    71,    45,    81,
     109,    77,   128,   134,   126,   109,   109,   107,    98,   108,
       5,    31,   109,    82,    31,    69,    84,   135,   133,    71,
      72,   131,    81,    78,     4,   107,   135,   108,     5
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    75,    75,    77,    76,    78,    76,
      79,    79,    80,    81,    81,    82,    82,    83,    83,    84,
      85,    85,    86,    86,    86,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    88,    88,    89,    89,    89,    89,    90,
      90,    90,    90,    91,    91,    92,    93,    93,    94,    94,
      94,    94,    94,    95,    96,    97,    98,    99,    98,   100,
     101,   101,   102,   103,   104,   105,   106,   107,   107,   108,
     108,   109,   110,   110,   111,   111,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   114,   114,   115,   115,
     116,   116,   117,   117,   117,   118,   118,   118,   119,   119,
     119,   119,   119,   120,   120,   120,   120,   121,   121,   122,
     123,   123,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   125,   125,   126,   126,   127,   128,   128,   130,   129,
     131,   129,   132,   133,   133,   134,   135,   135
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     0,     6,     0,     8,
       2,     3,     2,     0,     3,     3,     1,     1,     1,     3,
       0,     3,     1,     1,     1,     5,     3,     4,     6,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     1,     3,     4,     6,     1,
       1,     1,     2,     0,     1,     3,     0,     3,     1,     1,
       1,     1,     1,     3,     2,     3,     0,     0,     4,     3,
       0,     3,     1,     2,     3,     4,     3,     1,     4,     1,
       2,     1,     1,     3,     1,     3,     2,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     2,     2,     2,     1,     1,     3,     2,
       0,     2,     3,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     2,     0,     1,     2,     0,     3,     0,     5,
       0,     8,     2,     0,     3,     1,     1,     4
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
#line 493 "parser.y"
            {
  
}
#line 1966 "parser.tab.c"
    break;

  case 3: /* file_input: %empty  */
#line 498 "parser.y"
                           {
  
}
#line 1974 "parser.tab.c"
    break;

  case 4: /* file_input: NEWLINE file_input  */
#line 501 "parser.y"
                          {
  
}
#line 1982 "parser.tab.c"
    break;

  case 5: /* file_input: stmt file_input  */
#line 504 "parser.y"
                         {
  
}
#line 1990 "parser.tab.c"
    break;

  case 6: /* $@1: %empty  */
#line 509 "parser.y"
                          {
    if(recent_class == ""){
      gen(to_string(((yyvsp[-2].token_attr)).token_lex) + ":");
    }
    else{
      gen(recent_class + "." + to_string(((yyvsp[-2].token_attr)).token_lex) + ":");
    }
    gen("beginfunc");

    gen("push %rbp");
    gen("%rbp = %rsp");

    
    
    // gen()
    // string none = "None";
    // strcpy(($$).lexeme, none.c_str());
    func_return_type = "None";
    if(to_string(((yyvsp[-2].token_attr)).token_lex) == "__init__"){
      func_return_type = recent_class;
    }
    // int n_arg = ($3).func_numargs;
    // ($$).func_numargs = ($3).func_numargs;
    // int n_arg = ($$).func_numargs;
    Symbol_Table_Entry* func_entry = curr_table->make_entry(to_string(((yyvsp[-2].token_attr)).token_lex), "Function", func_return_type, offset, curr_scope, ((yyvsp[-3].token_attr)).linenum, -1, -1, ((yyvsp[-1].type_attr)).func_numargs, 1);
    offset += 0;

    table_stack.push(curr_table);
    curr_table = new Symbol_Table(curr_table);
    (func_entry->update_entry)(curr_table);
    vec_tables.push_back(curr_table);
    scope_stack.push(curr_scope);
    offset_stack.push(offset);
    if(recent_class == "")
    curr_scope = "Function@" + to_string(((yyvsp[-2].token_attr)).token_lex);
    else
    curr_scope = "Function@" + to_string(((yyvsp[-2].token_attr)).token_lex) + "." + recent_class;
    offset = 0;
    for(int i = 0; i< (int)(int)func_param_vec.size(); i++){
      curr_table->make_entry(func_param_vec[i].first, "Function_Parameter", func_param_vec[i].second, offset, curr_scope, ((yyvsp[-3].token_attr)).linenum, i+1, -1, ((yyvsp[-1].type_attr)).func_numargs, 1);
      // string temp_ = t_new();
      string rbp_offset = to_string(offset + 16);
      gen(func_param_vec[i].first + " = " + rbp_offset + "(%rbp)");
      gen("sub %rsp " + to_string(type_size(func_param_vec[i].second)));
      gen(to_string(-(offset + type_size(func_param_vec[i].second))) + "(%rbp) = " + func_param_vec[i].first);
      // gen(func_param_vec[i].first + " = " + temp_);
      offset+= type_size(func_param_vec[i].second);
    }

    // for(int i = 0; i < (int)func_param_vec.size(); i++){
      
    // }
    func_param_vec.clear();

}
#line 2050 "parser.tab.c"
    break;

  case 7: /* funcdef: DEF NAME parameters COLON $@1 func_body_suite  */
#line 565 "parser.y"
                     {
  ((yyval.type_attr)).linenum = ((yyvsp[-5].token_attr)).linenum;
  // entry needed 
  // table new - func_body_suite
  //  main() and __init__() will be here
 //// should check return type 

  // if(isreturnin none.c_str());
  string functype = "None";
  if(to_string(((yyvsp[-4].token_attr)).token_lex) == "__init__"){
    functype = recent_class;
  }
  strcpy(((yyval.type_attr)).type, functype.c_str());


  if(isreturning == 0){
      int max_offset = 0;
      string max_type = "";
      for(auto it = curr_table->table.begin(); it != curr_table->table.end(); it++){
        if(it->second.offset >= max_offset){
          max_offset = it->second.offset;
          max_type = it->second.type;
        }
      }
      int last_size = type_size(max_type);
      int func_size = max_offset + last_size;
      gen("add %rsp " + to_string(func_size));
      gen("pop %rbp");
      gen("ret");
  }

  curr_table = table_stack.top(); 
  table_stack.pop();
  curr_scope = scope_stack.top(); 
  scope_stack.pop();
  offset = offset_stack.top(); 
  offset_stack.pop();
  isreturning = 0;
  func_return_type = "";
  gen("endfunc");
  add_offset = 0;
}
#line 2097 "parser.tab.c"
    break;

  case 8: /* $@2: %empty  */
#line 607 "parser.y"
                                       {
  if(recent_class == ""){
    gen(to_string(((yyvsp[-4].token_attr)).token_lex) + ":");
  }
  else{
    gen(recent_class + "." + to_string(((yyvsp[-4].token_attr)).token_lex) + ":");
  }
  gen("beginfunc");
  gen("push %rbp");
  gen("%rbp = %rsp");
  // for(int i = 0; i < (int)func_param_vec.size(); i++){
  //     string temp_ = t_new();
  //     gen(temp_ + " = popparam");
  //     gen(func_param_vec[i].first + " = " + temp_);
  // }
string functype = to_string(((yyvsp[-1].type_attr)).lexeme);
// strcpy(($$).lexeme, ($5).lexeme); //this is return type
func_return_type = to_string(((yyvsp[-1].type_attr)).lexeme);
// ($$).func_numargs = ($3).func_numargs;
// int n_arg = ($3).func_numargs;
Symbol_Table_Entry* func_entry = curr_table->make_entry(to_string(((yyvsp[-4].token_attr)).token_lex), "Function", to_string(((yyvsp[-1].type_attr)).lexeme), offset, curr_scope, ((yyvsp[-5].token_attr)).linenum, -1, -1, ((yyvsp[-3].type_attr)).func_numargs, 1);
offset += 0;
table_stack.push(curr_table);
curr_table = new Symbol_Table(curr_table);
func_entry->update_entry(curr_table);
vec_tables.push_back(curr_table);
scope_stack.push(curr_scope);
offset_stack.push(offset);
if(recent_class == "")
curr_scope = "Function@" + to_string(((yyvsp[-4].token_attr)).token_lex);
else
curr_scope = "Function@" + to_string(((yyvsp[-4].token_attr)).token_lex) + "." + recent_class;
int new_offset = 0;
offset = new_offset;

for(int i = 0; i< (int)(int)func_param_vec.size(); i++){
  curr_table->make_entry(func_param_vec[i].first, "Function_Parameter", func_param_vec[i].second, offset, curr_scope, ((yyvsp[-5].token_attr)).linenum, i+1, -1, ((yyvsp[-3].type_attr)).func_numargs, 1);
  // string temp_ = t_new();
  string rbp_offset = to_string(offset + 16);
  gen(func_param_vec[i].first + " = " + rbp_offset + "(%rbp)");
  gen("sub %rsp " + to_string(type_size(func_param_vec[i].second)));
  gen(to_string(-(offset + type_size(func_param_vec[i].second))) + "(%rbp) = " + func_param_vec[i].first);
  // gen(func_param_vec[i].first + " = " + temp_);
  offset+= type_size(func_param_vec[i].second);
}
func_param_vec.clear();

}
#line 2150 "parser.tab.c"
    break;

  case 9: /* funcdef: DEF NAME parameters ARROW test COLON $@2 func_body_suite  */
#line 657 "parser.y"
                     {
  ((yyval.type_attr)).linenum = ((yyvsp[-7].token_attr)).linenum;
  // make_entry needed - test is return type
  // table new - func_body_suite
  string functype = to_string(((yyvsp[-3].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, functype.c_str());
  if(isreturning == 0 && func_return_type!="None"){
    cerr << ((yyvsp[-7].token_attr)).linenum << ": Error: wrong return type 'None', expected return type '"<< func_return_type <<"'\n";
    exit(0);
  }
  if(isreturning == 0){
      int max_offset = 0;
      string max_type = "";
      for(auto it = curr_table->table.begin(); it != curr_table->table.end(); it++){
        if(it->second.offset >= max_offset){
          max_offset = it->second.offset;
          max_type = it->second.type;
        }
      }
      int last_size = type_size(max_type);
      int func_size = max_offset + last_size;
      gen("add %rsp " + to_string(func_size));
      gen("pop %rbp");
      gen("ret");
  }
  curr_table = table_stack.top(); 
  table_stack.pop();
  curr_scope = scope_stack.top(); 
  scope_stack.pop();
  offset = offset_stack.top(); 
  offset_stack.pop();
  isreturning = 0;
  func_return_type = "";
  gen("endfunc");
  add_offset = 0;


}
#line 2193 "parser.tab.c"
    break;

  case 10: /* parameters: OPEN_ROUND_BRACKET CLOSE_ROUND_BRACKET  */
#line 697 "parser.y"
                                            {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].token_attr)).linenum;
  ((yyval.type_attr)).func_numargs = 0;
  // function defn args are here 
  // params are in symbol table of function with argnum
}
#line 2204 "parser.tab.c"
    break;

  case 11: /* parameters: OPEN_ROUND_BRACKET typedargslist CLOSE_ROUND_BRACKET  */
#line 703 "parser.y"
                                                            {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  ((yyval.type_attr)).func_numargs = ((yyvsp[-1].type_attr)).func_numargs;
  // function defn args are here 
  // params are in symbol table of function with argnum
}
#line 2215 "parser.tab.c"
    break;

  case 12: /* typedargslist: tfpdef Multi_tfpdef  */
#line 711 "parser.y"
                          {
   ((yyval.type_attr)).func_numargs = 1 + ((yyvsp[0].type_attr)).func_numargs;

}
#line 2224 "parser.tab.c"
    break;

  case 13: /* Multi_tfpdef: %empty  */
#line 718 "parser.y"
                   {
  ((yyval.type_attr)).func_numargs = 0;
}
#line 2232 "parser.tab.c"
    break;

  case 14: /* Multi_tfpdef: COMMA tfpdef Multi_tfpdef  */
#line 721 "parser.y"
                                 {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  ((yyval.type_attr)).func_numargs = 1 + ((yyvsp[0].type_attr)).func_numargs;
}
#line 2241 "parser.tab.c"
    break;

  case 15: /* tfpdef: NAME COLON test  */
#line 727 "parser.y"
                    {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  func_param_vec.push_back({to_string(((yyvsp[-2].token_attr)).token_lex), to_string(((yyvsp[0].type_attr)).lexeme)});
  // these are function definition arguments names. should they have an make_entry in symbol table?
  // enter this in function symbol table
}
#line 2252 "parser.tab.c"
    break;

  case 16: /* tfpdef: NAME  */
#line 733 "parser.y"
       {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  if(to_string(((yyvsp[0].token_attr)).token_lex) != "self"){
    cerr << ((yyvsp[0].token_attr)).linenum << ": Error: type hint for parameter '" << to_string(((yyvsp[0].token_attr)).token_lex) << "' not given" << "\n";
    exit(0);
  }
  func_param_vec.push_back({to_string(((yyvsp[0].token_attr)).token_lex), recent_class});

}
#line 2266 "parser.tab.c"
    break;

  case 17: /* stmt: simple_stmt  */
#line 745 "parser.y"
                 {
  
}
#line 2274 "parser.tab.c"
    break;

  case 18: /* stmt: compound_stmt  */
#line 748 "parser.y"
                     {
  
}
#line 2282 "parser.tab.c"
    break;

  case 19: /* simple_stmt: small_stmt Multi_small_stmt NEWLINE  */
#line 753 "parser.y"
                                         {
  
}
#line 2290 "parser.tab.c"
    break;

  case 20: /* Multi_small_stmt: %empty  */
#line 758 "parser.y"
                   {
  
}
#line 2298 "parser.tab.c"
    break;

  case 21: /* Multi_small_stmt: SEMICOLON small_stmt Multi_small_stmt  */
#line 761 "parser.y"
                                             {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  
}
#line 2307 "parser.tab.c"
    break;

  case 22: /* small_stmt: expr_stmt  */
#line 767 "parser.y"
               {
  
}
#line 2315 "parser.tab.c"
    break;

  case 23: /* small_stmt: flow_stmt  */
#line 770 "parser.y"
                 {
  
}
#line 2323 "parser.tab.c"
    break;

  case 24: /* small_stmt: global_stmt  */
#line 773 "parser.y"
                   {
  
}
#line 2331 "parser.tab.c"
    break;

  case 25: /* expr_stmt: Lhs_init COLON test EQUAL test  */
#line 784 "parser.y"
                                  {
  ((yyval.type_attr)).linenum = ((yyvsp[-4].type_attr)).linenum;


  string type1 = to_string(((yyvsp[-2].type_attr)).lexeme);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-4].type_attr)).type);
  }
  else{
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to float
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-4].type_attr)).linenum << ": Error: invalid assignment for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }




  
  if(to_string(((yyvsp[-4].type_attr)).lexeme).substr(0,5) == "self."){
    if(curr_scope == "Global"){
      cerr << ((yyvsp[-4].type_attr)).linenum << ": Error : 'self' is a restricted word, please use another variable name" << "\n";
      exit(0);
    }
    table_stack.top()->make_entry(to_string(((yyvsp[-4].type_attr)).lexeme), "Class_Attribute", to_string(((yyvsp[-2].type_attr)).lexeme), offset_stack.top(), scope_stack.top(), ((yyvsp[-4].type_attr)).linenum, -1, type_size(to_string(((yyvsp[-2].type_attr)).lexeme)), ((yyval.type_attr)).func_numargs, 1);
    int top_offset = offset_stack.top();
    offset_stack.pop();
    top_offset += type_size(to_string(((yyvsp[-2].type_attr)).lexeme));
    add_offset += type_size(to_string(((yyvsp[-2].type_attr)).lexeme));
    offset_stack.push(top_offset);
  }

  else{
      Symbol_Table_Entry *entry = curr_table->make_entry(to_string(((yyvsp[-4].type_attr)).lexeme), "Variable", to_string(((yyvsp[-2].type_attr)).lexeme), offset, curr_scope, ((yyvsp[-4].type_attr)).linenum, -1, type_size(to_string(((yyvsp[-2].type_attr)).lexeme)), ((yyval.type_attr)).func_numargs, 1);
      (entry->update_listlen(((yyvsp[0].type_attr)).listsize));
      offset += type_size(to_string(((yyvsp[-2].type_attr)).lexeme));
  }

  size_t pos_dot = to_string(((yyval.type_attr)).lexeme).find(".");
  if (pos_dot != string::npos){
    string attribute = to_string(((yyval.type_attr)).lexeme).substr(5);
    Symbol_Table *class_table = class_symbol_tables[recent_class];
    string offset_ = to_string(class_table->lookup("self."+attribute).offset);
    gen("*(self + " + offset_ + ") = " + to_string(((yyvsp[0].type_attr)).temp));
    // gen("sub %rsp " + to_string(type_size(($3).lexeme)));
    // gen(to_string(-(offset + add_offset)) + "(%rbp) = " + "*(self + " + offset_ + ")");
  }
  else{
    strcpy(((yyvsp[-4].type_attr)).type, ((yyvsp[-2].type_attr)).lexeme);
    gen(to_string(((yyvsp[-4].type_attr)).temp) + " = " + to_string(((yyvsp[0].type_attr)).temp));
    gen("sub %rsp " + to_string(type_size(((yyvsp[-2].type_attr)).lexeme)));
    gen(to_string(-(offset)) + "(%rbp) = " + to_string(((yyvsp[-4].type_attr)).temp));
  }

//  ($$)
  


}
#line 2426 "parser.tab.c"
    break;

  case 26: /* expr_stmt: Lhs_init COLON test  */
#line 874 "parser.y"
                              {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  // $1 is variable name
  // $3 also 
  
  if(to_string(((yyvsp[-2].type_attr)).lexeme).substr(0,5) == "self."){
    if(curr_scope == "Global"){
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error : 'self' is a restricted word, please use another variable name" << "\n";
      exit(0);
    }
    table_stack.top()->make_entry(to_string(((yyvsp[-2].type_attr)).lexeme), "Variable", to_string(((yyvsp[0].type_attr)).lexeme), offset_stack.top(), curr_scope, ((yyvsp[-2].type_attr)).linenum, -1, type_size(to_string(((yyvsp[0].type_attr)).lexeme)), ((yyval.type_attr)).func_numargs, 0);
    int top_offset = offset_stack.top();
    offset_stack.pop();
    top_offset += type_size(to_string(((yyvsp[0].type_attr)).lexeme));
    add_offset += type_size(to_string(((yyvsp[0].type_attr)).lexeme));
    offset_stack.push(top_offset);
  }
  
  else{
      curr_table->make_entry(to_string(((yyvsp[-2].type_attr)).lexeme), "Variable", to_string(((yyvsp[0].type_attr)).lexeme), offset, curr_scope, ((yyvsp[-2].type_attr)).linenum, -1, type_size(to_string(((yyvsp[0].type_attr)).lexeme)), ((yyval.type_attr)).func_numargs, 0);
      offset += type_size(to_string(((yyvsp[0].type_attr)).lexeme));

  }  

   strcpy(((yyvsp[-2].type_attr)).type, ((yyvsp[0].type_attr)).lexeme);
}
#line 2457 "parser.tab.c"
    break;

  case 27: /* expr_stmt: NAME OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET  */
#line 901 "parser.y"
                                                         {
  ((yyval.type_attr)).linenum = ((yyvsp[-3].token_attr)).linenum;
 // None function call
  auto it = all_types.find(to_string(((yyvsp[-3].token_attr)).token_lex));
  if (it == all_types.end()){
      if(curr_table->lookup(to_string(((yyvsp[-3].token_attr)).token_lex)).token == "null"){
          if (to_string(((yyvsp[-3].token_attr)).token_lex) == "print"){
            if(func_arg_vec.size()!=1){
                cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'print' function, expected 1 argument" << endl;
                exit(0);
            }
            string none = "None";
            strcpy(((yyval.type_attr)).type, none.c_str());
            for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
              gen("pushparam " + func_arg_temp_vec[i].second);
            }
            gen("push ret_addr");
            gen("sub %rsp 8");
            gen("call print 1");
            gen("add %rsp 8");
                


          }
          else if (to_string(((yyvsp[-3].token_attr)).token_lex) == "len"){
            string int_ = "int";
            strcpy(((yyval.type_attr)).type, int_.c_str());
            if(func_arg_vec.size()!=1){
                cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'len' function, expected 1 argument" << endl;
                exit(0);
            }
            if(func_arg_vec[0].second.size() > 5){
                if(func_arg_vec[0].second.substr(0,5) != "list@"){
                  cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
                  exit(0);
                }
            }
            else{
                  cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
                  exit(0);
            }
            
          }
          else if (to_string(((yyvsp[-3].token_attr)).token_lex) == "range"){
              string none = "None";
                strcpy(((yyval.type_attr)).type, none.c_str());
              if(func_arg_vec.size() > 2 || func_arg_vec.size() < 1){
                cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'range' function, expected 1 or 2 arguments" << endl;
                exit(0);
              }
              else if (func_arg_vec.size() == 2){
                if(func_arg_vec[0].second != "int"){
                  cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                }
                if(func_arg_vec[1].second != "int"){
                  cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                }
                range_start = func_arg_temp_vec[0].second;
                range_end = func_arg_temp_vec[1].second;
              }
              else if( func_arg_vec.size() == 1){
                if(func_arg_vec[0].second != "int"){
                  cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                }
                string temp_ = t_new();
                gen(temp_ + " = 0");
                range_start = temp_;
                range_end = func_arg_temp_vec[0].second;
              }
          }
          else{
            cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: undeclared function '" << to_string(((yyvsp[-3].token_attr)).token_lex) << "' called\n";
            exit(0);
          }
        
      }
      else if (curr_table->lookup(to_string(((yyvsp[-3].token_attr)).token_lex)).token != "Function"){
        cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: undeclared function '" << to_string(((yyvsp[-3].token_attr)).token_lex) << "' called\n";
            exit(0);
      }
      else{
        /// funccall is valid 
        // now check for arguments
        Symbol_Table_Entry func_defn = curr_table->lookup(to_string(((yyvsp[-3].token_attr)).token_lex));
        Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
        int num_args = func_defn.numargs;
        int func_params_size = 0;
        for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
          // num_args = (it->second).numargs;
          if((long unsigned int)num_args != func_arg_vec.size()){
            // number of args and param dont match 
            cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(((yyvsp[-3].token_attr)).token_lex) << "' function, expected " << num_args << " argument(s)" << endl;
            exit(0);
          }
          if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
            if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
              if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                // types are not same, typecast arg to param type

                if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                  string newt = t_new();
                  gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                  func_arg_temp_vec[(it->second).argnum -1].second = newt;
                }
              }
              func_params_size += type_size((it->second).type);
            }
            else{
              // types dont match even after typecasting
              cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ((yyvsp[-3].token_attr)).linenum << "\n";
              exit(0); // adapter

            }
          }

        }
        for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
          gen("pushparam " + func_arg_temp_vec[i].second);
        }
        gen("push ret_addr");
        gen("sub %rsp " + to_string(func_params_size));
        gen("call " + to_string(((yyvsp[-3].token_attr)).token_lex) + " " + to_string(func_arg_vec.size()));
        gen("add %rsp " + to_string(func_params_size));

      } 

  }

    if (class_symbol_tables.find(to_string(((yyval.type_attr)).lexeme)) != class_symbol_tables.end()) {
      string class_name = to_string(((yyval.type_attr)).lexeme);
      // if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
      //     ": Error: Undeclared function call " << class_name << " at line " << ($1).linenum << "\n";
      //     exit(0);
      // }
      Symbol_Table *class_table = class_symbol_tables[class_name];
      Symbol_Table_Entry func_defn = class_table->lookup("__init__");
      Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
      int num_args;
      func_arg_vec.insert(func_arg_vec.begin(), make_pair("random_string", class_name));
      for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
        num_args = (it->second).numargs;
        if((long unsigned int)num_args != func_arg_vec.size()){
          // number of args and param dont match 
          cerr << ((yyvsp[-3].token_attr)).linenum << "Error : Number of constructor call arguments do not match number of constructor parameters of class " << class_name << " at line " << ((yyvsp[-3].token_attr)).linenum << "\n";
          exit(0); // adapter
        }
        if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
          if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
            if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
              // types are not same, typecast arg to param type
              if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                string newt = t_new();
                gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                func_arg_temp_vec[(it->second).argnum -2].second = newt;
              }
            }
          }
          else{
            // types dont match even after typecasting
          cerr << ((yyvsp[-3].token_attr)).linenum << "Error : Types of constructor call arguments do not match types of constructor parameters of class " << class_name << " at line " << ((yyvsp[-3].token_attr)).linenum << "\n";
            exit(0); // adapter

          }
        }
      }

    }


  func_arg_vec.clear();
  func_arg_temp_vec.clear();

 
}
#line 2639 "parser.tab.c"
    break;

  case 28: /* expr_stmt: NAME DOT NAME OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET  */
#line 1078 "parser.y"
                                                                  {
  ((yyval.type_attr)).linenum = ((yyvsp[-5].token_attr)).linenum;
// None method call
  string object_name = to_string(((yyvsp[-5].token_attr)).token_lex);
  if(curr_table->lookup(object_name).token == "null"){
      cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: undeclared object '" << object_name << "'\n";
      exit(0);
  }

  
  else{
    /////// the name before dot is class name
      if((curr_table->lookup(object_name)).token == "Class"){
        string class_name = object_name;
        Symbol_Table *class_table = class_symbol_tables[class_name];
        string attribute = to_string(((yyvsp[-3].token_attr)).token_lex);
        if(class_table->lookup(attribute).token == "null"){
          cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
          exit(0);
        }
        else if (class_table->lookup(attribute).token != "Function"){
          cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: undeclared method " << attribute << " in class called" << class_name << "\n";
          exit(0);
        }

        else{

            Symbol_Table_Entry func_defn = class_table->lookup(attribute);
            Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
            int num_args = func_defn.numargs;
            int func_params_size = 0;
            for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
              // num_args = (it->second).numargs;
              if((long unsigned int)num_args != func_arg_vec.size()){
                // number of args and param dont match 
                cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(((yyvsp[-3].token_attr)).token_lex) << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                exit(0);
              }
              if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                  if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                    // types are not same, typecast arg to param type
                    if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                      string newt = t_new();
                      gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                      func_arg_temp_vec[(it->second).argnum -1].second = newt;
                    }
                  }
                  func_params_size += type_size((it->second).type);
                }
                else{
                  // types dont match even after typecasting
                  cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: Types of method call arguments do not match types of method parameters at line " << ((yyvsp[-5].token_attr)).linenum << "\n";
                  exit(0); // adapter

                }
              }
            }

            strcpy(((yyval.type_attr)).type, func_defn.type.c_str());
            for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
              gen("pushparam " + func_arg_temp_vec[i].second);
            }
            gen("push ret_addr");
            gen("sub %rsp " + to_string(func_params_size));
            gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
            gen("add %rsp " + to_string(func_params_size));

            if(func_defn.type != "None"){
                string temp_result = t_new();
                gen(temp_result + " = %rax");
                strcpy(((yyval.type_attr)).temp, temp_result.c_str());
            }

        }

      }

      /////// the name before dot is object name
      else{
        string class_name = (curr_table->lookup(object_name)).type; 
        if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
            cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
            exit(0);
        }
        Symbol_Table *class_table = class_symbol_tables[class_name];
        string attribute = to_string(((yyvsp[-3].token_attr)).token_lex);
    
        if(class_table->lookup(attribute).token == "null"){
          cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
          exit(0);
        }
        else if (class_table->lookup(attribute).token != "Function"){
          cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
          exit(0);
        }
        else{
          // Method call from object is valid 
            func_arg_vec.insert(func_arg_vec.begin(), make_pair(object_name, class_name));
            Symbol_Table_Entry func_defn = class_table->lookup(attribute);
            Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
            int num_args = func_defn.numargs;
            int func_params_size = 0;
            for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
              // num_args = (it->second).numargs;
              if((long unsigned int)num_args != func_arg_vec.size()){
                // number of args and param dont match 
                cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(((yyvsp[-3].token_attr)).token_lex) << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                exit(0); 
              }
              if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                  if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                    // types are not same, typecast arg to param type
                    if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                      string newt = t_new();
                      gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                      func_arg_temp_vec[(it->second).argnum -2].second = newt;
                    }
                  }
                  func_params_size += type_size((it->second).type);
                }
                else{
                  // types dont match even after typecasting
                  cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: Types of method call arguments do not match types of method parameters at line " << ((yyvsp[-5].token_attr)).linenum << "\n";
                  exit(0); // adapter

                }
              }
            }

            
            for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
              gen("pushparam " + func_arg_temp_vec[i].second);
            }
            gen("pushparam " +  object_name);
            gen("push ret_addr");
            gen("sub %rsp " + to_string(func_params_size));
            gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
            gen("add %rsp " + to_string(func_params_size));

            if(func_defn.type != "None"){
                string temp_result = t_new();
                gen(temp_result + " = %rax");
                strcpy(((yyval.type_attr)).temp, temp_result.c_str());
            }

        }
              
            
      }
            






    }
func_arg_vec.clear();
func_arg_temp_vec.clear();

}
#line 2807 "parser.tab.c"
    break;

  case 29: /* expr_stmt: atom  */
#line 1242 "parser.y"
       {
// dont do anythign here
}
#line 2815 "parser.tab.c"
    break;

  case 30: /* expr_stmt: Lhs_noninit EQUAL test  */
#line 1246 "parser.y"
                        {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  // type checking needed
  // $1 is variable name
  // if(curr_table->lookup(to_string(($1).lexeme)).token == "null"){
  //     exit(0);
  // }
  // else{
    curr_table->modify_lookup(to_string(((yyvsp[-2].type_attr)).lexeme), 1);
    // curr_table->lookup(to_string(($1).lexeme)).isinit = 1;
  // }
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
  }
  else{
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to float
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid assignment for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }

  if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){

    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + to_string(((yyvsp[0].type_attr)).temp));
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + to_string(((yyvsp[0].type_attr)).temp));
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") ");
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + to_string(((yyvsp[0].type_attr)).temp));
  }

else{
    gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + to_string(((yyvsp[0].type_attr)).temp));
    gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));
}
  

  
  

}
#line 2896 "parser.tab.c"
    break;

  case 31: /* expr_stmt: Lhs_noninit PLUS_EQUAL test  */
#line 1322 "parser.y"
                             {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
    // type checking needed
    // $1 is variable name

    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

// D = t23
// 	t24 = 1
// 	t25 = *(D + 0) + t24
// 	*(D + 0) = t25
    

  if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " + " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " + " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " + " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " + " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }



    

}
#line 2998 "parser.tab.c"
    break;

  case 32: /* expr_stmt: Lhs_noninit MINUS_EQUAL test  */
#line 1419 "parser.y"
                              {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  
    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

      if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " - " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " - " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " - " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " - " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

}
#line 3089 "parser.tab.c"
    break;

  case 33: /* expr_stmt: Lhs_noninit STAR_EQUAL test  */
#line 1505 "parser.y"
                             {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;

    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

      if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " * " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " * " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " * " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " * " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }
  
    

}
#line 3182 "parser.tab.c"
    break;

  case 34: /* expr_stmt: Lhs_noninit SLASH_EQUAL test  */
#line 1593 "parser.y"
                              {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;

    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

      if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " / " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " / " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " / " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " / " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }
  
    

}
#line 3275 "parser.tab.c"
    break;

  case 35: /* expr_stmt: Lhs_noninit PERCENTAGE_EQUAL test  */
#line 1681 "parser.y"
                                   {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;

    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

          if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " % " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " % " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " % " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " % " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }
  
    

}
#line 3368 "parser.tab.c"
    break;

  case 36: /* expr_stmt: Lhs_noninit AND_EQUAL test  */
#line 1769 "parser.y"
                            {
((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

        if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " & " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " & " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " & " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " & " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }
    

}
#line 3451 "parser.tab.c"
    break;

  case 37: /* expr_stmt: Lhs_noninit OR_EQUAL test  */
#line 1847 "parser.y"
                           {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

        if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " | " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " | " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " | " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " | " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

}
#line 3533 "parser.tab.c"
    break;

  case 38: /* expr_stmt: Lhs_noninit XOR_EQUAL test  */
#line 1924 "parser.y"
                            {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ^ " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ^ " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ^ " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " ^ " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

}
#line 3615 "parser.tab.c"
    break;

  case 39: /* expr_stmt: Lhs_noninit LEFT_SHIFT_EQUAL test  */
#line 2001 "parser.y"
                                   {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }

  if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " << " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " << " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " << " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " << " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

}
#line 3697 "parser.tab.c"
    break;

  case 40: /* expr_stmt: Lhs_noninit RIGHT_SHIFT_EQUAL test  */
#line 2078 "parser.y"
                                    {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }

  if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " >> " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " >> " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " >> " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " >> " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

}
#line 3779 "parser.tab.c"
    break;

  case 41: /* expr_stmt: Lhs_noninit DOUBLE_STAR_EQUAL test  */
#line 2155 "parser.y"
                                    {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ** " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ** " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ** " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " ** " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

}
#line 3869 "parser.tab.c"
    break;

  case 42: /* expr_stmt: Lhs_noninit DOUBLE_SLASH_EQUAL test  */
#line 2240 "parser.y"
                                     {
((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    if(((yyvsp[-2].type_attr)).isindexed && !((yyvsp[-2].type_attr)).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " // " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).listhead) + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }
  else if(((yyvsp[-2].type_attr)).isdotted && !((yyvsp[-2].type_attr)).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " // " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ") = " + nt1);
  }
  else if (((yyvsp[-2].type_attr)).isindexed && ((yyvsp[-2].type_attr)).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(((yyvsp[-2].type_attr)).objhead) + " + " + to_string(((yyvsp[-2].type_attr)).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " // " + to_string(((yyvsp[0].type_attr)).temp));
    gen("*(" + temp_ + " + " + to_string(((yyvsp[-2].type_attr)).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " // " + to_string(((yyvsp[0].type_attr)).temp));
      gen(to_string(((yyvsp[-2].type_attr)).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).offset + type_size(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type))) + "(%rbp) = " + to_string(((yyvsp[-2].type_attr)).temp));

      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }
    

}
#line 3960 "parser.tab.c"
    break;

  case 43: /* Lhs_init: NAME  */
#line 2333 "parser.y"
     {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].token_attr)).token_lex);
  strcpy(((yyval.type_attr)).temp, ((yyvsp[0].token_attr)).token_lex);
}
#line 3970 "parser.tab.c"
    break;

  case 44: /* Lhs_init: NAME DOT NAME  */
#line 2338 "parser.y"
                {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  if(to_string(((yyvsp[-2].token_attr)).token_lex) != "self"){
    cerr << ((yyvsp[-2].token_attr)).linenum << ": Error: attribute reinitialization of object '" << to_string(((yyvsp[-2].token_attr)).token_lex) << "' not allowed" << "\n";
    exit(0);
  }

 string self_dot = "self.";
 strcpy(((yyval.type_attr)).lexeme, self_dot.c_str());
 strcat(((yyval.type_attr)).lexeme, ((yyvsp[0].token_attr)).token_lex);

  if(curr_scope.size() < 17){
    cerr << ((yyvsp[-2].token_attr)).linenum << ": Error : initialization of self attribute not allowed in non-constructor / non-init method \n";
  exit(0);
  }
 if(curr_scope.size() >= 17 && curr_scope.substr(0,17) != "Function@__init__"){
  cerr << ((yyvsp[-2].token_attr)).linenum << ": Error : initialization of self attribute not allowed in non-constructor / non-init method \n";
  exit(0);
 }

}
#line 3996 "parser.tab.c"
    break;

  case 45: /* Lhs_noninit: NAME  */
#line 2361 "parser.y"
    {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  if(curr_table->lookup(to_string(((yyvsp[0].token_attr)).token_lex)).token == "null" || curr_table->lookup(to_string(((yyvsp[0].token_attr)).token_lex)).token == "Function" ){
      cerr << ((yyvsp[0].token_attr)).linenum << ": Error: undeclared variable '" << to_string(((yyvsp[0].token_attr)).token_lex) << "'\n";
      exit(0);
  }
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].token_attr)).token_lex);
  string name_type = curr_table->lookup(to_string(((yyvsp[0].token_attr)).token_lex)).type;
  strcpy(((yyval.type_attr)).type, name_type.c_str());
  strcpy(((yyval.type_attr)).temp, ((yyvsp[0].token_attr)).token_lex);
  // strcpy(($$).type, ($1).token_type);
}
#line 4013 "parser.tab.c"
    break;

  case 46: /* Lhs_noninit: NAME DOT NAME  */
#line 2373 "parser.y"
                {
((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
// this entire type???

  string object_name = to_string(((yyvsp[-2].token_attr)).token_lex);

  
  if(curr_table->lookup(object_name).token == "null" || curr_table->lookup(to_string(((yyvsp[-2].token_attr)).token_lex)).token == "Function" || curr_table->lookup(to_string(((yyvsp[-2].token_attr)).token_lex)).token == "Class"){
      cerr << ((yyvsp[-2].token_attr)).linenum << ": Error: undeclared object '" << object_name << "'\n";
      exit(0);
  }
  else{
    string class_name = (curr_table->lookup(object_name)).type;
    if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
        cerr << ((yyvsp[-2].token_attr)).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
        exit(0);
    }
    Symbol_Table *class_table = class_symbol_tables[class_name];
    string attribute = to_string(((yyvsp[0].token_attr)).token_lex);
    if(class_table->lookup("self."+attribute).token == "null"){
      cerr << ((yyvsp[-2].token_attr)).linenum << ": Error: undeclared attribute '" << attribute << "' in class '" << class_name << "'\n";
      exit(0);
    }
    else {
      string attribute_type = class_table->lookup("self."+attribute).type;
      strcpy(((yyval.type_attr)).type, attribute_type.c_str());
      string offset_ = to_string(class_table->lookup("self."+attribute).offset);
      strcpy(((yyval.type_attr)).objoffset, offset_.c_str());
      strcpy(((yyval.type_attr)).objhead, ((yyvsp[-2].token_attr)).token_lex);
      ((yyval.type_attr)).isdotted = 1;
    }
    strcpy(((yyval.type_attr)).lexeme, ((yyvsp[-2].token_attr)).token_lex);
    string dot = ".";
    strcat(((yyval.type_attr)).lexeme, dot.c_str());
    strcat(((yyval.type_attr)).lexeme, ((yyvsp[0].token_attr)).token_lex);


  }

  
  
}
#line 4060 "parser.tab.c"
    break;

  case 47: /* Lhs_noninit: NAME OPEN_SQUARE_BRACKET test CLOSE_SQUARE_BRACKET  */
#line 2416 "parser.y"
                                                     {
((yyval.type_attr)).linenum = ((yyvsp[-3].token_attr)).linenum;
// check for test type if its int
if(to_string(((yyvsp[-1].type_attr)).type) != "int"){
  cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: index is not integer type\n";
  exit(0);
}

//checking if its list type
if(curr_table->lookup(to_string(((yyvsp[-3].token_attr)).token_lex)).token != "null"){
    string name1_type = curr_table->lookup(to_string(((yyvsp[-3].token_attr)).token_lex)).type;
    if(name1_type.substr(0,5) != "list@"){
      cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: '" << to_string(((yyvsp[-3].token_attr)).token_lex) << "' is not a list, cannot be indexed " << endl;
      exit(0);
    }
    string list_type = name1_type;
    if(list_type.size() > 5){
      string without_list_type = list_type.substr(5);
      strcpy(((yyval.type_attr)).type, without_list_type.c_str());
    }
}
else{
   cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: undeclared variable '" << to_string(((yyvsp[-3].token_attr)).token_lex) << "'" << endl;
    exit(0);
}

// int index = atoi(($3).temp);
int typesize = type_size(to_string(((yyval.type_attr)).type));
// int list_offset = index*typesize;
((yyval.type_attr)).isindexed = 1;
strcpy(((yyval.type_attr)).listhead, ((yyvsp[-3].token_attr)).token_lex);
string temp_ = t_new();
strcpy(((yyval.type_attr)).listoffsettemp, temp_.c_str());
gen(temp_ + " = " + to_string(((yyvsp[-1].type_attr)).temp) + " * " + to_string(typesize));
// string temp1 = t_new();
// strcpy(($$).temp, temp1.c_str());
// gen("*(" + to_string(($1).token_lex) + " + " + temp_ + ") = " + temp1);

// important: Checking if index is in range



}
#line 4108 "parser.tab.c"
    break;

  case 48: /* Lhs_noninit: NAME DOT NAME OPEN_SQUARE_BRACKET test CLOSE_SQUARE_BRACKET  */
#line 2459 "parser.y"
                                                              {
((yyval.type_attr)).linenum = ((yyvsp[-5].token_attr)).linenum;
    // string input = to_string(($$).lexeme);
    string part1 = to_string(((yyvsp[-5].token_attr)).token_lex);
    string part2 = to_string(((yyvsp[-3].token_attr)).token_lex);
    string part3 = to_string(((yyvsp[-1].type_attr)).lexeme);

    string class_name = (curr_table->lookup(part1)).type; 
    if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
        cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
        exit(0);
    }
    Symbol_Table *class_table = class_symbol_tables[class_name];
    string attribute = part2;
    if(class_table->lookup("self."+attribute).token == "null"){
      cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: undeclared attribute '" << attribute << "' in class '" << class_name << "'\n";
      exit(0);
    }


    if(to_string(((yyvsp[-1].type_attr)).type) != "int"){
      cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: index is not integer type\n";
      exit(0);
    }

    
    string name1_type = class_table->lookup("self."+attribute).type;
    if(name1_type.substr(0,5) != "list@"){
      cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: '" << part1+"."+part2 << "' is not a list, cannot be indexed " << endl;
      exit(0);
    }
    string list_type = name1_type;
    if(list_type.size() > 5){
      string without_list_type = list_type.substr(5);
      strcpy(((yyval.type_attr)).type, without_list_type.c_str());
    }

    int typesize = type_size(to_string(((yyval.type_attr)).type));
    // int list_offset = index*typesize;
    ((yyval.type_attr)).isindexed = 1;
    ((yyval.type_attr)).isdotted = 1;
    strcpy(((yyval.type_attr)).listhead, ((yyvsp[-3].token_attr)).token_lex);
    string temp_ = t_new();
    strcpy(((yyval.type_attr)).listoffsettemp, temp_.c_str());
    gen(temp_ + " = " + to_string(((yyvsp[-1].type_attr)).temp) + " * " + to_string(typesize));
    string offset_ = to_string(class_table->lookup("self."+attribute).offset);
    strcpy(((yyval.type_attr)).objoffset, offset_.c_str());
    strcpy(((yyval.type_attr)).objhead, ((yyvsp[-5].token_attr)).token_lex);
    

}
#line 4164 "parser.tab.c"
    break;

  case 49: /* flow_stmt: BREAK  */
#line 2515 "parser.y"
           {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  gen("Goto "+ breakjumps.top());
}
#line 4173 "parser.tab.c"
    break;

  case 50: /* flow_stmt: CONTINUE  */
#line 2519 "parser.y"
                {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  gen("Goto "+ continuejumps.top());
}
#line 4182 "parser.tab.c"
    break;

  case 51: /* flow_stmt: RETURN  */
#line 2523 "parser.y"
              {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;

  isreturning = 1;

  if(func_return_type != "None"){
    cerr << ((yyvsp[0].token_attr)).linenum << ": Error: wrong return type 'None', expected return type '"<< func_return_type <<"'\n";
    exit(0);
  }
// check if return type is None
// your curr_table is function table
// return type of this function is stored in parent table 
// so before making symbol table for this new function, store its return type in a global variable
// and match with it

  int max_offset = 0;
  string max_type = "";
  for(auto it = curr_table->table.begin(); it != curr_table->table.end(); it++){
    if(it->second.offset >= max_offset){
      max_offset = it->second.offset;
      max_type = it->second.type;
    }
  }
  int last_size = type_size(max_type);
  int func_size = max_offset + last_size;
  gen("add %rsp " + to_string(func_size));
  gen("pop %rbp");
  gen("ret");

}
#line 4217 "parser.tab.c"
    break;

  case 52: /* flow_stmt: RETURN test  */
#line 2553 "parser.y"
                 {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].token_attr)).linenum;
  isreturning = 1;
// check return type 
  if(match_type(func_return_type,to_string(((yyvsp[0].type_attr)).type))){
    if(func_return_type != to_string(((yyvsp[0].type_attr)).type)){
      string newt = t_new();
      gen(newt + " = cast_to_" + func_return_type + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
  }
  else{
    cerr << ((yyvsp[-1].token_attr)).linenum << ": Error: wrong return type '" << to_string(((yyvsp[0].type_attr)).type) << "', expected return type '"<< func_return_type <<"'\n";
    exit(0);
  }

  int max_offset = 0;
  string max_type = "";
  for(auto it = curr_table->table.begin(); it != curr_table->table.end(); it++){
    if(it->second.offset >= max_offset){
      max_offset = it->second.offset;
      max_type = it->second.type;
    }
  }
  int last_size = type_size(max_type);
  int func_size = max_offset + last_size;
  gen("add %rsp " + to_string(func_size));
  gen("pop %rbp");
  gen("%rax = " + to_string(((yyvsp[0].type_attr)).temp));
  gen("ret");
}
#line 4253 "parser.tab.c"
    break;

  case 53: /* Opt_test: %empty  */
#line 2586 "parser.y"
                   {
  
}
#line 4261 "parser.tab.c"
    break;

  case 54: /* Opt_test: test  */
#line 2589 "parser.y"
            {
  
}
#line 4269 "parser.tab.c"
    break;

  case 55: /* global_stmt: GLOBAL NAME Multi_name  */
#line 2594 "parser.y"
                            {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  // make_entry needed
  for(int i = 0; i <  (int) vec_tables.size(); i++){
    if(vec_tables[i]->table.find(to_string(((yyvsp[-1].token_attr)).token_lex)) != vec_tables[i]->table.end()){
      cerr << ((yyvsp[-2].token_attr)).linenum << "Error : name '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' is declared before global declaration" << endl;
      exit(0);
    }
  }
  all_global_vars[to_string(((yyvsp[-1].token_attr)).token_lex)] = 1;
}
#line 4285 "parser.tab.c"
    break;

  case 56: /* Multi_name: %empty  */
#line 2607 "parser.y"
                   {
  
}
#line 4293 "parser.tab.c"
    break;

  case 57: /* Multi_name: COMMA NAME Multi_name  */
#line 2610 "parser.y"
                             {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  for(int i = 0; i < (int) vec_tables.size(); i++){
    if(vec_tables[i]->table.find(to_string(((yyvsp[-1].token_attr)).token_lex)) != vec_tables[i]->table.end()){
      cerr << ((yyvsp[-2].token_attr)).linenum << "Error : name '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' is declared before global declaration" << endl;
      exit(0);
    }
  }
  all_global_vars[to_string(((yyvsp[-1].token_attr)).token_lex)] = 1;
}
#line 4308 "parser.tab.c"
    break;

  case 58: /* compound_stmt: if_stmt  */
#line 2622 "parser.y"
             {
   
}
#line 4316 "parser.tab.c"
    break;

  case 59: /* compound_stmt: while_stmt  */
#line 2625 "parser.y"
                  {
   
}
#line 4324 "parser.tab.c"
    break;

  case 60: /* compound_stmt: for_stmt  */
#line 2628 "parser.y"
                {
   
}
#line 4332 "parser.tab.c"
    break;

  case 61: /* compound_stmt: funcdef  */
#line 2631 "parser.y"
               {
  
}
#line 4340 "parser.tab.c"
    break;

  case 62: /* compound_stmt: classdef  */
#line 2634 "parser.y"
                {
  
}
#line 4348 "parser.tab.c"
    break;

  case 63: /* if_stmt: dummy_if_suit Multi_elif Opt_else  */
#line 2640 "parser.y"
                                       {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  while(!if_scopes.empty() && if_scopes.top() != "delimiter"){
    if(if_scopes.top() != "\0"){
      gen(if_scopes.top() + ":");
    }
    if_scopes.pop();
  }
  
  if_scopes.pop();
  gen(to_string(((yyvsp[-2].type_attr)).gotoname) + ":");
  
}
#line 4366 "parser.tab.c"
    break;

  case 64: /* dummy_if_suit: dummyifstmt suite  */
#line 2655 "parser.y"
                  {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].type_attr)).linenum;
  string next_state = L_new();
  gen("Goto " + next_state);
  if_scopes.push("delimiter");
  strcpy(((yyval.type_attr)).gotoname, next_state.c_str());
  gen(to_string(((yyvsp[-1].type_attr)).gotoname) + ":");
}
#line 4379 "parser.tab.c"
    break;

  case 65: /* dummyifstmt: IF test COLON  */
#line 2666 "parser.y"
                      {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  // if_scopes.push(curr_if_scope);
  string next_state = L_new();
  gen("Ifz " + to_string(((yyvsp[-1].type_attr)).temp) + " Goto " + next_state);
  strcpy(((yyval.type_attr)).gotoname,next_state.c_str());
}
#line 4391 "parser.tab.c"
    break;

  case 66: /* Multi_elif: %empty  */
#line 2675 "parser.y"
                   {
  
}
#line 4399 "parser.tab.c"
    break;

  case 67: /* $@3: %empty  */
#line 2678 "parser.y"
                      {
  
  string next_state = L_new();
  gen("Goto " + next_state);
  if_scopes.push(next_state);
  gen(to_string(((yyvsp[-1].type_attr)).gotoname) + ":");
}
#line 4411 "parser.tab.c"
    break;

  case 68: /* Multi_elif: dummyelifstmt suite $@3 Multi_elif  */
#line 2685 "parser.y"
                {
((yyval.type_attr)).linenum = ((yyvsp[-3].type_attr)).linenum;
}
#line 4419 "parser.tab.c"
    break;

  case 69: /* dummyelifstmt: ELIF test COLON  */
#line 2690 "parser.y"
                    {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  string next_state = L_new();
  gen("Ifz " + to_string(((yyvsp[-1].type_attr)).temp) + " Goto " + next_state);
  strcpy(((yyval.type_attr)).gotoname,next_state.c_str());
}
#line 4430 "parser.tab.c"
    break;

  case 70: /* Opt_else: %empty  */
#line 2700 "parser.y"
                   {
  
}
#line 4438 "parser.tab.c"
    break;

  case 71: /* Opt_else: ELSE COLON suite  */
#line 2703 "parser.y"
                        {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
    // same scope, so no new symbol table 

}
#line 4448 "parser.tab.c"
    break;

  case 72: /* dummyWhilestmt: WHILE  */
#line 2735 "parser.y"
     {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  string loop_start = L_new();
  gen(loop_start + ":");
  strcpy(((yyval.type_attr)).gotoname,loop_start.c_str());
  continuejumps.push(loop_start);
}
#line 4460 "parser.tab.c"
    break;

  case 73: /* dummyWhilestmt1: dummyWhilestmt test  */
#line 2744 "parser.y"
                    {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].type_attr)).linenum;
  string loop_end = L_new();
  gen("Ifz " + to_string(((yyvsp[0].type_attr)).temp) + " Goto " + loop_end);
  strcpy(((yyval.type_attr)).gotoname,loop_end.c_str());
  strcpy(((yyval.type_attr)).gotonext, ((yyvsp[-1].type_attr)).gotoname);
  breakjumps.push(loop_end);
}
#line 4473 "parser.tab.c"
    break;

  case 74: /* while_stmt: dummyWhilestmt1 COLON suite  */
#line 2754 "parser.y"
                           {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
  gen("Goto " + to_string(((yyvsp[-2].type_attr)).gotonext));
  gen(to_string(((yyvsp[-2].type_attr)).gotoname) + ":");
  breakjumps.pop();
  continuejumps.pop();
}
#line 4485 "parser.tab.c"
    break;

  case 75: /* dummy_for_stmt: FOR NAME IN test  */
#line 2763 "parser.y"
                 {
  
  if ((curr_table->lookup(to_string(((yyvsp[-2].token_attr)).token_lex)).token == "null") || (curr_table->lookup(to_string(((yyvsp[-2].token_attr)).token_lex)).token == "Function")){
    cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: undeclared variable '" << to_string(((yyvsp[-2].token_attr)).token_lex) << "'\n";
    exit(0);
  }

  if(curr_table->lookup(to_string(((yyvsp[-2].token_attr)).token_lex)).type != "int"){
    cerr << ((yyvsp[-3].token_attr)).linenum << ": Error: " << curr_table->lookup(to_string(((yyvsp[-2].token_attr)).token_lex)).type << " type variable " << to_string(((yyvsp[-2].token_attr)).token_lex) << " not iterable\n";
    exit(0);
  }
  curr_table->modify_lookup(to_string(((yyvsp[-2].token_attr)).token_lex), 1);
  ((yyval.type_attr)).linenum = ((yyvsp[-3].token_attr)).linenum;
// FOR NAME IN test {
  string loop_itr = t_new();
  string loop_cond = t_new();
  // gen(loop_itr + " = " + range_start);
  // gen(loop_cond + " = " + range_end);
  gen(to_string(((yyvsp[-2].token_attr)).token_lex) + " = " + range_start);
  string l1 = L_new();
  string l2 = L_new();
  gen("Goto " + l2);
  gen(l1 + ":");
  //push goto label into stack
  continuejumps.push(l1);
  string temp_ = t_new();
  gen(temp_ + " = " + to_string(((yyvsp[-2].token_attr)).token_lex) + " + 1" );
  gen(to_string(((yyvsp[-2].token_attr)).token_lex) +  " = " + temp_);
  gen(l2+":");
  strcpy(((yyval.type_attr)).gotonext, l1.c_str());
  string next_state = L_new();
  string temp1 = t_new();
  gen(temp1 + " = " + to_string(((yyvsp[-2].token_attr)).token_lex) + " < " + range_end);
  gen("Ifz " + temp1 + " Goto " + next_state);
  //push break label into stack
  breakjumps.push(next_state);
  strcpy(((yyval.type_attr)).gotoname,next_state.c_str());

}
#line 4529 "parser.tab.c"
    break;

  case 76: /* for_stmt: dummy_for_stmt COLON suite  */
#line 2804 "parser.y"
                                {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].type_attr)).linenum;
    gen("Goto " + to_string(((yyvsp[-2].type_attr)).gotonext));
   gen(to_string(((yyvsp[-2].type_attr)).gotoname) + ":");
   continuejumps.pop();
   breakjumps.pop();
}
#line 4541 "parser.tab.c"
    break;

  case 77: /* suite: simple_stmt  */
#line 2814 "parser.y"
                 {
  
}
#line 4549 "parser.tab.c"
    break;

  case 78: /* suite: NEWLINE INDENT Nonzero_stmt DEDENT  */
#line 2817 "parser.y"
                                          {
  ((yyval.type_attr)).linenum = ((yyvsp[-3].token_attr)).linenum;
  
}
#line 4558 "parser.tab.c"
    break;

  case 79: /* Nonzero_stmt: stmt  */
#line 2823 "parser.y"
          {
  
}
#line 4566 "parser.tab.c"
    break;

  case 80: /* Nonzero_stmt: stmt Nonzero_stmt  */
#line 2826 "parser.y"
                         {

}
#line 4574 "parser.tab.c"
    break;

  case 81: /* test: or_test  */
#line 2831 "parser.y"
          {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
   strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);

}
#line 4585 "parser.tab.c"
    break;

  case 82: /* or_test: and_test  */
#line 2839 "parser.y"
               {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
}
#line 4595 "parser.tab.c"
    break;

  case 83: /* or_test: or_test OR and_test  */
#line 2844 "parser.y"
                      {
  // type checking needed

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  string bool_ = "bool";

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " or " + to_string(((yyvsp[0].type_attr)).temp));


}
#line 4660 "parser.tab.c"
    break;

  case 84: /* and_test: not_test  */
#line 2906 "parser.y"
              {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
}
#line 4670 "parser.tab.c"
    break;

  case 85: /* and_test: and_test AND not_test  */
#line 2911 "parser.y"
                        {
    // type checking needed

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  string bool_ = "bool";

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " and " + to_string(((yyvsp[0].type_attr)).temp));


  
}
#line 4735 "parser.tab.c"
    break;

  case 86: /* not_test: NOT not_test  */
#line 2973 "parser.y"
                  {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].token_attr)).linenum;
    // type checking needed

  string type1 = to_string(((yyvsp[0].type_attr)).type);
  if(type1 == "int" || type1 == "float" || type1 == "bool"){
    strcpy(((yyval.type_attr)).type , ((yyvsp[0].type_attr)).type);
  }
  else{
    cerr << ((yyvsp[-1].token_attr)).linenum << ": Error: invalid operation  'not' for '" << type1 << "' type\n";
    exit(0);
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + "not " + to_string(((yyvsp[0].type_attr)).temp));

  
}
#line 4758 "parser.tab.c"
    break;

  case 87: /* not_test: comparison  */
#line 2991 "parser.y"
                  {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
 
}
#line 4769 "parser.tab.c"
    break;

  case 88: /* comparison: expr  */
#line 2999 "parser.y"
           {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
  
}
#line 4780 "parser.tab.c"
    break;

  case 89: /* comparison: comparison LESSER expr  */
#line 3005 "parser.y"
                         {

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " < " + to_string(((yyvsp[0].type_attr)).temp));

}
#line 4843 "parser.tab.c"
    break;

  case 90: /* comparison: comparison GREATER expr  */
#line 3063 "parser.y"
                          {

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " > " + to_string(((yyvsp[0].type_attr)).temp));
  

}
#line 4906 "parser.tab.c"
    break;

  case 91: /* comparison: comparison DOUBLE_EQUAL expr  */
#line 3121 "parser.y"
                               {
  
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " == " + to_string(((yyvsp[0].type_attr)).temp));

}
#line 4969 "parser.tab.c"
    break;

  case 92: /* comparison: comparison GREATER_EQUAL expr  */
#line 3179 "parser.y"
                                {

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " >= " + to_string(((yyvsp[0].type_attr)).temp));
  

}
#line 5033 "parser.tab.c"
    break;

  case 93: /* comparison: comparison LESSER_EQUAL expr  */
#line 3238 "parser.y"
                               {

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " <= " + to_string(((yyvsp[0].type_attr)).temp));
  

}
#line 5097 "parser.tab.c"
    break;

  case 94: /* comparison: comparison NOT_EQUAL expr  */
#line 3297 "parser.y"
                            {

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(((yyval.type_attr)).type, type1.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " != " + to_string(((yyvsp[0].type_attr)).temp));
  

}
#line 5161 "parser.tab.c"
    break;

  case 95: /* comparison: comparison IN expr  */
#line 3356 "parser.y"
                     {
  

}
#line 5170 "parser.tab.c"
    break;

  case 96: /* expr: xor_expr  */
#line 3362 "parser.y"
              {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
  
}
#line 5181 "parser.tab.c"
    break;

  case 97: /* expr: expr OR_OP xor_expr  */
#line 3368 "parser.y"
                      {
  
  // type checking

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " | " + to_string(((yyvsp[0].type_attr)).temp));

}
#line 5228 "parser.tab.c"
    break;

  case 98: /* xor_expr: and_expr  */
#line 3412 "parser.y"
            {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
  
}
#line 5239 "parser.tab.c"
    break;

  case 99: /* xor_expr: xor_expr XOR and_expr  */
#line 3418 "parser.y"
                        {
  
  // type checking
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " ^ " + to_string(((yyvsp[0].type_attr)).temp));

}
#line 5285 "parser.tab.c"
    break;

  case 100: /* and_expr: shift_expr  */
#line 3461 "parser.y"
              {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
  
}
#line 5296 "parser.tab.c"
    break;

  case 101: /* and_expr: and_expr AND_OP shift_expr  */
#line 3467 "parser.y"
                             {
  
  // type checking
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " & " + to_string(((yyvsp[0].type_attr)).temp));
}
#line 5341 "parser.tab.c"
    break;

  case 102: /* shift_expr: arith_expr  */
#line 3509 "parser.y"
               {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
  
}
#line 5352 "parser.tab.c"
    break;

  case 103: /* shift_expr: shift_expr LEFT_SHIFT arith_expr  */
#line 3515 "parser.y"
                                   {
  
  // type checking

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " << " + to_string(((yyvsp[0].type_attr)).temp));
}
#line 5398 "parser.tab.c"
    break;

  case 104: /* shift_expr: shift_expr RIGHT_SHIFT arith_expr  */
#line 3556 "parser.y"
                                    {
  
// type checking
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " >> " + to_string(((yyvsp[0].type_attr)).temp));

}
#line 5444 "parser.tab.c"
    break;

  case 105: /* arith_expr: term  */
#line 3599 "parser.y"
         {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
  
}
#line 5455 "parser.tab.c"
    break;

  case 106: /* arith_expr: arith_expr PLUS term  */
#line 3605 "parser.y"
                       {
// type checking

  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " + " + to_string(((yyvsp[0].type_attr)).temp));
  
}
#line 5515 "parser.tab.c"
    break;

  case 107: /* arith_expr: arith_expr MINUS term  */
#line 3660 "parser.y"
                        {
// type checking
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }  

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " - " + to_string(((yyvsp[0].type_attr)).temp));

}
#line 5574 "parser.tab.c"
    break;

  case 108: /* term: factor  */
#line 3716 "parser.y"
             {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
}
#line 5584 "parser.tab.c"
    break;

  case 109: /* term: term STAR factor  */
#line 3721 "parser.y"
                   {
// type checking
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " * " + to_string(((yyvsp[0].type_attr)).temp));
  
}
#line 5643 "parser.tab.c"
    break;

  case 110: /* term: term SLASH factor  */
#line 3775 "parser.y"
                    {
// type checking
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " / " + to_string(((yyvsp[0].type_attr)).temp));

  
}
#line 5703 "parser.tab.c"
    break;

  case 111: /* term: term PERCENTAGE factor  */
#line 3830 "parser.y"
                         {
  // type checking
  string type1 = to_string(((yyvsp[-2].type_attr)).type);
  string type2 = to_string(((yyvsp[0].type_attr)).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(((yyval.type_attr)).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
      strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(((yyval.type_attr)).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
      strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
    }
    else{
      cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " % " + to_string(((yyvsp[0].type_attr)).temp));
}
#line 5761 "parser.tab.c"
    break;

  case 112: /* term: term DOUBLE_SLASH factor  */
#line 3883 "parser.y"
                           {
  // type checking
    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }
    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type2.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
        strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type2.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
        strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " // " + to_string(((yyvsp[0].type_attr)).temp));
  
}
#line 5820 "parser.tab.c"
    break;

  case 113: /* factor: PLUS factor  */
#line 3940 "parser.y"
                 {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].token_attr)).linenum;
  // type checking

  string type1 = to_string(((yyvsp[0].type_attr)).type);
  if(type1 == "int"){
    // no typecasting
    strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  }
  else if(type1 == "bool"){
    // cast $2 to int
    string int_ = "int";
    strcpy(((yyval.type_attr)).type, int_.c_str());
  }
  else if(type1 == "float"){
    // no typecasting
    strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  }
  else{
    cerr << ((yyvsp[-1].token_attr)).linenum << ": Error: Invalid operation for " << type1 << " type at line " << ((yyvsp[-1].token_attr)).linenum << "\n";
    exit(0); // adapter
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + "+ " + to_string(((yyvsp[0].type_attr)).temp));
  
}
#line 5852 "parser.tab.c"
    break;

  case 114: /* factor: MINUS factor  */
#line 3967 "parser.y"
                    {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].token_attr)).linenum;
  // type checking

  string type1 = to_string(((yyvsp[0].type_attr)).type);
  if(type1 == "int"){
    // no typecasting
    strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  }
  else if(type1 == "bool"){
    // cast $2 to int
    string int_ = "int";
    strcpy(((yyval.type_attr)).type, int_.c_str());
  }
  else if(type1 == "float"){
    // no typecasting
    strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  }
  else{
    cerr << ((yyvsp[-1].token_attr)).linenum << ": Error: Invalid operation for " << type1 << " type at line " << ((yyvsp[-1].token_attr)).linenum << "\n";
    exit(0); // adapter
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + "- " + to_string(((yyvsp[0].type_attr)).temp));

  
}
#line 5885 "parser.tab.c"
    break;

  case 115: /* factor: NOT_OP factor  */
#line 3995 "parser.y"
                     {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].token_attr)).linenum;
  // type checking
  string type1 = to_string(((yyvsp[0].type_attr)).type);
  if(type1 == "int"){
    // no typecasting
    strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  }
  else if(type1 == "bool"){
    // cast $2 to int
    string int_ = "int";
    strcpy(((yyval.type_attr)).type, int_.c_str());
  }
  else{
    cerr << ((yyvsp[-1].token_attr)).linenum << ": Error: invalid operation for " << type1 << " type at line " << ((yyvsp[-1].token_attr)).linenum << "\n";
    exit(0); // adapter
  }

  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + "~ " + to_string(((yyvsp[0].type_attr)).temp));
  
}
#line 5912 "parser.tab.c"
    break;

  case 116: /* factor: power  */
#line 4017 "parser.y"
             {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
}
#line 5922 "parser.tab.c"
    break;

  case 117: /* power: atom_expr  */
#line 4024 "parser.y"
                {
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].type_attr)).temp);
  

}
#line 5934 "parser.tab.c"
    break;

  case 118: /* power: atom_expr DOUBLE_STAR factor  */
#line 4031 "parser.y"
                               {

    string type1 = to_string(((yyvsp[-2].type_attr)).type);
    string type2 = to_string(((yyvsp[0].type_attr)).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(((yyval.type_attr)).type, ((yyvsp[-2].type_attr)).type);
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type2.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
        strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(((yyval.type_attr)).type, type2.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(((yyvsp[-2].type_attr)).temp));
        strcpy(((yyvsp[-2].type_attr)).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(((yyval.type_attr)).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(((yyvsp[0].type_attr)).temp));
        strcpy(((yyvsp[0].type_attr)).temp, newt.c_str());
      }
      else{
        cerr << ((yyvsp[-2].type_attr)).linenum << ": Error: invalid operation '" << to_string(((yyvsp[-1].token_attr)).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[-2].type_attr)).temp) + " ** " + to_string(((yyvsp[0].type_attr)).temp));



}
#line 5996 "parser.tab.c"
    break;

  case 119: /* atom_expr: atom Multi_trailer  */
#line 4091 "parser.y"
                        {
  ((yyval.type_attr)).isfunccall = ((yyvsp[0].type_attr)).isfunccall;
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[-1].type_attr)).lexeme);
  strcat(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  // string list = "list";
  // if(!strcmp(($1).lexeme, list.c_str())){
  //   string list_at = "list@";
  //   strcpy(($$).type, list_at.c_str());
  //   strcat(($$).type, ($2).type);
  // }
  // printf("%s\n", ($$).lexeme);
  // ($$).isname = ($1).isname;
  // ($$).isself = ($1).isself;
  // strcpy(($$).type, ($1).type);     // wrongggggggggg
  // if(($$).type[0]!='\0')printf("%s\n", ($$).type);
  
  
  

  // if(($$).isfunccall){
  //   // ($$).lexeme holds the value of caller
  // }

  string myString = to_string(((yyval.type_attr)).lexeme);
  int count_at = count(myString.begin(), myString.end(), '@');
  if(count_at >= 2){
    size_t pos = myString.find('@');
    string head = myString.substr(0, pos);
    cerr << ((yyvsp[-1].type_attr)).linenum << "Error : '"<< head <<"' indexed with more indices than its dimension" << endl;
    exit(0);
  }

  if(((yyvsp[-1].type_attr)).isname){

    int has_dot = 0, has_bracket = 0;
    size_t pos_dot = to_string(((yyval.type_attr)).lexeme).find(".");
    if (pos_dot != string::npos) has_dot = 1;
    size_t pos_bracket = to_string(((yyval.type_attr)).lexeme).find("@");
    if (pos_bracket != string::npos) has_bracket = 1;

    if(has_bracket && !has_dot && all_types.find(to_string(((yyval.type_attr)).lexeme)) == all_types.end()){
      
        if(to_string(((yyvsp[0].type_attr)).indextype) != "int"){
          cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: index is not integer type \n";
          exit(0);
        }
        if(curr_table->lookup(to_string(((yyvsp[-1].type_attr)).lexeme)).token != "null"){

            string name1_type = curr_table->lookup(to_string(((yyvsp[-1].type_attr)).lexeme)).type;
            if(name1_type.substr(0,5) != "list@"){
              cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: '" << to_string(((yyvsp[-1].type_attr)).lexeme) << "' is not a list, cannot be indexed" << endl;
              exit(0);
            }
            string list_type = name1_type;
            if(list_type.size() > 5){
              string without_list_type = list_type.substr(5);
              strcpy(((yyval.type_attr)).type, without_list_type.c_str());
            }
        }
        else{
            cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared variable '" << to_string(((yyvsp[-1].type_attr)).lexeme) << "'" << endl;
            exit(0);
        }

        string index_lexeme = to_string(((yyval.type_attr)).lexeme).substr(pos_bracket+1);
        string temp_ = t_new();
        int typesize = type_size(to_string(((yyval.type_attr)).type));
        gen(temp_ + " = " + to_string(((yyvsp[0].type_attr)).tempsquare) + " * " + to_string(typesize));

        string temp1 = t_new();
        gen(temp1 + " = *(" + to_string(((yyvsp[-1].type_attr)).lexeme) + " + " + temp_ + ")");
        strcpy(((yyval.type_attr)).temp, temp1.c_str());

          // important: Checking if index is in range

        
    }
    else if(has_bracket && has_dot){
      string input = to_string(((yyval.type_attr)).lexeme);
      string part1, part2, part3;

      size_t pos1 = input.find('.');
      size_t pos2 = input.find('@');

      if(pos1 != string::npos && pos2 != string::npos) {
          part1 = input.substr(0, pos1);
          part2 = input.substr(pos1 + 1, pos2 - pos1 - 1);
          part3 = input.substr(pos2 + 1);
      }

      string class_name = (curr_table->lookup(part1)).type; 
      if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
          cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
          exit(0);
      }
      Symbol_Table *class_table = class_symbol_tables[class_name];
      string attribute = part2;
      if(class_table->lookup("self."+attribute).token == "null"){
        cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: Unidentified attribute " << attribute << " in class " << class_name << " at line " << ((yyvsp[-1].type_attr)).linenum << "\n";
        exit(0);
      }


      if(to_string(((yyvsp[0].type_attr)).indextype) != "int"){
        cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: index is not integer type\n";
        exit(0);
      }

      
      string name1_type = class_table->lookup("self."+attribute).type;
      if(name1_type.substr(0,5) != "list@"){
        cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: '" << part1+"."+part2 << "' is not a list, cannot be indexed " << endl;
      exit(0);
      }
      string list_type = name1_type;
      if(list_type.size() > 5){
        string without_list_type = list_type.substr(5);
        strcpy(((yyval.type_attr)).type, without_list_type.c_str());
      }

      
      string temp_ = t_new();
      int typesize = type_size(to_string(((yyval.type_attr)).type));
      gen(temp_ + " = " + to_string(((yyvsp[0].type_attr)).tempsquare) + " * " + to_string(typesize));
      string offset_ = to_string(class_table->lookup("self."+attribute).offset);
      string temp1 = t_new();
      gen(temp1 + " = " + "*(" + part1 + " + " + offset_ + ") ");
      string temp_result = t_new();
      gen(temp_result + " = *(" + temp1 + " + " + temp_ + ")");
      strcpy(((yyval.type_attr)).temp, temp_result.c_str());

    }



    

    ///////// DOT exists
    else if (pos_dot != string::npos) {
        size_t pos = pos_dot;
        string object_name = to_string(((yyvsp[-1].type_attr)).lexeme);
        if(curr_table->lookup(object_name).token == "null"){
            cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared object or class '" << object_name << "'\n";
            exit(0);
        }
        else{
              /////// the name before dot is class name
              if((curr_table->lookup(object_name)).token == "Class"){
                string class_name = object_name;
                //// An attribute - NOT ALLOWED
                if(!((yyval.type_attr)).isfunccall){
                  cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: accessing attributes of class '" << class_name << "' without the mention of object not allowed\n";
                  exit(0);
                }

                //// A method - allowed with self mention 
                else{
                  // if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
                  //     cerr << ($1).linenum << ": Error: Invalid object type " << class_name << " at line " << ($1).linenum << "\n";
                  //     exit(0);
                  // }
                  Symbol_Table *class_table = class_symbol_tables[class_name];
                  string attribute = to_string(((yyval.type_attr)).lexeme).substr(pos+1);

                  if(class_table->lookup(attribute).token == "null"){
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
                    exit(0);
                  }
                  else if (class_table->lookup(attribute).token != "Function"){
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
                    exit(0);
                  }

                  else{
                    // Method call from class is valid 
                    // now check for arg types and num
                      Symbol_Table_Entry func_defn = class_table->lookup(attribute);
                      Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
                      int num_args = func_defn.numargs;
                      int func_params_size = 0;
                      for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
                        // num_args = (it->second).numargs;
                        if((long unsigned int)num_args != func_arg_vec.size()){
                          // number of args and param dont match 
                          cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << attribute << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                          exit(0); 
                        }
                        if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                          if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                            if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                              // types are not same, typecast arg to param type
                              if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                                string newt = t_new();
                                gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                                func_arg_temp_vec[(it->second).argnum -1].second = newt;
                              }
                              
                            }
                            func_params_size += type_size((it->second).type);
                          }
                          else{
                            // types dont match even after typecasting
                            cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ((yyvsp[-1].type_attr)).linenum << "\n";
                            exit(0); // adapter

                          }
                        }
                      }

                      strcpy(((yyval.type_attr)).type, func_defn.type.c_str());
                      // gen("pushparam " +  object_name);
                      for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
                        gen("pushparam " + func_arg_temp_vec[i].second);
                      }
                      gen("push ret_addr");
                      gen("sub %rsp " + to_string(func_params_size));
                      gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
                      gen("add %rsp " + to_string(func_params_size));

                      if(func_defn.type != "None"){
                          string temp_result = t_new();
                          gen(temp_result + " = %rax");
                          strcpy(((yyval.type_attr)).temp, temp_result.c_str());
                      }

                  }

                }
              }

              /////// the name before dot is object name
              else{
                  string class_name = (curr_table->lookup(object_name)).type; 
                  if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
                      cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
            exit(0);
                  }
                  Symbol_Table *class_table = class_symbol_tables[class_name];
                  string attribute = to_string(((yyval.type_attr)).lexeme).substr(pos+1);

                  //////// An attribute 
                  if(!((yyval.type_attr)).isfunccall){
                      if(class_table->lookup("self."+attribute).token == "null"){
                        cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared attribute '" << attribute << "' in class '" << class_name << "'\n";
          exit(0);
                      }
                      else {
                        if(class_table->lookup("self."+attribute).isinit == 0){
                          cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: uninitialised attribute '" << attribute << "' in class '" << class_name << "'\n";
          exit(0);
                        }
                        string attribute_type = class_table->lookup("self."+attribute).type;
                        strcpy(((yyval.type_attr)).type, attribute_type.c_str());
                        string temp_ = t_new();
                        string offset_ = to_string(class_table->lookup("self."+attribute).offset);
                        gen(temp_ + " = *(" + object_name + " + " + offset_ + ")");
                        strcpy(((yyval.type_attr)).temp, temp_.c_str());
                      }
                  }
                  
                  ///////////// A method 
                  if(((yyval.type_attr)).isfunccall){
                    if(class_table->lookup(attribute).token == "null"){
                      cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
          exit(0);
                    }
                    else if (class_table->lookup(attribute).token != "Function"){
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";                      exit(0);
                    }
                    else{
                      // Method call rom object is valid 

                        func_arg_vec.insert(func_arg_vec.begin(), make_pair(object_name, class_name));

                        Symbol_Table_Entry func_defn = class_table->lookup(attribute);
                        Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
                        int num_args = func_defn.numargs;
                        int func_params_size = 0;
                        for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
                          // num_args = (it->second).numargs;
                          if((long unsigned int)num_args != func_arg_vec.size()){
                            // number of args and param dont match 
                            cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << attribute << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                          exit(0); 
                          }
                          if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                            if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                              if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                                // types are not same, typecast arg to param type
                                if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                                  string newt = t_new();
                                  gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                                  func_arg_temp_vec[(it->second).argnum -2].second = newt;
                                }
                              }
                              func_params_size += type_size((it->second).type);
                            }
                            else{
                              // types dont match even after typecasting
                              cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ((yyvsp[-1].type_attr)).linenum << "\n";
                              exit(0); // adapter

                            }
                          }
                        }
                        strcpy(((yyval.type_attr)).type, func_defn.type.c_str());
                        
                        for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
                          gen("pushparam " + func_arg_temp_vec[i].second);
                        }
                        gen("pushparam " +  object_name);
                        gen("push ret_addr");
                        gen("sub %rsp " + to_string(func_params_size));
                        gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
                        gen("add %rsp " + to_string(func_params_size));

                        if(func_defn.type != "None"){
                            string temp_result = t_new();
                            gen(temp_result + " = %rax");
                            strcpy(((yyval.type_attr)).temp, temp_result.c_str());
                        }
                        

                    }
                    
                  }
              }
              
        }
    } 

    //////// DOT doesnt exist
    else {
      ////////// A function 
      if(((yyval.type_attr)).isfunccall){
        auto it = all_types.find(to_string(((yyval.type_attr)).lexeme));
        if (it == all_types.end()){
            if(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).token == "null"){
              if (to_string(((yyval.type_attr)).lexeme) == "len"){
                string int_ = "int";
                strcpy(((yyval.type_attr)).type, int_.c_str());
                if(func_arg_vec.size()!=1){
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'len' function, expected 1 argument" << endl;
                exit(0);
                }
                if(func_arg_vec[0].second.size() > 5){
                    if(func_arg_vec[0].second.substr(0,5) != "list@"){
                      cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
                  exit(0);
                    }
                }
                else{
                      cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
                  exit(0);
                }
                
                for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
                  gen("pushparam " + func_arg_temp_vec[i].second);
                }
                gen("push ret_addr");
                gen("sub %rsp 8");
                gen("call len 1");
                gen("add %rsp 8");
                string temp_ = t_new();
                gen(temp_ + " = %rax");
                strcpy(((yyval.type_attr)).temp, temp_.c_str()); // come back here

              }
              else if (to_string(((yyval.type_attr)).lexeme) == "range"){
                string none = "None";
                strcpy(((yyval.type_attr)).type, none.c_str());
                if(func_arg_vec.size() > 2 || func_arg_vec.size() < 1){
                  cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'range' function, expected 1 or 2 arguments" << endl;
                exit(0);
                }
                else if (func_arg_vec.size() == 2){
                  if(func_arg_vec[0].second != "int"){
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                  }
                  if(func_arg_vec[1].second != "int"){
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                  }
                  range_start = func_arg_temp_vec[0].second;
                  range_end = func_arg_temp_vec[1].second;
                }
                else if( func_arg_vec.size() == 1){
                  if(func_arg_vec[0].second != "int"){
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                  }
                  string temp_ = t_new();
                  gen(temp_ + " = 0");
                  range_start = temp_;
                  range_end = func_arg_temp_vec[0].second;
                }
              }
              else{
                cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared function '" << to_string(((yyval.type_attr)).lexeme) << "' called\n";
            exit(0);
              }
              
            }
            else if (curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).token != "Function"){

              cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared function '" << to_string(((yyval.type_attr)).lexeme) << "' called\n";
            exit(0);
            }

            else{
              /// funccall is valid 
              // now check for arguments
              Symbol_Table_Entry func_defn = curr_table->lookup(to_string(((yyvsp[-1].type_attr)).lexeme));
              // func_defn.print_sym_entry();
              Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
              int num_args = func_defn.numargs;
              int func_params_size = 0;
              for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
                // num_args = (it->second).numargs;
                if((long unsigned int)num_args != func_arg_vec.size()){
                  // number of args and param dont match 
                  cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(((yyval.type_attr)).lexeme) << "' function, expected " << num_args << " argument(s)" << endl;
            exit(0);
                }
                if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                  if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                    if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                      // types are not same, typecast arg to param type
                      if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                        string newt = t_new();
                        gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                        func_arg_temp_vec[(it->second).argnum -1].second = newt;
                      }
                    }
                    func_params_size += type_size((it->second).type);
                  }
                  else{
                    // types dont match even after typecasting
                    cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ((yyvsp[-1].type_attr)).linenum << "\n";
                    exit(0); // adapter

                  }
                }
              }

              
              strcpy(((yyval.type_attr)).type, func_defn.type.c_str());
              for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
                gen("pushparam " + func_arg_temp_vec[i].second);
              }
              gen("push ret_addr");
              gen("sub %rsp " + to_string(func_params_size));
              gen("call " + to_string(((yyvsp[-1].type_attr)).lexeme) + " " + to_string(func_arg_vec.size()));
              gen("add %rsp " + to_string(func_params_size));
              string temp_ = t_new();
              gen(temp_ + " = %rax" );
              strcpy(((yyval.type_attr)).temp, temp_.c_str());

            }

        }
        if (class_symbol_tables.find(to_string(((yyval.type_attr)).lexeme)) != class_symbol_tables.end()) {
          string class_name = to_string(((yyval.type_attr)).lexeme);
          // if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
          //     ": Error: Undeclared function call " << class_name << " at line " << ($1).linenum << "\n";
          //     exit(0);
          // }
          Symbol_Table *class_table = class_symbol_tables[class_name];
          Symbol_Table_Entry func_defn = class_table->lookup("__init__");
          Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
          int num_args = func_defn.numargs;
          int func_params_size = 0;
          func_arg_vec.insert(func_arg_vec.begin(), make_pair("random_string", class_name));
          for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
            if((long unsigned int)num_args != func_arg_vec.size()){
              // number of args and param dont match 
              cerr << ((yyvsp[-1].type_attr)).linenum << "Error : Number of constructor call arguments do not match number of constructor parameters of class " << class_name << " at line " << ((yyvsp[-1].type_attr)).linenum << "\n";
              exit(0); // adapter
            }
            if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
              if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                  // types are not same, typecast arg to param type
                  if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                    string newt = t_new();
                    gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                    func_arg_temp_vec[(it->second).argnum -2].second = newt;
                  }

                }
                func_params_size += type_size((it->second).type);
              }
              else{
                // types dont match even after typecasting
              cerr << ((yyvsp[-1].type_attr)).linenum << "Error : Types of constructor call arguments do not match types of constructor parameters of class " << class_name << " at line " << ((yyvsp[-1].type_attr)).linenum << "\n";
                exit(0); // adapter

              }
            }
          }



          strcpy(((yyval.type_attr)).type, func_defn.type.c_str());
          int max_offset = 0;
          string max_type = "";
          string max_token = "";
          for(auto it = class_table->table.begin(); it != class_table->table.end(); it++){
            if(it->second.offset >= max_offset){
              max_offset = it->second.offset;
              max_type = it->second.type;
              max_token = it->second.token;
            }
          }


          int last_size = 0;
          if(max_token == "Function" || max_token == "Class"){
            last_size = 0;
          }
          else{
            last_size = type_size(max_type);
          }

          int class_size = max_offset + last_size;
          string temp_size = t_new();
          gen(temp_size + " = " + to_string(class_size));
          gen("pushparam " + temp_size);
          gen("sub %rsp 4");
          gen("call allocmem 1");
          gen("add %rsp 4");
          string temp_self = t_new();
          gen(temp_self + " = %rax");
          
          for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
            gen("pushparam " + func_arg_temp_vec[i].second);
          }
          gen("pushparam " +  temp_self);
          gen("push ret_addr");
          gen("sub %rsp " + to_string(func_params_size));
          gen("call " + class_name + ".__init__ " + to_string(func_arg_vec.size()));
          gen("add %rsp " + to_string(func_params_size));
          // string temp_result = t_new();
          // gen(temp_result + " = %rax");
          strcpy(((yyval.type_attr)).temp, temp_self.c_str());
          


        }


      }

      ////////// A variable
      else{
    
        auto it = all_types.find(to_string(((yyval.type_attr)).lexeme));
        if (it == all_types.end()){
          if(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).token == "null" || curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).token == "Function"){
            if(to_string(((yyval.type_attr)).lexeme) != "__name__"){
              cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: undeclared variable '" << to_string(((yyval.type_attr)).lexeme) << "'\n";
              exit(0); 
            }
          } 
          else{
            if(curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).isinit == 0){
              cerr << ((yyvsp[-1].type_attr)).linenum << ": Error: uninitialised variable '" << to_string(((yyval.type_attr)).lexeme) << "'\n";
            exit(0);
            }
            string variable_type = curr_table->lookup(to_string(((yyval.type_attr)).lexeme)).type;
            strcpy(((yyval.type_attr)).type, variable_type.c_str());
          }
        }
      }
    }
  }

  if(((yyval.type_attr)).isfunccall){
    func_arg_vec.clear();
    func_arg_temp_vec.clear();
  }
}
#line 6584 "parser.tab.c"
    break;

  case 120: /* Multi_trailer: %empty  */
#line 4676 "parser.y"
                   {
  ((yyval.type_attr)).lexeme[0] = '\0';
  ((yyval.type_attr)).isfunccall = 0;
}
#line 6593 "parser.tab.c"
    break;

  case 121: /* Multi_trailer: trailer Multi_trailer  */
#line 4680 "parser.y"
                             {
  ((yyval.type_attr)).isfunccall = ((yyvsp[-1].type_attr)).isfunccall || ((yyvsp[0].type_attr)).isfunccall;
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[-1].type_attr)).lexeme);
  strcat(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).tempsquare, ((yyvsp[-1].type_attr)).tempsquare);
  strcat(((yyval.type_attr)).tempsquare, ((yyvsp[0].type_attr)).tempsquare);
  if(to_string(((yyvsp[0].type_attr)).indextype).size() != 0){
    strcpy(((yyval.type_attr)).indextype, ((yyvsp[0].type_attr)).indextype);
  }
  else{
    strcpy(((yyval.type_attr)).indextype, ((yyvsp[-1].type_attr)).indextype);
  }
  // strcpy(($$).type, ($1).type);
}
#line 6612 "parser.tab.c"
    break;

  case 122: /* atom: OPEN_ROUND_BRACKET Opt_test CLOSE_ROUND_BRACKET  */
#line 4696 "parser.y"
                                                     {
    strcpy(((yyval.type_attr)).type, ((yyvsp[-1].type_attr)).type);
    strcpy(((yyval.type_attr)).temp, ((yyvsp[-1].type_attr)).temp);
    strcpy(((yyval.type_attr)).lexeme, ((yyvsp[-1].type_attr)).lexeme);
    ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;

}
#line 6624 "parser.tab.c"
    break;

  case 123: /* atom: OPEN_SQUARE_BRACKET testlist CLOSE_SQUARE_BRACKET  */
#line 4703 "parser.y"
                                                         {
  // hardddddddddddddddddddd
  // all list handling
  // type checking needed
  
  // string list_at = "list@";
  
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  strcpy(((yyval.type_attr)).type, ((yyvsp[-1].type_attr)).type);
  string type_list = to_string(((yyvsp[-1].type_attr)).type);
  string type_index;
  if(type_list.size() > 5){
    type_index = type_list.substr(5);
  }

  int type_size_ = type_size(type_index);
  int total_size = type_size_*list_temps.size();

  reverse(list_temps.begin(), list_temps.end());

  string temp1 = t_new();
  gen(temp1 + " = " + to_string(total_size));
  gen("pushparam " + temp1);
  gen("push ret_addr");
  gen("sub %rsp 4");
  gen("call allocmem 1");
  gen("add %rsp 4");
  string temp_ = t_new();
  gen(temp_ + " = %rax");
  // gen("*(" + temp_ + " + " + to_string(0) + ")" + " = " + to_string(list_temps.size()));
  for(auto it = 0; it < (int)list_temps.size(); it++){
    gen("*(" + temp_ + " + " + to_string(it * type_size_) + ")" + " = " + list_temps[it]);
  }
  strcpy(((yyval.type_attr)).temp, temp_.c_str());
  int list_size = list_temps.size();
  ((yyval.type_attr)).listsize = list_size;
  list_temps.clear();
  //   strcpy(($$).type, );
  // }
}
#line 6669 "parser.tab.c"
    break;

  case 124: /* atom: NAME  */
#line 4743 "parser.y"
            {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].token_attr)).token_lex);
  ((yyval.type_attr)).isname = 1;
  if(curr_table->lookup(to_string(((yyvsp[0].token_attr)).token_lex)).token != "null"){
    string name_type = curr_table->lookup(to_string(((yyvsp[0].token_attr)).token_lex)).type;
    strcpy(((yyval.type_attr)).type, name_type.c_str());
    // string one = "1";
    // strcat(($$).type, one.c_str());

  }
  if(curr_table->lookup(to_string(((yyvsp[0].token_attr)).token_lex)).token != "null"){
    int name_type = curr_table->lookup(to_string(((yyvsp[0].token_attr)).token_lex)).listlen;
    ((yyval.type_attr)).listsize = name_type;
    // string one = "1";
    // strcat(($$).type, one.c_str());

  }
  if(to_string(((yyvsp[0].token_attr)).token_lex) == "__name__") {
    string str_ = "str";
    strcpy(((yyval.type_attr)).type, str_.c_str());
  }
  strcpy(((yyval.type_attr)).temp , ((yyvsp[0].token_attr)).token_lex);
  // strcpy(($$).type, "name");
}
#line 6699 "parser.tab.c"
    break;

  case 125: /* atom: NUMBER  */
#line 4770 "parser.y"
              {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  // should assign int and float types
   if(to_string(((yyvsp[0].token_attr)).token_type) == "int")strcpy(((yyval.type_attr)).type, "int");
   if(to_string(((yyvsp[0].token_attr)).token_type) == "float")strcpy(((yyval.type_attr)).type, "float");
   strcpy(((yyval.type_attr)).temp , t_new().c_str());
   gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[0].token_attr)).token_lex));
   ((yyval.type_attr)).isname = 0;
}
#line 6713 "parser.tab.c"
    break;

  case 126: /* atom: STRING  */
#line 4779 "parser.y"
            {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
    // should assign string types
    string str_ = "str";
    strcpy(((yyval.type_attr)).type, str_.c_str());
    strcpy(((yyval.type_attr)).temp , t_new().c_str());
    gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[0].token_attr)).token_lex));
    ((yyval.type_attr)).isname = 0;

}
#line 6728 "parser.tab.c"
    break;

  case 127: /* atom: NONE  */
#line 4789 "parser.y"
            {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
// should assign None types
string none_ = "None";
strcpy(((yyval.type_attr)).type, none_.c_str());
((yyval.type_attr)).isname = 0;
}
#line 6740 "parser.tab.c"
    break;

  case 128: /* atom: TRUE  */
#line 4796 "parser.y"
            {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  // should assign bool types
//   ($$).size = 1;
  string bool_ = "bool";
  strcpy(((yyval.type_attr)).type, bool_.c_str());
  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[0].token_attr)).token_lex));
  ((yyval.type_attr)).isname = 0;
}
#line 6755 "parser.tab.c"
    break;

  case 129: /* atom: FALSE  */
#line 4806 "parser.y"
             {
  ((yyval.type_attr)).linenum = ((yyvsp[0].token_attr)).linenum;
  // should assign bool types
//   ($$).size = 1;
  string bool_ = "bool";
  strcpy(((yyval.type_attr)).type, bool_.c_str());
  strcpy(((yyval.type_attr)).temp , t_new().c_str());
  gen(to_string(((yyval.type_attr)).temp) + " = " + to_string(((yyvsp[0].token_attr)).token_lex));
  ((yyval.type_attr)).isname = 0;
}
#line 6770 "parser.tab.c"
    break;

  case 130: /* trailer: OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET  */
#line 4818 "parser.y"
                                                        {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  ((yyval.type_attr)).isfunccall = 1;
  string empty = "";
  strcpy(((yyval.type_attr)).lexeme, empty.c_str());
  ((yyval.type_attr)).listsize = ((yyvsp[-1].type_attr)).listsize;

}
#line 6783 "parser.tab.c"
    break;

  case 131: /* trailer: OPEN_SQUARE_BRACKET test CLOSE_SQUARE_BRACKET  */
#line 4826 "parser.y"
                                                     {

((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  ((yyval.type_attr)).isfunccall = 0;
  // ($$).isbracket = 1;
  string at = "@";
  strcpy(((yyval.type_attr)).lexeme, at.c_str());
  strcat(((yyval.type_attr)).lexeme, ((yyvsp[-1].type_attr)).lexeme);
  strcpy(((yyval.type_attr)).indextype, ((yyvsp[-1].type_attr)).type);
  strcpy(((yyval.type_attr)).temp, ((yyvsp[-1].type_attr)).temp);
  // int typesize = type_size(to_string(($2).type));
  // string temp_ = t_new();
  // strcpy(($$).tempsquare, temp_.c_str());
  // gen(temp_ + " = " + to_string(($2).temp) + " * " + to_string(typesize));
  strcpy(((yyval.type_attr)).tempsquare, ((yyvsp[-1].type_attr)).temp);

}
#line 6805 "parser.tab.c"
    break;

  case 132: /* trailer: DOT NAME  */
#line 4843 "parser.y"
                {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].token_attr)).linenum;
  // not sure what to do 
  ((yyval.type_attr)).isfunccall = 0;
  string at = ".";
  strcpy(((yyval.type_attr)).lexeme, at.c_str());
  strcat(((yyval.type_attr)).lexeme, ((yyvsp[0].token_attr)).token_lex);
  
}
#line 6819 "parser.tab.c"
    break;

  case 133: /* Opt_arglist: %empty  */
#line 4854 "parser.y"
                   {
  
}
#line 6827 "parser.tab.c"
    break;

  case 134: /* Opt_arglist: arglist  */
#line 4857 "parser.y"
               {
  
}
#line 6835 "parser.tab.c"
    break;

  case 135: /* testlist: test Multi_test  */
#line 4862 "parser.y"
                      {
  ((yyval.type_attr)).linenum = ((yyvsp[-1].type_attr)).linenum;
  string list_at = "list@";
  strcpy(((yyval.type_attr)).type, list_at.c_str());
  strcat(((yyval.type_attr)).type, ((yyvsp[-1].type_attr)).type); // occurs only in list and they are homogeneous so
  list_temps.push_back(to_string(((yyvsp[-1].type_attr)).temp));
}
#line 6847 "parser.tab.c"
    break;

  case 136: /* Multi_test: %empty  */
#line 4871 "parser.y"
                   {
  
}
#line 6855 "parser.tab.c"
    break;

  case 137: /* Multi_test: COMMA test Multi_test  */
#line 4874 "parser.y"
                             {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  list_temps.push_back(to_string(((yyvsp[-1].type_attr)).temp));
}
#line 6864 "parser.tab.c"
    break;

  case 138: /* $@4: %empty  */
#line 4880 "parser.y"
                 {
  
  // gen("beginclass");
  curr_table->make_entry(to_string(((yyvsp[-1].token_attr)).token_lex), "Class", to_string(((yyvsp[-1].token_attr)).token_lex), offset, curr_scope, ((yyvsp[-2].token_attr)).linenum, -1, -1, -1, 1);
  offset+=0;
  table_stack.push(curr_table);
  curr_table = new Symbol_Table(curr_table);
  class_symbol_tables[to_string(((yyvsp[-1].token_attr)).token_lex)] = curr_table;
  all_types.insert(to_string(((yyvsp[-1].token_attr)).token_lex));
  all_types.insert("list@" + to_string(((yyvsp[-1].token_attr)).token_lex));
  recent_class = to_string(((yyvsp[-1].token_attr)).token_lex);
  vec_tables.push_back(curr_table);
  scope_stack.push(curr_scope);
  offset_stack.push(offset);
  string new_scope = "Class@" + to_string(((yyvsp[-1].token_attr)).token_lex);
  curr_scope = new_scope;
  offset = 0;
}
#line 6887 "parser.tab.c"
    break;

  case 139: /* classdef: CLASS NAME COLON $@4 suite  */
#line 4898 "parser.y"
           { 
  ((yyval.type_attr)).linenum = ((yyvsp[-4].token_attr)).linenum;
  // new symbol table

  curr_table = table_stack.top(); 
  table_stack.pop();
  curr_scope = scope_stack.top(); 
  scope_stack.pop();
  offset = offset_stack.top(); 
  offset_stack.pop();
  recent_class = "";
  // strcpy(($$).type, ($2).token_lex);
  
  // gen("endclass");

}
#line 6908 "parser.tab.c"
    break;

  case 140: /* $@5: %empty  */
#line 4914 "parser.y"
                                                               {
  // gen("beginclass");
// check if NAME exists in global 
if(curr_table->lookup(to_string(((yyvsp[-2].token_attr)).token_lex)).token == "null"){
  cerr << ((yyvsp[-5].token_attr)).linenum << ": Error: base / parent class '" << to_string(((yyvsp[-2].token_attr)).token_lex) <<"' does not exist\n";
  exit(0);
}
else{
    child_to_parent_classes[to_string(((yyvsp[-4].token_attr)).token_lex)] = to_string(((yyvsp[-2].token_attr)).token_lex);
    curr_table->make_entry(to_string(((yyvsp[-4].token_attr)).token_lex), "Class", to_string(((yyvsp[-4].token_attr)).token_lex), offset, curr_scope, ((yyvsp[-5].token_attr)).linenum, -1, -1, -1, 1);
    offset+=0;
    table_stack.push(curr_table);
    curr_table = new Symbol_Table(curr_table);
    
    Symbol_Table *parent_class_table = class_symbol_tables[to_string(((yyvsp[-2].token_attr)).token_lex)];
    for(auto it = parent_class_table->table.begin(); it != parent_class_table->table.end(); it++ ){
      if(it->first != "__init__"){
        Symbol_Table_Entry* entry = curr_table->make_entry(it->first, it->second.token, it->second.type, it->second.offset, "Class@" + to_string(((yyvsp[-4].token_attr)).token_lex), it->second.line, it->second.argnum, it->second.width, it->second.numargs, it->second.isinit);
        entry->update_entry(it->second.childtable);
      }

    }

    class_symbol_tables[to_string(((yyvsp[-4].token_attr)).token_lex)] = curr_table;
    all_types.insert(to_string(((yyvsp[-4].token_attr)).token_lex));
    all_types.insert("list@" + to_string(((yyvsp[-4].token_attr)).token_lex));
    recent_class = to_string(((yyvsp[-4].token_attr)).token_lex);
    vec_tables.push_back(curr_table);
    scope_stack.push(curr_scope);
    offset_stack.push(offset);
    string new_scope = "Class@" + to_string(((yyvsp[-4].token_attr)).token_lex);
    curr_scope = new_scope;

    int max_offset = 0;
    string max_type = "";
    string max_token = "";
    for(auto it = parent_class_table->table.begin(); it != parent_class_table->table.end(); it++){
      if(it->second.offset >= max_offset){
        max_offset = it->second.offset;
        max_type = it->second.type;
        max_token = it->second.token;
      }
    }
    int last_size = 0;
    if(max_token == "Function" || max_token == "Class"){
      last_size = 0;
    }
    else{
      last_size = type_size(max_type);
    }

    int class_size = max_offset + last_size;
    offset = class_size;
}


}
#line 6970 "parser.tab.c"
    break;

  case 141: /* classdef: CLASS NAME OPEN_ROUND_BRACKET NAME CLOSE_ROUND_BRACKET COLON $@5 suite  */
#line 4973 "parser.y"
           {
  ((yyval.type_attr)).linenum = ((yyvsp[-7].token_attr)).linenum;
  // new symbol table
  curr_table = table_stack.top(); 
  table_stack.pop();
  curr_scope = scope_stack.top(); 
  scope_stack.pop();
  offset = offset_stack.top(); 
  offset_stack.pop();
  recent_class = "";
  // strcpy(($$).type, ($2).token_lex);
  // gen("endclass");
}
#line 6988 "parser.tab.c"
    break;

  case 142: /* arglist: argument Multi_argument  */
#line 4988 "parser.y"
                              {
  
}
#line 6996 "parser.tab.c"
    break;

  case 143: /* Multi_argument: %empty  */
#line 4993 "parser.y"
                   {
  
}
#line 7004 "parser.tab.c"
    break;

  case 144: /* Multi_argument: COMMA argument Multi_argument  */
#line 4996 "parser.y"
                                     {
  ((yyval.type_attr)).linenum = ((yyvsp[-2].token_attr)).linenum;
  
}
#line 7013 "parser.tab.c"
    break;

  case 145: /* argument: test  */
#line 5002 "parser.y"
          {
  strcpy(((yyval.type_attr)).type, ((yyvsp[0].type_attr)).type);
  strcpy(((yyval.type_attr)).lexeme, ((yyvsp[0].type_attr)).lexeme);
  func_arg_vec.push_back({to_string(((yyvsp[0].type_attr)).lexeme), to_string(((yyvsp[0].type_attr)).type)});
  func_arg_temp_vec.push_back({to_string(((yyvsp[0].type_attr)).lexeme), to_string(((yyvsp[0].type_attr)).temp)});
}
#line 7024 "parser.tab.c"
    break;

  case 146: /* func_body_suite: simple_stmt  */
#line 5010 "parser.y"
                 {
  
}
#line 7032 "parser.tab.c"
    break;

  case 147: /* func_body_suite: NEWLINE INDENT Nonzero_stmt DEDENT  */
#line 5013 "parser.y"
                                          {
  ((yyval.type_attr)).linenum = ((yyvsp[-3].token_attr)).linenum;
  
}
#line 7041 "parser.tab.c"
    break;


#line 7045 "parser.tab.c"

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

#line 5020 "parser.y"


int main(int argc, char *argv[]){

  argc--, argv++;
  if(argc != 2) {
    cerr << "Error: Please run ./run.sh -i <input.py>\n";
    exit(1);
  }
  char *input_filename = argv[0];
  int verbose = atoi(argv[1]);
  if(verbose) yydebug = 1;
  yyin = fopen(input_filename, "r");
  if(yyin == NULL) {
    cerr << "Error: Input file " << input_filename << " is missing\n";
    exit(1);
  }
  yyparse();
  // yyin = fopen("test.py", "r");
    
  //   yyparse();

  int flag = 0;
  ofstream fout;
  for(auto it: vec_tables){
    if(it->table.begin() == it->table.end()){
      continue;
    }
    string scope_ = it->table.begin()->second.scopename;
    if(scope_ == "Global"){
      flag = 1;
      fout.close();
    }
    else if(scope_.substr(0, 6) == "Class@"){
      flag = 1;
      fout.close();
    }
    else if(scope_.substr(0, 9) == "Function@"){
      flag = 1;
      fout.close();
    }
    if(flag == 0){
      for(auto entry=it->table.begin(); entry!=it->table.end(); entry++){
        fout<<entry->first<<","<<entry->second.token<<","<<entry->second.type<<","<<entry->second.offset<<","<<entry->second.scopename<<","<<entry->second.line<<","<<entry->second.numargs<<","<<entry->second.argnum<<'\n';
      }
    }
    else{
      flag = 0;
      string output = scope_ + ".csv";
      // cout<<output<<endl;
      fout.open(output);
      fout<<"Lexeme"<<','<<"Token"<<','<<"Type/Return Type"<<','<<"Offset"<<','<<"Scope Name"<<','<<"Line Number"<<','<<"Number of Parameters"<<','<<"Parameter Number"<<'\n';
      for(auto entry=it->table.begin(); entry!=it->table.end(); entry++){
        fout<<entry->first<<","<<entry->second.token<<","<<entry->second.type<<","<<entry->second.offset<<","<<entry->second.scopename<<","<<entry->second.line<<","<<entry->second.numargs<<","<<entry->second.argnum<<'\n';
      }
    }
  }
  fout.close();
  

  // ofstream outputFile("output.txt");
  // if (!outputFile.is_open()) {
  //     cerr << ($1).linenum << "Failed to open the file for writing!" << endl;
  //     return 1;
  // }

  // for(long unsigned int i = 0; i < vec_tables.size(); i++){
  //   vec_tables[i]->print_sym_table(outputFile);
  //   outputFile << "\n\n---------------------\n\n";
  // }

  //   outputFile.close();

  ofstream outputFile1("3AC.txt");
  if (!outputFile1.is_open()) {
      cerr << "Failed to open the file for writing!" << endl;
      return 1;
  }

  for(long unsigned int i = 0; i < code_3ac.size(); i++){
    // vec_tables[i]->print_sym_table(outputFile1);
    if(code_3ac[i][code_3ac[i].size()-1]==':'){
      outputFile1 << code_3ac[i] << "\n";
    }
    else{
      outputFile1 << "\t" << code_3ac[i] << "\n";
    }
    
  }

    outputFile1.close();


  return 0;
}

void yyerror(const char * s)
{
  cerr << "Error in line " << yylineno << " : " << s << endl;
  exit(0);
}

