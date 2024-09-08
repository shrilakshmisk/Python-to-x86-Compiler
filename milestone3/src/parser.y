%{
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
  string nl = "\n# ";

  // vector<string> testlist_types_vec;
  string func_return_type;
  int isreturning = 0;
  int func_stack_offset = 0;
  // map <string, int> class_size;
  int class_flag = 0; 
  map <string, Symbol_Table*> class_symbol_tables;
  string recent_class;
  unordered_set <string> all_types = {"int", "float", "str", "bool", "list@int", "list@float", "list@str", "list@bool"};
  stack <string> breakjumps;
  stack <string> continuejumps;
  vector <string> code_3ac; 
  vector <string> code_x86 = {".section\t.rodata", ".LC0:", ".string\t\"%ld\\n\"" , ".LC1:", ".string\t\"%s\\n\"", ".globl	main", ".text"};
  map <string, string> child_to_parent_classes;
  stack<string> if_scopes;
  string range_start, range_end;
  int add_offset = 0;
  map <string, string> funcrbp;
  map <string, string> classrbp;
  int string_count = 5;



  // all_types.insert("int");
  // all_types.insert("float");
  // all_types.insert("str");
  // all_types.insert("bool");

  int dummy_num = 0;

  string dummy(){
    string s = to_string(dummy_num);
    dummy_num++;
    return s;
  }


  int type_size(string s)
    {
      // have not handled size of an object
      int islist = 0;
      if(s.length() >= 5){
        string t = s.substr(0,5);
        if(t == "list@") islist = 1;
      }

      if(!islist){
        if(s == "int") return 8;
        else if(s == "float") return 8;
        else if(s == "bool") return 8;
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
    // if (child_to_parent_classes.find(b) != child_to_parent_classes.end()) {
    //     if(a == child_to_parent_classes[b]){
    //       return 1;
    //     }
        
    // }
    // return 0;

    while (child_to_parent_classes.find(b) != child_to_parent_classes.end()){
      if(a == child_to_parent_classes[b]){
        return 1;
      }
      else{
        b = child_to_parent_classes[b];
      }
    }
    return 0;
  }
}

void gen(string line_3ac){
  code_3ac.push_back(line_3ac);
}

void x86(string line_x86){
  code_x86.push_back(line_x86);
}

// }
long long t_count = 0;
long long L_count = 0;

string t_new(){
  string temp_var = "#t"+to_string(t_count++);
  return temp_var;
}
string L_new(){
  string temp_var = ".L"+to_string(L_count++);
  return temp_var;
}

%}

%define parse.error verbose
// %define api.value.type

%union {
  struct {
    int token_num;
    char token_lex[1000];
    char token_type[1000];
    int linenum;
  } token_attr;
  struct {
    int nt_nim;
    char lexeme[1000];
    int size;
    int func_numargs;
    char type[1000];
    int isname;
    int isfunccall;
    char lefthandside[1000];
    char gotoname[1000];
    char gotonext[1000];
    int isindexed;
    char indextype[1000];
    char listoffsettemp[1000];
    char temp[1000];
    char listhead[1000];
    char tempdot[1000];
    char tempsquare[1000];
    char tempround [1000];
    char objoffset[1000];
    char objhead[1000];
    int isdotted;
    int listsize;
    int linenum;

  } type_attr;
}

/*terminals and non terminals*/
%type<type_attr> file_input
%type<type_attr> funcdef
// %type<type_attr> Opt_arrow_test
%type<type_attr> parameters
// %type<type_attr> Opt_typedargslist
%type<type_attr> typedargslist
// %type<type_attr> Opt_equal_test
%type<type_attr> Multi_tfpdef
%type<type_attr> tfpdef
// %type<type_attr> Opt_colon_test
%type<type_attr> stmt
%type<type_attr> simple_stmt
%type<type_attr> Multi_small_stmt
%type<type_attr> small_stmt
%type<type_attr> expr_stmt
// %type<type_attr> Var_assign
// %type<type_attr> Opt_nonzero_equal_test
// %type<type_attr> Nonzero_equal_test
// %type<type_attr> annassign
// %type<type_attr> augassign
%type<type_attr> flow_stmt
%type<type_attr> Opt_test
%type<type_attr> global_stmt
%type<type_attr> Multi_name
// %type<type_attr> assert_stmt
// %type<type_attr> Opt_comma_test
%type<type_attr> compound_stmt
%type<type_attr> if_stmt
%type<type_attr> Multi_elif
%type<type_attr> Opt_else
%type<type_attr> while_stmt
%type<type_attr> for_stmt
%type<type_attr> suite
%type<type_attr> Nonzero_stmt
%type<type_attr> test
// %type<type_attr> Opt_if_else
%type<type_attr> or_test
// %type<type_attr> Multi_and_test
%type<type_attr> and_test
// %type<type_attr> Multi_not_test
%type<type_attr> not_test
%type<type_attr> comparison
// %type<type_attr> Multi_co_expr
// %type<type_attr> comp_op
%type<type_attr> expr
// %type<type_attr> Multi_xor_expr
%type<type_attr> xor_expr
// %type<type_attr> Multi_and_expr
%type<type_attr> and_expr
// %type<type_attr> Multi_shift_expr
%type<type_attr> shift_expr
// %type<type_attr> Multi_arith_expr
%type<type_attr> arith_expr
// %type<type_attr> Multi_term
%type<type_attr> term
// %type<type_attr> Multi_factor
%type<type_attr> factor
%type<type_attr> power
// %type<type_attr> Opt_double_star_factor
%type<type_attr> atom_expr
%type<type_attr> Multi_trailer
%type<type_attr> atom
// %type<type_attr> Multi_string
%type<type_attr> trailer
%type<type_attr> Opt_arglist
%type<type_attr> testlist
%type<type_attr> Multi_test
%type<type_attr> classdef
// %type<type_attr> Opt_round_bracket_opt_arglist
%type<type_attr> arglist
%type<type_attr> Multi_argument
%type<type_attr> argument
%type<type_attr> func_body_suite
// %type<type_attr> Opt_testlist
%type<type_attr> unit
// %type<type_attr> Test_dash
// %type<type_attr> Lhs
// %type<type_attr> Rhs
%type<type_attr> Lhs_init
%type<type_attr> Lhs_noninit
%type<type_attr> dummy_if_suit
%type<type_attr> dummyifstmt
%type<type_attr> dummyelifstmt
%type<type_attr> dummyWhilestmt
%type<type_attr> dummyWhilestmt1
%type<type_attr> dummy_for_stmt

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
// %token<token_attr> SELF
%token<token_attr> NEWLINE
%token<token_attr> NUMBER
%token<token_attr> CLOSE_ROUND_BRACKET
%token<token_attr> CLOSE_SQUARE_BRACKET


%%

/*productions*/
unit: 
file_input  {
  
}

file_input:
%empty                     {
  
}       
| NEWLINE file_input      {
  
}
| stmt file_input        {
  
} 

funcdef:
DEF NAME parameters COLON {
    if(recent_class == ""){
      gen(to_string(($2).token_lex) + ":");
      x86("\n# beginfunc " + to_string(($2).token_lex));
      x86(to_string(($2).token_lex) + ":");
    }
    else{
      gen(recent_class + "." + to_string(($2).token_lex) + ":");
      x86("\n# beginfunc " + recent_class + "." + to_string(($2).token_lex));
      x86(recent_class + "." + to_string(($2).token_lex) + ":");
    }
    gen("beginfunc");
    gen("push %rbp");
    gen("%rbp = %rsp");
    x86("pushq\t%rbp");
    x86("movq\t%rsp,\t%rbp");
    x86("pushq\t%rbx");
		x86("pushq\t%rdi");
		x86("pushq\t%rsi");
		x86("pushq\t%r12");
		x86("pushq\t%r13");
		x86("pushq\t%r14");
		x86("pushq\t%r15");
    func_stack_offset = (int) code_x86.size();
    
    
    // gen()
    // string none = "None";
    // strcpy(($$).lexeme, none.c_str());
    func_return_type = "None";
    if(to_string(($2).token_lex) == "__init__"){
      func_return_type = recent_class;
    }
    // int n_arg = ($3).func_numargs;
    // ($$).func_numargs = ($3).func_numargs;
    // int n_arg = ($$).func_numargs;
    Symbol_Table_Entry* func_entry = curr_table->make_entry(to_string(($2).token_lex), "Function", func_return_type, offset, curr_scope, ($1).linenum, -1, -1, ($3).func_numargs, 1);
    offset += 0;

    table_stack.push(curr_table);
    curr_table = new Symbol_Table(curr_table);
    (func_entry->update_entry)(curr_table);
    vec_tables.push_back(curr_table);
    scope_stack.push(curr_scope);
    offset_stack.push(offset);
    if(recent_class == "")
    curr_scope = "Function@" + to_string(($2).token_lex);
    else
    curr_scope = "Function@" + to_string(($2).token_lex) + "." + recent_class;
    offset = 0;
    for(int i = 0; i< (int)func_param_vec.size(); i++){
      curr_table->make_entry(func_param_vec[i].first, "Function_Parameter", func_param_vec[i].second, offset, curr_scope, ($1).linenum, i+1, -1, ($3).func_numargs, 1);
      // string temp_ = t_new();
      string rbp_offset = to_string(offset + 16);
      gen(func_param_vec[i].first + " = " + rbp_offset + "(%rbp)");
      gen("sub %rsp " + to_string(type_size(func_param_vec[i].second)));
      gen(to_string(-(offset + type_size(func_param_vec[i].second))) + "(%rbp) = " + func_param_vec[i].first);
      // gen(func_param_vec[i].first + " = " + temp_);
      funcrbp[func_param_vec[i].first] = rbp_offset;
      offset+= type_size(func_param_vec[i].second);
    }

    // for(int i = 0; i < (int)func_param_vec.size(); i++){
      
    // }
    

}

func_body_suite      {
  ($$).linenum = ($1).linenum;
  // entry needed 
  // table new - func_body_suite
  //  main() and __init__() will be here
 //// should check return type 

  // if(isreturnin none.c_str());
  int stack_offset = 8*((int)funcrbp.size() - (int)func_param_vec.size());
  if(stack_offset % 16 == 0) {
    stack_offset += 8;
  }
  string functype = "None";
  if(to_string(($2).token_lex) == "__init__"){
    functype = recent_class;
  }
  strcpy(($$).type, functype.c_str());


  if(to_string(($2).token_lex) == "main"){
    gen("exit");
    x86("\n# end main");
    x86("movq\t$60,\t%rax");
		x86("xor\t\t%rdi,\t%rdi");
		x86("syscall");
  }
  else{
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
    gen("endfunc");
    x86("\n# endfunc" + to_string(($2).token_lex));
    string func_name = curr_scope.substr(9);
    x86("jmp\t\t" + func_name + "_.end");
    // x86("add\t\t$" + to_string(stack_offset) + ",\t%rsp");
    // x86("popq\t%r15");
    // x86("popq\t%r14");
    // x86("popq\t%r13");
    // x86("popq\t%r12");
    // x86("popq\t%rsi");
    // x86("popq\t%rdi");
    // x86("popq\t%rbx");
    // x86("popq\t%rbp");
    // x86("ret");

    x86(func_name + "_.end:");
    x86("add\t\t$" + to_string(stack_offset) + ",\t%rsp");
    x86("popq\t%r15");
    x86("popq\t%r14");
    x86("popq\t%r13");
    x86("popq\t%r12");
    x86("popq\t%rsi");
    x86("popq\t%rdi");
    x86("popq\t%rbx");
    x86("popq\t%rbp");
    x86("ret");
    
    
  }
  


  curr_table = table_stack.top(); 
  table_stack.pop();
  curr_scope = scope_stack.top(); 
  scope_stack.pop();
  offset = offset_stack.top(); 
  offset_stack.pop();
  isreturning = 0;
  func_return_type = "";
  
  add_offset = 0;
  code_x86.insert(code_x86.begin() + func_stack_offset, "sub\t\t$" + to_string(stack_offset) + ",\t%rsp");
  func_param_vec.clear();
  funcrbp.clear();
  func_stack_offset = 0;
}
| DEF NAME parameters ARROW test COLON {
  if(recent_class == ""){
    gen(to_string(($2).token_lex) + ":");
    x86("\n# beginfunc " + to_string(($2).token_lex));
    x86(to_string(($2).token_lex) + ":");
  }
  else{
    gen(recent_class + "." + to_string(($2).token_lex) + ":");
    x86("\n# beginfunc " + recent_class + "." + to_string(($2).token_lex));
    x86(recent_class + "." + to_string(($2).token_lex) + ":");
  }
  gen("beginfunc");
  gen("push %rbp");
  gen("%rbp = %rsp");
  x86("pushq\t%rbp");
  x86("movq\t%rsp,\t%rbp");
  x86("pushq\t%rbx");
  x86("pushq\t%rdi");
  x86("pushq\t%rsi");
  x86("pushq\t%r12");
  x86("pushq\t%r13");
  x86("pushq\t%r14");
  x86("pushq\t%r15");
  func_stack_offset = (int) code_x86.size();
  // for(int i = 0; i < (int)func_param_vec.size(); i++){
  //     string temp_ = t_new();
  //     gen(temp_ + " = popparam");
  //     gen(func_param_vec[i].first + " = " + temp_);
  // }
string functype = to_string(($5).lexeme);
// strcpy(($$).lexeme, ($5).lexeme); //this is return type
func_return_type = to_string(($5).lexeme);
// ($$).func_numargs = ($3).func_numargs;
// int n_arg = ($3).func_numargs;
Symbol_Table_Entry* func_entry = curr_table->make_entry(to_string(($2).token_lex), "Function", to_string(($5).lexeme), offset, curr_scope, ($1).linenum, -1, -1, ($3).func_numargs, 1);
offset += 0;
table_stack.push(curr_table);
curr_table = new Symbol_Table(curr_table);
func_entry->update_entry(curr_table);
vec_tables.push_back(curr_table);
scope_stack.push(curr_scope);
offset_stack.push(offset);
if(recent_class == "")
curr_scope = "Function@" + to_string(($2).token_lex);
else
curr_scope = "Function@" + to_string(($2).token_lex) + "." + recent_class;
int new_offset = 0;
offset = new_offset;

for(int i = 0; i< (int)func_param_vec.size(); i++){
  curr_table->make_entry(func_param_vec[i].first, "Function_Parameter", func_param_vec[i].second, offset, curr_scope, ($1).linenum, i+1, -1, ($3).func_numargs, 1);
  // string temp_ = t_new();
  string rbp_offset = to_string(offset + 16);
  gen(func_param_vec[i].first + " = " + rbp_offset + "(%rbp)");
  gen("sub %rsp " + to_string(type_size(func_param_vec[i].second)));
  gen(to_string(-(offset + type_size(func_param_vec[i].second))) + "(%rbp) = " + func_param_vec[i].first);
  // gen(func_param_vec[i].first + " = " + temp_);
  funcrbp[func_param_vec[i].first] = rbp_offset;
  offset+= type_size(func_param_vec[i].second);
}


}


func_body_suite      {
  ($$).linenum = ($1).linenum;
  // make_entry needed - test is return type
  // table new - func_body_suite
  int stack_offset = 8*((int)funcrbp.size() - (int)func_param_vec.size());
  if(stack_offset % 16 == 0) {
    stack_offset += 8;
  }
  string functype = to_string(($5).lexeme);
  strcpy(($$).type, functype.c_str());
  if(isreturning == 0 && func_return_type!="None"){
    cerr << ($1).linenum << ": Error: wrong return type 'None', expected return type '"<< func_return_type <<"'\n";
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
    x86("\n# endfunc" + to_string(($2).token_lex));
    string func_name = curr_scope.substr(9);
    x86("jmp\t\t" + func_name + "_.end");
    // x86("add\t\t$" + to_string(stack_offset) + ",\t%rsp");
    // x86("popq\t%r15");
		// x86("popq\t%r14");
		// x86("popq\t%r13");
		// x86("popq\t%r12");
		// x86("popq\t%rsi");
		// x86("popq\t%rdi");
		// x86("popq\t%rbx");
		// x86("popq\t%rbp");
		// x86("ret");
    
      
  }
  string func_name = curr_scope.substr(9);
  x86(func_name + "_.end:");
  x86("add\t\t$" + to_string(stack_offset) + ",\t%rsp");
  x86("popq\t%r15");
  x86("popq\t%r14");
  x86("popq\t%r13");
  x86("popq\t%r12");
  x86("popq\t%rsi");
  x86("popq\t%rdi");
  x86("popq\t%rbx");
  x86("popq\t%rbp");
  x86("ret");

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
  code_x86.insert(code_x86.begin() + func_stack_offset, "sub\t\t$" + to_string(stack_offset) + ",\t%rsp");

  func_param_vec.clear();
  funcrbp.clear();
  func_stack_offset = 0;

}

