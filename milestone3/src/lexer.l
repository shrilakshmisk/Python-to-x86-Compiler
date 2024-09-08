%{
    #include<iostream>
    #include<map>
    #include<vector>
    #include <string>
    #include<fstream>
    #include <bits/stdc++.h>
    #include <stack>
    #include "parser.tab.h"
    using namespace std;
    stack <int> indentation_st;
    int num_spaces = 0;
    int flag = 0,state = 0;
    stack<int> state_st;    
%}

%option yylineno

    /* keywords */

PASS            "pass"
BREAK           "break"
CONTINUE        "continue"
RETURN          "return"
RAISE           "raise"
FROM            "from"
GLOBAL          "global"
NONLOCAL        "nonlocal"
DEL             "del"
ASSERT          "assert"
IMPORT          "import"
AS              "as"
CLASS           "class"
DEF             "def"
IF              "if"
ELIF            "elif"
ELSE            "else"
WHILE           "while"
FOR             "for"
IN              "in"
WITH            "with"
TRY             "try"
EXCEPT          "except"
FINALLY         "finally"
NONE            "None"
TRUE            "True"
FALSE           "False"
YIELD           "yield"
OR              "or"
AND             "and"
NOT             "not"
IS              "is"
LAMBDA          "lambda"
SELF            "self"

    /* operators */
OPEN_ROUND_BRACKET          "("
CLOSE_ROUND_BRACKET         ")"
ARROW                       "->"
SEMICOLON                   ";"
COLON                       ":"
EQUAL                       "="
PLUS_EQUAL                  "+="
MINUS_EQUAL                 "-="
STAR_EQUAL                  "*="
AT_EQUAL                    "@="
SLASH_EQUAL                 "/="
PERCENTAGE_EQUAL            "%="
AND_EQUAL                   "&="
OR_EQUAL                    "|="
XOR_EQUAL                   "^="
LEFT_SHIFT_EQUAL            "<<="
RIGHT_SHIFT_EQUAL           ">>="
DOUBLE_STAR_EQUAL           "**="
DOUBLE_SLASH_EQUAL          "//="
COMMA                       ","
DOT                         "."
ELLIPSIS                    "..."
STAR                        "*"
AT                          "@"
SLASH                       "/"
DOUBLE_STAR                 "**"
OR_OP                       "|"
PLUS                        "+"
MINUS                       "-"
OPEN_SQUARE_BRACKET         "["
CLOSE_SQUARE_BRACKET        "]"
OPEN_CURLY_BRACKET          "{"
CLOSE_CURLY_BRACKET         "}"
COLON_EQUAL                 ":="
DOUBLE_EQUAL                "=="
NOT_EQUAL                   "!="
LESSER_EQUAL                "<="
LESSER                      "<"
GREATER_EQUAL               ">="
GREATER                     ">"
XOR                         "^"
AND_OP                      "&"
LEFT_SHIFT                  "<<"
RIGHT_SHIFT                 ">>"
DOUBLE_SLASH                "//"
PERCENTAGE                  "%"
NOT_OP                      "~"

    /* dunders */
NAME_DUNDER                 "__name__"
MAIN_DUNDER                 "__main__"
INIT_DUNDER                 "__init__"

    /* helpers */
