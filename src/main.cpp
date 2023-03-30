#include <iostream>
#include "node.h"

extern NBlock* programBlock;
extern SymbolTableStorage *symtab_storage;
extern int yyparse();

int main(int argc, char **argv)
{
    yyparse();
    Visitor *visitors[] = {
        new PrettyPrintVisitor(),
        new SymbolTableFillerVisitor(symtab_storage)
    };
    for (auto visitor: visitors) {
        std::cout << "visit " << visitor->name << std::endl;
        programBlock->visit(visitor);
        std::cout << std::endl;
    }
    return 0;
}

