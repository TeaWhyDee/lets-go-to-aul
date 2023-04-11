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
        new SymbolTableFillerVisitor(symtab_storage),
        new DeclaredBeforeUseCheckerVisitor(symtab_storage),
    };
    try{
        for (auto visitor: visitors) {
            std::cout << "visit " << visitor->name << std::endl;
            programBlock->visit(visitor);
            std::cout << std::endl;
            visitor->cleanup();
        }
    } catch (SemanticError* e) {
        std::cout << "Semantic error: " << e->what() << std::endl;
    }
    return 0;
}

