all: lex.cpp bison parser

parser:
	g++ -o bison parser.cpp lex.cpp main.cpp

clean:
	$(RM) -rf lex.cpp lex.hpp parser

test: flex
	cat ../test/*.aul | ./parser

bison:
	bison -d -o parser.cpp parser.y;

flex: lex.cpp
	g++ $^ -o parser

lex.cpp: lex.l
	flex -o $@ lex.l