SPECIAL_CHARS                {OPEN_ROUND_BRACKET}|{CLOSE_ROUND_BRACKET}|{SEMICOLON}|{COLON}|{EQUAL}|{COMMA}|{DOT}|{STAR}|{AT}|{SLASH}|{OR_OP}|{PLUS}|{MINUS}|{OPEN_SQUARE_BRACKET}|{CLOSE_SQUARE_BRACKET}|{LESSER}|{GREATER}|{XOR}|{AND_OP}|{PERCENTAGE}|{NOT_OP}|{UNDERSCORE}|"\\"|"!"|" "                      
SPECIAL_CHAR                [^\'\"]
LETTER                      [a-zA-Z]
DIGIT                       [0-9]
UNDERSCORE                  "_"
DOUBLE_QUOTE                [\"] 
SINGLE_QUOTE                [\']
BACKSLASH                   "\\"


    /* others */
NEWLINE_CHAR                "\n"|"\r\n"
NAME                        ({LETTER}|{UNDERSCORE})({LETTER}|{UNDERSCORE}|{DIGIT})*
SPACE                       [ ]
SHORT_STRING                ([\"]({LETTER}|"\\\n"|"\\\r\n"|{DIGIT}|{SPECIAL_CHAR}|[\']|[\\][\"])*[\"])|([\']({LETTER}|"\\\n"|"\\\r\n"|{DIGIT}|{SPECIAL_CHAR}|[\"]|[\\][\'])*[\'])
LONG_STRING                 ([\"][\"][\"]({LETTER}|{DIGIT}|{SPECIAL_CHAR}|[\\][\"]|[\\][\']|[\']|[\"][^\"]|[\"][\"][^\"]|[\n]|[\r][\n])*[\"][\"][\"])|([\'][\'][\']({LETTER}|{DIGIT}|{SPECIAL_CHAR}|[\\][\']|[\\][\"]|[\"]|[\'][^\']|[\'][\'][^\']|[\n]|[\r][\n])*[\'][\'][\'])
COMMENT                     "#"([^\n\r])*


NONZERODIGIT        [1-9]
BINDIGIT            [0-1]
OCTDIGIT            [0-7]
HEXDIGIT            {DIGIT}|[a-fA-F]

HEXINT              "0"("x"|"X")({UNDERSCORE}?{HEXDIGIT})+
OCTINT              "0"("o"|"O")({UNDERSCORE}?{OCTDIGIT})+
BININT              "0"("b"|"B")({UNDERSCORE}?{BINDIGIT})+
DECIMALINT          {NONZERODIGIT}({UNDERSCORE}?{DIGIT})*|"0"+({UNDERSCORE}"0")*

INTEGER             {DECIMALINT}|{BININT}|{OCTINT}|{HEXINT}

INTPART             {DIGIT}({UNDERSCORE}?{DIGIT})*
FRACTION            "."{INTPART}
EXPONENT            ("e"|"E") ["+""-"]{INTPART}
POINTFLOAT          {INTPART}{FRACTION}|{INTPART}"."
EXPONENTFLOAT       ({INTPART}|{POINTFLOAT})EXPONENT

FLOAT               {POINTFLOAT}|{EXPONENTFLOAT}
    
IMAGNUM             ({FLOAT}|{INTPART})("j"|"J")

NUMBER		    {INTEGER}|{FLOAT}|{IMAGNUM}

    /* states */
%x	ind_ded
%s	implicit_line_join_square
%s  implicit_line_join_round
                                     
%%

<ind_ded>. {
    if(flag==0){
	indentation_st.push(0);
	flag=1;
    }
    // cout<< "ind_ded state begins\n";
	for(int i=yyleng-1;i >= 0 ;i--){
        unput(yytext[i]);
    }
    //cout<<num_spaces<<" "<<indentation_st.top()<<"\n";
	if(num_spaces > indentation_st.top()){
		indentation_st.push(num_spaces);
		//return indent token
		BEGIN(INITIAL);
        return INDENT;
		//cout<<"INDENT"<<endl;
	}
	else if(num_spaces == indentation_st.top()){
		BEGIN(INITIAL);
	}
	else{
		indentation_st.pop();
		//return dedent token to parser;
        if(num_spaces > indentation_st.top()){
            cout<<"Error: Indentation error at line " << yylineno <<"\n";
            exit(1);
        }
        return DEDENT;
		//cout<<"DEDENT"<<endl;
	}

}

<implicit_line_join_square>"\n"|"\r\n" {
	//leave it empty	
}
<implicit_line_join_round>"\n"|"\r\n" {
	//leave it empty	
}
<implicit_line_join_square>{CLOSE_SQUARE_BRACKET} {
	//if(state_st.top()!=2){
	//	cout<<""<<endl;
	//	exit(1);
	//}
	state_st.pop();
	if(state_st.top() == 0)
		BEGIN(INITIAL);
	else if(state_st.top()==1)
		BEGIN(implicit_line_join_round);
	yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return CLOSE_SQUARE_BRACKET;
	//return token
}
<implicit_line_join_square>{OPEN_SQUARE_BRACKET} {
        state_st.push(2);
        yylval.token_attr.linenum = yylineno;
        strcpy(yylval.token_attr.token_lex, yytext); return OPEN_SQUARE_BRACKET;
        //return token

      }
<implicit_line_join_round>{OPEN_ROUND_BRACKET} {
	state_st.push(1);
        yylval.token_attr.linenum = yylineno;
        strcpy(yylval.token_attr.token_lex, yytext); return OPEN_ROUND_BRACKET;
	//return token
}
<implicit_line_join_round>{CLOSE_ROUND_BRACKET} {
        //if(state_st.top()!=1){
        //        cout<<"stray "<<endl;
        //        exit(1);
        //}
        state_st.pop();
        if(state_st.top() == 0)
                BEGIN(INITIAL);
        else if(state_st.top()==2)
                BEGIN(implicit_line_join_square);
        yylval.token_attr.linenum = yylineno;
        strcpy(yylval.token_attr.token_lex, yytext); return CLOSE_ROUND_BRACKET;
        //return token
}

{LONG_STRING}|{SHORT_STRING}         {
    //cout<<"STRING, "<<yytext<<"\n";
    string type_s = "str";
    strcpy(yylval.token_attr.token_type, type_s.c_str()); 
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return STRING;
    
}

{DOUBLE_QUOTE} {
    cout<<"will be passed to parser as double quote token: " << yytext<<"\n";
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DOUBLE_QUOTE;
    //cout<<"will be passed to parser as double quote token: " << yytext<<"\n";
}

{SINGLE_QUOTE} {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return SINGLE_QUOTE;
    //cout<<"will be passed to parser as single quote token: " << yytext<<"\n";
}

{BREAK}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return BREAK;
    //cout<< "BREAK: " << yytext << "\n";
}

{CONTINUE}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return CONTINUE;
    //cout<< "CONTINUE: " << yytext << "\n";
}

{RETURN}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return RETURN;
    //cout<< "RETURN: " << yytext << "\n";
}


{GLOBAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return GLOBAL;
    //cout<< "GLOBAL: " << yytext << "\n";
}

{ASSERT}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return ASSERT;
    //cout<< "ASSERT: " << yytext << "\n";
}

{CLASS}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return CLASS;
    //cout<< "CLASS: " << yytext << "\n";
}

{DEF}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DEF;
    //cout<< "DEF: " << yytext << "\n";
}

{IF}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return IF;
    //cout<< "IF: " << yytext << "\n";
}

