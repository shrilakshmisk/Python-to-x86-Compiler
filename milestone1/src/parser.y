
%{
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
%}

%define parse.error verbose

%union {
  struct {
    int token_num;
    char token_lex[1000];
  } token_attr;
  int nt_num;
  // char nt_lex[1000];
}

/*terminals and non terminals*/
%type<nt_num> file_input
%type<nt_num> funcdef
%type<nt_num> Opt_arrow_test
%type<nt_num> parameters
%type<nt_num> Opt_typedargslist
%type<nt_num> typedargslist
// %type<nt_num> Opt_equal_test
%type<nt_num> Multi_tfpdef
%type<nt_num> tfpdef
%type<nt_num> Opt_colon_test
%type<nt_num> stmt
%type<nt_num> simple_stmt
%type<nt_num> Multi_small_stmt
%type<nt_num> small_stmt
%type<nt_num> expr_stmt
// %type<nt_num> Var_assign
// %type<nt_num> Opt_nonzero_equal_test
// %type<nt_num> Nonzero_equal_test
// %type<nt_num> annassign
%type<nt_num> augassign
%type<nt_num> flow_stmt
%type<nt_num> Opt_test
%type<nt_num> global_stmt
%type<nt_num> Multi_name
%type<nt_num> assert_stmt
%type<nt_num> Opt_comma_test
%type<nt_num> compound_stmt
%type<nt_num> if_stmt
%type<nt_num> Multi_elif
%type<nt_num> Opt_else
%type<nt_num> while_stmt
%type<nt_num> for_stmt
%type<nt_num> suite
%type<nt_num> Nonzero_stmt
%type<nt_num> test
%type<nt_num> Opt_if_else
%type<nt_num> or_test
// %type<nt_num> Multi_and_test
%type<nt_num> and_test
// %type<nt_num> Multi_not_test
%type<nt_num> not_test
%type<nt_num> comparison
// %type<nt_num> Multi_co_expr
%type<nt_num> comp_op
%type<nt_num> expr
// %type<nt_num> Multi_xor_expr
%type<nt_num> xor_expr
// %type<nt_num> Multi_and_expr
%type<nt_num> and_expr
// %type<nt_num> Multi_shift_expr
%type<nt_num> shift_expr
// %type<nt_num> Multi_arith_expr
%type<nt_num> arith_expr
// %type<nt_num> Multi_term
%type<nt_num> term
// %type<nt_num> Multi_factor
%type<nt_num> factor
%type<nt_num> power
// %type<nt_num> Opt_double_star_factor
%type<nt_num> atom_expr
%type<nt_num> Multi_trailer
%type<nt_num> atom
%type<nt_num> Multi_string
%type<nt_num> trailer
%type<nt_num> Opt_arglist
%type<nt_num> testlist
%type<nt_num> Multi_test
%type<nt_num> classdef
%type<nt_num> Opt_round_bracket_opt_arglist
%type<nt_num> arglist
%type<nt_num> Multi_argument
%type<nt_num> argument
%type<nt_num> func_body_suite
%type<nt_num> Opt_testlist
%type<nt_num> unit
%type<nt_num> Test_dash

