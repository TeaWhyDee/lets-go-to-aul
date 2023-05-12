#include <iostream>
#include <fstream>

#include "node.h"

extern NBlock* programBlock;
extern SymbolTableStorage* symtab_storage;
extern int yyparse();

int main(int argc, char** argv) {
    yyparse();
    auto pretty_print_visitor = new PrettyPrintVisitor();
    Visitor *visitors[] = {
        pretty_print_visitor,
        new SymbolTableFillerVisitor(),
        // new TypeDeducer(),
        new DeclaredBeforeUseCheckerVisitor(),
        new TypeChecker(pretty_print_visitor),
    };
    for (auto visitor : visitors) {
        std::cout << "\n\n------------------" << visitor->name << "------------------" << std::endl;
        programBlock->visit(visitor);
        std::cout << std::endl;
        visitor->cleanup();
    }

    auto visitor = new CodeGenVisitor();
    programBlock->returnExpr = new NNil();
    std::cout << "\n\n------------------" << visitor->name << "------------------" << std::endl;
    programBlock->visit(visitor);
    visitor->cleanup();

    visitor->module->print(llvm::errs(), nullptr, false, false);
    llvm::StringRef filename = "codegen.ll";
    std::error_code err;
    llvm::raw_fd_ostream filestream(filename, err);
    visitor->module->print(filestream, nullptr, false, false);
    return 0;
}
