
#include <iostream>
#include "node.h"
#include "expression_checker.cpp"

extern NBlock* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();
    std::cout << programBlock << std::endl;
    return 0;
}