{ELIF}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return ELIF;
    //cout<< "ELIF: " << yytext << "\n";
}

{ELSE}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return ELSE;
    //cout<< "ELSE: " << yytext << "\n";
}


{WHILE}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return WHILE;
    //cout<< "WHILE: " << yytext << "\n";
}

{FOR}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return FOR;
    //cout<< "FOR: " << yytext << "\n";
}

{IN}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return IN;
    //cout<< "IN: " << yytext << "\n";
}


{NONE}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return NONE;
    //cout<< "NONE: " << yytext << "\n";
}

{TRUE}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); 
    string type_s = "bool";
    strcpy(yylval.token_attr.token_type, type_s.c_str()); 
    return TRUE;
    //cout<< "TRUE: " << yytext << "\n";
}

{FALSE}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); 
    string type_s = "bool";
    strcpy(yylval.token_attr.token_type, type_s.c_str()); 
    return FALSE;
    //cout<< "FALSE: " << yytext << "\n";
}

{OR}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return OR;
    //cout<< "OR: " << yytext << "\n";
}

{AND}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return AND;
    //cout<< "AND: " << yytext << "\n";
}

{NOT}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return NOT;
    //cout<< "NOT: " << yytext << "\n";
}

{IS}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return IS;
    //cout<< "IS: " << yytext << "\n";
}

