all: flex

clean:
	$(RM) -rf lex.cpp lex.hpp parser

test: flex
	cat ../test/*.aul | ./parser


flex: lex.cpp
	g++ $^ -o parser

lex.cpp: lex.l
	flex -o $@ lex.l
