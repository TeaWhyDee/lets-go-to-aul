
#include <iostream>

#include "node.h"

extern NBlock* programBlock;
extern int yyparse();

int main(int argc, char** argv) {
    yyparse();
    auto pretty_print_visitor = new PrettyPrintVisitor();
    auto type_checker = new TypeChecker(pretty_print_visitor);

    std::cout << "\n\n-----------Type check-----------" << std::endl;
    programBlock->visit(type_checker);
    std::cout << "-----------Pretty print-----------" << std::endl;
    programBlock->visit(pretty_print_visitor);
    return 0;
}