parameters:
OPEN_ROUND_BRACKET CLOSE_ROUND_BRACKET      {
  ($$).linenum = ($1).linenum;
  ($$).func_numargs = 0;
  // function defn args are here 
  // params are in symbol table of function with argnum
}
| OPEN_ROUND_BRACKET typedargslist CLOSE_ROUND_BRACKET      {
  ($$).linenum = ($1).linenum;
  ($$).func_numargs = ($2).func_numargs;
  // function defn args are here 
  // params are in symbol table of function with argnum
}

typedargslist:
tfpdef Multi_tfpdef       {
   ($$).func_numargs = 1 + ($2).func_numargs;

}


Multi_tfpdef:
%empty             {
  ($$).func_numargs = 0;
}
| COMMA tfpdef Multi_tfpdef      {
  ($$).linenum = ($1).linenum;
  ($$).func_numargs = 1 + ($3).func_numargs;
}

tfpdef:
NAME COLON test     {
  ($$).linenum = ($1).linenum;
  func_param_vec.push_back({to_string(($1).token_lex), to_string(($3).lexeme)});
  // these are function definition arguments names. should they have an make_entry in symbol table?
  // enter this in function symbol table
}
| NAME {
  ($$).linenum = ($1).linenum;
  if(to_string(($1).token_lex) != "self"){
    cerr << ($1).linenum << ": Error: type hint for parameter '" << to_string(($1).token_lex) << "' not given" << "\n";
    exit(0);
  }
  func_param_vec.push_back({to_string(($1).token_lex), recent_class});

}


stmt:
simple_stmt      {
  
}
| compound_stmt      {
  
}

simple_stmt:
small_stmt Multi_small_stmt NEWLINE      {
  
}

Multi_small_stmt:
%empty             {
  
}
| SEMICOLON small_stmt Multi_small_stmt      {
  ($$).linenum = ($1).linenum;
  
}

small_stmt:
expr_stmt      {
  
}
| flow_stmt      {
  
}
| global_stmt      {
  
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


expr_stmt:
Lhs_init COLON test EQUAL test    {
  ($$).linenum = ($1).linenum;


  string type1 = to_string(($3).lexeme);
  string type2 = to_string(($5).type);

  if(type1 == type2){
      // no typecasting required
      strcpy(($$).type, ($1).type);
  }
  else{
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($5).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($5).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($5).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($5).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($5).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($5).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($5).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t\t$0,\t%rdx");
      x86("jne\t\t1f"); // output 1
      x86("movq\t$0,\t%rdx");
      x86("jmp\t\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");

      strcpy(($5).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($5).temp));
      strcpy(($5).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to float
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($5).temp));
      strcpy(($5).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid assignment for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }




  
  if(to_string(($1).lexeme).substr(0,5) == "self."){
    if(curr_scope == "Global"){
      cerr << ($1).linenum << ": Error : 'self' is a restricted word, please use another variable name" << "\n";
      exit(0);
    }
    table_stack.top()->make_entry(to_string(($1).lexeme), "Class_Attribute", to_string(($3).lexeme), offset_stack.top(), scope_stack.top(), ($1).linenum, -1, type_size(to_string(($3).lexeme)), ($$).func_numargs, 1);
    int top_offset = offset_stack.top();
    offset_stack.pop();
    top_offset += type_size(to_string(($3).lexeme));
    add_offset += type_size(to_string(($3).lexeme));
    offset_stack.push(top_offset);

  }

  else{
      Symbol_Table_Entry *entry = curr_table->make_entry(to_string(($1).lexeme), "Variable", to_string(($3).lexeme), offset, curr_scope, ($1).linenum, -1, type_size(to_string(($3).lexeme)), ($$).func_numargs, 1);
      (entry->update_listlen(($5).listsize));
      offset += type_size(to_string(($3).lexeme));
  }

  size_t pos_dot = to_string(($$).lexeme).find(".");
  if (pos_dot != string::npos){
    string attribute = to_string(($$).lexeme).substr(5);
    Symbol_Table *class_table = class_symbol_tables[recent_class];
    string offset_ = to_string(class_table->lookup("self."+attribute).offset);
    gen("*(self + " + offset_ + ") = " + to_string(($5).temp));
    x86(nl + "*(self + " + offset_ + ") = " + to_string(($5).temp));
    x86("movq\t" + funcrbp["self"] + "(%rbp),\t%rdx");
    x86("addq\t$" + offset_ + ",\t%rdx");
    x86("movq\t" + funcrbp[to_string(($5).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
    // get back 
    // gen("sub %rsp " + to_string(type_size(($3).lexeme)));
    // gen(to_string(-(offset + add_offset)) + "(%rbp) = " + "*(self + " + offset_ + ")");
  }
  else{
    strcpy(($1).type, ($3).lexeme);
    gen(to_string(($1).temp) + " = " + to_string(($5).temp));
    gen("sub %rsp " + to_string(type_size(($3).lexeme)));
    gen(to_string(-(offset)) + "(%rbp) = " + to_string(($1).temp));
    x86(nl + to_string(($1).temp) + " = " + to_string(($5).temp));
    // x86("sub\t\t$8,\t%rsp");
    x86("movq\t" + funcrbp[to_string(($5).temp)] + "(%rbp),\t%rdx");
    funcrbp[to_string(($1).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  }

//  ($$)
  


}
| Lhs_init COLON test         {
  ($$).linenum = ($1).linenum;
  // $1 is variable name
  // $3 also 
  
  if(to_string(($1).lexeme).substr(0,5) == "self."){
    if(curr_scope == "Global"){
      cerr << ($1).linenum << ": Error : 'self' is a restricted word, please use another variable name" << "\n";
      exit(0);
    }
    table_stack.top()->make_entry(to_string(($1).lexeme), "Variable", to_string(($3).lexeme), offset_stack.top(), curr_scope, ($1).linenum, -1, type_size(to_string(($3).lexeme)), ($$).func_numargs, 0);
    int top_offset = offset_stack.top();
    offset_stack.pop();
    top_offset += type_size(to_string(($3).lexeme));
    add_offset += type_size(to_string(($3).lexeme));
    offset_stack.push(top_offset);
  }
  
  else{
      curr_table->make_entry(to_string(($1).lexeme), "Variable", to_string(($3).lexeme), offset, curr_scope, ($1).linenum, -1, type_size(to_string(($3).lexeme)), ($$).func_numargs, 0);
      offset += type_size(to_string(($3).lexeme));

  }  

   strcpy(($1).type, ($3).lexeme);
   x86(nl + to_string(($1).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[to_string(($1).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
}

| NAME OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET{
  ($$).linenum = ($1).linenum;
 // None function call
  auto it = all_types.find(to_string(($1).token_lex));
  if (it == all_types.end()){
      if(curr_table->lookup(to_string(($1).token_lex)).token == "null"){
          if (to_string(($1).token_lex) == "print"){
            if(func_arg_vec.size()!=1){
                cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'print' function, expected 1 argument" << endl;
                exit(0);
            }
            string none = "None";
            strcpy(($$).type, none.c_str());
            for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
              gen("pushparam " + func_arg_temp_vec[i].second);
            }
            gen("push ret_addr");
            gen("sub %rsp 8");
            gen("call print 1");
            gen("add %rsp 8");
            // cout << -64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()) << endl;
            // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
            //   x86(nl + "aligning stack");
            //   x86("pushq\t$0");
            //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
            // } // legital

            if(func_arg_vec[0].second == "str"){
              x86(nl + "print(" + func_arg_temp_vec[0].second + ")");
              // // x86("sub\t\t$8,\t%rsp");
              x86("movq\t" + funcrbp[func_arg_temp_vec[0].second] + "(%rbp),\t%rax");
              x86("movq\t%rax,\t%rsi");
              x86("leaq\t.LC1(%rip),\t%rax");
              x86("movq\t%rax,\t%rdi");
              x86("movq\t$0,\t%rax");
              x86("call\tprintf@PLT");
            }
            else{
              x86(nl + "print(" + func_arg_temp_vec[0].second + ")");
              // // x86("sub\t\t$8,\t%rsp");
              x86("movq\t" + funcrbp[func_arg_temp_vec[0].second] + "(%rbp),\t%rax");
              x86("movq\t%rax,\t%rsi");
              x86("leaq\t.LC0(%rip),\t%rax");
              x86("movq\t%rax,\t%rdi");
              x86("movq\t$0,\t%rax");
              x86("call\tprintf@PLT");
            }

          
            
            // x86("add\t\t$8,\t%rsp");
                


          }
          else if (to_string(($1).token_lex) == "len"){
            string int_ = "int";
            strcpy(($$).type, int_.c_str());
            if(func_arg_vec.size()!=1){
                cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'len' function, expected 1 argument" << endl;
                exit(0);
            }
            if(func_arg_vec[0].second.size() > 5){
                if(func_arg_vec[0].second.substr(0,5) != "list@"){
                  cerr << ($1).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
                  exit(0);
                }
            }
            else{
                  cerr << ($1).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
                  exit(0);
            }
            
          }
          else if (to_string(($1).token_lex) == "range"){
              string none = "None";
                strcpy(($$).type, none.c_str());
              if(func_arg_vec.size() > 2 || func_arg_vec.size() < 1){
                cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'range' function, expected 1 or 2 arguments" << endl;
                exit(0);
              }
              else if (func_arg_vec.size() == 2){
                if(func_arg_vec[0].second != "int"){
                  cerr << ($1).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                }
                if(func_arg_vec[1].second != "int"){
                  cerr << ($1).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                }
                range_start = func_arg_temp_vec[0].second;
                range_end = func_arg_temp_vec[1].second;
              }
              else if( func_arg_vec.size() == 1){
                if(func_arg_vec[0].second != "int"){
                  cerr << ($1).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                }
                string temp_ = t_new();
                range_start = temp_;
                range_end = func_arg_temp_vec[0].second;
              }
          }
          else{
            cerr << ($1).linenum << ": Error: undeclared function '" << to_string(($1).token_lex) << "' called\n";
            exit(0);
          }
        
      }
      else if (curr_table->lookup(to_string(($1).token_lex)).token != "Function"){
        cerr << ($1).linenum << ": Error: undeclared function '" << to_string(($1).token_lex) << "' called\n";
            exit(0);
      }
      else{
        /// funccall is valid 
        // now check for arguments
        Symbol_Table_Entry func_defn = curr_table->lookup(to_string(($1).token_lex));
        Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
        int num_args = func_defn.numargs;
        int func_params_size = 0;
        for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
          // num_args = (it->second).numargs;
          if((long unsigned int)num_args != func_arg_vec.size()){
            // number of args and param dont match 
            cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(($1).token_lex) << "' function, expected " << num_args << " argument(s)" << endl;
            exit(0);
          }
          if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
            if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
              if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                // types are not same, typecast arg to param type

                if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                  string newt = t_new();
                  gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                  // final remaining
                  
                  if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                    funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                    x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                    x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                    x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                  }

                  if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                    funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                    x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                    x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                    x86("cmp\t$0,\t%rdx");
                    x86("jne\t\t1f");
                    x86("movq\t$0,\t%rdx");
                    x86("jmp\t2f");
                    x86("1:");
                    x86("movq\t$1,\t%rdx");
                    x86("2:");
                    x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                  }
                  

                  func_arg_temp_vec[(it->second).argnum -1].second = newt;
                }
              }
              func_params_size += type_size((it->second).type);
            }
            else{
              // types dont match even after typecasting
              cerr << ($1).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ($1).linenum << "\n";
              exit(0); // adapter

            }
          }

        }
        int flag = 0;
        if(func_arg_temp_vec.size() %2 == 0){
          x86(nl + "aligning stack");
          x86("pushq\t$0");
          flag = 1;
          // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        } // ;egital
        //  if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 != 0 && func_arg_temp_vec.size()%2 == 0){
        //   x86(nl + "aligning stack");
        //   x86("pushq\t$0");
        //   flag = 1;
        //   // x86(nl + "aligning stack");
        //   // x86("pushq\t$0");
        //   // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        //  } // legital
        x86("\n# funccall " + to_string(($$).lexeme));
        x86("pushq\t%rax");
        x86("pushq\t%rcx");
        x86("pushq\t%rdx");
        x86("pushq\t%r8");
        x86("pushq\t%r9");
        x86("pushq\t%r10");
        x86("pushq\t%r11");


        for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
          gen("pushparam " + func_arg_temp_vec[i].second);
          x86(nl + "pushparam " + func_arg_temp_vec[i].second);
          x86("movq\t" + funcrbp[func_arg_temp_vec[i].second] + "(%rbp),\t%rbx");
          x86("pushq\t%rbx");
        }
        gen("push ret_addr");
        gen("sub %rsp " + to_string(func_params_size));
        gen("call " + to_string(($1).token_lex) + " " + to_string(func_arg_vec.size()));
        x86(nl + "call " + to_string(($1).token_lex) + " " + to_string(func_arg_vec.size()));
        
        x86("call\t" + to_string(($1).token_lex));
        gen("add %rsp " + to_string(func_params_size)); // might need to change to func_arg_vec.size()*8 
        x86("add\t\t$" + to_string(func_params_size) + ",\t%rsp");
        x86("popq\t%r11");
        x86("popq\t%r10");
        x86("popq\t%r9");
        x86("popq\t%r8");
        x86("popq\t%rdx");
        x86("popq\t%rcx");
        x86("popq\t%rax");
        if(flag){
          x86("add\t\t$8,\t%rsp");
        }

      } 

  }
    
    // pending
    if (class_symbol_tables.find(to_string(($$).lexeme)) != class_symbol_tables.end()) {
      string class_name = to_string(($$).lexeme);
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
          cerr << ($1).linenum << "Error : Number of constructor call arguments do not match number of constructor parameters of class " << class_name << " at line " << ($1).linenum << "\n";
          exit(0); // adapter
        }
        if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
          if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
            if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
              // types are not same, typecast arg to param type
              if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                string newt = t_new();
                gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                // final remaining
                if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                  funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                  x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                  x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                  x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                }

                if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                  funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                  x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                  x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                  x86("cmp\t$0,\t%rdx");
                  x86("jne\t\t1f");
                  x86("movq\t$0,\t%rdx");
                  x86("jmp\t2f");
                  x86("1:");
                  x86("movq\t$1,\t%rdx");
                  x86("2:");
                  x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                }

                func_arg_temp_vec[(it->second).argnum -2].second = newt;
              }
            }
          }
          else{
            // types dont match even after typecasting
          cerr << ($1).linenum << "Error : Types of constructor call arguments do not match types of constructor parameters of class " << class_name << " at line " << ($1).linenum << "\n";
            exit(0); // adapter

          }
        }
      }

    }


  func_arg_vec.clear();
  func_arg_temp_vec.clear();

 
}
| NAME DOT NAME OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET{
  // pending
  ($$).linenum = ($1).linenum;
// None method call
  string object_name = to_string(($1).token_lex);
  if(curr_table->lookup(object_name).token == "null"){
      cerr << ($1).linenum << ": Error: undeclared object '" << object_name << "'\n";
      exit(0);
  }

  
  else{
    /////// the name before dot is class name
      if((curr_table->lookup(object_name)).token == "Class"){
        string class_name = object_name;
        Symbol_Table *class_table = class_symbol_tables[class_name];
        string attribute = to_string(($3).token_lex);
        if(class_table->lookup(attribute).token == "null"){
          cerr << ($1).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
          exit(0);
        }
        else if (class_table->lookup(attribute).token != "Function"){
          cerr << ($1).linenum << ": Error: undeclared method " << attribute << " in class called" << class_name << "\n";
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
                cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(($3).token_lex) << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                exit(0);
              }
              if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                  if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                    // types are not same, typecast arg to param type
                    if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                      string newt = t_new();
                      gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                      // final remaining
                      if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                        x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                        x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                      }

                      if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                        x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                        x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                        x86("cmp\t$0,\t%rdx");
                        x86("jne\t\t1f");
                        x86("movq\t$0,\t%rdx");
                        x86("jmp\t2f");
                        x86("1:");
                        x86("movq\t$1,\t%rdx");
                        x86("2:");
                        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                      }
                      func_arg_temp_vec[(it->second).argnum -1].second = newt;
                    }
                  }
                  func_params_size += type_size((it->second).type);
                }
                else{
                  // types dont match even after typecasting
                  cerr << ($1).linenum << ": Error: Types of method call arguments do not match types of method parameters at line " << ($1).linenum << "\n";
                  exit(0); // adapter

                }
              }
            }

            int flag = 0;
            if(func_arg_temp_vec.size()%2 == 0){
              x86(nl + "aligning stack");
              x86("pushq\t$0");
              flag = 1;
              // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
            } 
            
            string b = class_name;
            while (child_to_parent_classes.find(b) != child_to_parent_classes.end()){
              string a = child_to_parent_classes[b];
              Symbol_Table *parent_table = class_symbol_tables[a];
              if(parent_table->lookup(attribute).token == "Function"){
                b = a;
              }
              else{
                break;
              }
            }

            x86("\n# funccall " + to_string(($$).lexeme));
            x86("pushq\t%rax");
            x86("pushq\t%rcx");
            x86("pushq\t%rdx");
            x86("pushq\t%r8");
            x86("pushq\t%r9");
            x86("pushq\t%r10");
            x86("pushq\t%r11");

            strcpy(($$).type, func_defn.type.c_str());
            for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
              gen("pushparam " + func_arg_temp_vec[i].second);
              x86(nl + "pushparam " + func_arg_temp_vec[i].second);
              x86("movq\t" + funcrbp[func_arg_temp_vec[i].second] + "(%rbp),\t%rbx");
              x86("pushq\t%rbx");
            }
            gen("push ret_addr");
            gen("sub %rsp " + to_string(func_params_size));
            gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
            x86(nl + "call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
            x86("call\t" + b + "." + attribute);
            
            gen("add %rsp " + to_string(func_params_size));
            x86("add\t\t$" + to_string(func_params_size) + ",\t%rsp");

            // if(func_defn.type != "None"){
            //     string temp_result = t_new();
            //     gen(temp_result + " = %rax");
            //     strcpy(($$).temp, temp_result.c_str());
            // }

            x86("popq\t%r11");
            x86("popq\t%r10");
            x86("popq\t%r9");
            x86("popq\t%r8");
            x86("popq\t%rdx");
            x86("popq\t%rcx");
            x86("popq\t%rax");
            if(flag){
              x86("add\t\t$8,\t%rsp");
            }

        }

      }

      /////// the name before dot is object name
      else{
        string class_name = (curr_table->lookup(object_name)).type; 
        if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
            cerr << ($1).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
            exit(0);
        }
        Symbol_Table *class_table = class_symbol_tables[class_name];
        string attribute = to_string(($3).token_lex);
    
        if(class_table->lookup(attribute).token == "null"){
          cerr << ($1).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
          exit(0);
        }
        else if (class_table->lookup(attribute).token != "Function"){
          cerr << ($1).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
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
                cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(($3).token_lex) << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                exit(0); 
              }
              if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                  if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                    // types are not same, typecast arg to param type
                    if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                      string newt = t_new();
                      gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                      // final remaining 2
                      if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                        x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                        x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                      }

                      if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                        x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                        x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                        x86("cmp\t$0,\t%rdx");
                        x86("jne\t\t1f");
                        x86("movq\t$0,\t%rdx");
                        x86("jmp\t2f");
                        x86("1:");
                        x86("movq\t$1,\t%rdx");
                        x86("2:");
                        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                      }
                      func_arg_temp_vec[(it->second).argnum -2].second = newt;
                    }
                  }
                  func_params_size += type_size((it->second).type);
                }
                else{
                  // types dont match even after typecasting
                  cerr << ($1).linenum << ": Error: Types of method call arguments do not match types of method parameters at line " << ($1).linenum << "\n";
                  exit(0); // adapter

                }
              }
            }

            int flag = 0;
            if(func_arg_temp_vec.size()%2 != 0){
              x86(nl + "aligning stack");
              x86("pushq\t$0");
              flag = 1;
              // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
            } 

            string b = class_name;
            while (child_to_parent_classes.find(b) != child_to_parent_classes.end()){
              string a = child_to_parent_classes[b];
              Symbol_Table *parent_table = class_symbol_tables[a];
              if(parent_table->lookup(attribute).token == "Function"){
                b = a;
              }
              else{
                break;
              }
            }

            x86("\n# funccall " + to_string(($$).lexeme));
            x86("pushq\t%rax");
            x86("pushq\t%rcx");
            x86("pushq\t%rdx");
            x86("pushq\t%r8");
            x86("pushq\t%r9");
            x86("pushq\t%r10");
            x86("pushq\t%r11");

            
            for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
              gen("pushparam " + func_arg_temp_vec[i].second);
              x86(nl + "pushparam " + func_arg_temp_vec[i].second);
              x86("movq\t" + funcrbp[func_arg_temp_vec[i].second] + "(%rbp),\t%rbx");
              x86("pushq\t%rbx");
            }
            gen("pushparam " +  object_name);
            x86(nl + "pushparam " + object_name);
            x86("movq\t" + funcrbp[object_name] + "(%rbp),\t%rbx");
            x86("pushq\t%rbx");
            gen("push ret_addr");
            gen("sub %rsp " + to_string(func_params_size));
            gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
            x86(nl + "call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
            x86("call\t" + b + "." + attribute);

            
            gen("add %rsp " + to_string(func_params_size));
            x86("add\t\t$" + to_string(func_params_size) + ",\t%rsp");

            // if(func_defn.type != "None"){
            //     string temp_result = t_new();
            //     gen(temp_result + " = %rax");
            //     strcpy(($$).temp, temp_result.c_str());
            // }

            x86("popq\t%r11");
            x86("popq\t%r10");
            x86("popq\t%r9");
            x86("popq\t%r8");
            x86("popq\t%rdx");
            x86("popq\t%rcx");
            x86("popq\t%rax");
            if(flag){
              x86("add\t\t$8,\t%rsp");
            }

        }
              
            
      }
            






    }
