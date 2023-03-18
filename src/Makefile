all: clean lex.cpp bison parser

parser:
	g++ -o parser parser.cpp lex.cpp main.cpp

clean:
	$(RM) -rf lex.cpp bison parser.cpp parser.hpp lex.hpp parser

test: flex
	cat ../test/*.aul | ./parser

bison:
	bison -d -o parser.cpp parser.y;

flex: lex.cpp
	g++ $^ -o parser

lex.cpp: lex.l
	flex -o $@ lex.l
