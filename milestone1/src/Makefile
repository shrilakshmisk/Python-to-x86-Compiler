all:	parser_exec.out

parser.tab.c parser.tab.h:	parser.y
	bison -t -v -d parser.y

lex.yy.c: lexer.l
	flex lexer.l

lex.o:	lex.yy.c parser.tab.h
	g++ -g -Wall -c lex.yy.c -o lex.o

bison.o:	parser.tab.c
	g++ -g -Wall -c parser.tab.c -o bison.o

parser_exec.out: lex.o bison.o
	g++ -g -Wall lex.o bison.o -o parser_exec.out

clean:
	rm *.o *.out *.output *.tab.* lex.yy.c