%token<token_attr> STRING
%token<token_attr> INDENT
%token<token_attr> DEDENT
%token<token_attr> DOUBLE_QUOTE
%token<token_attr> SINGLE_QUOTE
%token<token_attr> BREAK
%token<token_attr> CONTINUE
%token<token_attr> RETURN
%token<token_attr> GLOBAL
%token<token_attr> ASSERT
%token<token_attr> CLASS
%token<token_attr> DEF
%token<token_attr> IF
%token<token_attr> ELIF
%token<token_attr> ELSE
%token<token_attr> WHILE
%token<token_attr> FOR
%token<token_attr> IN
%token<token_attr> NONE
%token<token_attr> TRUE
%token<token_attr> FALSE
%token<token_attr> OR
%token<token_attr> AND
%token<token_attr> NOT
%token<token_attr> IS
%token<token_attr> OPEN_ROUND_BRACKET
%token<token_attr> ARROW
%token<token_attr> SEMICOLON
%token<token_attr> COLON
%token<token_attr> EQUAL
%token<token_attr> PLUS_EQUAL
%token<token_attr> MINUS_EQUAL
%token<token_attr> STAR_EQUAL
%token<token_attr> SLASH_EQUAL
%token<token_attr> PERCENTAGE_EQUAL
%token<token_attr> AND_EQUAL
%token<token_attr> OR_EQUAL
%token<token_attr> XOR_EQUAL
%token<token_attr> LEFT_SHIFT_EQUAL
%token<token_attr> RIGHT_SHIFT_EQUAL
%token<token_attr> DOUBLE_STAR_EQUAL
%token<token_attr> DOUBLE_SLASH_EQUAL
%token<token_attr> COMMA
%token<token_attr> DOT
%token<token_attr> STAR
%token<token_attr> SLASH
%token<token_attr> DOUBLE_STAR
%token<token_attr> OR_OP
%token<token_attr> PLUS
%token<token_attr> MINUS
%token<token_attr> OPEN_SQUARE_BRACKET
%token<token_attr> COLON_EQUAL
%token<token_attr> DOUBLE_EQUAL
%token<token_attr> NOT_EQUAL
%token<token_attr> LESSER_EQUAL
%token<token_attr> LESSER
%token<token_attr> GREATER_EQUAL
%token<token_attr> GREATER
%token<token_attr> XOR
%token<token_attr> AND_OP
%token<token_attr> LEFT_SHIFT
%token<token_attr> RIGHT_SHIFT
%token<token_attr> DOUBLE_SLASH
%token<token_attr> PERCENTAGE
%token<token_attr> NOT_OP
%token<token_attr> NAME
%token<token_attr> NEWLINE
%token<token_attr> NUMBER
%token<token_attr> CLOSE_ROUND_BRACKET
%token<token_attr> CLOSE_SQUARE_BRACKET


%%

/*productions*/
unit: 
file_input  {
  $$ = nodes++;
  node_entities[$$] = "unit";
  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));
  // edges[parent_entities.size()-1] = "ghfdk";
}

file_input:
%empty                    {
  // cout<<"hi\n";
  $$ = -1;
}       
| NEWLINE file_input      {
  // cout<<"hii\n";
  if($2 == -1){
    ($1).token_num = nodes++;
    temp_str = "NEWLINE";
    node_entities[($1).token_num] = temp_str;
    $$ = ($1).token_num;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "file_input";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    ($1).token_num = nodes++;
    temp_str = "NEWLINE";
    node_entities[($1).token_num] = temp_str;
    child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
}
| stmt file_input        {
  // cout<<"hiii\n";
  if($2 == -1){
    $$ = $1;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "file_input";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));


    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
} 

funcdef:
DEF NAME parameters Opt_arrow_test COLON func_body_suite      {
  $$ = nodes++;
  node_entities[$$] = "funcdef";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "DEF("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($2).token_num = nodes++;
  temp_str = "NAME("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));
  edges[parent_entities.size()-1]="def";

  if($3 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  }

  if($4 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($4, node_entities[$4]));
    edges[parent_entities.size()-1]="return type";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($5).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($5).token_lex)+")";
  // node_entities[($5).token_num] = temp_str;
  // child_entities.push_back(make_pair(($5).token_num, node_entities[($5).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($6, node_entities[$6]));
  edges[parent_entities.size()-1]="function body";

}

Opt_arrow_test:
%empty             {
  $$ = -1;
}
| ARROW test      {
  // $$ = nodes++;
  // node_entities[$$] = "Opt_arrow_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "ARROW("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));
  $$ = $2;
}

parameters:
OPEN_ROUND_BRACKET Opt_typedargslist CLOSE_ROUND_BRACKET      {
  
  

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if($2 != -1){
    $$ = nodes++;
    node_entities[$$] = "parameters";
    
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
    edges[parent_entities.size()-1]="( )";
  }

  else{
    $$ = -1;
  }


  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}

Opt_typedargslist:
%empty             {
  $$ = -1;
}
| typedargslist      {
  $$ = $1;

}

// typedargslist:
// typedargslist COMMA Tfpdef_opt_equal_test      {

  
// }
// | Tfpdef_opt_equal_test {

// }

