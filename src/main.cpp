#include <iostream>

#include "node.h"

extern NBlock* programBlock;
extern SymbolTableStorage* symtab_storage;
extern int yyparse();

int main(int argc, char** argv) {
    yyparse();
    auto pretty_print_visitor = new PrettyPrintVisitor();
    Visitor* visitors[] = {
        new TypeChecker(pretty_print_visitor),
        pretty_print_visitor,
        new SymbolTableFillerVisitor(),
        new DeclaredBeforeUseCheckerVisitor(),
    };
    try {
        for (auto visitor : visitors) {
            std::cout << "\n\n------------------" << visitor->name << "------------------" << std::endl;
            programBlock->visit(visitor);
            std::cout << std::endl;
            visitor->cleanup();
        }
    } catch (SemanticError* e) {
        std::cout << "Semantic error: " << e->what() << std::endl;
    }
    return 0;
}