{OPEN_ROUND_BRACKET}      {
    if(state == 0){
	state_st.push(0);
	state = 1;
    }
    state_st.push(1);
    BEGIN(implicit_line_join_round);
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return OPEN_ROUND_BRACKET;
    //cout<< "OPEN_ROUND_BRACKET: " << yytext << "\n";
}

{CLOSE_ROUND_BRACKET}   {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return CLOSE_ROUND_BRACKET;
}

{ARROW}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return ARROW;
    //cout<< "ARROW: " << yytext << "\n";
}

{SEMICOLON}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return SEMICOLON;
    //cout<< "SEMICOLON: " << yytext << "\n";
}

{COLON}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return COLON;
    //cout<< "COLON: " << yytext << "\n";
}

{EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return EQUAL;
        //cout<< "EQUAL: " << yytext << "\n";
}

{PLUS_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return PLUS_EQUAL;
    //cout<< "PLUS_EQUAL: " << yytext << "\n";
}

{MINUS_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return MINUS_EQUAL;
    //cout<< "MINUS_EQUAL: " << yytext << "\n";
}

{STAR_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return STAR_EQUAL;
    //cout<< "STAR_EQUAL: " << yytext << "\n";
}

{SLASH_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return SLASH_EQUAL;
    //cout<< "SLASH_EQUAL: " << yytext << "\n";
}

{PERCENTAGE_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return PERCENTAGE_EQUAL;
    //cout<< "PERCENTAGE_EQUAL: " << yytext << "\n";
}

{AND_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return AND_EQUAL;
    //cout<< "AND_EQUAL: " << yytext << "\n";
}

{OR_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return OR_EQUAL;
    //cout<< "OR_EQUAL: " << yytext << "\n";
}

{XOR_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return XOR_EQUAL;
    //cout<< "XOR_EQUAL: " << yytext << "\n";
}

{LEFT_SHIFT_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return LEFT_SHIFT_EQUAL;
    //cout<< "LEFT_SHIFT_EQUAL: " << yytext << "\n";
}

{RIGHT_SHIFT_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return RIGHT_SHIFT_EQUAL;
    //cout<< "RIGHT_SHIFT_EQUAL: " << yytext << "\n";
}

{DOUBLE_STAR_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DOUBLE_STAR_EQUAL;
    //cout<< "DOUBLE_STAR_EQUAL: " << yytext << "\n";
}

{DOUBLE_SLASH_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DOUBLE_SLASH_EQUAL;
    //cout<< "DOUBLE_SLASH_EQUAL: " << yytext << "\n";
}

{COMMA}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return COMMA;
    //cout<< "COMMA: " << yytext << "\n";
}

{DOT}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DOT;
    //cout<< "DOT: " << yytext << "\n";
}


{STAR}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return STAR;
    //cout<< "STAR: " << yytext << "\n";
}

{SLASH}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return SLASH;
    //cout<< "SLASH: " << yytext << "\n";
}

{DOUBLE_STAR}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DOUBLE_STAR;
    //cout<< "DOUBLE_STAR: " << yytext << "\n";
}

{OR_OP}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return OR_OP;
    //cout<< "OR_OP: " << yytext << "\n";
}

{PLUS}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return PLUS;
    //cout<< "PLUS: " << yytext << "\n";
}

{MINUS}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return MINUS;
    //cout<< "MINUS: " << yytext << "\n";
}

{OPEN_SQUARE_BRACKET}      {
    if(state == 0){
        state_st.push(0);
        state = 1;
    }
    state_st.push(2);
    BEGIN(implicit_line_join_square);
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return OPEN_SQUARE_BRACKET;
    //cout<< "OPEN_SQUARE_BRACKET: " << yytext << "\n";
}

{CLOSE_SQUARE_BRACKET}   {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return CLOSE_SQUARE_BRACKET;
}

{COLON_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return COLON_EQUAL;
    //cout<< "COLON_EQUAL: " << yytext << "\n";
}

{DOUBLE_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DOUBLE_EQUAL;
    //cout<< "DOUBLE_EQUAL: " << yytext << "\n";
}