// Tfpdef_opt_equal_test:
// tfpdef            {
//   $$ = -1;
// }
// | tfpdef EQUAL test      {
  
// }

typedargslist:
tfpdef Multi_tfpdef       {

  if($2 == -1){
    $$ = $1;
  }
  else{
    $$ = nodes++;
    node_entities[$$] = "typedargslist";

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));

      parent_entities.push_back(make_pair($$, node_entities[$$]));
      child_entities.push_back(make_pair($2, node_entities[$2]));
  }
}

// Opt_equal_test:
// %empty             {
//   $$ = -1;
// }
// | EQUAL test      {
//   $$ = nodes++;
//   node_entities[$$] = "Opt_equal_test";

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "EQUAL("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($2, node_entities[$2]));
// }


Multi_tfpdef:
%empty             {
  $$ = -1;
}
| COMMA tfpdef Multi_tfpdef      {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_tfpdef";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if($3 != -1){
    $$ = nodes++;
    node_entities[$$] = "argslist";

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  }
  else{
    $$ = $2;
  }
}

tfpdef:
NAME Opt_colon_test       {
  if($2 == -1){
    ($1).token_num = nodes++;
    temp_str = "NAME("+string((char*)($1).token_lex)+")";
    node_entities[($1).token_num] = temp_str;
    $$ = ($1).token_num;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "arg";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    ($1).token_num = nodes++;
    temp_str = "NAME("+string((char*)($1).token_lex)+")";
    node_entities[($1).token_num] = temp_str;
    child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
    edges[parent_entities.size()-1] = "parameter type";
  }

}

Opt_colon_test:
%empty             {
  $$ = -1;
}
| COLON test      {
  // $$ = nodes++;
  // node_entities[$$] = "Opt_colon_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  $$ = $2;

}

stmt:
simple_stmt      {
  $$ = $1;
}
| compound_stmt      {
  $$ = $1;
}

simple_stmt:
small_stmt Multi_small_stmt NEWLINE      {
  
  if($2 != -1){
    $$ = nodes++;
    node_entities[$$] = "simple_stmt";

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
  else{
    $$ = $1;
  }
  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++; 
  // temp_str = "NEWLINE";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

}

Multi_small_stmt:
%empty             {
  $$ = -1;
}
| SEMICOLON small_stmt Multi_small_stmt      {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_small_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "SEMICOLON("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if($3 != -1){
    $$ = nodes++;
    node_entities[$$] = "Multi_small_stmt";

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  }

  else {
    $$ = $2;
  }
}

small_stmt:
expr_stmt      {
  $$ = $1;
}
| flow_stmt      {
  $$ = $1;
}
| global_stmt      {
  $$ = $1;
}
| assert_stmt      {
  $$ = $1;
}

expr_stmt:
test COLON test EQUAL test      {
  ($4).token_num = nodes++;
  temp_str = "EQUAL("+string((char*)($4).token_lex)+")";
  node_entities[($4).token_num] = temp_str;
  $$ = ($4).token_num;
  
  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($2).token_lex)+")";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
  edges[parent_entities.size()-1]="type";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($5, node_entities[$5]));

  
}
| test COLON test         {
    $$ = nodes++;
    node_entities[$$] = "expr_stmt";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($2).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($2).token_lex)+")";
  // node_entities[($2).token_num] = temp_str;
  // child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
  edges[parent_entities.size()-1]="type";


}
| test augassign test {
  $$ = $2;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));


}
| Test_dash {
  $$ = $1;

}


Test_dash:
test EQUAL Test_dash {
  ($2).token_num = nodes++;
  temp_str = "EQUAL("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));

}
| test  {
  $$ = $1;
}



// Nonzero_equal_test:
// EQUAL test      {
//   $$ = nodes++;
//   node_entities[$$] = "Nonzero_equal_test";

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "EQUAL("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($2, node_entities[$2]));

// }
// | EQUAL test Nonzero_equal_test      {
//   $$ = nodes++;
//   node_entities[$$] = "Nonzero_equal_test";

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "EQUAL("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($2, node_entities[$2]));

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($3, node_entities[$3]));
// }

// annassign:
// COLON test EQUAL test      {
  
// }
// | COLON test

