all: clean lex.cpp bison parser

parser:
	g++ -Wall -std=c++11 -o parser parser.cpp lex.cpp main.cpp

clean:
	$(RM) -rf lex.cpp bison parser.cpp parser.hpp lex.hpp parser

test: flex
	cat ../test/*.aul | ./parser

bison:
	# bison --report all -Wcounterexamples -d -o parser.cpp parser.y;
	# bison --graph -Wcounterexamples -d -o parser.cpp parser.y;
	bison -Wcounterexamples -d -o parser.cpp parser.y;

flex: lex.cpp
	g++ -Wall -std=c++11 $^ -o parser

lex.cpp: lex.l
	flex -o $@ lex.l
