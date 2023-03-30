#include <iostream>

#include "node.h"

extern NBlock* programBlock;
extern SymbolTableStorage *symtab_storage;
extern int yyparse();

int main(int argc, char** argv) {
    yyparse();
<<<<<<< HEAD
    auto pretty_print_visitor = new PrettyPrintVisitor();
    auto type_checker = new TypeChecker(pretty_print_visitor);

    std::cout << "\n\n-----------Type check-----------" << std::endl;
    programBlock->visit(type_checker);
    std::cout << "-----------Pretty print-----------" << std::endl;
    programBlock->visit(pretty_print_visitor);
=======
    Visitor *visitors[] = {
        new PrettyPrintVisitor(),
        new SymbolTableFillerVisitor(),
        new DeclaredBeforeUseCheckerVisitor(),
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
>>>>>>> f973284 (Init commit)
    return 0;
}