augassign:
PLUS_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "PLUS_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| MINUS_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "MINUS_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| STAR_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "STAR_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| SLASH_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "SLASH_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| PERCENTAGE_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "PERCENTAGE_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| AND_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "AND_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| OR_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "OR_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| XOR_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "XOR_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| LEFT_SHIFT_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "LEFT_SHIFT_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| RIGHT_SHIFT_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "RIGHT_SHIFT_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| DOUBLE_STAR_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "DOUBLE_STAR_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| DOUBLE_SLASH_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "augassign";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "DOUBLE_SLASH_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}

flow_stmt:      
BREAK      {
  // $$ = nodes++;
  // node_entities[$$] = "flow_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "BREAK("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}
| CONTINUE      {
  // $$ = nodes++;
  // node_entities[$$] = "flow_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "CONTINUE("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}
| RETURN Opt_test      {

  if($2 == -1){
    ($1).token_num = nodes++;
    temp_str = "RETURN("+string((char*)($1).token_lex)+")";
    node_entities[($1).token_num] = temp_str;
    $$ = ($1).token_num;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "flow_stmt";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    ($1).token_num = nodes++;
    temp_str = "RETURN("+string((char*)($1).token_lex)+")";
    node_entities[($1).token_num] = temp_str;
    child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }

  
}

Opt_test:
%empty             {
  $$ = -1;
}
| test      {
  $$ = $1;
}

global_stmt:
GLOBAL NAME Multi_name      {
  $$ = nodes++;
  node_entities[$$] = "global_stmt";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "GLOBAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($2).token_num = nodes++;
  temp_str = "NAME("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  if($3 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  }   
}

Multi_name:
%empty             {
  $$ = -1;
}
| COMMA NAME Multi_name      {
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

  if($3 != -1){
    $$ = nodes++;
    node_entities[$$] = "Multi_name";  

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    ($2).token_num = nodes++;
    temp_str = "NAME("+string((char*)($2).token_lex)+")";
    node_entities[($2).token_num] = temp_str;
    child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  } 
  else{
    ($2).token_num = nodes++;
    temp_str = "NAME("+string((char*)($2).token_lex)+")";
    node_entities[($2).token_num] = temp_str;
    $$ = ($2).token_num;
  }
}

assert_stmt:
ASSERT test Opt_comma_test      {
  $$ = nodes++;
  node_entities[$$] = "assert_stmt";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "ASSERT("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2])); 
  
  if($3 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  } 
}

Opt_comma_test:
%empty             {
  $$ = -1;
}
| COMMA test       {
  // $$ = nodes++;
  // node_entities[$$] = "Opt_comma_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2])); 

  $$ = $2;
}

compound_stmt:
if_stmt      {
  $$ = $1; 
}
| while_stmt      {
  $$ = $1; 
}
| for_stmt      {
  $$ = $1; 
}
| funcdef      {
  $$ = $1;
}
| classdef      {
  $$ = $1;
}

if_stmt:
IF test COLON suite Multi_elif Opt_else      {
  $$ = nodes++;
  node_entities[$$] = "if_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "IF("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
  edges[parent_entities.size()-1]="if";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($4, node_entities[$4]));
  edges[parent_entities.size()-1]="then";

  if($5 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($5, node_entities[$5]));
  }

  if($6 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($6, node_entities[$6]));
    edges[parent_entities.size()-1]="else";
  }
}

Multi_elif:
%empty             {
  $$ = -1;
}
| ELIF test COLON suite Multi_elif      {
  $$ = nodes++;
  node_entities[$$] = "Multi_elif";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "ELIF("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
  edges[parent_entities.size()-1]="elif";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($4, node_entities[$4]));
  edges[parent_entities.size()-1]="then";

  if($5 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($5, node_entities[$5]));
  }
}

Opt_else:
%empty             {
  $$ = -1;
}
| ELSE COLON suite      {
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
  $$ = $3;

}

while_stmt:
WHILE test COLON suite Opt_else      {
  $$ = nodes++;
  node_entities[$$] = "while_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "WHILE("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
  edges[parent_entities.size()-1] = "while";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($4, node_entities[$4]));
  edges[parent_entities.size()-1] = "body";

  if($5 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($5, node_entities[$5]));
  }
}