func_arg_vec.clear();
func_arg_temp_vec.clear();

}

| atom {
// dont do anythign here
}

| Lhs_noninit EQUAL test{
  // pending for self.a in child classes
  ($$).linenum = ($1).linenum;
  // type checking needed
  // $1 is variable name
  // if(curr_table->lookup(to_string(($1).lexeme)).token == "null"){
  //     exit(0);
  // }
  // else{
    curr_table->modify_lookup(to_string(($1).lexeme), 1);
    // curr_table->lookup(to_string(($1).lexeme)).isinit = 1;
  // }
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
      // no typecasting required
      strcpy(($$).type, ($1).type);
  }
  else{
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t\t$0,\t%rdx");
      x86("jne\t\t1f"); // output 1
      x86("movq\t$0,\t%rdx");
      x86("jmp\t\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to float
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid assignment for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }

  if(($1).isindexed && !($1).isdotted){

    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + to_string(($3).temp));
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + to_string(($3).temp));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + to_string(($3).temp));
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + to_string(($3).temp));
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") ");
    x86(nl + temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") ");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[temp_] + "(%rbp)");

    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + to_string(($3).temp));
    x86(nl + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + to_string(($3).temp));
    x86("movq\t" + funcrbp[temp_] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }

else{
    gen(to_string(($1).temp) + " = " + to_string(($3).temp));
    gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
    x86(nl + to_string(($1).temp) + " = " + to_string(($3).temp));
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
}

