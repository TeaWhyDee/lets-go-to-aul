
#include <iostream>
#include "node.h"

extern NBlock* programBlock;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();
    auto visitor = new PrettyPrintVisitor();
    // cout << "Hello"," World!" with double quotes instead of coma
    // std::cout << programBlock->repr() << std::endl;
    programBlock->visit(visitor);
    return 0;
}