for_stmt:
FOR expr IN testlist COLON suite Opt_else       {
  $$ = nodes++;
  node_entities[$$] = "for_stmt";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "FOR("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
  edges[parent_entities.size()-1] = "for";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "IN("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($4, node_entities[$4]));
  edges[parent_entities.size()-1] = "in";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($5).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($5).token_lex)+")";
  // node_entities[($5).token_num] = temp_str;
  // child_entities.push_back(make_pair(($5).token_num, node_entities[($5).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($6, node_entities[$6]));
  edges[parent_entities.size()-1] = "body";

  if($7 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($7, node_entities[$7]));
  }
  
}


suite:
simple_stmt      {
  $$ = $1;
}
| NEWLINE INDENT Nonzero_stmt DEDENT      {
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

  $$ = $3;

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($4).token_num = nodes++; 
  // temp_str = "DEDENT";
  // node_entities[($4).token_num] = temp_str;
  // child_entities.push_back(make_pair(($4).token_num, node_entities[($4).token_num]));
}

Nonzero_stmt:
stmt      {
  $$ = $1;
}
| stmt Nonzero_stmt      {
  $$ = nodes++;
  node_entities[$$] = "stmts";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));

}

test:
or_test Opt_if_else      {
  if($2 == -1){
    $$ = $1;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "test";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));


    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
}

Opt_if_else:
%empty             {
  $$ = -1;
}
| IF or_test ELSE test      {
  $$ = nodes++;
  node_entities[$$] = "Opt_if_else";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "IF("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($3).token_num = nodes++;
  temp_str = "ELSE("+string((char*)($3).token_lex)+")";
  node_entities[($3).token_num] = temp_str;
  child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($4, node_entities[$4]));
}

or_test:
and_test       {
  $$ = $1;
}
| or_test OR and_test {
  ($2).token_num = nodes++;
  temp_str = "OR("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
  

}

// Multi_and_test:
// %empty             {
//   $$ = -1;
// }
// | OR and_test Multi_and_test      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_and_test";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "OR("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

and_test:
not_test      {
  $$ = $1;

}
| and_test AND not_test {
  ($2).token_num = nodes++;
  temp_str = "AND("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}

// Multi_not_test:
// %empty             {
//   $$ = -1;
// }
// | AND not_test Multi_not_test      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_not_test";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "AND("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

not_test:
NOT not_test      {
  // $$ = nodes++;
  // node_entities[$$] = "not_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "NOT("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  $$ = ($1).token_num;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
}
| comparison      {
  $$ = $1;

}

comparison:
expr       {
  $$ = $1;
  

}
| comparison comp_op expr {

  $$ = $2;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));

}

// Multi_co_expr:
// %empty             {
//   $$ = -1;
// }
// | comp_op expr Multi_co_expr      {
//   $$ = nodes++;
//   node_entities[$$] = "Multi_co_expr";

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($1, node_entities[$1]));

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($2, node_entities[$2]));

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

comp_op:
LESSER      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "LESSER("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| GREATER      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "GREATER("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}      
| DOUBLE_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "DOUBLE_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| GREATER_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "GREATER_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| LESSER_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "LESSER_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| NOT_EQUAL      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "NOT_EQUAL("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| IN      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "IN("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;
}
| NOT IN      {
  $$ = nodes++;
  node_entities[$$] = "comp_op";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "NOT("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($2).token_num = nodes++;
  temp_str = "IN("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));
}
| IS      {
  // $$ = nodes++;
  // node_entities[$$] = "comp_op";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "IS("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}
| IS NOT      {
  $$ = nodes++;
  node_entities[$$] = "comp_op";

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "IS("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($2).token_num = nodes++;
  temp_str = "NOT("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));
}

expr:
xor_expr      {
  $$ = $1;
}
| expr OR_OP xor_expr {
  ($2).token_num = nodes++;
  temp_str = "BITWISE_OR("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}

// Multi_xor_expr:
// %empty             {
//   $$ = -1;
// }
// | OR_OP xor_expr Multi_xor_expr      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_xor_expr";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "OR_OP("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($2, node_entities[$2]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