{NOT_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return NOT_EQUAL;
    //cout<< "NOT_EQUAL: " << yytext << "\n";
}

{LESSER_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return LESSER_EQUAL;
    //cout<< "LESSER_EQUAL: " << yytext << "\n";
}

{LESSER}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return LESSER;
    //cout<< "LESSER: " << yytext << "\n";
}

{GREATER_EQUAL}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return GREATER_EQUAL;
    //cout<< "GREATER_EQUAL: " << yytext << "\n";
}

{GREATER}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return GREATER;
    //cout<< "GREATER: " << yytext << "\n";
}

{XOR}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return XOR;
    //cout<< "XOR: " << yytext << "\n";
}

{AND_OP}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return AND_OP;
    //cout<< "AND_OP: " << yytext << "\n";
}

{LEFT_SHIFT}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return LEFT_SHIFT;
    //cout<< "LEFT_SHIFT: " << yytext << "\n";
}

{RIGHT_SHIFT}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return RIGHT_SHIFT;
    //cout<< "RIGHT_SHIFT: " << yytext << "\n";
}

{DOUBLE_SLASH}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return DOUBLE_SLASH;
    //cout<< "DOUBLE_SLASH: " << yytext << "\n";
}

{PERCENTAGE}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return PERCENTAGE;
    //cout<< "PERCENTAGE: " << yytext << "\n";
}

{NOT_OP}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return NOT_OP;
    //cout<< "NOT_OP: " << yytext << "\n";
}

{NAME}      {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext);
   // yylval.token_attr.token_isname = 1;
   // strcpy(yylval.token_attr.token_type, type_s.c_str()); 
     return NAME;
    //cout<< "NAME: " << yytext << "\n";
}

{NEWLINE_CHAR}      {
    char c = yyinput();
    // cout<<"first char after newline: "<<(int)c<<"\n";
    num_spaces = 0;
    if(c == '\n') {
        // cout<<"@1\n";
        c = yyinput();
    }
    if(c == '\r') {
        // cout<<"@2\n";
        c = yyinput();
        c = yyinput();
    }
    if(c == '#'){
        c = yyinput();
		while(c != '\n'){
			c = yyinput();
		}
		c = yyinput();
    }
	while(c==' ' || c == '\n'||c== '\r' || c == '#'){
        // cout<<"inside while loop\n";
		if(c == '\n'){
                        //c = yyinput();
                        num_spaces = 0;
                }
        if(c == '\r'){
                        //c = yyinput();
                        c = yyinput();
                        num_spaces = 0;
                }
        if(c == '#'){
			c = yyinput();
			while(c != '\n'){
				c = yyinput();
			}
			num_spaces = 0;
		}
		if(c == ' ') num_spaces++;
		c = yyinput();

		
	}
	unput(c);
     if(c!='\n' && c!='\r') {
        // cout<<"going to ind_ded\n";
        BEGIN(ind_ded);
    }
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); return NEWLINE;
    //cout<< "NEWLINE: " << "\n"; 
}

{BACKSLASH}{NEWLINE_CHAR} {
    //cout<<"No token generated: " << yytext << "\n";
}

{COMMENT} {
    //cout<< "COMMENT: " << yytext << "\n";
}

{FLOAT} {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); 
    string type_s = "float";
    strcpy(yylval.token_attr.token_type, type_s.c_str()); 
    return NUMBER;
}

{INTEGER} {
    yylval.token_attr.linenum = yylineno;
    strcpy(yylval.token_attr.token_lex, yytext); 
    string type_s = "int";
    strcpy(yylval.token_attr.token_type, type_s.c_str()); 
    return NUMBER;
}

{SPACE} {
    
}

<<EOF>> {yyterminate();}

[^\0] {
  string s = yytext;
  char c = s[0];  
  cout<<"Error: Invalid character " << (int) c << " at line " << yylineno << "\n";
  exit(1);
} 



%%


int yywrap(){
    //indentation_st.push(0); 
    return 1;
}





