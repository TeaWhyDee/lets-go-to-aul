.PHONY: all compile parser clean test


file ?= ../test/codegen.lua
all: clean lex.cpp bison parser compile-and-run

clean:
	$(RM) -rf lex.cpp bison parser.cpp parser.hpp lex.hpp parser a.out

lex.cpp: lex.l
	flex -o $@ lex.l

flex: lex.cpp
	g++ -Wall -g -std=c++11 $^ -o parser

bison:
	bison -Wall -d -o parser.cpp parser.y;

parser:
	g++ -Wall -g -o parser parser.cpp lex.cpp main.cpp `llvm-config --cxxflags --ldflags --libs core` -fexceptions 

compile-and-run:
	./parser < $(file)

	# clang++ -S -emit-llvm builtin.cpp -o builtin.ll
	# llvm-link -o program.ll codegen.ll builtin.ll
	# llc -filetype=obj program.ll -o program.o
	# clang++ program.o -o program
	clang -S -emit-llvm builtin.cpp -o builtin.ll
	clang++ codegen.ll builtin.ll
	./a.out

test: flex
	cat ../test/*.aul | ./parser