xor_expr:
and_expr    {
  $$ = $1;
  
}
| xor_expr XOR and_expr {
  ($2).token_num = nodes++;
  temp_str = "BITWISE_XOR("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}

// Multi_and_expr:
// %empty             {
//   $$ = -1;
// }
// | XOR and_expr Multi_and_expr      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_and_expr";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "XOR("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

and_expr:
shift_expr    {
  $$ = $1;
  
}
| and_expr AND_OP shift_expr {
  ($2).token_num = nodes++;
  temp_str = "BITWISE_AND("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}

// Multi_shift_expr:
// %empty             {
//   $$ = -1;
// }
// | AND_OP shift_expr Multi_shift_expr      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_shift_expr";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "AND_OP("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

shift_expr:
arith_expr     {
  $$ = $1;
}
| shift_expr LEFT_SHIFT arith_expr {
  ($2).token_num = nodes++;
  temp_str = "LEFT_SHIFT("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}
| shift_expr RIGHT_SHIFT arith_expr {
  ($2).token_num = nodes++;
  temp_str = "RIGHT_SHIFT("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));

}

// Multi_arith_expr:
// %empty             {
//   $$ = -1;
// }
// | LEFT_SHIFT arith_expr Multi_arith_expr      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_arith_expr";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "LEFT_SHIFT("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }
// | RIGHT_SHIFT arith_expr Multi_arith_expr      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_arith_expr";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "RIGHT_SHIFT("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

arith_expr:
term     {
  $$ = $1;

}
| arith_expr PLUS term {
  ($2).token_num = nodes++;
  temp_str = "PLUS("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}
| arith_expr MINUS term {
  ($2).token_num = nodes++;
  temp_str = "MINUS("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));

}

// Multi_term:
// %empty             {
//   $$ = -1;
// }
// | PLUS term Multi_term      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_term";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   // ($1).token_num = nodes++;
//   // temp_str = "PLUS("+string((char*)($1).token_lex)+")";
//   // node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   // child_entities.push_back(make_pair($2, node_entities[$2]));

//   // if($3 != -1){
//   //   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   //   child_entities.push_back(make_pair($3, node_entities[$3]));
//   // }

//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_term";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "PLUS("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   $$ = ($1).token_num;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   if($3 == -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
  
//   if($3 != -1){
//     pair<int, string> temp_pa
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
  

  
  

// }
// | MINUS term Multi_term      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_term";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "MINUS("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

term:
factor       {
  $$ = $1;
}
| term STAR factor {
  ($2).token_num = nodes++;
  temp_str = "STAR("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}
| term SLASH factor {
  ($2).token_num = nodes++;
  temp_str = "SLASH("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));

}
| term PERCENTAGE factor {
  ($2).token_num = nodes++;
  temp_str = "PERCENTAGE("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));

}
| term DOUBLE_SLASH factor {
  ($2).token_num = nodes++;
  temp_str = "DOUBLE_SLASH("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));

}



// Multi_factor:
// %empty             {
//   $$ = -1;
// }
// | STAR factor Multi_factor      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_factor";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "STAR("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }
// | SLASH factor Multi_factor      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_factor";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "SLASH("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }
// | PERCENTAGE factor Multi_factor      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_factor";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "PERCENTAGE("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }      
// | DOUBLE_SLASH factor Multi_factor      {
//   // $$ = nodes++;
//   // node_entities[$$] = "Multi_factor";

//   // parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "DOUBLE_SLASH("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
//   $$ = ($1).token_num;

//   if($3 != -1){
//     parent_entities.push_back(make_pair($3, node_entities[$3]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }
//   else{
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($2, node_entities[$2]));
//   }

//   if($3 != -1){
//     parent_entities.push_back(make_pair($$, node_entities[$$]));
//     child_entities.push_back(make_pair($3, node_entities[$3]));
//   }
// }

factor:
PLUS factor      {
  // $$ = nodes++;
  // node_entities[$$] = "factor";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "PLUS("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
}      
| MINUS factor      {
  // $$ = nodes++;
  // node_entities[$$] = "factor";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "MINUS("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
}
| NOT_OP factor      {
  // $$ = nodes++;
  // node_entities[$$] = "factor";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "BITWISE_NOT("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));
  $$ = ($1).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
}
| power      {
  $$ = $1;
}
      