// if(type1 == "bool"){
//   //  cout << "hereeeee" << "\n";
//     x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($3).temp));
//     x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
//     x86("cmp\t\t$0,\t%rdx");
//     x86("cmp\t\t$0,\t%rdx");
//     x86("jne\t\t1f"); // output 1
//     x86("movq\t$0,\t%rdx");
//     x86("jmp\t\t2f");
//     x86("1:");
//     x86("movq\t$1,\t%rdx");
//     x86("2:");
//     x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
//   }
  

  
  

}
| Lhs_noninit PLUS_EQUAL test{
  ($$).linenum = ($1).linenum;
    // type checking needed
    // $1 is variable name

    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

// D = t23
// 	t24 = 1
// 	t25 = *(D + 0) + t24
// 	*(D + 0) = t25
    
  // pending
  if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    // x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rdx");
    // x86("addq\t$1,\t%rdx");
    // x86("imulq\t$8,\t%rdx,\t%rdx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " + " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " + " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
    // x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");


    string nt1 = t_new();
    gen(nt1 + " = " + nt + " + " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " + " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");


    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " + " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " + " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + to_string(($1).temp) + " = " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rcx");
      x86("addq\t%rcx,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }



    

}
| Lhs_noninit MINUS_EQUAL test{
  ($$).linenum = ($1).linenum;
  
    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

      if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " - " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " - " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("subq\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");

  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");

    string nt1 = t_new();
    gen(nt1 + " = " + nt + " - " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " - " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("subq\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " - " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " - " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " - " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("subq\t%rcx,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }

}
| Lhs_noninit STAR_EQUAL test{
  ($$).linenum = ($1).linenum;

    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

  if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " * " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " * " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("imulq\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");

    string nt1 = t_new();
    gen(nt1 + " = " + nt + " * " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " * " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("imulq\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " * " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " * " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " * " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("imulq\t%rcx,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }
  
    

}
| Lhs_noninit SLASH_EQUAL test{
  ($$).linenum = ($1).linenum;

    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

      if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " / " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " / " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rax");
    x86("cqto");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
    x86("idiv\t%rbx");
    x86("movq\t%rax,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");

    string nt1 = t_new();
    gen(nt1 + " = " + nt + " / " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " / " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rax");
    x86("cqto");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
    x86("idiv\t%rbx");
    x86("movq\t%rax,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " / " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " / " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " / " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rax");
      x86("cqto");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
      x86("idiv\t%rbx");
      x86("movq\t%rax,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }
  
  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }
    

}
| Lhs_noninit PERCENTAGE_EQUAL test{
  ($$).linenum = ($1).linenum;

    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

  if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " % " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " % " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rax");
    x86("cqto");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
    x86("idiv\t%rbx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");
    
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " % " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " % " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rax");
    x86("cqto");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
    x86("idiv\t%rbx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " % " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " % " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " % " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rax");
      x86("cqto");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
      x86("idiv\t%rbx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }
  
    

}
| Lhs_noninit AND_EQUAL test{
($$).linenum = ($1).linenum;
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

        if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " & " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " & " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("and\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");

    string nt1 = t_new();
    gen(nt1 + " = " + nt + " & " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " & " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("and\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    
    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " & " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " & " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " & " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("and\t%rcx,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }
    

}
| Lhs_noninit OR_EQUAL test{
  ($$).linenum = ($1).linenum;
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

        if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " | " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " | " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("or\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");
    
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " | " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " | " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("or\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " | " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " | " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " | " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("or\t%rcx,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }

}
| Lhs_noninit XOR_EQUAL test{
  ($$).linenum = ($1).linenum;
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ^ " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " ^ " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("xor\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");
    
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ^ " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " + " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("xor\t%rcx,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");



    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ^ " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " ^ " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " ^ " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("xor\t%rcx,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }

}
| Lhs_noninit LEFT_SHIFT_EQUAL test{
  ($$).linenum = ($1).linenum;
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }

  if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " << " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " << " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("sal\t\t%cl,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");
    
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " << " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " << " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("sal\t\t%cl,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " << " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " << " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " << " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("sal\t\t%cl,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }

}
| Lhs_noninit RIGHT_SHIFT_EQUAL test{
  ($$).linenum = ($1).linenum;
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to int
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
    }
  }

  if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " >> " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " >> " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("sar\t\t%cl,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt1 = t_new();
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");

    gen(nt1 + " = " + nt + " >> " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " >> " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("sar\t\t%cl,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " >> " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " >> " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " >> " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("sar\t\t%cl,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }

}
| Lhs_noninit DOUBLE_STAR_EQUAL test{
  ($$).linenum = ($1).linenum;
    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ** " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " ** " + to_string(($3).temp));
    string exponent_index = t_new();
    funcrbp[exponent_index] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t$0,\t" + funcrbp[exponent_index] + "(%rbp)");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t$1,\t" + funcrbp[nt1] + "(%rbp)");
    x86("jmp\t\t2f");
    x86("1:");
    x86("movq\t" + funcrbp[exponent_index] + "(%rbp),\t%rdx");
    x86("addq\t$1,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[exponent_index] + "(%rbp)");
    x86("2:");
    x86("movq\t" + funcrbp[exponent_index] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("cmp\t\t%rdx,\t%rcx");
    x86("je\t\t3f"); 
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rdx");
    x86("imulq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    x86("jmp\t\t1b");
    x86("3:");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ** " + to_string(($3).temp));
    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " ** " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " ** " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " ** " + to_string(($3).temp));
      string exponent_index = t_new();
      funcrbp[exponent_index] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t$0,\t" + funcrbp[exponent_index] + "(%rbp)");
      funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t$1,\t" + funcrbp[nt] + "(%rbp)");
      x86("jmp\t\t2f");
      x86("1:");
      x86("movq\t" + funcrbp[exponent_index] + "(%rbp),\t%rdx");
      x86("addq\t$1,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[exponent_index] + "(%rbp)");
      x86("2:");
      x86("movq\t" + funcrbp[exponent_index] + "(%rbp),\t%rdx");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
      x86("cmp\t\t%rdx,\t%rcx");
      x86("je\t\t3f"); 
      x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
      x86("imulq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
      x86("jmp\t\t1b");
      x86("3:");
      x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }

}
| Lhs_noninit DOUBLE_SLASH_EQUAL test{
($$).linenum = ($1).linenum;
    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86 (nl + newt + " = " + "cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t\t$0,\t%rdx");
        x86("jne\t\t1f"); // output 1
        x86("movq\t$0,\t%rdx");
        x86("jmp\t\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to int
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to float
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
      exit(0);
      }
    }

    if(($1).isindexed && !($1).isdotted){
    string nt = t_new();
    gen( nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ")");
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rcx");
    x86("addq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("movq\t(%rcx),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt] + "(%rbp)");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " // " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " // " + to_string(($3).temp));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rax");
    x86("cqto");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
    x86("idiv\t%rbx");
    x86("movq\t%rax,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");
    gen("*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).listhead) + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).listhead)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($1).listoffsettemp)] + "(%rbp),\t%rcx");
    x86("addq\t%rcx,\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if(($1).isdotted && !($1).isindexed){
    string nt = t_new();
    gen(nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86(nl + nt + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t(%rdx),\t%rcx");
    funcrbp[nt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rcx,\t" + funcrbp[nt] + "(%rbp)");
    
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " // " + to_string(($3).temp));
    x86(nl + nt1 + " = " + nt + " // " + to_string(($3).temp));
    funcrbp[nt1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[nt] + "(%rbp),\t%rax");
    x86("cqto");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
    x86("idiv\t%rbx");
    x86("movq\t%rax,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[nt1] + "(%rbp)");

    gen("*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86(nl + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ") = " + nt1);
    x86("movq\t" + funcrbp[to_string(($1).objhead)] + "(%rbp),\t%rdx");
    x86("addq\t" + funcrbp[to_string(($1).objoffset)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[nt1] + "(%rbp),\t%rcx");
    x86("movq\t%rcx,\t(%rdx)");
  }
  else if (($1).isindexed && ($1).isdotted){
    string temp_ = t_new();
    gen(temp_ + " = " + "*(" + to_string(($1).objhead) + " + " + to_string(($1).objoffset) + ")");
    string nt = t_new();
    gen(nt + " = " + "*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ")");
    string nt1 = t_new();
    gen(nt1 + " = " + nt + " // " + to_string(($3).temp));
    gen("*(" + temp_ + " + " + to_string(($1).listoffsettemp) + ") = " + nt1);
  }

  else{
      string nt = t_new();
      gen(nt + " = " + to_string(($1).temp) + " // " + to_string(($3).temp));
      gen(to_string(($1).temp) + " = " + nt);
      gen(to_string(-(curr_table->lookup(to_string(($$).lexeme)).offset + type_size(curr_table->lookup(to_string(($$).lexeme)).type))) + "(%rbp) = " + to_string(($1).temp));
      x86(nl + nt + " = " + to_string(($1).temp) + " // " + to_string(($3).temp));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rax");
      x86("cqto");
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
      x86("idiv\t%rbx");
      x86("movq\t%rax,\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
      // gen(to_string(($1).temp) + " = " + to_string(($3).temp));
  }

  // if(type1 == "bool"){
  //   x86(nl + to_string(($1).temp) + " = cast_to_bool" + to_string(($1).temp));
  //   x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("cmp\t\t$0,\t%rdx");
  //   x86("jne\t\t1f"); // output 1
  //   x86("movq\t$0,\t%rdx");
  //   x86("jmp\t\t2f");
  //   x86("1:");
  //   x86("movq\t$1,\t%rdx");
  //   x86("2:");
  //   x86("movq\t%rdx,\t" + funcrbp[to_string(($1).temp)] + "(%rbp)");
  // }
    

}

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


// pending
Lhs_init:
NAME {
  ($$).linenum = ($1).linenum;
  strcpy(($$).lexeme, ($1).token_lex);
  strcpy(($$).temp, ($1).token_lex);
}
| NAME DOT NAME {
  ($$).linenum = ($1).linenum;
  if(to_string(($1).token_lex) != "self"){
    cerr << ($1).linenum << ": Error: attribute reinitialization of object '" << to_string(($1).token_lex) << "' not allowed" << "\n";
    exit(0);
  }

 string self_dot = "self.";
 strcpy(($$).lexeme, self_dot.c_str());
 strcat(($$).lexeme, ($3).token_lex);

  if(curr_scope.size() < 17){
    cerr << ($1).linenum << ": Error : initialization of self attribute not allowed in non-constructor / non-init method \n";
  exit(0);
  }
 if(curr_scope.size() >= 17 && curr_scope.substr(0,17) != "Function@__init__"){
  cerr << ($1).linenum << ": Error : initialization of self attribute not allowed in non-constructor / non-init method \n";
  exit(0);
 }

}

Lhs_noninit:
NAME{
  ($$).linenum = ($1).linenum;
  if(curr_table->lookup(to_string(($1).token_lex)).token == "null" || curr_table->lookup(to_string(($1).token_lex)).token == "Function" ){
      cerr << ($1).linenum << ": Error: undeclared variable '" << to_string(($1).token_lex) << "'\n";
      exit(0);
  }
  strcpy(($$).lexeme, ($1).token_lex);
  string name_type = curr_table->lookup(to_string(($1).token_lex)).type;
  strcpy(($$).type, name_type.c_str());
  strcpy(($$).temp, ($1).token_lex);
  // strcpy(($$).type, ($1).token_type);
}
| NAME DOT NAME {
($$).linenum = ($1).linenum;
// this entire type???

  string object_name = to_string(($1).token_lex);

  
  if(curr_table->lookup(object_name).token == "null" || curr_table->lookup(to_string(($1).token_lex)).token == "Function" || curr_table->lookup(to_string(($1).token_lex)).token == "Class"){
      cerr << ($1).linenum << ": Error: undeclared object '" << object_name << "'\n";
      exit(0);
  }
  else{
    string class_name = (curr_table->lookup(object_name)).type;
    if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
        cerr << ($1).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
        exit(0);
    }
    Symbol_Table *class_table = class_symbol_tables[class_name];
    string attribute = to_string(($3).token_lex);
    if(class_table->lookup("self."+attribute).token == "null"){
      cerr << ($1).linenum << ": Error: undeclared attribute '" << attribute << "' in class '" << class_name << "'\n";
      exit(0);
    }
    else {
      string attribute_type = class_table->lookup("self."+attribute).type;
      strcpy(($$).type, attribute_type.c_str());
      string offsettemp = t_new();
      funcrbp[offsettemp] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      string offset_ = to_string(class_table->lookup("self."+attribute).offset);
      x86(nl + offsettemp + " = offset(" + class_name + "," + attribute + ")");
      x86("movq\t$" + offset_ + ",\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[offsettemp] + "(%rbp)");
      strcpy(($$).objoffset, offsettemp.c_str());
      strcpy(($$).objhead, ($1).token_lex);
      ($$).isdotted = 1;
    }
    strcpy(($$).lexeme, ($1).token_lex);
    string dot = ".";
    strcat(($$).lexeme, dot.c_str());
    strcat(($$).lexeme, ($3).token_lex);


  }

  
  
}

| NAME OPEN_SQUARE_BRACKET test CLOSE_SQUARE_BRACKET {
($$).linenum = ($1).linenum;
// check for test type if its int
if(to_string(($3).type) != "int"){
  cerr << ($1).linenum << ": Error: index is not integer type\n";
  exit(0);
}

//checking if its list type
if(curr_table->lookup(to_string(($1).token_lex)).token != "null"){
    string name1_type = curr_table->lookup(to_string(($1).token_lex)).type;
    if(name1_type.substr(0,5) != "list@"){
      cerr << ($1).linenum << ": Error: '" << to_string(($1).token_lex) << "' is not a list, cannot be indexed " << endl;
      exit(0);
    }
    string list_type = name1_type;
    if(list_type.size() > 5){
      string without_list_type = list_type.substr(5);
      strcpy(($$).type, without_list_type.c_str());
    }
}
else{
   cerr << ($1).linenum << ": Error: undeclared variable '" << to_string(($1).token_lex) << "'" << endl;
    exit(0);
}

// int index = atoi(($3).temp);
int typesize = type_size(to_string(($$).type));
// int list_offset = index*typesize;
($$).isindexed = 1;
strcpy(($$).listhead, ($1).token_lex);
string temp_ = t_new();
strcpy(($$).listoffsettemp, temp_.c_str());
gen(temp_ + " = " + to_string(($3).temp) + " * " + to_string(typesize));
x86(nl + temp_ + " = " + to_string(($3).temp) + " * " + to_string(typesize));
// x86("sub\t\t$8,\t%rsp");
funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
x86("addq\t$1,\t%rdx");
x86("imulq\t$8,\t%rdx");
x86("movq\t%rdx,\t" + funcrbp[temp_] + "(%rbp)");

// string temp1 = t_new();
// strcpy(($$).temp, temp1.c_str());
// gen("*(" + to_string(($1).token_lex) + " + " + temp_ + ") = " + temp1);

// important: Checking if index is in range



}
| NAME DOT NAME OPEN_SQUARE_BRACKET test CLOSE_SQUARE_BRACKET {
($$).linenum = ($1).linenum;
    // string input = to_string(($$).lexeme);
    string part1 = to_string(($1).token_lex);
    string part2 = to_string(($3).token_lex);
    string part3 = to_string(($5).lexeme);

    string class_name = (curr_table->lookup(part1)).type; 
    if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
        cerr << ($1).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
        exit(0);
    }
    Symbol_Table *class_table = class_symbol_tables[class_name];
    string attribute = part2;
    if(class_table->lookup("self."+attribute).token == "null"){
      cerr << ($1).linenum << ": Error: undeclared attribute '" << attribute << "' in class '" << class_name << "'\n";
      exit(0);
    }


    if(to_string(($5).type) != "int"){
      cerr << ($1).linenum << ": Error: index is not integer type\n";
      exit(0);
    }

    
    string name1_type = class_table->lookup("self."+attribute).type;
    if(name1_type.substr(0,5) != "list@"){
      cerr << ($1).linenum << ": Error: '" << part1+"."+part2 << "' is not a list, cannot be indexed " << endl;
      exit(0);
    }
    string list_type = name1_type;
    if(list_type.size() > 5){
      string without_list_type = list_type.substr(5);
      strcpy(($$).type, without_list_type.c_str());
    }

    int typesize = type_size(to_string(($$).type));
    // int list_offset = index*typesize;
    ($$).isindexed = 1;
    ($$).isdotted = 1;
    strcpy(($$).listhead, ($3).token_lex);
    string temp_ = t_new();
    strcpy(($$).listoffsettemp, temp_.c_str());
    gen(temp_ + " = " + to_string(($5).temp) + " * " + to_string(typesize));
    x86(nl + temp_ + " = " + to_string(($5).temp) + " * " + to_string(typesize));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t" + funcrbp[to_string(($5).temp)] + "(%rbp),\t%rdx");
    x86("addq\t$1,\t%rdx");
    x86("imulq\t$8,\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[temp_] + "(%rbp)");
    // x86(nl + temp_ + " = " + to_string(($5).temp) + " * " + to_string(typesize));
    // // x86("sub\t\t$8,\t%rsp");
    // funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    // x86("movq\t" + to_string(($5)))
    string offsettemp = t_new();
    funcrbp[offsettemp] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    string offset_ = to_string(class_table->lookup("self."+attribute).offset);
    x86(nl + offsettemp + " = offset(" + class_name + "," + attribute + ")");
    x86("movq\t$" + offset_ + ",\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[offsettemp] + "(%rbp)");
    strcpy(($$).objoffset, offsettemp.c_str());
    strcpy(($$).objhead, ($1).token_lex);
    

}




flow_stmt:      
BREAK      {
  ($$).linenum = ($1).linenum;
  gen("Goto "+ breakjumps.top());
  x86("jmp\t\t" + breakjumps.top());
}
| CONTINUE      {
  ($$).linenum = ($1).linenum;
  gen("Goto "+ continuejumps.top());
  x86("jmp\t\t" + continuejumps.top());
}
| RETURN      {
  ($$).linenum = ($1).linenum;

  isreturning = 1;

  if(func_return_type != "None"){
    cerr << ($1).linenum << ": Error: wrong return type 'None', expected return type '"<< func_return_type <<"'\n";
    exit(0);
  }
// check if return type is None
// your curr_table is function table
// return type of this function is stored in parent table 
// so before making symbol table for this new function, store its return type in a global variable
// and match with it

  // int max_offset = 0;
  // string max_type = "";
  // for(auto it = curr_table->table.begin(); it != curr_table->table.end(); it++){
  //   if(it->second.offset >= max_offset){
  //     max_offset = it->second.offset;
  //     max_type = it->second.type;
  //   }
  // }
  // int last_size = type_size(max_type);
  // int func_size = max_offset + last_size;
  // gen("add %rsp " + to_string(func_size));
  // gen("pop %rbp");
  // gen("ret");
  int stack_offset = 8*((int)funcrbp.size() - (int)func_param_vec.size());
  if(stack_offset % 16 == 0){
    stack_offset += 8;
  }
  x86("\n# endfunc");
  string func_name = curr_scope.substr(9);
  x86("jmp\t\t" + func_name + "_.end");
  // x86("add\t\t$" + to_string(stack_offset) + ",\t%rsp");
  // x86("popq\t%r15");
  // x86("popq\t%r14");
  // x86("popq\t%r13");
  // x86("popq\t%r12");
  // x86("popq\t%rsi");
  // x86("popq\t%rdi");
  // x86("popq\t%rbx");
  // x86("popq\t%rbp");
  // x86("ret");


}
| RETURN test    {
  ($$).linenum = ($1).linenum;
  isreturning = 1;
// check return type 
  if(match_type(func_return_type,to_string(($2).type))){
    if(func_return_type != to_string(($2).type)){
      string newt = t_new();
      gen(newt + " = cast_to_" + func_return_type + " " + to_string(($2).temp));
      x86(nl + newt + " = cast_to_" + func_return_type + " " + to_string(($2).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      if(func_return_type == "int" && to_string(($2).type) == "bool"){
        x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      }

      if(func_return_type == "bool" && to_string(($2).type) == "int"){
        x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t$0,\t%rdx");
        x86("jne\t\t1f");
        x86("movq\t$0,\t%rdx");
        x86("jmp\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      }
      strcpy(($2).temp, newt.c_str());
    }
  }
  else{
    cerr << ($1).linenum << ": Error: wrong return type '" << to_string(($2).type) << "', expected return type '"<< func_return_type <<"'\n";
    exit(0);
  }
  int stack_offset = 8*((int)funcrbp.size() - (int)func_param_vec.size());
  if(stack_offset % 16 == 0){
    stack_offset += 8;
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
  gen("%rax = " + to_string(($2).temp));
  gen("ret");
  x86("\n# %rax = " + to_string(($2).temp));
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rax");
  // x86("\n# endfunc" + to_string(($2).token_lex));
  x86("\n# endfunc");
  string func_name = curr_scope.substr(9);
  // cout << func_name << endl;
  x86("jmp\t\t" + func_name + "_.end");
  // x86("add\t\t$" + to_string(stack_offset) + ",\t%rsp");
  // x86("popq\t%r15");
  // x86("popq\t%r14");
  // x86("popq\t%r13");
  // x86("popq\t%r12");
  // x86("popq\t%rsi");
  // x86("popq\t%rdi");
  // x86("popq\t%rbx");
  // x86("popq\t%rbp");
  // x86("ret");
}

Opt_test:
%empty             {
  
}
| test      {
  
}

global_stmt:
GLOBAL NAME Multi_name      {
  ($$).linenum = ($1).linenum;
  // make_entry needed
  for(int i = 0; i <  (int) vec_tables.size(); i++){
    if(vec_tables[i]->table.find(to_string(($2).token_lex)) != vec_tables[i]->table.end()){
      cerr << ($1).linenum << "Error : name '" << to_string(($2).token_lex) << "' is declared before global declaration" << endl;
      exit(0);
    }
  }
  all_global_vars[to_string(($2).token_lex)] = 1;
}

Multi_name:
%empty             {
  
}
| COMMA NAME Multi_name      {
  ($$).linenum = ($1).linenum;
  for(int i = 0; i < (int) vec_tables.size(); i++){
    if(vec_tables[i]->table.find(to_string(($2).token_lex)) != vec_tables[i]->table.end()){
      cerr << ($1).linenum << "Error : name '" << to_string(($2).token_lex) << "' is declared before global declaration" << endl;
      exit(0);
    }
  }
  all_global_vars[to_string(($2).token_lex)] = 1;
}

compound_stmt:
if_stmt      {
   
}
| while_stmt      {
   
}
| for_stmt      {
   
}
| funcdef      {
  
}
| classdef      {
  
}


if_stmt:
dummy_if_suit Multi_elif Opt_else      {
  ($$).linenum = ($1).linenum;
  while(!if_scopes.empty() && if_scopes.top() != "delimiter"){
    if(if_scopes.top() != "\0"){
      gen(if_scopes.top() + ":");
      x86(if_scopes.top() + ":");
    }
    if_scopes.pop();
  }
  
  if_scopes.pop();
  gen(to_string(($1).gotoname) + ":");
  x86(to_string(($1).gotoname) + ":");
  
}

dummy_if_suit :
dummyifstmt suite {
  ($$).linenum = ($1).linenum;
  string next_state = L_new();
  gen("Goto " + next_state);
  x86(nl + "Goto " + next_state);
  x86("jmp\t\t" + next_state);
  if_scopes.push("delimiter");
  strcpy(($$).gotoname, next_state.c_str());
  gen(to_string(($1).gotoname) + ":");
  x86(to_string(($1).gotoname) + ":");
}


dummyifstmt:
IF test COLON         {
  ($$).linenum = ($1).linenum;
  // if_scopes.push(curr_if_scope);
  string next_state = L_new();
  gen("Ifz " + to_string(($2).temp) + " Goto " + next_state);
  x86(nl + "Ifz " + to_string(($2).temp) + " Goto " + next_state);
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("je\t\t" + next_state); //false
  strcpy(($$).gotoname,next_state.c_str());
}

Multi_elif:
%empty             {
  
}
| dummyelifstmt suite {
  
  string next_state = L_new();
  gen("Goto " + next_state);
  x86(nl + "Goto " + next_state);
  x86("jmp\t\t" + next_state);
  if_scopes.push(next_state);
  gen(to_string(($1).gotoname) + ":");
  x86(to_string(($1).gotoname) + ":");
} 
Multi_elif      {
($$).linenum = ($1).linenum;
}

dummyelifstmt:
ELIF test COLON     {
  ($$).linenum = ($1).linenum;
  string next_state = L_new();
  gen("Ifz " + to_string(($2).temp) + " Goto " + next_state);
  x86(nl + "Ifz " + to_string(($2).temp) + " Goto " + next_state);
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("je\t\t" + next_state); //false
  strcpy(($$).gotoname,next_state.c_str());
}



Opt_else:
%empty             {
  
}
| ELSE COLON suite      {
  ($$).linenum = ($1).linenum;
    // same scope, so no new symbol table 

}

// if_stmt:
// IF test COLON suite Multi_elif Opt_else      {

// }

// Multi_elif:
// %empty             {
  
// }
// | ELIF test COLON suite Multi_elif      {

// }

// Opt_else:
// %empty             {
  
// }
// | ELSE COLON suite      {

// }





dummyWhilestmt:
WHILE{
  ($$).linenum = ($1).linenum;
  string loop_start = L_new();
  gen(loop_start + ":");
  x86(loop_start + ":");
  strcpy(($$).gotoname,loop_start.c_str());
  continuejumps.push(loop_start);
}

dummyWhilestmt1:
dummyWhilestmt test {
  ($$).linenum = ($1).linenum;
  string loop_end = L_new();
  gen("Ifz " + to_string(($2).temp) + " Goto " + loop_end);
  x86(nl + "Ifz " + to_string(($2).temp) + " Goto " + loop_end);
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("je\t\t" + loop_end);
  strcpy(($$).gotoname,loop_end.c_str());
  strcpy(($$).gotonext, ($1).gotoname);
  breakjumps.push(loop_end);
}

while_stmt:
dummyWhilestmt1 COLON suite{
  ($$).linenum = ($1).linenum;
  gen("Goto " + to_string(($1).gotonext));
  x86(nl + "Goto " + to_string(($1).gotonext));
  x86("jmp\t" + to_string(($1).gotonext));
  gen(to_string(($1).gotoname) + ":");
  x86(to_string(($1).gotoname) + ":");
  breakjumps.pop();
  continuejumps.pop();
}

dummy_for_stmt:
FOR NAME IN test {
  
  if ((curr_table->lookup(to_string(($2).token_lex)).token == "null") || (curr_table->lookup(to_string(($2).token_lex)).token == "Function")){
    cerr << ($1).linenum << ": Error: undeclared variable '" << to_string(($2).token_lex) << "'\n";
    exit(0);
  }

  if(curr_table->lookup(to_string(($2).token_lex)).type != "int"){
    cerr << ($1).linenum << ": Error: " << curr_table->lookup(to_string(($2).token_lex)).type << " type variable " << to_string(($2).token_lex) << " not iterable\n";
    exit(0);
  }
  curr_table->modify_lookup(to_string(($2).token_lex), 1);
  ($$).linenum = ($1).linenum;
// FOR NAME IN test {
  string loop_itr = t_new();
  string loop_cond = t_new();
  // gen(loop_itr + " = " + range_start);
  // gen(loop_cond + " = " + range_end);
  gen(to_string(($2).token_lex) + " = " + range_start);
  x86(nl + to_string(($2).token_lex) + " = " + range_start);
  x86("movq\t" + funcrbp[range_start] + "(%rbp),%rdx");
  x86("movq\t%rdx," + funcrbp[to_string(($2).token_lex)] + "(%rbp)");
  string l1 = L_new();
  string l2 = L_new();
  gen("Goto " + l2);
  x86(nl + "Goto " + l2);
  x86("jmp\t\t" + l2);
  gen(l1 + ":");
  x86(l1 + ":");
  //push goto label into stack
  continuejumps.push(l1);
  string temp_ = t_new();
  gen(temp_ + " = " + to_string(($2).token_lex) + " + 1" );
  gen(to_string(($2).token_lex) +  " = " + temp_);
  x86(nl + to_string(($2).token_lex) + " += 1");
  x86("movq\t" + funcrbp[to_string(($2).token_lex)] + "(%rbp),\t%rdx");
  x86("addq\t$1,\t%rdx");
  x86("movq\t%rdx,"+ funcrbp[to_string(($2).token_lex)] + "(%rbp)");
  gen(l2+":");
  x86(l2 + ":");
  strcpy(($$).gotonext, l1.c_str());
  string next_state = L_new();
  string temp1 = t_new();
  gen(temp1 + " = " + to_string(($2).token_lex) + " < " + range_end);
  x86(nl + temp_ +"= "+ to_string(($2).token_lex) + "<" + range_end);
  funcrbp[temp1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t" + funcrbp[to_string(($2).token_lex)] + "(%rbp),\t%rdx");
  x86("movq\t" + funcrbp[range_end] + "(%rbp),\t%rcx");
  x86("cmp\t\t%rdx,\t%rcx");
  x86("jg\t\t1f"); // true
  x86("movq\t$0,\t%rdx");
  x86("jmp\t\t2f"); // false
  x86("1:");
  x86("movq\t$1,\t%rdx");
  x86("2:");
  x86("movq\t%rdx,\t" + funcrbp[temp1] + "(%rbp)");

  gen("Ifz " + temp1 + " Goto " + next_state);
  x86(nl + "Ifz " + temp1 + " Goto " + next_state);
  x86("movq\t" + funcrbp[temp1] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("je\t\t" + next_state); //false
  //push break label into stack
  breakjumps.push(next_state);
  strcpy(($$).gotoname,next_state.c_str());

}

for_stmt:
dummy_for_stmt COLON suite      {
  ($$).linenum = ($1).linenum;
    gen("Goto " + to_string(($1).gotonext));
    x86(nl + "Goto " + to_string(($1).gotonext));
     x86("jmp\t\t" + to_string(($1).gotonext));
   gen(to_string(($1).gotoname) + ":");
    x86(to_string(($1).gotoname) + ":");
   continuejumps.pop();
   breakjumps.pop();
}


suite:
simple_stmt      {
  
}
| NEWLINE INDENT Nonzero_stmt DEDENT      {
  ($$).linenum = ($1).linenum;
  
}

Nonzero_stmt:
stmt      {
  
}
| stmt Nonzero_stmt      {

}

test:
or_test   {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
   strcpy(($$).temp , ($1).temp);

}

or_test:
and_test       {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
}
| or_test OR and_test {
  // type checking needed

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  string bool_ = "bool";

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required

      
      strcpy(($$).type, type1.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }


  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " or " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " or " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("jne\t\t1f"); //true
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("jne\t\t1f"); //true
  x86("movq\t$0,\t%rdx");
  x86("jmp\t\t2f"); //false
  x86("1:");
  x86("movq\t$1,\t%rdx");
  x86("2:");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

}

and_test:
not_test      {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
}
| and_test AND not_test {
    // type checking needed

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  string bool_ = "bool";

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required

      
      strcpy(($$).type, type1.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " and " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " and " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("je\t\t1f"); //false
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("je\t\t1f"); //false
  x86("movq\t$1,\t%rdx");
  x86("jmp\t\t2f"); //true
  x86("1:");
  x86("movq\t$0,\t%rdx");
  x86("2:");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");


  
}

not_test:
NOT not_test      {
  ($$).linenum = ($1).linenum;
    // type checking needed

  string type1 = to_string(($2).type);
  if(type1 == "int" || type1 == "float" || type1 == "bool"){
    strcpy(($$).type , ($2).type);
  }
  else{
    cerr << ($1).linenum << ": Error: invalid operation  'not' for '" << type1 << "' type\n";
    exit(0);
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + "not " + to_string(($2).temp));
  x86(nl + to_string(($$).temp) + " = " + "not " + to_string(($2).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
  x86("cmp\t\t$0,\t%rdx");
  x86("je\t\t1f"); //true
  x86("movq\t$0,\t%rdx");
  x86("jmp\t\t2f"); //false
  x86("1:");
  x86("movq\t$1,\t%rdx");
  x86("2:");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  
}
| comparison      {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
 
}

comparison:
expr       {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
  
}
| comparison LESSER expr {

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(($$).type, "int");
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " < " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " < " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  if(type1 == "str"){
    // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
    //   x86(nl + "aligning stack");
    //   x86("pushq\t$0");
    //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    // }   // legital
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rdx,\t%rdi");
    x86("movq\t%rcx,\t%rsi");
    x86("call\tstrcmp@PLT");
    x86("movsx\t%eax,\t%rax");
    x86("cmp\t\t$0,\t%rax");
    // x86("test\t%rax,\t%rax");
    x86("jge\t\t1f\t\t# false"); // false
    x86("movq\t$1,\t%rdx");
    x86("jmp\t\t2f\t\t# true"); // true
    x86("1:");
    x86("movq\t$0,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }
  else{
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("cmp\t\t%rdx,\t%rcx");
    x86("jg\t\t1f"); // true
    x86("movq\t$0,\t%rdx");
    x86("jmp\t\t2f"); // false
    x86("1:");
    x86("movq\t$1,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }

}
| comparison GREATER expr {

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(($$).type, "int");
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " > " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " > " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  if(type1 == "str"){
    // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
    //   x86(nl + "aligning stack");
    //   x86("pushq\t$0");
    //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    // }   // legital
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rdx,\t%rdi");
    x86("movq\t%rcx,\t%rsi");
    x86("call\tstrcmp@PLT");
    x86("movsx\t%eax,\t%rax");
    x86("cmp\t\t$0,\t%rax");
    // x86("test\t%rax,\t%rax");
    x86("jle\t\t1f\t\t# false"); // false
    x86("movq\t$1,\t%rdx");
    x86("jmp\t\t2f\t\t# true"); // true
    x86("1:");
    x86("movq\t$0,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }
  else{
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("cmp\t\t%rdx,\t%rcx");
    x86("jl\t\t1f"); // true
    x86("movq\t$0,\t%rdx");
    x86("jmp\t\t2f"); // false
    x86("1:");
    x86("movq\t$1,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }

}
| comparison DOUBLE_EQUAL expr {
  
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  
  string int_ = "int";

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(($$).type, int_.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " == " + to_string(($3).temp));

  // cout << to_string(($1).lexeme) << endl;

  // if(to_string(($1).lexeme) != "__name__"){

  // }
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " == " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");

  if(type1 == "str"){
    // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
    //   x86(nl + "aligning stack");
    //   x86("pushq\t$0");
    //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    // }   // legital
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rdx,\t%rdi");
    x86("movq\t%rcx,\t%rsi");
    x86("call\tstrcmp@PLT");
    x86("movsx\t%eax,\t%rax");
    x86("cmp\t\t$0,\t%rax");
    // x86("test\t%rax,\t%rax");
    x86("jne\t\t1f"); // false
    x86("movq\t$1,\t%rdx");
    x86("jmp\t\t2f"); // true
    x86("1:");
    x86("movq\t$0,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }
  else{
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("cmp\t\t%rdx,\t%rcx");
    x86("je\t\t1f"); // true
    x86("movq\t$0,\t%rdx");
    x86("jmp\t\t2f"); // false
    x86("1:");
    x86("movq\t$1,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }

}
| comparison GREATER_EQUAL expr {

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(($$).type, "int");
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " >= " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " >= " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");

  if(type1 == "str"){
    // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
    //   x86(nl + "aligning stack");
    //   x86("pushq\t$0");
    //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    // }   // legital
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rdx,\t%rdi");
    x86("movq\t%rcx,\t%rsi");
    x86("call\tstrcmp@PLT");
    x86("movsx\t%eax,\t%rax");
    x86("cmp\t\t$0,\t%rax");
    // x86("test\t%rax,\t%rax");
    x86("jl\t\t1f"); // false
    x86("movq\t$1,\t%rdx");
    x86("jmp\t\t2f"); // true
    x86("1:");
    x86("movq\t$0,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  }
  else{
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("cmp\t\t%rdx,\t%rcx");
    x86("jle\t\t1f"); // true
    x86("movq\t$0,\t%rdx");
    x86("jmp\t\t2f"); // false
    x86("1:");
    x86("movq\t$1,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }

}
| comparison LESSER_EQUAL expr {

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(($$).type, "int");
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " <= " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " <= " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");

  if(type1 == "str"){
    // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
    //   x86(nl + "aligning stack");
    //   x86("pushq\t$0");
    //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    // }   // legital
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rdx,\t%rdi");
    x86("movq\t%rcx,\t%rsi");
    x86("call\tstrcmp@PLT");
    x86("movsx\t%eax,\t%rax");
    x86("cmp\t\t$0,\t%rax");
    // x86("test\t%rax,\t%rax");
    x86("jg\t\t1f"); // false
    x86("movq\t$1,\t%rdx");
    x86("jmp\t\t2f"); // true
    x86("1:");
    x86("movq\t$0,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  }
  else{
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("cmp\t\t%rdx,\t%rcx");
    x86("jge\t\t1f"); // true
    x86("movq\t$0,\t%rdx");
    x86("jmp\t\t2f"); // false
    x86("1:");
    x86("movq\t$1,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }

}
| comparison NOT_EQUAL expr {

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float" || type1 == "str"){
      // no typecasting required

      
      strcpy(($$).type, "int");
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " != " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " != " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");

  if(type1 == "str"){
    // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
    //   x86(nl + "aligning stack");
    //   x86("pushq\t$0");
    //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    // }   // legital
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("movq\t%rdx,\t%rdi");
    x86("movq\t%rcx,\t%rsi");
    x86("call\tstrcmp@PLT");
    x86("movsx\t%eax,\t%rax");
    x86("cmp\t\t$0,\t%rax");
    // x86("test\t%rax,\t%rax");
    x86("je\t\t1f"); // false
    x86("movq\t$1,\t%rdx");
    x86("jmp\t\t2f"); // true
    x86("1:");
    x86("movq\t$0,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }
  else{
    x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
    x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
    x86("cmp\t\t%rdx,\t%rcx");
    x86("jne\t\t1f"); // true
    x86("movq\t$0,\t%rdx");
    x86("jmp\t\t2f"); // false
    x86("1:");
    x86("movq\t$1,\t%rdx");
    x86("2:");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  }

}
| comparison IN expr {
  

}

expr:
xor_expr      {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
  
}
| expr OR_OP xor_expr {
  
  // type checking

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " | " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " | " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("or\t\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
}

xor_expr:
and_expr    {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
  
}
| xor_expr XOR and_expr {
  
  // type checking
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " ^ " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " ^ " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("xor\t\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

}

and_expr:
shift_expr    {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
  
}
| and_expr AND_OP shift_expr {
  
  // type checking
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " & " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " & " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("and\t\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
}

shift_expr:
arith_expr     {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
  
}
| shift_expr LEFT_SHIFT arith_expr {
  
  // type checking

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " << " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " << " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
  x86("sal\t\t%cl,\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
}
| shift_expr RIGHT_SHIFT arith_expr {
  
// type checking
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " >> " + to_string(($3).temp));

  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " >> " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
  x86("sar\t\t%cl,\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");


}

arith_expr:
term     {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
  
}
| arith_expr PLUS term {
// type checking

  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " + " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " + " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("addq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  
}
| arith_expr MINUS term {
// type checking
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }  

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " - " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " - " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  // x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rax");
  x86("subq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  // x86("neg\t\t%rdx");
  // x86("subq\t%rax,\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

}

term:
factor       {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
}
| term STAR factor {
// type checking
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " * " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " * " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("imulq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  
}
| term SLASH factor {
// type checking
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " / " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " / " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rax");
  x86("cqto");
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
  x86("idiv\t%rbx");
  x86("movq\t%rax,\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  
}
| term PERCENTAGE factor {
  // type checking
  string type1 = to_string(($1).type);
  string type2 = to_string(($3).type);

  if(type1 == type2){
    if(type1 == "int" || type1 == "bool" || type1 == "float"){
      // no typecasting required
      strcpy(($$).type, ($1).type);
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }
  else if(type1 != type2){
    if(type1 == "int" && type2 == "bool"){
      strcpy(($$).type, type1.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
      strcpy(($3).temp, newt.c_str());
    }
    else if(type1 == "bool" && type2 == "int"){
      strcpy(($$).type, type2.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
      x86("cmp\t$0,\t%rdx");
      x86("jne\t\t1f");
      x86("movq\t$0,\t%rdx");
      x86("jmp\t2f");
      x86("1:");
      x86("movq\t$1,\t%rdx");
      x86("2:");
      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "int" && type2 == "float"){
      strcpy(($$).type, type2.c_str());
      // typecast $1 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
      strcpy(($1).temp, newt.c_str());
    }
    else if(type1 == "float" && type2 == "int"){
      strcpy(($$).type, type1.c_str());
      // typecast $3 to bool
      string newt = t_new();
      gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
      strcpy(($3).temp, newt.c_str());
    }
    else{
      cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
    }
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " % " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " % " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rax");
  x86("cqto");
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
  x86("idiv\t%rbx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  
}
| term DOUBLE_SLASH factor {
  // type checking
    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }
    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type2.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
        x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t$0,\t%rdx");
        x86("jne\t\t1f");
        x86("movq\t$0,\t%rdx");
        x86("jmp\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($1).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type2.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
        strcpy(($1).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " // " + to_string(($3).temp));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " // " + to_string(($3).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rax");
  x86("cqto");
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rbx");
  x86("idiv\t%rbx");
  x86("movq\t%rax,\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  
}


factor:
PLUS factor      {
  ($$).linenum = ($1).linenum;
  // type checking

  string type1 = to_string(($2).type);
  if(type1 == "int"){
    // no typecasting
    strcpy(($$).type, ($2).type);
  }
  else if(type1 == "bool"){
    // cast $2 to int
    string int_ = "int";
    strcpy(($$).type, int_.c_str());
  }
  else if(type1 == "float"){
    // no typecasting
    strcpy(($$).type, ($2).type);
  }
  else{
    cerr << ($1).linenum << ": Error: Invalid operation for " << type1 << " type at line " << ($1).linenum << "\n";
    exit(0); // adapter
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + "+ " + to_string(($2).temp));
  x86(nl + to_string(($$).temp) + " = " + "+ " + to_string(($2).temp));
  // x86("sub\t\t$8,\t%rsp");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");

  
}      
| MINUS factor      {
  ($$).linenum = ($1).linenum;
  // type checking

  string type1 = to_string(($2).type);
  if(type1 == "int"){
    // no typecasting
    strcpy(($$).type, ($2).type);
  }
  else if(type1 == "bool"){
    // cast $2 to int
    string int_ = "int";
    strcpy(($$).type, int_.c_str());
  }
  else if(type1 == "float"){
    // no typecasting
    strcpy(($$).type, ($2).type);
  }
  else{
    cerr << ($1).linenum << ": Error: Invalid operation for " << type1 << " type at line " << ($1).linenum << "\n";
    exit(0); // adapter
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + "- " + to_string(($2).temp));
  x86(nl + to_string(($$).temp) + " = " + "- " + to_string(($2).temp));
  // x86("sub\t\t$8,\t%rsp");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
  x86("xor\t\t%rcx,\t%rcx");
  x86("subq\t%rdx,\t%rcx");
  x86("movq\t%rcx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  
}
| NOT_OP factor      {
  ($$).linenum = ($1).linenum;
  // type checking
  string type1 = to_string(($2).type);
  if(type1 == "int"){
    // no typecasting
    strcpy(($$).type, ($2).type);
  }
  else if(type1 == "bool"){
    // cast $2 to int
    string int_ = "int";
    strcpy(($$).type, int_.c_str());
  }
  else{
    cerr << ($1).linenum << ": Error: invalid operation for " << type1 << " type at line " << ($1).linenum << "\n";
    exit(0); // adapter
  }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + "~ " + to_string(($2).temp));
  x86(nl + to_string(($$).temp) + " = " + "~ " + to_string(($2).temp));
  // x86("sub\t\t$8,\t%rsp");
  x86("movq\t" + funcrbp[to_string(($2).temp)] + "(%rbp),\t%rdx");
  x86("addq\t$1,\t%rdx");
  x86("neg\t\t%rdx");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  
}
| power      {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
}
      
power:
atom_expr       {
  strcpy(($$).lexeme, ($1).lexeme);
  strcpy(($$).type, ($1).type);
  strcpy(($$).temp , ($1).temp);
  

}
| atom_expr DOUBLE_STAR factor {

    string type1 = to_string(($1).type);
    string type2 = to_string(($3).type);

    if(type1 == type2){
      if(type1 == "int" || type1 == "bool" || type1 == "float"){
        // no typecasting required
        strcpy(($$).type, ($1).type);
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

    else if(type1 != type2){
      if(type1 == "int" && type2 == "bool"){
        strcpy(($$).type, type1.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        x86(nl + newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)"); 
        strcpy(($3).temp, newt.c_str());
      }
      else if(type1 == "bool" && type2 == "int"){
        strcpy(($$).type, type2.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
        x86(nl + newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
        funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        x86("movq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
        x86("cmp\t$0,\t%rdx");
        x86("jne\t\t1f");
        x86("movq\t$0,\t%rdx");
        x86("jmp\t2f");
        x86("1:");
        x86("movq\t$1,\t%rdx");
        x86("2:");
        x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
        strcpy(($1).temp, newt.c_str());
      }
      else if(type1 == "int" && type2 == "float"){
        strcpy(($$).type, type2.c_str());
        // typecast $1 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type2 + " " + to_string(($1).temp));
        strcpy(($1).temp, newt.c_str());
      }
      else if(type1 == "float" && type2 == "int"){
        strcpy(($$).type, type1.c_str());
        // typecast $3 to bool
        string newt = t_new();
        gen(newt + " = cast_to_" + type1 + " " + to_string(($3).temp));
        strcpy(($3).temp, newt.c_str());
      }
      else{
        cerr << ($1).linenum << ": Error: invalid operation '" << to_string(($2).token_lex) << "' for types '" << type1 << "' and '" << type2 << "'\n";
        exit(0);
      }
    }

  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).temp) + " ** " + to_string(($3).temp));

  x86(nl + to_string(($$).temp) + " = " + to_string(($1).temp) + " ** " + to_string(($3).temp));
  string exponent_index = t_new();
  funcrbp[exponent_index] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t$0,\t" + funcrbp[exponent_index] + "(%rbp)");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t$1,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  x86("jmp\t\t2f");
  x86("1:");
  x86("movq\t" + funcrbp[exponent_index] + "(%rbp),\t%rdx");
  x86("addq\t$1,\t%rdx");
  x86("movq\t%rdx,\t" + funcrbp[exponent_index] + "(%rbp)");
  x86("2:");
  x86("movq\t" + funcrbp[exponent_index] + "(%rbp),\t%rdx");
  x86("movq\t" + funcrbp[to_string(($3).temp)] + "(%rbp),\t%rcx");
  x86("cmp\t\t%rdx,\t%rcx");
  x86("je\t\t3f"); 
  x86("movq\t" + funcrbp[to_string(($$).temp)] + "(%rbp),\t%rdx");
  x86("imulq\t" + funcrbp[to_string(($1).temp)] + "(%rbp),\t%rdx");
  x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  x86("jmp\t\t1b");
  x86("3:");







}

// pending
atom_expr:
atom Multi_trailer      {
  ($$).isfunccall = ($2).isfunccall;
  strcpy(($$).lexeme, ($1).lexeme);
  strcat(($$).lexeme, ($2).lexeme);
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

  string myString = to_string(($$).lexeme);
  int count_at = count(myString.begin(), myString.end(), '@');
  if(count_at >= 2){
    size_t pos = myString.find('@');
    string head = myString.substr(0, pos);
    cerr << ($1).linenum << "Error : '"<< head <<"' indexed with more indices than its dimension" << endl;
    exit(0);
  }

  if(($1).isname){

    int has_dot = 0, has_bracket = 0;
    size_t pos_dot = to_string(($$).lexeme).find(".");
    if (pos_dot != string::npos) has_dot = 1;
    size_t pos_bracket = to_string(($$).lexeme).find("@");
    if (pos_bracket != string::npos) has_bracket = 1;

    if(has_bracket && !has_dot && all_types.find(to_string(($$).lexeme)) == all_types.end()){
      
        if(to_string(($2).indextype) != "int"){
          cerr << ($1).linenum << ": Error: index is not integer type \n";
          exit(0);
        }
        if(curr_table->lookup(to_string(($1).lexeme)).token != "null"){

            string name1_type = curr_table->lookup(to_string(($1).lexeme)).type;
            if(name1_type.substr(0,5) != "list@"){
              cerr << ($1).linenum << ": Error: '" << to_string(($1).lexeme) << "' is not a list, cannot be indexed" << endl;
              exit(0);
            }
            string list_type = name1_type;
            if(list_type.size() > 5){
              string without_list_type = list_type.substr(5);
              strcpy(($$).type, without_list_type.c_str());
            }
        }
        else{
            cerr << ($1).linenum << ": Error: undeclared variable '" << to_string(($1).lexeme) << "'" << endl;
            exit(0);
        }

        string index_lexeme = to_string(($$).lexeme).substr(pos_bracket+1);
        string temp_ = t_new();
        funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        int typesize = type_size(to_string(($$).type));
        gen(temp_ + " = " + to_string(($2).tempsquare) + " * " + to_string(typesize));
        x86(nl + temp_ + " = (" + to_string(($2).tempsquare) + " + 1) * " + to_string(typesize));
        // x86("sub\t\t$8,\t%rsp");
        x86("movq\t" + funcrbp[to_string(($2).tempsquare)] + "(%rbp),\t%rdx");
        x86("addq\t$1,\t%rdx");
        x86("imulq\t$" + to_string(typesize) + ",\t%rdx");
        x86("movq\t%rdx,\t" + funcrbp[temp_] + "(%rbp)");

        string temp1 = t_new();
        funcrbp[temp1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
        gen(temp1 + " = *(" + to_string(($1).lexeme) + " + " + temp_ + ")");
        x86(nl + temp1 + " = *(" + to_string(($1).lexeme) + " + " + temp_ + ")");
        // x86("sub\t\t$8,\t%rsp");
        x86("movq\t" + funcrbp[to_string(($1).lexeme)] + "(%rbp),\t%rdx");
        x86("addq\t" + funcrbp[temp_] + "(%rbp),\t%rdx");
        x86("movq\t(%rdx),\t%rcx");
        x86("movq\t%rcx,\t" + funcrbp[temp1] + "(%rbp)");
        strcpy(($$).temp, temp1.c_str());


          // important: Checking if index is in range

        
    }
    else if(has_bracket && has_dot){
      string input = to_string(($$).lexeme);
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
          cerr << ($1).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
          exit(0);
      }
      Symbol_Table *class_table = class_symbol_tables[class_name];
      string attribute = part2;
      if(class_table->lookup("self."+attribute).token == "null"){
        cerr << ($1).linenum << ": Error: Unidentified attribute " << attribute << " in class " << class_name << " at line " << ($1).linenum << "\n";
        exit(0);
      }


      if(to_string(($2).indextype) != "int"){
        cerr << ($1).linenum << ": Error: index is not integer type\n";
        exit(0);
      }

      
      string name1_type = class_table->lookup("self."+attribute).type;
      if(name1_type.substr(0,5) != "list@"){
        cerr << ($1).linenum << ": Error: '" << part1+"."+part2 << "' is not a list, cannot be indexed " << endl;
      exit(0);
      }
      string list_type = name1_type;
      if(list_type.size() > 5){
        string without_list_type = list_type.substr(5);
        strcpy(($$).type, without_list_type.c_str());
      }

      
      string temp_ = t_new();
      int typesize = type_size(to_string(($$).type));
      gen(temp_ + " = " + to_string(($2).tempsquare) + " * " + to_string(typesize));
      x86(nl + temp_ + " = (" + to_string(($2).tempsquare) + " + 1) * " + to_string(typesize));
      funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      // x86("sub\t\t$8,\t%rsp");
      x86("movq\t" + funcrbp[to_string(($2).tempsquare)] + "(%rbp),\t%rdx");
      x86("addq\t$1,\t%rdx");
      x86("imulq\t$" + to_string(typesize) + ",\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[temp_] + "(%rbp)");
      string offset_ = to_string(class_table->lookup("self."+attribute).offset);
      string temp1 = t_new();
      // funcrbp[temp1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      gen(temp1 + " = " + "*(" + part1 + " + " + offset_ + ") ");
      x86(nl + temp1 + " = *(" + part1 + " + " + offset_ + ")");
      // x86("sub\t\t$8,\t%rsp");
      x86("movq\t" + funcrbp[part1] + "(%rbp),\t%rdx");
      x86("addq\t$" + offset_ + ",\t%rdx");
      x86("movq\t(%rdx),\t%rcx");

      

      string temp_result = t_new();
      gen(temp_result + " = *(" + temp1 + " + " + temp_ + ")");
      funcrbp[temp_result] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
      x86(nl + temp_result + " = *(" + temp1 + " + " + temp_ + ")");
      // x86("sub\t\t$8,\t%rsp");
      x86("addq\t" + funcrbp[temp_] + "(%rbp),\t%rcx");
      x86("movq\t(%rcx),\t%rdx");
      x86("movq\t%rdx,\t" + funcrbp[temp_result] + "(%rbp)");
      strcpy(($$).temp, temp_result.c_str());

    }



    

    ///////// DOT exists
    else if (pos_dot != string::npos) {
        size_t pos = pos_dot;
        string object_name = to_string(($1).lexeme);
        if(curr_table->lookup(object_name).token == "null"){
            cerr << ($1).linenum << ": Error: undeclared object or class '" << object_name << "'\n";
            exit(0);
        }
        else{
              /////// the name before dot is class name
              if((curr_table->lookup(object_name)).token == "Class"){
                string class_name = object_name;
                //// An attribute - NOT ALLOWED
                if(!($$).isfunccall){
                  cerr << ($1).linenum << ": Error: accessing attributes of class '" << class_name << "' without the mention of object not allowed\n";
                  exit(0);
                }

                //// A method - allowed with self mention 
                else{
                  // if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
                  //     cerr << ($1).linenum << ": Error: Invalid object type " << class_name << " at line " << ($1).linenum << "\n";
                  //     exit(0);
                  // }
                  Symbol_Table *class_table = class_symbol_tables[class_name];
                  string attribute = to_string(($$).lexeme).substr(pos+1);

                  if(class_table->lookup(attribute).token == "null"){
                    cerr << ($1).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
                    exit(0);
                  }
                  else if (class_table->lookup(attribute).token != "Function"){
                    cerr << ($1).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
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
                          cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << attribute << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                          exit(0); 
                        }
                        if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                          if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                            if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                              // types are not same, typecast arg to param type
                              if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                                string newt = t_new();
                                gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                                // final remaining
                                if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                                  funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                                  x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                                  x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                                  x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                                }

                                if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                                  funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                                  x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                                  x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                                  x86("cmp\t$0,\t%rdx");
                                  x86("jne\t\t1f");
                                  x86("movq\t$0,\t%rdx");
                                  x86("jmp\t2f");
                                  x86("1:");
                                  x86("movq\t$1,\t%rdx");
                                  x86("2:");
                                  x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                                }
                                func_arg_temp_vec[(it->second).argnum -1].second = newt;
                              }
                              
                            }
                            func_params_size += type_size((it->second).type);
                          }
                          else{
                            // types dont match even after typecasting
                            cerr << ($1).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ($1).linenum << "\n";
                            exit(0); // adapter

                          }
                        }
                      }

                      int flag = 0;
                        if(func_arg_temp_vec.size()%2 == 0){
                          x86(nl + "aligning stack");
                          x86("pushq\t$0");
                          flag = 1;
                          // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                        } 

                        string b = class_name;
                        while (child_to_parent_classes.find(b) != child_to_parent_classes.end()){
                          string a = child_to_parent_classes[b];
                          Symbol_Table *parent_table = class_symbol_tables[a];
                          if(parent_table->lookup(attribute).token == "Function"){
                            b = a;
                          }
                          else{
                            break;
                          }
                        }

                        x86("\n# funccall " + to_string(($$).lexeme));
                        x86("pushq\t%rax");
                        x86("pushq\t%rcx");
                        x86("pushq\t%rdx");
                        x86("pushq\t%r8");
                        x86("pushq\t%r9");
                        x86("pushq\t%r10");
                        x86("pushq\t%r11");

                      strcpy(($$).type, func_defn.type.c_str());
                      // gen("pushparam " +  object_name);
                      for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
                        gen("pushparam " + func_arg_temp_vec[i].second);
                        x86(nl + "pushparam " + func_arg_temp_vec[i].second);
                        x86("movq\t" + funcrbp[func_arg_temp_vec[i].second] + "(%rbp),\t%rbx");
                        x86("pushq\t%rbx");
                      }
                      gen("push ret_addr");
                      gen("sub %rsp " + to_string(func_params_size));
                      gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
                      x86(nl + "call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
                      x86("call\t" + b + "." + attribute);

                      gen("add %rsp " + to_string(func_params_size));
                      x86("add\t\t$" + to_string(func_params_size) + ",\t%rsp");

                      if(func_defn.type != "None"){
                          string temp_result = t_new();
                          gen(temp_result + " = %rax");
                          strcpy(($$).temp, temp_result.c_str());
                          x86(nl + temp_result + " = %rax");
                          funcrbp[temp_result] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                          x86("movq\t%rax,\t" + funcrbp[temp_result] + "(%rbp)");
                      }

                      x86("popq\t%r11");
                      x86("popq\t%r10");
                      x86("popq\t%r9");
                      x86("popq\t%r8");
                      x86("popq\t%rdx");
                      x86("popq\t%rcx");
                      x86("popq\t%rax");
                      if(flag){
                        x86("add\t\t$8,\t%rsp");
                      }

                  }

                }
              }

              /////// the name before dot is object name
              else{
                  string class_name = (curr_table->lookup(object_name)).type; 
                  if (class_symbol_tables.find(class_name) == class_symbol_tables.end()) {
                      cerr << ($1).linenum << ": Error: invalid object type / undeclared class '" << class_name << "'\n";
            exit(0);
                  }
                  Symbol_Table *class_table = class_symbol_tables[class_name];
                  string attribute = to_string(($$).lexeme).substr(pos+1);

                  //////// An attribute 
                  if(!($$).isfunccall){
                      if(class_table->lookup("self."+attribute).token == "null"){
                        cerr << ($1).linenum << ": Error: undeclared attribute '" << attribute << "' in class '" << class_name << "'\n";
          exit(0);
                      }
                      else {
                        if(class_table->lookup("self."+attribute).isinit == 0){
                          cerr << ($1).linenum << ": Error: uninitialised attribute '" << attribute << "' in class '" << class_name << "'\n";
          exit(0);
                        }
                        string attribute_type = class_table->lookup("self."+attribute).type;
                        strcpy(($$).type, attribute_type.c_str());
                        string temp_ = t_new();
                        string offset_ = to_string(class_table->lookup("self."+attribute).offset);
                        gen(temp_ + " = *(" + object_name + " + " + offset_ + ")");
                        funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                        x86(nl + temp_ + " = *(" + object_name + " + " + offset_ + ")");
                        x86("movq\t" + funcrbp[object_name] + "(%rbp),\t%rdx");
                        x86("addq\t$" + offset_ + ", %rdx");
                        x86("movq\t(%rdx),\t%rcx");
                        x86("movq\t%rcx,\t" + funcrbp[temp_] + "(%rbp)");
                        strcpy(($$).temp, temp_.c_str());
                      }
                  }
                  
                  ///////////// A method 
                  if(($$).isfunccall){
                    if(class_table->lookup(attribute).token == "null"){
                      cerr << ($1).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";
          exit(0);
                    }
                    else if (class_table->lookup(attribute).token != "Function"){
                    cerr << ($1).linenum << ": Error: undeclared method '" << attribute << "' in class '"<< class_name << "' called" << "\n";                      exit(0);
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
                            cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << attribute << "' method in class " << class_name << ", expected " << num_args << " argument(s)" << endl;
                          exit(0); 
                          }
                          if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                            if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                              if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                                // types are not same, typecast arg to param type
                                if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                                  string newt = t_new();
                                  gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                                  // final remaining 2
                                  if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                                    funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                                    x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                                    x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                                    x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                                  }

                                  if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                                    funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                                    x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                                    x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                                    x86("cmp\t$0,\t%rdx");
                                    x86("jne\t\t1f");
                                    x86("movq\t$0,\t%rdx");
                                    x86("jmp\t2f");
                                    x86("1:");
                                    x86("movq\t$1,\t%rdx");
                                    x86("2:");
                                    x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                                  }
                                  func_arg_temp_vec[(it->second).argnum -2].second = newt;
                                }
                              }
                              func_params_size += type_size((it->second).type);
                            }
                            else{
                              // types dont match even after typecasting
                              cerr << ($1).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ($1).linenum << "\n";
                              exit(0); // adapter

                            }
                          }
                        }
                        
                        int flag = 0;
                        if(func_arg_temp_vec.size()%2 != 0){
                          x86(nl + "aligning stack");
                          x86("pushq\t$0");
                          flag = 1;
                          // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                        } 

                        string b = class_name;
                        while (child_to_parent_classes.find(b) != child_to_parent_classes.end()){
                          string a = child_to_parent_classes[b];
                          Symbol_Table *parent_table = class_symbol_tables[a];
                          if(parent_table->lookup(attribute).token == "Function"){
                            b = a;
                          }
                          else{
                            break;
                          }
                        }

                        x86("\n# funccall " + to_string(($$).lexeme));
                        x86("pushq\t%rax");
                        x86("pushq\t%rcx");
                        x86("pushq\t%rdx");
                        x86("pushq\t%r8");
                        x86("pushq\t%r9");
                        x86("pushq\t%r10");
                        x86("pushq\t%r11");




                        strcpy(($$).type, func_defn.type.c_str());
                        
                        for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
                          gen("pushparam " + func_arg_temp_vec[i].second);
                          x86(nl + "pushparam " + func_arg_temp_vec[i].second);
                          x86("movq\t" + funcrbp[func_arg_temp_vec[i].second] + "(%rbp),\t%rbx");
                          x86("pushq\t%rbx");
                        }
                        gen("pushparam " +  object_name);
                        x86(nl + "pushparam " + object_name);
                        x86("movq\t" + funcrbp[object_name] + "(%rbp),\t%rbx");
                        x86("pushq\t%rbx");

                        gen("push ret_addr");
                        gen("sub %rsp " + to_string(func_params_size));
                        gen("call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
                        x86(nl + "call " + class_name + "." + attribute + " " + to_string(func_arg_vec.size()));
                        x86("call\t" + b + "." + attribute);

                        gen("add %rsp " + to_string(func_params_size));
                        x86("add\t\t$" + to_string(func_params_size) + ",\t%rsp");

                        if(func_defn.type != "None"){
                            string temp_result = t_new();
                            gen(temp_result + " = %rax");
                            strcpy(($$).temp, temp_result.c_str());
                            x86(nl + temp_result + " = %rax");
                            funcrbp[temp_result] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                            x86("movq\t%rax,\t" + funcrbp[temp_result] + "(%rbp)");

                        }

                        x86("popq\t%r11");
                        x86("popq\t%r10");
                        x86("popq\t%r9");
                        x86("popq\t%r8");
                        x86("popq\t%rdx");
                        x86("popq\t%rcx");
                        x86("popq\t%rax");
                        if(flag){
                          x86("add\t\t$8,\t%rsp");
                        }

                    }
                    
                  }
              }
              
        }
    } 

    //////// DOT doesnt exist
    else {
      ////////// A function 
      if(($$).isfunccall){
        auto it = all_types.find(to_string(($$).lexeme));
        if (it == all_types.end()){
            if(curr_table->lookup(to_string(($$).lexeme)).token == "null"){
              if (to_string(($$).lexeme) == "len"){
                string int_ = "int";
                strcpy(($$).type, int_.c_str());
                if(func_arg_vec.size()!=1){
                    cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'len' function, expected 1 argument" << endl;
                exit(0);
                }
                if(func_arg_vec[0].second.size() > 5){
                    if(func_arg_vec[0].second.substr(0,5) != "list@"){
                      cerr << ($1).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
                  exit(0);
                    }
                }
                else{
                      cerr << ($1).linenum << ": Error: non-list type argument passed in 'len' function, expected list type argument" << endl;
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
                funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                gen(temp_ + " = %rax");
                x86(nl + temp_ + " = len(" + func_arg_temp_vec[0].second + ") = *(" + func_arg_temp_vec[0].second + ")");
                // x86("sub\t\t$8,\t%rsp");
                x86("movq\t" + funcrbp[func_arg_temp_vec[0].second] + "(%rbp),\t%rdx");
                x86("movq\t(%rdx),\t%rax");
                x86("cqto");
                x86("movq\t$8,\t%rbx");
                x86("idivq\t%rbx");
                x86("subq\t$1,\t%rax");
                x86("movq\t%rax,\t" + funcrbp[temp_] + "(%rbp)");
                
                
                strcpy(($$).temp, temp_.c_str()); // come back here

              }
              else if (to_string(($$).lexeme) == "range"){
                string none = "None";
                strcpy(($$).type, none.c_str());
                if(func_arg_vec.size() > 2 || func_arg_vec.size() < 1){
                  cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " arguments passed in 'range' function, expected 1 or 2 arguments" << endl;
                exit(0);
                }
                else if (func_arg_vec.size() == 2){
                  if(func_arg_vec[0].second != "int"){
                    cerr << ($1).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                  }
                  if(func_arg_vec[1].second != "int"){
                    cerr << ($1).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                  }
                  range_start = func_arg_temp_vec[0].second;
                  range_end = func_arg_temp_vec[1].second;
                }
                else if( func_arg_vec.size() == 1){
                  if(func_arg_vec[0].second != "int"){
                    cerr << ($1).linenum << ": Error: non-int type argument(s) passed in 'range' function, expected int type argument(s)" << endl;
                  exit(0);
                  }
                  string temp_ = t_new();
                  gen(temp_ + " = 0");
                  x86(nl + temp_ + "= 0");
                  funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                  x86("movq\t$0," + funcrbp[temp_] + "(%rbp)");
                  range_start = temp_;
                  range_end = func_arg_temp_vec[0].second;
                }
              }
              else{
                cerr << ($1).linenum << ": Error: undeclared function '" << to_string(($$).lexeme) << "' called\n";
            exit(0);
              }
              
            }
            else if (curr_table->lookup(to_string(($$).lexeme)).token != "Function"){

              cerr << ($1).linenum << ": Error: undeclared function '" << to_string(($$).lexeme) << "' called\n";
            exit(0);
            }

            else{
              /// funccall is valid 
              // now check for arguments
              Symbol_Table_Entry func_defn = curr_table->lookup(to_string(($1).lexeme));
              // func_defn.print_sym_entry();
              Symbol_Table* func_table = (Symbol_Table*)func_defn.childtable;
              int num_args = func_defn.numargs;
              int func_params_size = 0;
              for(auto it = (func_table->table).begin(); it!= (func_table->table).end(); it++){
                // num_args = (it->second).numargs;
                if((long unsigned int)num_args != func_arg_vec.size()){
                  // number of args and param dont match 
                  cerr << ($1).linenum << ": Error: " << func_arg_vec.size() << " argument(s) passed in '" << to_string(($$).lexeme) << "' function, expected " << num_args << " argument(s)" << endl;
            exit(0);
                }
                if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
                  if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                    if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                      // types are not same, typecast arg to param type
                      if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                        string newt = t_new();
                        gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                        // final remaining
                        if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                          funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                          x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                          x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                          x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                        }

                        if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                          funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                          x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -1].second);
                          x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -1].second] + "(%rbp), %rdx");
                          x86("cmp\t$0,\t%rdx");
                          x86("jne\t\t1f");
                          x86("movq\t$0,\t%rdx");
                          x86("jmp\t2f");
                          x86("1:");
                          x86("movq\t$1,\t%rdx");
                          x86("2:");
                          x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                        }
                        func_arg_temp_vec[(it->second).argnum -1].second = newt;
                      }
                    }
                    func_params_size += type_size((it->second).type);
                  }
                  else{
                    // types dont match even after typecasting
                    cerr << ($1).linenum << ": Error: Types of function call arguments do not match types of function parameters at line " << ($1).linenum << "\n";
                    exit(0); // adapter

                  }
                }
              }
              int flag = 0;
              if(func_arg_temp_vec.size()%2 == 0){
                x86(nl + "aligning stack");
                x86("pushq\t$0");
                flag = 1;
                // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
              } // legital
              // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 != 0 && func_arg_temp_vec.size()%2 == 0){
              //   x86(nl + "aligning stack");
              //   x86("pushq\t$0");
              //   flag = 1;
              //   // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
              // } // legital 

              x86("\n# funccall " + to_string(($$).lexeme));
              x86("pushq\t%rax");
              x86("pushq\t%rcx");
              x86("pushq\t%rdx");
              x86("pushq\t%r8");
              x86("pushq\t%r9");
              x86("pushq\t%r10");
              x86("pushq\t%r11");

              
              strcpy(($$).type, func_defn.type.c_str());
              for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
                gen("pushparam " + func_arg_temp_vec[i].second);
                x86(nl + "pushparam " + func_arg_temp_vec[i].second);
                x86("movq\t" + funcrbp[func_arg_temp_vec[i].second] + "(%rbp),\t%rbx");
                x86("pushq\t%rbx");
              }
              gen("push ret_addr");
              gen("sub %rsp " + to_string(func_params_size));
              gen("call " + to_string(($1).lexeme) + " " + to_string(func_arg_vec.size()));
              x86(nl + "call " + to_string(($1).lexeme) + " " + to_string(func_arg_vec.size()));
              x86("call\t" + to_string(($1).lexeme));
              gen("add %rsp " + to_string(func_params_size)); // might need to change to func_arg_vec.size()*8 
              x86("add\t\t$" + to_string(func_params_size) + ",\t%rsp"); // might need to change to func_arg_vec.size()*8 
              string temp_ = t_new();
              gen(temp_ + " = %rax" );
              x86(nl + temp_ + " = %rax" );
              funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
              x86("mov\t\t%rax,\t" + funcrbp[temp_] + "(%rbp)");
              x86("popq\t%r11");
              x86("popq\t%r10");
              x86("popq\t%r9");
              x86("popq\t%r8");
              x86("popq\t%rdx");
              x86("popq\t%rcx");
              x86("popq\t%rax");
              if(flag){
                x86("add\t\t$8,\t%rsp");
              }
              strcpy(($$).temp, temp_.c_str());

            }

        }
        if (class_symbol_tables.find(to_string(($$).lexeme)) != class_symbol_tables.end()) {
          string class_name = to_string(($$).lexeme);
          // cout << "class_name: " << class_name << "\n";
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
              cerr << ($1).linenum << "Error : Number of constructor call arguments do not match number of constructor parameters of class " << class_name << " at line " << ($1).linenum << "\n";
              exit(0); // adapter
            }
            if((it->second).argnum -1 < num_args && (it->second).argnum -1 >= 0){
              if(match_type((it->second).type, func_arg_vec[(it->second).argnum -1].second)){
                if((it->second).type != func_arg_vec[(it->second).argnum -1].second){
                  // types are not same, typecast arg to param type
                  if((it->second).type == "int" || (it->second).type == "float" || (it->second).type == "bool"){
                    string newt = t_new();
                    gen(newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                    // final remaining 2
                    if((it->second).type == "int" && func_arg_vec[(it->second).argnum -1].second == "bool"){
                      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                      x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                      x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                    }

                    if((it->second).type == "bool" && func_arg_vec[(it->second).argnum -1].second == "int"){
                      funcrbp[newt] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
                      x86(nl + newt + " = cast_to_" + (it->second).type + " " + func_arg_temp_vec[(it->second).argnum -2].second);
                      x86("movq\t" + funcrbp[func_arg_temp_vec[(it->second).argnum -2].second] + "(%rbp), %rdx");
                      x86("cmp\t$0,\t%rdx");
                      x86("jne\t\t1f");
                      x86("movq\t$0,\t%rdx");
                      x86("jmp\t2f");
                      x86("1:");
                      x86("movq\t$1,\t%rdx");
                      x86("2:");
                      x86("movq\t%rdx,\t" + funcrbp[newt] + "(%rbp)");
                    }
                    func_arg_temp_vec[(it->second).argnum -2].second = newt;
                  }

                }
                func_params_size += type_size((it->second).type);
              }
              else{
                // types dont match even after typecasting
              cerr << ($1).linenum << "Error : Types of constructor call arguments do not match types of constructor parameters of class " << class_name << " at line " << ($1).linenum << "\n";
                exit(0); // adapter

              }
            }
          }



          strcpy(($$).type, func_defn.type.c_str());
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
          x86(nl + temp_size + " = " + to_string(class_size));
          funcrbp[temp_size] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
          x86("movq\t$" + to_string(class_size) + ",\t" + funcrbp[temp_size] + "(%rbp)");
          gen("pushparam " + temp_size);
          gen("sub %rsp 4");
          gen("call allocmem 1");
          x86(nl + "call malloc " + to_string(class_size));
          x86("movq\t" + funcrbp[temp_size] + "(%rbp),\t%rdi");
          x86("call\tmalloc@PLT");
          gen("add %rsp 4");

          string temp_self = t_new();
          funcrbp[temp_self] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
          gen(temp_self + " = %rax");
          x86(nl + temp_self + " = %rax");
          x86("movq\t%rax,\t" + funcrbp[temp_self] + "(%rbp)");

          int flag = 0;
          if(func_arg_temp_vec.size()%2 != 0){
            x86(nl + "aligning stack");
            x86("pushq\t$0");
            flag = 1;
            // funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
          } 

          x86("\n# funccall " + to_string(($$).lexeme));
          x86("pushq\t%rax");
          x86("pushq\t%rcx");
          x86("pushq\t%rdx");
          x86("pushq\t%r8");
          x86("pushq\t%r9");
          x86("pushq\t%r10");
          x86("pushq\t%r11");
          
          for(int i = (int)func_arg_temp_vec.size() - 1; i >= 0; i--){
            gen("pushparam " + func_arg_temp_vec[i].second);
            x86(nl + "pushparam " + func_arg_temp_vec[i].second);
            x86("movq\t" + funcrbp[func_arg_temp_vec[i].second] + "(%rbp),\t%rbx");
            x86("pushq\t%rbx");
          }
          gen("pushparam " +  temp_self);
          x86(nl + "pushparam " + temp_self);
          x86("movq\t" + funcrbp[temp_self] + "(%rbp),\t%rbx");
          x86("pushq\t%rbx");
          gen("push ret_addr");
          gen("sub %rsp " + to_string(func_params_size));
          gen("call " + class_name + ".__init__ " + to_string(func_arg_vec.size()));
          x86(nl + "call " + class_name + ".__init__ " + to_string(func_arg_vec.size()));
          x86("call " + class_name + ".__init__ ");

          gen("add %rsp " + to_string(func_params_size));
          x86("add\t\t$" + to_string(func_params_size) + ",\t%rsp"); 
          // string temp_result = t_new();
          // gen(temp_result + " = %rax");
          x86("popq\t%r11");
          x86("popq\t%r10");
          x86("popq\t%r9");
          x86("popq\t%r8");
          x86("popq\t%rdx");
          x86("popq\t%rcx");
          x86("popq\t%rax");
          if(flag){
            x86("add\t\t$8,\t%rsp");
          }
          strcpy(($$).temp, temp_self.c_str());
          


        }


      }

      ////////// A variable
      else{
    
        auto it = all_types.find(to_string(($$).lexeme));
        if (it == all_types.end()){
          if(curr_table->lookup(to_string(($$).lexeme)).token == "null" || curr_table->lookup(to_string(($$).lexeme)).token == "Function"){
            if(to_string(($$).lexeme) != "__name__"){
              cerr << ($1).linenum << ": Error: undeclared variable '" << to_string(($$).lexeme) << "'\n";
              exit(0); 
            }
          } 
          else{
            if(curr_table->lookup(to_string(($$).lexeme)).isinit == 0){
              cerr << ($1).linenum << ": Error: uninitialised variable '" << to_string(($$).lexeme) << "'\n";
            exit(0);
            }
            string variable_type = curr_table->lookup(to_string(($$).lexeme)).type;
            strcpy(($$).type, variable_type.c_str());
          }
        }
      }
    }
  }

  if(($$).isfunccall){
    func_arg_vec.clear();
    func_arg_temp_vec.clear();
  }
}

Multi_trailer:
%empty             {
  ($$).lexeme[0] = '\0';
  ($$).isfunccall = 0;
}
| trailer Multi_trailer      {
  ($$).isfunccall = ($1).isfunccall || ($2).isfunccall;
  strcpy(($$).lexeme, ($1).lexeme);
  strcat(($$).lexeme, ($2).lexeme);
  strcpy(($$).tempsquare, ($1).tempsquare);
  strcat(($$).tempsquare, ($2).tempsquare);
  if(to_string(($2).indextype).size() != 0){
    strcpy(($$).indextype, ($2).indextype);
  }
  else{
    strcpy(($$).indextype, ($1).indextype);
  }
  // strcpy(($$).type, ($1).type);
}

atom:
OPEN_ROUND_BRACKET Opt_test CLOSE_ROUND_BRACKET      {
    strcpy(($$).type, ($2).type);
    strcpy(($$).temp, ($2).temp);
    strcpy(($$).lexeme, ($2).lexeme);
    ($$).linenum = ($1).linenum;

}
| OPEN_SQUARE_BRACKET testlist CLOSE_SQUARE_BRACKET      {
  // hardddddddddddddddddddd
  // all list handling
  // type checking needed
  
  // string list_at = "list@";
  
  ($$).linenum = ($1).linenum;
  strcpy(($$).type, ($2).type);
  string type_list = to_string(($2).type);
  string type_index;
  if(type_list.size() > 5){
    type_index = type_list.substr(5);
  }

  int type_size_ = type_size(type_index);
  int total_size = type_size_*list_temps.size();

  reverse(list_temps.begin(), list_temps.end());

  string temp1 = t_new();
  gen(temp1 + " = " + to_string(total_size));
  x86(nl + temp1 + " = " + to_string(total_size + 8));
  // x86("sub\t\t$8,\t%rsp");
  funcrbp[temp1] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t$" + to_string(total_size + 8) + ",\t" + funcrbp[temp1] + "(%rbp)");
  gen("pushparam " + temp1);
  
  // cout << -64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()) << endl;
  // if((-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size())) % 16 == 0){
  //   x86(nl + "aligning stack");
  //   x86("pushq\t$0");
  //   funcrbp[dummy()] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  // } // legital 
  x86(nl + "pushparam " + temp1);
  x86("movq\t" + funcrbp[temp1] + "(%rbp),\t%rdi");
  x86("call\tmalloc@PLT");

  gen("push ret_addr");
  gen("sub %rsp 4");
  gen("call allocmem 1");
  gen("add %rsp 4");
  string temp_ = t_new();
  
  gen(temp_ + " = %rax");
  x86(nl + temp_ + " = %rax");
  // x86("sub\t\t$8,\t%rsp");
  funcrbp[temp_] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t%rax,\t" + funcrbp[temp_] + "(%rbp)");
  x86(nl + "len of list " +  + " = " + temp1);
  x86("movq\t" + funcrbp[temp_] + "(%rbp),\t%rdx");
  x86("addq\t$" + to_string(0) + ",\t%rdx");
  x86("movq\t" + funcrbp[temp1] + "(%rbp),\t%rax");
  x86("movq\t%rax,\t(%rdx)");
  // gen("*(" + temp_ + " + " + to_string(0) + ")" + " = " + to_string(list_temps.size()));
  for(auto it = 0; it < (int)list_temps.size(); it++){
    
    gen("*(" + temp_ + " + " + to_string(it * type_size_) + ")" + " = " + list_temps[it]);
    x86(nl + "*(" + temp_ + " + " + to_string((it + 1) * type_size_) + ")" + " = " + list_temps[it]);
    x86("movq\t" + funcrbp[temp_] + "(%rbp),\t%rdx");
    x86("addq\t$" + to_string((it + 1) * type_size_) + ",\t%rdx");
    x86("movq\t" + funcrbp[list_temps[it]] + "(%rbp),\t%rax");
    x86("movq\t%rax,\t(%rdx)");
  }
  strcpy(($$).temp, temp_.c_str());
  int list_size = list_temps.size();
  ($$).listsize = list_size;
  list_temps.clear();
  //   strcpy(($$).type, );
  // }
}
| NAME      {
  ($$).linenum = ($1).linenum;
  strcpy(($$).lexeme, ($1).token_lex);
  ($$).isname = 1;
  if(curr_table->lookup(to_string(($1).token_lex)).token != "null"){
    string name_type = curr_table->lookup(to_string(($1).token_lex)).type;
    strcpy(($$).type, name_type.c_str());
    // string one = "1";
    // strcat(($$).type, one.c_str());

  }
  if(curr_table->lookup(to_string(($1).token_lex)).token != "null"){
    int name_type = curr_table->lookup(to_string(($1).token_lex)).listlen;
    ($$).listsize = name_type;
    // string one = "1";
    // strcat(($$).type, one.c_str());

  }
  if(to_string(($1).token_lex) == "__name__") {
    string str_ = "str";
    strcpy(($$).type, str_.c_str());
  }
  strcpy(($$).temp , ($1).token_lex);
  // strcpy(($$).type, "name");
}
// 

| NUMBER      {
  ($$).linenum = ($1).linenum;
  // should assign int and float types
   if(to_string(($1).token_type) == "int")strcpy(($$).type, "int");
   if(to_string(($1).token_type) == "float")strcpy(($$).type, "float");
   strcpy(($$).temp , t_new().c_str());
   gen(to_string(($$).temp) + " = " + to_string(($1).token_lex));
   x86(nl + to_string(($$).temp) + " = " + to_string(($1).token_lex));
   // x86("sub\t\t$8,\t%rsp");
   funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
   x86("movq\t$" + to_string(($1).token_lex) + ",\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
   ($$).isname = 0;
}
| STRING    {
  ($$).linenum = ($1).linenum;
    // should assign string types
    string token_lex = to_string(($1).token_lex);
    string final_lex = "";
    if(token_lex[0] == '\''){
      for(int i = 0; i < (int)token_lex.size(); i++){
        if(token_lex[i] == '\''){
          token_lex[i] = '\"';
          final_lex += "\"";
        }
        else if(token_lex[i] == '\"'){
          token_lex[i] = '\'';
          final_lex += "\\\"";
        }
        else{
          final_lex += token_lex[i];
        }
      }
    }
    if(final_lex.size() == 0) final_lex = token_lex;
    // cout << final_lex << endl;
    strcpy(($1).token_lex, final_lex.c_str());
    string str_ = "str";
    strcpy(($$).type, str_.c_str());
    strcpy(($$).temp , t_new().c_str());
    gen(to_string(($$).temp) + " = " + to_string(($1).token_lex));
    ($$).isname = 0;
    x86(nl + to_string(($$).temp) + " = " + to_string(($1).token_lex));
    // x86("sub\t\t$8,\t%rsp");
    funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
    x86("leaq\t.LC" + to_string((string_count/2)) + "(%rip),\t%rdx");
    x86("movq\t%rdx,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
    code_x86.insert(code_x86.begin() + string_count, ".LC" + to_string((string_count/2)) + ":");
    code_x86.insert(code_x86.begin() + string_count + 1, ".string\t" + to_string(($1).token_lex));
    string_count += 2;
    func_stack_offset += 2;

}
| NONE      {
  ($$).linenum = ($1).linenum;
// should assign None types
string none_ = "None";
strcpy(($$).type, none_.c_str());
($$).isname = 0;
}
| TRUE      {
  ($$).linenum = ($1).linenum;
  // should assign bool types
//   ($$).size = 1;
  string bool_ = "bool";
  strcpy(($$).type, bool_.c_str());
  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).token_lex));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).token_lex));
  // x86("sub\t\t$8,\t%rsp");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t$1,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  ($$).isname = 0;
}
| FALSE      {
  ($$).linenum = ($1).linenum;
  // should assign bool types
//   ($$).size = 1;
  string bool_ = "bool";
  strcpy(($$).type, bool_.c_str());
  strcpy(($$).temp , t_new().c_str());
  gen(to_string(($$).temp) + " = " + to_string(($1).token_lex));
  x86(nl + to_string(($$).temp) + " = " + to_string(($1).token_lex));
  // x86("sub\t\t$8,\t%rsp");
  funcrbp[to_string(($$).temp)] = to_string(-64 - 8*((int)funcrbp.size() - (int)func_param_vec.size()));
  x86("movq\t$0,\t" + funcrbp[to_string(($$).temp)] + "(%rbp)");
  ($$).isname = 0;
}

trailer:
OPEN_ROUND_BRACKET Opt_arglist CLOSE_ROUND_BRACKET      {
  ($$).linenum = ($1).linenum;
  ($$).isfunccall = 1;
  string empty = "";
  strcpy(($$).lexeme, empty.c_str());
  ($$).listsize = ($2).listsize;

}
| OPEN_SQUARE_BRACKET test CLOSE_SQUARE_BRACKET      {

($$).linenum = ($1).linenum;
  ($$).isfunccall = 0;
  // ($$).isbracket = 1;
  string at = "@";
  strcpy(($$).lexeme, at.c_str());
  strcat(($$).lexeme, ($2).lexeme);
  strcpy(($$).indextype, ($2).type);
  strcpy(($$).temp, ($2).temp);
  // int typesize = type_size(to_string(($2).type));
  // string temp_ = t_new();
  // strcpy(($$).tempsquare, temp_.c_str());
  // gen(temp_ + " = " + to_string(($2).temp) + " * " + to_string(typesize));
  strcpy(($$).tempsquare, ($2).temp);

}
| DOT NAME      {
  ($$).linenum = ($1).linenum;
  // not sure what to do 
  ($$).isfunccall = 0;
  string at = ".";
  strcpy(($$).lexeme, at.c_str());
  strcat(($$).lexeme, ($2).token_lex);
  
}

Opt_arglist:
%empty             {
  
}
| arglist      {
  
}

testlist:
test Multi_test       {
  ($$).linenum = ($1).linenum;
  string list_at = "list@";
  strcpy(($$).type, list_at.c_str());
  strcat(($$).type, ($1).type); // occurs only in list and they are homogeneous so
  list_temps.push_back(to_string(($1).temp));
}

Multi_test:
%empty             {
  
}
| COMMA test Multi_test      {
  ($$).linenum = ($1).linenum;
  list_temps.push_back(to_string(($2).temp));
}

classdef:
CLASS NAME COLON {
  
  // gen("beginclass");
  curr_table->make_entry(to_string(($2).token_lex), "Class", to_string(($2).token_lex), offset, curr_scope, ($1).linenum, -1, -1, -1, 1);
  offset+=0;
  table_stack.push(curr_table);
  curr_table = new Symbol_Table(curr_table);
  class_symbol_tables[to_string(($2).token_lex)] = curr_table;
  all_types.insert(to_string(($2).token_lex));
  all_types.insert("list@" + to_string(($2).token_lex));
  recent_class = to_string(($2).token_lex);
  vec_tables.push_back(curr_table);
  scope_stack.push(curr_scope);
  offset_stack.push(offset);
  string new_scope = "Class@" + to_string(($2).token_lex);
  curr_scope = new_scope;
  offset = 0;
}
suite      { 
  ($$).linenum = ($1).linenum;
  // new symbol table

  curr_table = table_stack.top(); 
  table_stack.pop();
  curr_scope = scope_stack.top(); 
  scope_stack.pop();
  offset = offset_stack.top(); 
  offset_stack.pop();
  recent_class = "";
  classrbp.clear();
  // strcpy(($$).type, ($2).token_lex);
  
  // gen("endclass");

}
| CLASS NAME OPEN_ROUND_BRACKET NAME CLOSE_ROUND_BRACKET COLON {
  // gen("beginclass");
// check if NAME exists in global 
if(curr_table->lookup(to_string(($4).token_lex)).token == "null"){
  cerr << ($1).linenum << ": Error: base / parent class '" << to_string(($4).token_lex) <<"' does not exist\n";
  exit(0);
}
else{
    child_to_parent_classes[to_string(($2).token_lex)] = to_string(($4).token_lex);
    curr_table->make_entry(to_string(($2).token_lex), "Class", to_string(($2).token_lex), offset, curr_scope, ($1).linenum, -1, -1, -1, 1);
    offset+=0;
    table_stack.push(curr_table);
    curr_table = new Symbol_Table(curr_table);
    
    Symbol_Table *parent_class_table = class_symbol_tables[to_string(($4).token_lex)];
    for(auto it = parent_class_table->table.begin(); it != parent_class_table->table.end(); it++ ){
      if(it->first != "__init__"){
        Symbol_Table_Entry* entry = curr_table->make_entry(it->first, it->second.token, it->second.type, it->second.offset, "Class@" + to_string(($2).token_lex), it->second.line, it->second.argnum, it->second.width, it->second.numargs, it->second.isinit);
        entry->update_entry(it->second.childtable);
      }

    }

    class_symbol_tables[to_string(($2).token_lex)] = curr_table;
    all_types.insert(to_string(($2).token_lex));
    all_types.insert("list@" + to_string(($2).token_lex));
    recent_class = to_string(($2).token_lex);
    vec_tables.push_back(curr_table);
    scope_stack.push(curr_scope);
    offset_stack.push(offset);
    string new_scope = "Class@" + to_string(($2).token_lex);
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


suite      {
  ($$).linenum = ($1).linenum;
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

arglist:
argument Multi_argument       {
  
}

Multi_argument:
%empty             {
  
}
| COMMA argument Multi_argument      {
  ($$).linenum = ($1).linenum;
  
}

argument:
test      {
  strcpy(($$).type, ($1).type);
  strcpy(($$).lexeme, ($1).lexeme);
  func_arg_vec.push_back({to_string(($1).lexeme), to_string(($1).type)});
  func_arg_temp_vec.push_back({to_string(($1).lexeme), to_string(($1).temp)});
}

func_body_suite:
simple_stmt      {
  
}
| NEWLINE INDENT Nonzero_stmt DEDENT      {
  ($$).linenum = ($1).linenum;
  
}



%%

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

  // int flag = 0;
  // ofstream fout;
  // for(auto it: vec_tables){
  //   if(it->table.begin() == it->table.end()){
  //     continue;
  //   }
  //   string scope_ = it->table.begin()->second.scopename;
  //   if(scope_ == "Global"){
  //     flag = 1;
  //     fout.close();
  //   }
  //   else if(scope_.substr(0, 6) == "Class@"){
  //     flag = 1;
  //     fout.close();
  //   }
  //   else if(scope_.substr(0, 9) == "Function@"){
  //     flag = 1;
  //     fout.close();
  //   }
  //   if(flag == 0){
  //     for(auto entry=it->table.begin(); entry!=it->table.end(); entry++){
  //       fout<<entry->first<<","<<entry->second.token<<","<<entry->second.type<<","<<entry->second.offset<<","<<entry->second.scopename<<","<<entry->second.line<<","<<entry->second.numargs<<","<<entry->second.argnum<<'\n';
  //     }
  //   }
  //   else{
  //     flag = 0;
  //     string output = scope_ + ".csv";
  //     // cout<<output<<endl;
  //     fout.open(output);
  //     fout<<"Lexeme"<<','<<"Token"<<','<<"Type/Return Type"<<','<<"Offset"<<','<<"Scope Name"<<','<<"Line Number"<<','<<"Number of Parameters"<<','<<"Parameter Number"<<'\n';
  //     for(auto entry=it->table.begin(); entry!=it->table.end(); entry++){
  //       fout<<entry->first<<","<<entry->second.token<<","<<entry->second.type<<","<<entry->second.offset<<","<<entry->second.scopename<<","<<entry->second.line<<","<<entry->second.numargs<<","<<entry->second.argnum<<'\n';
  //     }
  //   }
  // }
  // fout.close();
  

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

  ofstream outputFile2("x86.s");
  if (!outputFile2.is_open()) {
      cerr << "Failed to open the file for writing!" << endl;
      return 1;
  }

  for(long unsigned int i = 0; i < code_x86.size(); i++){
    // vec_tables[i]->print_sym_table(outputFile2);
    if(code_x86[i][code_x86[i].size()-1]==':'){
      outputFile2 << code_x86[i] << "\n";
    }
    else{
      outputFile2 << "\t\t" << code_x86[i] << "\n";
    }
    
  }

  outputFile2.close();


  return 0;
}

void yyerror(const char * s)
{
  cerr << "Error in line " << yylineno << " : " << s << endl;
  exit(0);
}

