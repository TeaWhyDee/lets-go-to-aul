#include <iostream>

#include "node.h"

extern NBlock* programBlock;
extern SymbolTableStorage* symtab_storage;
extern int yyparse();

int main(int argc, char** argv) {
    yyparse();
    auto pretty_print_visitor = new PrettyPrintVisitor();
    Visitor *visitors[] = {
        pretty_print_visitor,
        // new TypeDeducer(),
        new SymbolTableFillerVisitor(),
        new DeclaredBeforeUseCheckerVisitor(),
        new TypeChecker(pretty_print_visitor),
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

    TheContext = std::make_unique<llvm::LLVMContext>();
    TheModule = std::make_unique<llvm::Module>("codegen ", *TheContext);
    Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);

    auto visitor = new CodeGenVisitor();
    std::cout << "\n\n------------------" << visitor->name << "------------------" << std::endl;
    programBlock->visit(visitor);
    visitor->cleanup();

    TheModule->print(llvm::errs(), nullptr);

    return 0;
}