power:
atom_expr       {
  $$ = $1;
}
| atom_expr DOUBLE_STAR factor {
  ($2).token_num = nodes++;
  temp_str = "DOUBLE_STAR("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  $$ = ($2).token_num;

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));
}

// Opt_double_star_factor:
// %empty             {
//   $$ = -1;
// }
// | DOUBLE_STAR factor      {
//   $$ = nodes++;
//   node_entities[$$] = "Opt_double_star_factor";

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   ($1).token_num = nodes++;
//   temp_str = "DOUBLE_STAR("+string((char*)($1).token_lex)+")";
//   node_entities[($1).token_num] = temp_str;
//   child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

//   parent_entities.push_back(make_pair($$, node_entities[$$]));
//   child_entities.push_back(make_pair($2, node_entities[$2]));
// }

atom_expr:
atom Multi_trailer      {
  if($2 == -1){
    $$ = $1;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "atom_expr";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));


    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
}

Multi_trailer:
%empty             {
  $$ = -1;
}
| trailer Multi_trailer      {

  if($2 == -1){
    $$ = $1;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "Multi_trailer";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));


    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
}

atom:
OPEN_ROUND_BRACKET Opt_test CLOSE_ROUND_BRACKET      {
  $$ = nodes++;
  node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if($2 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
    edges[parent_entities.size()-1] = "( )";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
| OPEN_SQUARE_BRACKET Opt_testlist CLOSE_SQUARE_BRACKET      {
  $$ = nodes++;
  node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_SQUARE_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if($2 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
    edges[parent_entities.size()-1] = "[ ]";

  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_SQUARE_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
| NAME      {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "NAME("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}
| NUMBER      {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "NUMBER("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}
| STRING Multi_string     {
    if($2 != -1){
      $$ = nodes++;
      node_entities[$$] = "atom";

      parent_entities.push_back(make_pair($$, node_entities[$$]));
      ($1).token_num = nodes++;
      temp_str = "STRING("+string((char*)($1).token_lex)+")";
      node_entities[($1).token_num] = temp_str;
      child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

      parent_entities.push_back(make_pair($$, node_entities[$$]));
      child_entities.push_back(make_pair($2, node_entities[$2]));
    }
    else{
      ($1).token_num = nodes++;
      temp_str = "STRING("+string((char*)($1).token_lex)+")";
      node_entities[($1).token_num] = temp_str;
      $$ = ($1).token_num;
    }
}
| NONE      {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "NONE("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}
| TRUE      {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "TRUE("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}
| FALSE      {
  // $$ = nodes++;
  // node_entities[$$] = "atom";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($1).token_num = nodes++;
  temp_str = "FALSE("+string((char*)($1).token_lex)+")";
  node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  $$ = ($1).token_num;
}

Opt_testlist:
%empty             {
  $$ = -1;
}
| testlist      {
  $$ = $1;
}


Multi_string:
%empty      {
  // // $$ = nodes++;
  // // node_entities[$$] = "Nonzero_string";

  // // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "STRING("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // $$ = ($1).token_num;
  $$ = -1;
}
| STRING Multi_string      {

  if($2 != -1){
    $$ = nodes++;
    node_entities[$$] = "Multi_string";

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    ($1).token_num = nodes++;
    temp_str = "STRING("+string((char*)($1).token_lex)+")";
    node_entities[($1).token_num] = temp_str;
    child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
  else{
    ($1).token_num = nodes++;
    temp_str = "STRING("+string((char*)($1).token_lex)+")";
    node_entities[($1).token_num] = temp_str;
    $$ = ($1).token_num;
  }
  
}

trailer:
OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET      {
  $$ = nodes++;
  node_entities[$$] = "trailer";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if($2 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
    edges[parent_entities.size()-1] = "( )";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
| OPEN_SQUARE_BRACKET testlist CLOSE_SQUARE_BRACKET      {
  $$ = nodes++;
  node_entities[$$] = "trailer";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_SQUARE_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($2, node_entities[$2]));
  edges[parent_entities.size()-1] = "[ ]";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_SQUARE_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}
| DOT NAME      {
  $$ = nodes++;
  node_entities[$$] = "trailer";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "DOT("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($2).token_num = nodes++;
  temp_str = "NAME("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  edges[parent_entities.size()-1] = ".";
}

Opt_arglist:
%empty             {
  $$ = -1;
}
| arglist      {
  $$ = $1;
}

testlist:
test Multi_test       {
  if($2 == -1){
    $$ = $1;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "testlist";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));


    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }

}

Multi_test:
%empty             {
  $$ = -1;
}
| COMMA test Multi_test      {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_test";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if($3 != -1){
    $$ = nodes++;
    node_entities[$$] = "Multi_test";

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  }
  else{
    $$ = $2;
  }

}

classdef:
CLASS NAME Opt_round_bracket_opt_arglist COLON suite      {
  $$ = nodes++;
  node_entities[$$] = "classdef";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "CLASS("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($2).token_num = nodes++;
  temp_str = "NAME("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));
  edges[parent_entities.size()-1] = "class";

  if($3 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($4).token_num = nodes++;
  // temp_str = "COLON("+string((char*)($4).token_lex)+")";
  // node_entities[($4).token_num] = temp_str;
  // child_entities.push_back(make_pair(($4).token_num, node_entities[($4).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($5, node_entities[$5]));
  edges[parent_entities.size()-1] = "class body";

}

Opt_round_bracket_opt_arglist:
%empty             {
  $$ = -1;
}
| OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET      {
  $$ = nodes++;
  node_entities[$$] = "class parameters";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "OPEN_ROUND_BRACKET("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  if($2 != -1){
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
    edges[parent_entities.size()-1] = "( )";
  }

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($3).token_num = nodes++;
  // temp_str = "CLOSE_ROUND_BRACKET("+string((char*)($3).token_lex)+")";
  // node_entities[($3).token_num] = temp_str;
  // child_entities.push_back(make_pair(($3).token_num, node_entities[($3).token_num]));
}

arglist:
argument Multi_argument       {
  if($2 == -1){
    $$ = $1;
  }

  else{
    $$ = nodes++;
    node_entities[$$] = "arglist";
    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($1, node_entities[$1]));


    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));
  }
}

Multi_argument:
%empty             {
  $$ = -1;
}
| COMMA argument Multi_argument      {
  // $$ = nodes++;
  // node_entities[$$] = "Multi_argument";

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($1).token_num = nodes++;
  // temp_str = "COMMA("+string((char*)($1).token_lex)+")";
  // node_entities[($1).token_num] = temp_str;
  // child_entities.push_back(make_pair(($1).token_num, node_entities[($1).token_num]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($2, node_entities[$2]));

  if($3 != -1){
    $$ = nodes++;
    node_entities[$$] = "Multi_argument";

    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($2, node_entities[$2]));


    parent_entities.push_back(make_pair($$, node_entities[$$]));
    child_entities.push_back(make_pair($3, node_entities[$3]));
  }
  else{
    $$ = $2;
  }
}

argument:
test      {
  $$ = $1;
}
| test EQUAL test      {
  $$ = nodes++;
  node_entities[$$] = "argument";
  
  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($1, node_entities[$1]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  ($2).token_num = nodes++;
  temp_str = "EQUAL("+string((char*)($2).token_lex)+")";
  node_entities[($2).token_num] = temp_str;
  child_entities.push_back(make_pair(($2).token_num, node_entities[($2).token_num]));

  parent_entities.push_back(make_pair($$, node_entities[$$]));
  child_entities.push_back(make_pair($3, node_entities[$3]));


}

func_body_suite:
simple_stmt      {
  $$ = $1;

}
| NEWLINE INDENT Nonzero_stmt DEDENT      {
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

  $$ = $3;

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // child_entities.push_back(make_pair($3, node_entities[$3]));

  // parent_entities.push_back(make_pair($$, node_entities[$$]));
  // ($4).token_num = nodes++; 
  // temp_str = "DEDENT";
  // node_entities[($4).token_num] = temp_str;
  // child_entities.push_back(make_pair(($4).token_num, node_entities[($4).token_num]));
}

%%

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
