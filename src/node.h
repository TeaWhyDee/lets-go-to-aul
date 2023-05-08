#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

// #include <llvm/IR/Value.h>

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;
class Node;
class NBlock;
class NNum;
class NNil;
class NBool;
class NString;
class NDeclarationStatement;
class NFunctionDeclaration;
class NIdentifier;
class NBinaryOperatorExpression;
class NUnaryOperatorExpression;
class NTableConstructor;
class NWhileStatement;
class NDoStatement;
class NRepeatUntilStatement;
class NIfStatement;
class NNumericForStatement;
class NGenericForStatement;
class NAssignmentStatement;
class NReturnStatement;
class NAccessKey;
class NExpressionCall;
class Visitor;
class PrettyPrintVisitor;
class NStructDeclaration;
class StructBody;
class NType;
class NStringType;
class NNumType;
class NBoolType;
class NNilType;
class NTableType;
class NFunctionType;
class NStructType;
class NAnyType;
class SymbolTableEntry;
class SymbolTable;
class ScopedSymbolTable;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NIdentifier*> IdentifierList;
typedef std::vector<NVariableDeclaration*> VariableList;
typedef std::pair<NExpression*, NBlock*> conditionBlock;
typedef std::pair<NIdentifier*, NExpression*> keyvalPair;
typedef std::vector<NType*> typeList;

typedef enum {
    ADD = 0,
    SUBSTRACT = 1,
    MULTIPLY = 2,
    DIVIDE = 3,
    POWER = 4,
    FLOOR_DIVIDE = 5,
    MODULO = 6,
    LESS_THAN = 7,
    GREATER_THAN = 8,
    LESS_THAN_OR_EQUAL = 9,
    GREATER_THAN_OR_EQUAL = 10,
    EQUAL = 11,
    NOT_EQUAL = 12,
    AND = 13,
    OR = 14,
} BinOpType;

typedef enum {
    MINUS = 0,
    NOT = 1,
} UnOpType;

class Visitor {
   public:
    std::string name;
    virtual void visitNNum(NNum* node) = 0;
    virtual void visitNNil(NNil* node) = 0;
    virtual void visitNBool(NBool* node) = 0;
    virtual void visitNString(NString* node) = 0;
    virtual void visitNIdentifier(NIdentifier* node) = 0;
    virtual void visitNBinaryOperatorExpression(
        NBinaryOperatorExpression* node) = 0;
    virtual void visitNUnaryOperatorExpression(
        NUnaryOperatorExpression* node) = 0;
    virtual void visitNTableConstructor(NTableConstructor* node) = 0;
    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) = 0;
    virtual void visitNAccessKey(NAccessKey* node) = 0;
    virtual void visitNExpressionCall(NExpressionCall* node) = 0;
    virtual void visitNWhileStatement(NWhileStatement* node) = 0;
    virtual void visitNRepeatUntilStatement(NRepeatUntilStatement* node) = 0;
    virtual void visitNDoStatement(NDoStatement* node) = 0;
    virtual void visitNIfStatement(NIfStatement* node) = 0;
    virtual void visitNNumericForStatement(NNumericForStatement* node) = 0;
    virtual void visitNGenericForStatement(NGenericForStatement* node) = 0;
    virtual void visitNAssignmentStatement(NAssignmentStatement* node) = 0;
    virtual void visitNDeclarationStatement(NDeclarationStatement* node) = 0;
    virtual void visitNReturnStatement(NReturnStatement* node) = 0;
    virtual void visitNBlock(NBlock* node) = 0;
    virtual void visitNExpression(NExpression* node) = 0;
    virtual void visitNStructDeclaration(NStructDeclaration* node) = 0;
    virtual void visitNType(NType* node) = 0;
    virtual void visitNStringType(NStringType* node) = 0;
    virtual void visitNNumType(NNumType* node) = 0;
    virtual void visitNBoolType(NBoolType* node) = 0;
    virtual void visitNNilType(NNilType* node) = 0;
    virtual void visitNTableType(NTableType* node) = 0;
    virtual void visitNFunctionType(NFunctionType* node) = 0;
    virtual void visitNStructType(NStructType* node) = 0;
    virtual void visitNAnyType(NAnyType *node) = 0;
    virtual void cleanup() = 0;
};

class Position {
   public:
    int lineno;
    int colno;

    Position(int lineno, int colno) : lineno(lineno), colno(colno) {}
};

class SymbolTableEntry {
   public:
    std::string name;
    NType* type;
    Position position;
    llvm::Value* value;
    int usages;

    SymbolTableEntry(
        std::string name,
        NType* type,
        Position position) : name(name), type(type), position(position), usages(0) {}
};

class SymbolTable {
   public:
    SymbolTable* parent;
    std::vector<SymbolTable*> children;
    std::vector<SymbolTableEntry*> entries;
    bool check_parent = true;

    virtual SymbolTableEntry* lookup_here(std::string name, int above_lineno) = 0;
    virtual SymbolTableEntry* lookup(std::string name, int above_lineno, bool check_parent = false) = 0;
    virtual SymbolTableEntry* lookup_or_throw(std::string name, int above_lineno, bool check_parent = true) = 0;
    virtual SymbolTableEntry* declare(SymbolTableEntry* entry, bool check_parent = false) = 0;
    virtual void scope_started(bool check_parent = true) = 0;
    virtual void scope_ended() = 0;
    virtual void enter_scope() = 0;
    virtual void exit_scope() = 0;
    virtual void prepare_for_next_run() = 0;
};

class SymbolTableStorage {
   public:
    SymbolTable* symtab;

    SymbolTableStorage(SymbolTable* symtab) : symtab(symtab) {}
};

extern SymbolTableStorage* symtab_storage;

class SymtabVisitor : public Visitor {
   public:
    virtual void cleanup() {
        while (symtab_storage->symtab->parent != nullptr) {
            symtab_storage->symtab = symtab_storage->symtab->parent;
        }
        symtab_storage->symtab->prepare_for_next_run();
    }
};

class SemanticError : public std::exception {
   public:
    std::string message;
    Position position;

    SemanticError(std::string message, Position position) : message(message), position(position) {}

    SemanticError(const char* message, Position position) : position(position) {
        this->message = std::string(message);
        this->position = position;
    }

    virtual const char* what() const throw() {
        std::stringstream* ss = new std::stringstream();
        *ss << message << " at " << position.lineno << ":" << position.colno;
        const char* cstr = strdup(ss->str().c_str());
        return cstr;
    }
};

class ScopedSymbolTable : public SymbolTable {
   public:
    ScopedSymbolTable(bool check_parent = true) {
        this->check_parent = check_parent;
    }
    int scope_id = 0;

    virtual SymbolTableEntry* lookup_here(std::string name, int above_lineno) {
        for (auto entry : this->entries) {
            bool same_name = entry->name == name;
            bool declared_above = entry->position.lineno < above_lineno;
            if (same_name and declared_above) {
                return entry;
            }
        }
        return nullptr;
    }
    virtual SymbolTableEntry* lookup(std::string name, int above_lineno, bool check_parent = false) {
        SymbolTable* symtab = this;
        bool check;
        do {
            SymbolTableEntry* prev_entry = symtab->lookup_here(name, above_lineno);

            if (prev_entry != nullptr) {
                return prev_entry;
            }
            check = check_parent and symtab->check_parent;
            std::cout << "Check parent(" << check_parent << ", ";
            std::cout << symtab->check_parent << "): " << check << std::endl;
        } while (symtab->parent != nullptr and (symtab = symtab->parent) and check);

        return nullptr;
    }

    virtual SymbolTableEntry* lookup_or_throw(std::string name, int above_lineno, bool check_parent = false) {
        auto result = this->lookup(name, above_lineno, check_parent);
        if (result == nullptr) {
            throw SemanticError(name + " is not defined around", Position(above_lineno, 0));
        }
        return result;
    }

    virtual SymbolTableEntry* lookup(SymbolTableEntry* entry, bool check_parent = false) {
        return this->lookup(entry->name, entry->position.lineno, check_parent);
    }

    virtual SymbolTableEntry* declare(SymbolTableEntry* entry, bool check_parent = false) {
        auto prev_entry = this->lookup(entry, check_parent);

        if (prev_entry == nullptr) {
            std::cout << "Declare "
                      << "'" << entry->name << "'";
            std::cout << " at position " << entry->position.lineno << ":" << entry->position.colno << std::endl;
            this->entries.push_back(entry);
            prev_entry = entry;
        } else {
            std::cerr << "Declare "
                      << "'" << entry->name << "'";
            std::cerr << " on position " << entry->position.lineno << ":" << entry->position.colno;
            std::cerr << ", again, prev is on " << prev_entry->position.lineno << ":" << prev_entry->position.colno << std::endl;
        }
        return entry;
    }

    virtual void enter_scope() {
        std::cout << "Scope entered" << std::endl;
        auto next_scope = this->children[this->scope_id++];
        symtab_storage->symtab = next_scope;
        std::cout << "Now scope is " << symtab_storage->symtab << std::endl;
    }

    virtual void scope_started(bool check_parent = true) {
        auto child = new ScopedSymbolTable(check_parent);
        child->parent = this;
        this->children.push_back(child);
        this->enter_scope();
    }

    virtual void exit_scope() {
        // current symbol table is the parent
        std::cout << "Scope ended" << std::endl;
        symtab_storage->symtab = symtab_storage->symtab->parent;
        std::cout << "Now scope is " << symtab_storage->symtab << std::endl;
    }

    virtual void scope_ended() {
        this->exit_scope();
    }

    virtual void prepare_for_next_run() {
        this->scope_id = 0;
        for (auto child : this->children) {
            child->prepare_for_next_run();
        }
    }
};

class Node {
   public:
    virtual ~Node() {}
    virtual void visit(Visitor* v) = 0;
    // virtual llvm::Value *codegen() = 0;
};

class NStatement : public Node {
public:
    llvm::Value* llvm_value = nullptr;
};

class NExpression : public NStatement {
   public:
    NType* type = nullptr;
    virtual void visit(Visitor* v) { v->visitNExpression(this); }
};

class NBlock : public Node {
   public:
    StatementList statements;
    NExpression* returnExpr;

    NBlock() : statements(StatementList()), returnExpr(nullptr) {}

    NBlock(StatementList statements, NExpression* returnExpr)
        : statements(statements), returnExpr(returnExpr) {}

    NBlock(StatementList statements) : statements(statements), returnExpr(nullptr) {}

    virtual void visit(Visitor* v) { v->visitNBlock(this); }

    // virtual llvm::Value *codegen() {
    //     return nullptr;
    // }
};

class NIdentifier : public NExpression {
   public:
    std::string name;
    Position position;
    NIdentifier(const std::string* name, Position position) : name(*name), position(position) {}
    NIdentifier(const std::string name, NType *type) : name(name), position(Position(0, 0)) { this->type = type; }
    NIdentifier(NType* type) : name(""), position(Position(0, 0)) { this->type = type; }

    static IdentifierList* fromTypeList(typeList* types) {
        IdentifierList* list = new IdentifierList();
        for (auto type : *types) {
            list->push_back(new NIdentifier(type));
        }
        return list;
    }

    virtual void visit(Visitor* v) { v->visitNIdentifier(this); }
};

class NType : public Node {
   public:
    virtual void visit(Visitor* v) {
        v->visitNType(this);
    }

    virtual operator std::string() const = 0;
};

class NStringType : public NType {
   public:
    NStringType() {}

    virtual void visit(Visitor* v) {
        v->visitNStringType(this);
    }
    virtual operator std::string() const {
        return "string";
    }
};

class NNumType : public NType {
   public:
    NNumType() {}

    virtual void visit(Visitor* v) {
        v->visitNNumType(this);
    }

    virtual operator std::string() const {
        return "number";
    }
};

class NBoolType : public NType {
   public:
    NBoolType() {}

    virtual void visit(Visitor* v) {
        v->visitNBoolType(this);
    }

    virtual operator std::string() const {
        return "boolean";
    }
};

class NNilType : public NType {
   public:
    NNilType() {}

    virtual void visit(Visitor* v) {
        v->visitNNilType(this);
    }

    virtual operator std::string() const {
        return "nil";
    }
};

class NAnyType: public NType {
public:
    NAnyType() {}
    virtual void visit(Visitor* v) {
        v->visitNAnyType(this);
    }

    virtual operator std::string() const {
        return "Any";
    }
};

class NTableType : public NType {
   public:
    NType* keyType;
    NType* valueType;
    NTableType(NType* keyType, NType* valueType) : keyType(keyType), valueType(valueType) {}

    virtual void visit(Visitor* v) {
        v->visitNTableType(this);
    }

    virtual operator std::string() const {
        return "table[key=" + std::string(*keyType) + ", value=" + std::string(*valueType) + "]";
    }
};

class NFunctionType : public NType {
public:
    llvm::Function* llvm_value;
    IdentifierList* arguments;
    typeList* returnTypes;
    bool varargs;

    NFunctionType(IdentifierList* arguments, typeList* returnTypes) : arguments(arguments), returnTypes(returnTypes) {}

    virtual void visit(Visitor* v) {
        v->visitNFunctionType(this);
    }

    virtual operator std::string() const {
        std::string result = "function(";
        for (auto arg : *arguments) {
            result += std::string(*arg->type) + ", ";
        }
        result += ") -> (";
        for (auto ret : *returnTypes) {
            result += std::string(*ret) + ", ";
        }
        result += ")";
        return result;
    }
};

class NStructType : public NType {
   public:
    NIdentifier* name;
    IdentifierList* fields;
    IdentifierList* methods;
    NStructType(NIdentifier* name, IdentifierList* fields, IdentifierList* methods) : name(name), fields(fields), methods(methods) {}

    NStructType(NIdentifier* name) : name(name), fields(nullptr), methods(nullptr) {}

    virtual void
    visit(Visitor* v) {
        v->visitNStructType(this);
    }

    virtual operator std::string() const {
        return "struct";
    }
};

class NNum : public NExpression {
   public:
    double value;
    NNum(long double value) : value(value) { this->type = new NNumType(); }

    virtual void visit(Visitor* v) { v->visitNNum(this); }
};

class NNil : public NExpression {
   public:
    NNil() { this->type = new NNilType(); }

    virtual void visit(Visitor* v) { v->visitNNil(this); }
};

class NBool : public NExpression {
   public:
    bool value;
    NBool(bool value) : value(value) { this->type = new NBoolType(); }

    virtual void visit(Visitor* v) { v->visitNBool(this); }
};

class NString : public NExpression {
   public:
    std::string& value;
    NString(std::string& value) : value(value) { this->type = new NStringType(); }

    virtual void visit(Visitor* v) { v->visitNString(this); }
};

class NBinaryOperatorExpression : public NExpression {
   public:
    NExpression* lhs;
    BinOpType op;
    NExpression* rhs;
    Position position;
    NBinaryOperatorExpression(NExpression* lhs, BinOpType op, NExpression* rhs, Position position)
        : lhs(lhs), op(op), rhs(rhs), position(position) {}

    virtual void visit(Visitor* v) { v->visitNBinaryOperatorExpression(this); }
};

class NUnaryOperatorExpression : public NExpression {
   public:
    UnOpType op;
    NExpression* rhs;
    Position position;
    NUnaryOperatorExpression(UnOpType op, NExpression* rhs, Position position) : op(op), rhs(rhs), position(position) {}

    virtual void visit(Visitor* v) { v->visitNUnaryOperatorExpression(this); }
};

class NTableConstructor : public NExpression {
   public:
    // Two different ways to create a table
    std::vector<keyvalPair*> keyvalPairList;  // Either one of these
    ExpressionList expressionList;            // or both are nullptr!!
    NTableConstructor() {}

    virtual void visit(Visitor* v) { v->visitNTableConstructor(this); }
};

class NWhileStatement : public NStatement {
   public:
    NExpression* condition;
    NBlock* block;
    NWhileStatement(NExpression* condition, NBlock* block)
        : condition(condition), block(block) {}

    virtual void visit(Visitor* v) { v->visitNWhileStatement(this); }
};

class NRepeatUntilStatement : public NStatement {
   public:
    NExpression* condition;
    NBlock* block;
    NRepeatUntilStatement(NExpression* condition, NBlock* block)
        : condition(condition), block(block) {}

    virtual void visit(Visitor* v) { v->visitNRepeatUntilStatement(this); }
};

class NDoStatement : public NStatement {
   public:
    NBlock* block;
    NDoStatement(NBlock* block) : block(block) {}

    virtual void visit(Visitor* v) { v->visitNDoStatement(this); }
};

class NIfStatement : public NStatement {
   public:
    std::vector<conditionBlock*> conditionBlockList;
    NBlock* elseBlock;
    NIfStatement(std::vector<conditionBlock*> conditionBlockList,
                 NBlock* elseBlock)
        : conditionBlockList(conditionBlockList), elseBlock(elseBlock) {}

    virtual void visit(Visitor* v) { v->visitNIfStatement(this); }
};

class NNumericForStatement : public NStatement {
   public:
    NIdentifier* id;
    NExpression* start;
    NExpression* end;
    NExpression* step;
    NBlock* block;
    NNumericForStatement(NIdentifier* id, NExpression* start, NExpression* end,
                         NExpression* step, NBlock* block)
        : id(id), start(start), end(end), step(step), block(block) {}

    virtual void visit(Visitor* v) { v->visitNNumericForStatement(this); }
};

class NGenericForStatement : public NStatement {
   public:
    IdentifierList identifiers;
    NExpression* expression;
    NBlock* block;
    NGenericForStatement(IdentifierList identifiers, NExpression* expression,
                         NBlock* block)
        : identifiers(identifiers), expression(expression), block(block) {}

    virtual void visit(Visitor* v) { v->visitNGenericForStatement(this); }
};

class NReturnStatement : public NStatement {
   public:
    NExpression* expression;
    NReturnStatement(NExpression* expression) : expression(expression) {}

    virtual void visit(Visitor* v) { v->visitNReturnStatement(this); }
};

class NAssignmentStatement : public NStatement {
   public:
    NExpression* ident;
    NType* type;
    NExpression* expression;
    NAssignmentStatement(NExpression* ident, NExpression* expression)
        : ident(ident), type(nullptr), expression(expression) { ident->type = type; }

    NAssignmentStatement(NExpression* ident, NType* type, NExpression* expression) : ident(ident), type(type), expression(expression) { ident->type = type; }

    virtual void visit(Visitor* v) { v->visitNAssignmentStatement(this); }
};

class NDeclarationStatement : public NStatement {
   public:
    NIdentifier* ident;
    NExpression* expression;
    Position position;
    NDeclarationStatement(NIdentifier* ident, NExpression* expression, Position position)
        : ident(ident), expression(expression), position(position) {}

    NDeclarationStatement(NIdentifier* ident, NType* type)
        : ident(ident), expression(nullptr), position(Position(0, 0)) {
        this->ident->type = type;
    }

    NDeclarationStatement(
        NIdentifier* ident,
        NType* type,
        NExpression* expression,
        Position position) : ident(ident), expression(expression), position(position) {
        this->ident->type = type;
    }

    static IdentifierList* toIdentifierList(std::vector<NDeclarationStatement*>* declarations) {
        if (declarations == nullptr) {
            return nullptr;
        }
        IdentifierList* list = new IdentifierList();
        for (auto declaration : *declarations) {
            list->push_back(declaration->ident);
        }
        return list;
    }

    virtual void visit(Visitor* v) { v->visitNDeclarationStatement(this); }
};

class NAccessKey : public NExpression {
   public:
    NExpression* expr;

    NExpression* indexExpr;

    NAccessKey(NExpression* expr, NExpression* indexexpr)
        : expr(expr), indexExpr(indexexpr) {}

    virtual void visit(Visitor* v) { v->visitNAccessKey(this); }
};

class NExpressionCall : public NExpression {
   public:
    NExpression* expr;

    ExpressionList exprlist;

    NExpressionCall(NExpression* expr, ExpressionList exprlist)
        : expr(expr), exprlist(exprlist) {}

    virtual void visit(Visitor* v) { v->visitNExpressionCall(this); }
};

class NFunctionDeclaration : public NStatement {
   public:
    typeList* return_type;
    NIdentifier* id;
    std::vector<NDeclarationStatement*>* arguments;
    NBlock* block;
    Position position;

    NFunctionDeclaration(
        typeList* return_type,
        NIdentifier* id,
        std::vector<NDeclarationStatement*>* arguments,
        NBlock* block,
        Position position)
        : return_type(return_type),
          id(id),
          arguments(arguments),
          block(block),
          position(position) {}

    static IdentifierList* toIdentifierList(std::vector<NFunctionDeclaration*>* declarations) {
        if (declarations == nullptr) {
            return nullptr;
        }
        IdentifierList* list = new IdentifierList();
        for (auto declaration : *declarations) {
            list->push_back(declaration->id);
        }
        return list;
    }

    NType* get_type() {
        return new NFunctionType(NDeclarationStatement::toIdentifierList(this->arguments), this->return_type);
    }

    virtual void visit(Visitor* v) { v->visitNFunctionDeclaration(this); }
};

class StructBody {
   public:
    std::vector<NDeclarationStatement*> fields;
    std::vector<NFunctionDeclaration*> methods;

    StructBody()
        : fields(std::vector<NDeclarationStatement*>()),
          methods(std::vector<NFunctionDeclaration*>()){};
};

class NStructDeclaration : public NStatement {
   public:
    NIdentifier* id;
    Position position;
    std::vector<NDeclarationStatement*> fields;
    std::vector<NFunctionDeclaration*> methods;

    NStructDeclaration(NIdentifier* id, Position position, StructBody* body)
        : id(id), position(position), fields(body->fields), methods(body->methods) {}

    virtual void visit(Visitor* v) { v->visitNStructDeclaration(this); }
};

class PrettyPrintVisitor : public Visitor {
   public:
    int tabs;
    PrettyPrintVisitor() : tabs(0) { this->name = "Pretty Print"; }
    const std::string indent() { return std::string(4 * this->tabs, ' '); }

    virtual void visitNNum(NNum* node) {
        std::cout << "NNum(value=" << node->value << ", type=";
        node->type->visit(this);
        std::cout << ")";
    }

    virtual void visitNNil(NNil* node) { std::cout << "NNil()"; }

    virtual void visitNBool(NBool* node) {
        std::cout << "NBool(value=" << node->value << ", type=";
        node->type->visit(this);
        std::cout << ")";
    }

    virtual void visitNString(NString* node) {
        std::cout << "NStr(value=" << node->value << ", type=";
        node->type->visit(this);
        std::cout << ")";
    }

    virtual void visitNIdentifier(NIdentifier* node) {
        std::cout << "NIdentifier(name=" << node->name;
        if (node->type != nullptr) {
            std::cout << ", type=";
            node->type->visit(this);
        }
        std::cout << ")";
    }

    virtual void visitNBinaryOperatorExpression(
        NBinaryOperatorExpression* node) {
        std::cout << "NBinaryOperatorExpression";
        std::cout << "(lhs=";
        node->lhs->visit(this);
        std::cout << ", op=";
        printBinaryOperator(node->op);
        std::cout << ", rhs=";
        node->rhs->visit(this);
        std::cout << ")";
    }

    void printBinaryOperator(BinOpType op) {
        switch (op) {
            case BinOpType::ADD:
                std::cout << "+";
                break;
            case BinOpType::SUBSTRACT:
                std::cout << "-";
                break;
            case BinOpType::MULTIPLY:
                std::cout << "*";
                break;
            case BinOpType::DIVIDE:
                std::cout << "/";
                break;
            case BinOpType::MODULO:
                std::cout << "%";
                break;
            case BinOpType::POWER:
                std::cout << "^";
                break;
            case BinOpType::EQUAL:
                std::cout << "==";
                break;
            case BinOpType::NOT_EQUAL:
                std::cout << "~=";
                break;
            case BinOpType::LESS_THAN:
                std::cout << "<";
                break;
            case BinOpType::LESS_THAN_OR_EQUAL:
                std::cout << "<=";
                break;
            case BinOpType::GREATER_THAN:
                std::cout << ">";
                break;
            case BinOpType::GREATER_THAN_OR_EQUAL:
                std::cout << ">=";
                break;
            case BinOpType::AND:
                std::cout << "and";
                break;
            case BinOpType::OR:
                std::cout << "or";
                break;
            case BinOpType::FLOOR_DIVIDE:
                std::cout << "//";
                break;
            default:
                std::cout << "unknown";
                break;
        }
    }

    void printUnaryOperator(UnOpType op) {
        switch (op) {
            case UnOpType::MINUS:
                std::cout << "-";
                break;
            case UnOpType::NOT:
                std::cout << "not";
                break;
            default:
                std::cout << "unknown";
                break;
        }
    }

    virtual void visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) {
        std::cout << "NUnaryOperatorExpression(op=";
        printUnaryOperator(node->op);
        std::cout << ", rhs=";
        node->rhs->visit(this);
        std::cout << ")";
    }

    virtual void visitNTableConstructor(NTableConstructor* node) {
        std::cout << "NTableConstructor(fields=[";
        for (auto field : node->keyvalPairList) {
            std::cout << "\n\t{ key=";
            field->first->visit(this);
            std::cout << ", value=";
            field->second->visit(this);
            std::cout << " }, ";
        }
        for (auto field : node->expressionList) {
            std::cout << "\n\texpr=";
            field->visit(this);
            std::cout << ", ";
        }
        std::cout << "\n    ])";
    }

    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) {
        std::cout << "NFunctionDeclaration(id=";
        node->id->visit(this);
        if (node->return_type != nullptr) {
            std::cout << ", return_type=[";
            for (auto type : *node->return_type) {
                type->visit(this);
                if (type != node->return_type->back())
                    std::cout << ", ";
            }
            std::cout << "]";
        }
        std::cout << ", block=[\n\t";
        node->block->visit(this);
        std::cout << "]";
        if (node->arguments != nullptr) {
            std::cout << ", arguments=[";
            for (auto arg : *node->arguments) {
                arg->visit(this);
                if (arg != node->arguments->back())
                    std::cout << ", ";
            }
            std::cout << "])";
        }
        std::cout << ")";
    }

    virtual void visitNAccessKey(NAccessKey* node) {
        std::cout << "\n\tNAccessKey(expr=";
        node->expr->visit(this);
        std::cout << ",\n  \t idx_expr=[";
        node->indexExpr->visit(this);
        std::cout << "])";
    }

    virtual void visitNExpressionCall(NExpressionCall* node) {
        std::cout << "\n\tNExpressionCall(expr=";
        node->expr->visit(this);
        std::cout << ", expr_list=[";
        for (auto expr : node->exprlist) {
            expr->visit(this);
            std::cout << ", ";
        }
        std::cout << "])";
    }

    virtual void visitNWhileStatement(NWhileStatement* node) {
        std::cout << "NWhileStatement(condition=";
        node->condition->visit(this);
        std::cout << ", block=\n\t";
        node->block->visit(this);
        std::cout << ")";
    }

    virtual void visitNRepeatUntilStatement(NRepeatUntilStatement* node) {
        std::cout << "NRepeatUntilStatement(condition=";
        node->condition->visit(this);
        std::cout << ", block=\n\t";
        node->block->visit(this);
        std::cout << ")";
    }

    virtual void visitNDoStatement(NDoStatement* node) {
        std::cout << "NDoStatement(block=";
        node->block->visit(this);
        std::cout << ")";
    }

    virtual void visitNIfStatement(NIfStatement* node) {
        std::cout << "NIfStatement(conditions=[";
        for (auto clause : node->conditionBlockList) {
            std::cout << "condition=";
            clause->first->visit(this);
            std::cout << "block=\n\t";
            clause->second->visit(this);
            if (clause != node->conditionBlockList.back()) {
                std::cout << ", ";
            }
        }
        std::cout << "])";
        if (node->elseBlock != nullptr) {
            std::cout << ", elseBlock=\n\t";
            node->elseBlock->visit(this);
        }
    }
    virtual void visitNNumericForStatement(NNumericForStatement* node) {
        std::cout << "NNumericForStatement(id=";
        node->id->visit(this);
        std::cout << ", start=";
        node->start->visit(this);
        std::cout << ", end=";
        node->end->visit(this);
        std::cout << ", step=";
        node->step->visit(this);
        std::cout << ", block=\n\t";
        node->block->visit(this);
        std::cout << ")";
    }

    virtual void visitNGenericForStatement(NGenericForStatement* node) {
        std::cout << "NGenericForStatement(identifiers=[";
        for (auto ident : node->identifiers) {
            ident->visit(this);
            if (ident != node->identifiers.back()) {
                std::cout << ", ";
            }
        }
        std::cout << "], expression=[";
        node->expression->visit(this);
        std::cout << "], block=\n\t";
        node->block->visit(this);
        std::cout << ")";
    }

    virtual void visitNAssignmentStatement(NAssignmentStatement* node) {
        std::cout << "NAssignmentStatement(ident=";
        node->ident->visit(this);
        std::string type = "`To be deduced`";
        if (node->type != nullptr) {
            std::cout << ", type=";
            node->type->visit(this);
        }
        std::cout << ", expr=";
        node->expression->visit(this);
        std::cout << ")";
    }

    virtual void visitNDeclarationStatement(NDeclarationStatement* node) {
        std::cout << "NDeclarationStatement(ident=";
        node->ident->visit(this);
        std::string type = "`To be deduced`";
        if (node->ident->type != nullptr) {
            std::cout << ", type=";
            node->ident->type->visit(this);
        }
        if (node->expression != nullptr) {
            std::cout << ", expr=";
            node->expression->visit(this);
        }
        std::cout << ")";
    }

    virtual void visitNReturnStatement(NReturnStatement* node) {
        std::cout << "NReturnStatement(expr=";
        node->expression->visit(this);
        std::cout << ")";
    }

    virtual void visitNBlock(NBlock* node) {
        std::cout << "NBlock(\n  statements=[" << std::endl;
        for (auto stmt : node->statements) {
            std::cout << "    ";
            stmt->visit(this);
            std::cout << std::endl;
        }
        std::cout << "  ]";
        std::cout << "\n  ]";
        if (node->returnExpr != nullptr) {
            std::cout << ",\n  returnExpr=";
            node->returnExpr->visit(this);
        }
        std::cout << "\n)";
    }

    virtual void visitNExpression(NExpression* node) {
        std::cout << "NExpression(nothing)";
    }

    virtual void visitNStructDeclaration(NStructDeclaration* node) {
        std::cout << "NStructDeclaration(id=";
        node->id->visit(this);
        std::cout << ", fields=[";
        for (auto field : node->fields) {
            field->visit(this);
            if (field != node->fields.back()) {
                std::cout << ", ";
            }
        }
        std::cout << "], methods=[";
        for (auto field : node->methods) {
            field->visit(this);
            if (field != node->methods.back()) {
                std::cout << ", ";
            }
        }
        std::cout << "])";
    }

    virtual void visitNType(NType* node) {
        std::cout << "NType(nothing)";
    }

    virtual void visitNNumType(NNumType* node) {
        std::cout << "NNumType";
    }

    virtual void visitNBoolType(NBoolType* node) {
        std::cout << "NBoolType";
    }

    virtual void visitNStringType(NStringType* node) {
        std::cout << "NStringType";
    }

    virtual void visitNNilType(NNilType* node) {
        std::cout << "NNilType";
    }

    virtual void visitNTableType(NTableType* node) {
        std::cout << "NTableType(keyType=";
        node->keyType->visit(this);
        std::cout << ", valueType=";
        node->valueType->visit(this);
        std::cout << ")\n";
    }

    virtual void visitNFunctionType(NFunctionType* node) {
        // TODO: print function type
        std::cout << "NFunctionType" << std::flush;
    }

    virtual void visitNStructType(NStructType* node) {
        // TODO: print struct type
        std::cout << "NStructType(";
        std::cout << "name=" << node->name << ",";
        std::cout << "type=" << node->name->type << ")";
    }
    virtual void cleanup() {}

    virtual void visitNAnyType(NAnyType *node) {}
};

class TypeChecker : public SymtabVisitor {
   public:
    bool isInsideFunction = false;
    NType* functionReturnType = nullptr;
    PrettyPrintVisitor* prettyPrinter;
    TypeChecker(PrettyPrintVisitor* prettyPrinter) : prettyPrinter(prettyPrinter) { this->name = "TypeChecker"; }

    bool compareTypes(NType* lhs, NType* rhs) {
        // since it is pointers to different objects, we need to check
        // if they are pointers for the same class
        if (lhs == nullptr) {
            std::cout << "LHS is null" << std::endl;
            return false;
        }
        if (rhs == nullptr) {
            std::cout << "RHS is null" << std::endl;
            return false;
        }

        if (typeid(*lhs) != typeid(*rhs)) {
            return false;
        }

        // if it is a table type, we need to check the key and value types
        if (typeid(*lhs) == typeid(NTableType)) {
            return compareTableTypes(dynamic_cast<NTableType*>(lhs), dynamic_cast<NTableType*>(rhs));
        }

        if (typeid(*lhs) == typeid(NFunctionType)) {
            return compareFunctionTypes(dynamic_cast<NFunctionType*>(lhs), dynamic_cast<NFunctionType*>(rhs));
        }

        if (typeid(*lhs) == typeid(NStructType)) {
            return compareStructTypes(dynamic_cast<NStructType*>(lhs), dynamic_cast<NStructType*>(rhs));
        }

        // if it is not a table type, then it is a primitive type
        // compare primitive types
        if (typeid(*lhs) == typeid(NNumType)) {
            return true;
        } else if (typeid(*lhs) == typeid(NBoolType)) {
            return true;
        } else if (typeid(*lhs) == typeid(NStringType)) {
            return true;
        } else if (typeid(*lhs) == typeid(NNilType)) {
            return true;
        }
        auto msg = typeid(*lhs).name();
        throw SemanticError(msg, Position(-1, -1));
        return false;
    }

    bool compareFunctionTypes(const NFunctionType* t1, const NFunctionType* t2) {
        if (t1 == nullptr || t2 == nullptr) {
            return false;
        }
        if (t1->varargs || t2->varargs) {
            // NOTE: temporary solution
            // It should compare arguments, but allows more elements of the same type at the end
            return true;
        }
        // Compare the return types
        if (t1->returnTypes == nullptr || t2->returnTypes == nullptr) {
            // If one of them is null, then they are not the same
            if (t1->returnTypes != t2->returnTypes) {
                return false;
            }
        } else {
            // If both of them are not null, then compare the types
            if (t1->returnTypes->size() != t2->returnTypes->size()) {
                return false;
            }
            for (int i = 0; i < t1->returnTypes->size(); ++i) {
                if (!compareTypes(t1->returnTypes->at(i), t2->returnTypes->at(i))) {
                    return false;
                }
            }
        }
        // Compare the argument types
        if (t1->arguments == nullptr || t2->arguments == nullptr) {
            // If one of them is null, then they are not the same
            if (t1->arguments != t2->arguments) {
                return false;
            }
        } else {
            // If both of them are not null, then compare the types
            if (t1->arguments->size() != t2->arguments->size()) {
                return false;
            } else {
                for (int i = 0; i < t1->arguments->size(); ++i) {
                    if (!compareTypes(t1->arguments->at(i)->type, t2->arguments->at(i)->type)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool compareStructTypes(NStructType* t1, NStructType* t2) {
        if (t1 == nullptr || t2 == nullptr) {
            return false;
        }
        if (t1->name == nullptr || t2->name == nullptr) {
            return false;
        }
        // here only check by name is needed, since only unique struct name defines a struct type
        // TODO name should be checked in the symbol table and corresponding struct type should be obtained
        return t1->name->name == t2->name->name;
    }

    bool compareTableTypes(NTableType* t1, NTableType* t2) {
        if (t1 == nullptr || t2 == nullptr) {
            return false;
        }
        // compare key types
        if (!compareTypes(t1->keyType, t2->keyType)) {
            return false;
        }
        // compare value types
        if (!compareTypes(t1->valueType, t2->valueType)) {
            return false;
        }
        return true;
    }

    virtual void visitNNum(NNum* node) {
        node->type = new NNumType();
    }

    virtual void visitNBool(NBool* node) {
        node->type = new NBoolType();
    }

    virtual void visitNString(NString* node) {
        node->type = new NStringType();
    }

    virtual void visitNNil(NNil* node) {
        node->type = new NNilType();
    }

    virtual void visitNDeclarationStatement(NDeclarationStatement* node) {
        std::cout << "DeclarationStatement(" << std::endl;
        std::cout << "lhs: " << node->ident->name;
        // check if it is a declaration without an expression
        if (node->expression == nullptr) {
            if (node->ident->type == nullptr) {
                std::cout << "TypeError: type and expression not specified, cannot be deduced(no expression)";
                throw SemanticError("Type of '" + node->ident->name + "' cannot be deduced, expression and type not specified", node->position);
            } else {
                std::cout << " type: ";
                node->ident->type->visit(this->prettyPrinter);
            }
            std::cout << ")\n"
                      << std::endl;
            return;
        }

        std::cout << std::endl
                  << "rhs: ";
        node->expression->visit(this);

        auto entry = symtab_storage->symtab->lookup_or_throw(node->ident->name, node->position.lineno + 1, true);
        entry->type = node->expression->type;

        if (compareTypes(node->ident->type, node->expression->type)) {
            std::cout << "Type approved, type: ";
            node->ident->type->visit(this->prettyPrinter);
            std::cout << ")" << std::endl;
            return;
        }

        if (node->ident->type == nullptr and node->expression->type == nullptr) {
            std::cout << "Both types are not defined";
            std::cout << ")" << std::endl;
            throw SemanticError("Type of '" + node->ident->name + "' cannot be deduced", node->position);
        }

        if (node->ident->type == nullptr and node->expression->type != nullptr) {
            std::cout << "Deduced type: ";
            node->ident->type = node->expression->type;
            node->ident->type->visit(this->prettyPrinter);
            std::cout << ")" << std::endl;
            return;
        }

        std::cout << "TypeError: type mismatch, rhs type: ";
        if (node->expression->type == nullptr) {
            std::cout << "not defined";
        } else {
            node->expression->type->visit(this->prettyPrinter);
        }
        std::cout << ", but lhs type: ";
        node->ident->type->visit(this->prettyPrinter);
        std::cout << std::endl
                  << ")" << std::endl;
        throw SemanticError("Type mismatch: " + node->ident->name, node->position);
    }

    virtual void visitNExpression(NExpression* node) {
        std::cout << "Expression(";
        node->visit(this->prettyPrinter);
        std::cout << ", has type: ";
        if (node->type == nullptr) {
            // TODO probably should throw an error here
            std::cout << "TypeError: unknown expression(type unknown)";
        } else {
            node->type->visit(this->prettyPrinter);
        }
        std::cout << ")" << std::endl;
    }

    virtual void visitNIdentifier(NIdentifier* node) {
        std::cout << "Identifier(";
        node->visit(this->prettyPrinter);
        std::cout << ",";
        SymbolTableEntry* entry = symtab_storage->symtab->lookup_or_throw(node->name, node->position.lineno, true);
        if (entry == nullptr) {
            throw SemanticError("TypeError: identifier " + node->name + " not defined", node->position);
        }
        if (entry->type == nullptr) {
            throw SemanticError("TypeError: identifier " + node->name + " TYPE not defined", node->position);
        }
        node->type = entry->type;
        std::cout << "type=";
        entry->type->visit(this->prettyPrinter);
        std::cout << ")" << std::endl;
    }

    virtual void visitNBinaryOperatorExpression(NBinaryOperatorExpression* node) {
        std::cout << "BinaryOperatorExpression(";
        node->visit(this->prettyPrinter);
        node->lhs->visit(this);
        node->rhs->visit(this);
        if (node->lhs->type == nullptr) {
            throw SemanticError("lhs type not defined", node->position);
        }
        if (node->rhs->type == nullptr) {
            throw SemanticError("rhs type not defined", node->position);
        }

        if (not compareTypes(node->lhs->type, node->rhs->type)) {
            std::cout << "TypeError: type mismatch, lhs type: ";
            node->lhs->type->visit(this->prettyPrinter);
            std::cout << ", rhs type: ";
            node->rhs->type->visit(this->prettyPrinter);
            std::cout << ", but should be the same)" << std::endl;
            throw SemanticError("Binary operator type mismatch", node->position);
        }
        // possible operators for num:
        // +, -, *, /, %, ^, ==, ~=, <, <=, >, >=
        // BinOpType.ADD, BinOpType.SUBSTRACT, BinOpType.MULTIPLY, BinOpType.DIVIDE, BinOpType.MODULO, BinOpType.POWER, BinOpType.EQUAL, BinOpType.NOT_EQUAL, BinOpType.LESS, BinOpType.LESS_EQUAL, BinOpType.GREATER, BinOpType.GREATER_EQUAL
        auto num_allowed_ops = std::vector<BinOpType>{BinOpType::ADD, BinOpType::SUBSTRACT,
                                                      BinOpType::MULTIPLY, BinOpType::DIVIDE,
                                                      BinOpType::MODULO, BinOpType::POWER, BinOpType::EQUAL,
                                                      BinOpType::NOT_EQUAL, BinOpType::LESS_THAN, BinOpType::LESS_THAN_OR_EQUAL,
                                                      BinOpType::GREATER_THAN, BinOpType::GREATER_THAN_OR_EQUAL};
        // possible operators for string:
        // ==, ~=, <, <=, >, >=, +
        auto str_allowed_ops = std::vector<BinOpType>{BinOpType::EQUAL,
                                                      BinOpType::NOT_EQUAL, BinOpType::LESS_THAN, BinOpType::LESS_THAN_OR_EQUAL,
                                                      BinOpType::GREATER_THAN, BinOpType::GREATER_THAN_OR_EQUAL, BinOpType::ADD};
        // possible operators for bool:
        // and, or, ==, ~=, <, <=, >, >=
        auto bool_allowed_ops = std::vector<BinOpType>{BinOpType::AND, BinOpType::OR,
                                                       BinOpType::EQUAL, BinOpType::NOT_EQUAL,
                                                       BinOpType::LESS_THAN, BinOpType::LESS_THAN_OR_EQUAL,
                                                       BinOpType::GREATER_THAN, BinOpType::GREATER_THAN_OR_EQUAL};

        // logical operators
        auto logical_ops = std::vector<BinOpType>{BinOpType::AND, BinOpType::OR, BinOpType::EQUAL, BinOpType::NOT_EQUAL, BinOpType::LESS_THAN, BinOpType::LESS_THAN_OR_EQUAL, BinOpType::GREATER_THAN, BinOpType::GREATER_THAN_OR_EQUAL};
        auto is_logical_op = std::find(logical_ops.begin(), logical_ops.end(), node->op) != logical_ops.end();
        // check if lhs->type is NNumType
        if (dynamic_cast<NNumType*>(node->lhs->type) != nullptr) {
            // check if the operator is in the list of possible operators
            if (std::find(num_allowed_ops.begin(), num_allowed_ops.end(), node->op) == num_allowed_ops.end()) {
                std::cout << "TypeError: operator " << node->op << " is not allowed for type num" << std::endl;
                throw SemanticError("Binary operator: operator not allowed for type num", node->position);
                return;
            }
        }

        // check if lhs->type is NStringType
        if (dynamic_cast<NStringType*>(node->lhs->type) != nullptr) {
            // check if the operator is in the list of possible operators
            if (std::find(str_allowed_ops.begin(), str_allowed_ops.end(), node->op) == str_allowed_ops.end()) {
                std::cout << "TypeError: operator " << node->op << " is not allowed for type string" << std::endl;
                throw SemanticError("Binary operator: operator not allowed for type string", node->position);
                return;
            }
        }

        // check if lhs->type is NBoolType
        if (dynamic_cast<NBoolType*>(node->lhs->type) != nullptr) {
            // check if the operator is in the list of possible operators
            if (std::find(bool_allowed_ops.begin(), bool_allowed_ops.end(), node->op) == bool_allowed_ops.end()) {
                std::cout << "TypeError: operator " << node->op << " is not allowed for type bool" << std::endl;
                throw SemanticError("Binary operator: operator not allowed for type bool", node->position);
                return;
            }
        }

        std::cout << "Type approved, type: ";
        if (is_logical_op) {
            node->type = new NBoolType();
        } else {
            node->type = node->lhs->type;
        }
        node->type->visit(this->prettyPrinter);

        std::cout << ")" << std::endl;
    }

    virtual void
    visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) {
        std::cout << "UnaryOperatorExpression(";
        node->visit(this->prettyPrinter);
        node->rhs->visit(this);
        if (node->rhs->type != nullptr) {
            node->type = new NBoolType();
        } else {
            std::cout << "TypeError: type mismatch, rhs type is not defined)" << std::endl;
            throw SemanticError("Unary operator type mismatch", node->position);
            return;
        }

        // possible operators for num:
        auto num_allowed_ops = std::vector<UnOpType>{UnOpType::MINUS};
        // possible operators for bool:
        auto bool_allowed_ops = std::vector<UnOpType>{UnOpType::NOT};
        // check if rhs->type is NNumType
        if (dynamic_cast<NNumType*>(node->rhs->type) != nullptr) {
            // check if the operator is in the list of possible operators
            if (std::find(num_allowed_ops.begin(), num_allowed_ops.end(), node->op) == num_allowed_ops.end()) {
                std::cout << "TypeError: operator " << node->op << " is not allowed for type num" << std::endl;
                throw SemanticError("Unary operator: operator not allowed for type num", node->position);
                return;
            }
        } else if (dynamic_cast<NBoolType*>(node->rhs->type) != nullptr) {
            // check if the operator is in the list of possible operators
            if (std::find(bool_allowed_ops.begin(), bool_allowed_ops.end(), node->op) == bool_allowed_ops.end()) {
                std::cout << "TypeError: operator " << node->op << " is not allowed for type bool" << std::endl;
                throw SemanticError("Unary operator: operator not allowed for type bool", node->position);
                return;
            }
        } else {
            std::cout << "TypeError: operator " << node->op << " is not allowed for type " << node->rhs->type << std::endl;
            throw SemanticError("Unary operator: operator not allowed for type", node->position);
            return;
        }
        std::cout << ")" << std::endl;
    }

    virtual void visitFunctionCall(NExpressionCall* node) {
        auto functionType = dynamic_cast<NFunctionType*>(node->expr->type);

        if (functionType->varargs) {
            std::cout << "Function has vararg param, skip args check";
        }
        // check argument types
        else if (functionType->arguments == nullptr || node->exprlist.empty()) {
            // check if both is empty
            if (functionType->arguments != nullptr || not node->exprlist.empty()) {
                std::cout << "TypeError: number of arguments is not correct";
                std::cout << ")" << std::endl;
                return;
            }
        } else {
            // If the number of arguments is not 0, check the number of arguments and the types
            if (functionType->arguments->size() != node->exprlist.size()) {
                std::cout << "TypeError: number of arguments is not correct";
                std::cout << ")" << std::endl;
                return;
            } else {
                for (int i = 0; i < functionType->arguments->size(); i++) {
                    node->exprlist.at(i)->visit(this);  // set type of the expression
                    if (node->exprlist.at(i)->type == nullptr) {
                        std::cout << "TypeError: argument type is not correct ";
                        std::cout << "at position " << i << ", expected type: ";
                        functionType->arguments->at(i)->visit(this->prettyPrinter);
                        std::cout << " but got type: UNKNOWN";
                        std::cout << ")" << std::endl;
                        throw SemanticError("TypeError for function args", Position(0, 0));
                    }
                    if (not compareTypes(functionType->arguments->at(i)->type, node->exprlist.at(i)->type)) {
                        std::cout << "TypeError: argument type is not correct ";
                        std::cout << "at position " << i << " expected type: ";
                        functionType->arguments->at(i)->type->visit(this->prettyPrinter);
                        std::cout << " but got type: ";
                        node->exprlist.at(i)->type->visit(this->prettyPrinter);
                        std::cout << ")" << std::endl;
                        throw SemanticError("TypeError for function args", Position(0, 0));
                    }
                }
            }
        }
        // set type to the return type of the function
        if (functionType->returnTypes != nullptr) {
            // assign to the first element of the return type list (for now)
            node->type = functionType->returnTypes->at(0);
        } else {
            // if the function does not return anything, set the type to nil
            node->type = new NNilType();
        }
        std::cout << "Type approved, return type: ";
        node->type->visit(this->prettyPrinter);
        std::cout << ")" << std::endl;
    }

    virtual void visitStructCall(NExpressionCall* node) {
    }

    virtual void visitNExpressionCall(NExpressionCall* node) {
        std::cout << "ExpressionCall(";
        node->visit(this->prettyPrinter);
        if (node->expr == nullptr) {
            throw SemanticError("Expression is not defined", Position(-1, -1));
            // std::cout << "TypeError: expression is not defined";
            // std::cout << ")" << std::endl;
            // return;
        }

        node->expr->visit(this);

        bool is_function = dynamic_cast<NFunctionType*>(node->expr->type) != nullptr;
        bool is_struct = dynamic_cast<NStructType*>(node->expr->type) != nullptr;

        bool is_ident_call = dynamic_cast<NIdentifier*>(node->expr) != nullptr;
        if (is_ident_call) {
            NIdentifier* ident = dynamic_cast<NIdentifier*>(node->expr);
            auto entry = symtab_storage->symtab->lookup_or_throw(ident->name, ident->position.lineno);
            entry->type->visit(this->prettyPrinter);
            node->expr->type = entry->type;
            is_function = dynamic_cast<NFunctionType*>(node->expr->type) != nullptr;
            is_struct = dynamic_cast<NStructType*>(node->expr->type) != nullptr;
            if (not is_function and not is_struct) {
                std::cout << "Entry '" << ident->name << "' is not callable at " << entry->position.lineno << std::endl;
            }
        }

        if (is_function) {
            this->visitFunctionCall(node);
            node->type = dynamic_cast<NFunctionType*>(node->expr->type)->returnTypes->at(0);
        } else if (is_struct) {
            this->visitStructCall(node);
            node->type = dynamic_cast<NStructType*>(node->expr->type);
        } else {
            throw SemanticError("Expression is not callable", Position(-1, -1));
        }
        std::cout << "type=";
        if (node->type != nullptr) {
            node->type->visit(this->prettyPrinter);
        }

        std::cout << ")" << std::endl;
    }

    void checkConditionalExpression(NExpression* expression) {
        // check if type of expression->type pointer is pointer to class NBoolType
        if (expression->type == nullptr) {
            throw SemanticError("TypeError: expression type not known (cannot be approved)", Position(-1, -1));
        }

        if (dynamic_cast<NBoolType*>(expression->type) != nullptr) {
            std::cout << "Type approved(bool)";
            return;
        }
        std::cout << "TypeError: wrong type (condition is ";
        expression->type->visit(this->prettyPrinter);
        std::cout << " but should be bool)";
        throw SemanticError("TypeError: conditional expression", Position(-1, -1));
    }

    void checkConditionalBlockList(std::vector<conditionBlock*> conditionBlockList) {
        for (auto conditionBlock : conditionBlockList) {
            std::cout << "condition: ";
            conditionBlock->first->visit(this);
            checkConditionalExpression(conditionBlock->first);
            symtab_storage->symtab->enter_scope();
            conditionBlock->second->visit(this);
            symtab_storage->symtab->exit_scope();
            std::cout << std::endl;
        }
    }

    virtual void visitNIfStatement(NIfStatement* node) {
        std::cout << "IfStatement(";
        node->visit(this->prettyPrinter);
        checkConditionalBlockList(node->conditionBlockList);
        if (node->elseBlock != nullptr) {
            std::cout << "else: ";
            symtab_storage->symtab->enter_scope();
            node->elseBlock->visit(this);
            symtab_storage->symtab->exit_scope();
        }
        std::cout << ")" << std::endl;
    }

    virtual void visitNWhileStatement(NWhileStatement* node) {
        std::cout << "WhileStatement(";
        std::cout << "condition: ";
        node->condition->visit(this);
        node->visit(this->prettyPrinter);
        checkConditionalExpression(node->condition);
        node->block->visit(this);
        std::cout << ")" << std::endl;
    }

    virtual void visitNRepeatUntilStatement(NRepeatUntilStatement* node) {
        std::cout << "RepeatUntilStatement(";
        node->visit(this->prettyPrinter);
        std::cout << "condition: ";
        node->condition->visit(this);
        checkConditionalExpression(node->condition);
        node->block->visit(this);
        std::cout << ")" << std::endl;
    }

    virtual void visitNNumericForStatement(NNumericForStatement* node) {
        std::cout << "NumericForStatement(";
        if (node->start == nullptr || node->end == nullptr) {
            std::cout << "TypeError: start or end is not defined";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: start or end is not defined for numeric for", Position(-1, -1));
            return;
        }

        if (node->step == nullptr) {
            // if step is not defined, set it to 1
            node->step = new NNum(1);
        }
        node->start->visit(this);
        node->end->visit(this);
        node->step->visit(this);

        // check if the start, end and step are numbers
        if (not compareTypes(node->start->type, new NNumType()) ||
            not compareTypes(node->end->type, new NNumType()) ||
            not compareTypes(node->step->type, new NNumType())) {
            std::cout << "TypeError: start, end or step is not a number";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: start, end or step is not a number", Position(-1, -1));
            return;
        }
        node->block->visit(this);
        std::cout << ")" << std::endl;
    }

    virtual void visitNGenericForStatement(NGenericForStatement* node) {
        std::cout << "GenericForStatement(";

        // check if identifiers are defined and there are 2 of them
        if (node->identifiers.size() != 2) {
            std::cout << "TypeError: there should be 2 identifiers";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: there should be 2 identifiers", Position(-1, -1));
            return;
        }

        // check if the expression list type is a table
        node->expression->visit(this);
        if (dynamic_cast<NTableType*>(node->expression->type) == nullptr) {
            std::cout << "TypeError: expression is not a table";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: expression is not a table", Position(-1, -1));
            return;
        }
        node->block->visit(this);
        std::cout << ")" << std::endl;
    }

    virtual void visitNReturnStatement(NReturnStatement* node) {
        std::cout << "ReturnStatement(";
        if (not this->isInsideFunction) {
            std::cout << "TypeError: return statement is not in a function";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: return statement is outside of a function", Position(-1, -1));
            return;
        }
        node->expression->visit(this);
        if (not compareTypes(this->functionReturnType, node->expression->type)) {
            std::cout << "TypeError: return type is not correct";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: return type is not correct", Position(-1, -1));
            return;
        }
        std::cout << "Type approved, return type: ";
        node->expression->type->visit(this->prettyPrinter);
        std::cout << ")" << std::endl;
    }

    virtual void visitNTableConstructor(NTableConstructor* node) {
        std::cout << "TableConstructor(";
        node->visit(this->prettyPrinter);
        // check for key value pairs
        if (node->keyvalPairList.size() > 0) {
            auto first_element = node->keyvalPairList[0];
            // check if the first element is defined
            if (first_element->first == nullptr or first_element->second == nullptr) {
                std::cout << "TypeError: key or value is not defined";
                std::cout << ")" << std::endl;
                throw SemanticError("TypeError: key or value is not defined", Position(-1, -1));
                return;
            }
            first_element->first->visit(this);
            first_element->second->visit(this);
            if (first_element->first->type == nullptr or first_element->second->type == nullptr) {
                std::cout << "TypeError: key or value type is not known";
                std::cout << ")" << std::endl;
                throw SemanticError("TypeError: key or value type is not known", Position(-1, -1));
                return;
            }

            // if key is not a number or string or bool, throw an error
            if (not compareTypes(first_element->first->type, new NNumType()) and
                not compareTypes(first_element->first->type, new NStringType()) and
                not compareTypes(first_element->first->type, new NBoolType())) {
                std::cout << "TypeError: key is not a number or string or bool";
                std::cout << ")" << std::endl;
                throw SemanticError("TypeError: key is not a number or string or bool", Position(-1, -1));
                return;
            }

            // check if the types of the key value pairs are the same
            for (auto keyvalPair : node->keyvalPairList) {
                keyvalPair->first->visit(this);
                keyvalPair->second->visit(this);
                if (not compareTypes(keyvalPair->first->type, first_element->first->type)) {
                    std::cout << "TypeError: key type is not the same";
                    std::cout << ")" << std::endl;
                    throw SemanticError("TypeError: key type is not the same", Position(-1, -1));
                    return;
                }
                if (not compareTypes(keyvalPair->second->type, first_element->second->type)) {
                    std::cout << "TypeError: value type is not the same";
                    std::cout << ")" << std::endl;
                    throw SemanticError("TypeError: value type is not the same", Position(-1, -1));
                    return;
                }
            }
            // if it is successfully checked, set the type of the table to the type of the first element
            node->type = new NTableType(first_element->first->type, first_element->second->type);
        } else if (node->expressionList.size() > 0) {
            auto first_element = node->expressionList[0];
            first_element->visit(this);
            if (first_element->type == nullptr) {
                std::cout << "TypeError: type of the first element is not known";
                std::cout << ")" << std::endl;
                throw SemanticError("TypeError: type of the first element is not known", Position(-1, -1));
                return;
            }

            // check if the types of the elements are the same
            for (auto expression : node->expressionList) {
                expression->visit(this);
                if (not compareTypes(expression->type, first_element->type)) {
                    std::cout << "TypeError: type of the element is not the same";
                    std::cout << ")" << std::endl;
                    throw SemanticError("TypeError: type of the element is not the same", Position(-1, -1));
                    return;
                }
            }

            // if it is successfully checked, it is an array of the type of the first element
            node->type = new NTableType(new NNumType(), first_element->type);
        }
        std::cout << ")" << std::endl;
    }

    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) {
        this->isInsideFunction = true;
        std::cout << "FunctionDeclaration(";
        node->visit(this->prettyPrinter);
        // create a function type for the function
        auto arglist = NDeclarationStatement::toIdentifierList(node->arguments);
        node->id->type = new NFunctionType(arglist, node->return_type);
        // set the return type of the function for the return statement check
        if (node->return_type != nullptr) {
            this->functionReturnType = node->return_type->at(0);
        } else {
            this->functionReturnType = nullptr;
        }
        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();
        this->isInsideFunction = false;
    }

    virtual void visitNAccessKey(NAccessKey* node) {
        std::cout << "\nAccessKey(";
        node->visit(this->prettyPrinter);
        std::cout << "\n key: ";
        node->expr->visit(this);
        if (node->expr->type == nullptr) {
            std::cout << "TypeError: expression type not known (cannot be approved)";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: expression type not known", Position(-1, -1));
            return;
        }
        // check if the type of expr is a table
        if (dynamic_cast<NTableType*>(node->expr->type) != nullptr) {
            // check if table has the key
            auto tableType = dynamic_cast<NTableType*>(node->expr->type);
            node->indexExpr->visit(this);
            if (not compareTypes(tableType->keyType, node->indexExpr->type)) {
                std::cout << "TypeError: key type is not correct";
                std::cout << ")" << std::endl;
                throw SemanticError("TypeError: key type is not correct", Position(-1, -1));
                return;
            } else {
                std::cout << "Type approved, key type: ";
                node->indexExpr->type->visit(this->prettyPrinter);
                std::cout << ")" << std::endl;
                return;
            }
        } else if (dynamic_cast<NStructType*>(node->expr->type) != nullptr) {
            // check if struct has the key
            auto structType = dynamic_cast<NStructType*>(node->expr->type);
            // if indexExpr is function call, check if the function in a struct
            // if indexExpr is identifier, check if the identifier is a struct
            if (dynamic_cast<NExpressionCall*>(node->indexExpr) != nullptr) {
                auto functionCall = dynamic_cast<NExpressionCall*>(node->indexExpr);
                if (functionCall == nullptr) {
                    std::cout << "TypeError: function call is not correct";
                    std::cout << ")" << std::endl;
                    throw SemanticError("TypeError: function call is not correct", Position(-1, -1));
                    return;
                }
                // expression if a name of a function -> check if the function is in a struct
                // cast functionCall->expr to NIdentifier
                auto functionIdent = dynamic_cast<NIdentifier*>(functionCall->expr);
                if (functionIdent == nullptr) {
                    std::cout << "TypeError: function has no name";
                    std::cout << ")" << std::endl;
                    throw SemanticError("TypeError: function has no name", Position(-1, -1));
                    return;
                }
                // iterate over methods of the structType fields structType->field is a vector of NIdentifier
                for (auto method : *structType->methods) {
                    if (method->name == functionIdent->name) {
                        // cast method->type to NFunctionType
                        auto methodType = dynamic_cast<NFunctionType*>(method->type);
                        // check if the function arguments are correct
                        functionCall->expr->type = method->type;
                        functionCall->visit(this);

                        if (not compareTypes(functionCall->type, methodType->returnTypes->at(0))) {
                            std::cout << "TypeError: return type is not correct, type check failed";
                            std::cout << ")" << std::endl;
                            throw SemanticError("TypeError: there is no such method in the struct", Position(-1, -1));
                            return;
                        } else {
                            std::cout << "Type approved, return type: ";
                            functionCall->type->visit(this->prettyPrinter);
                            std::cout << ")" << std::endl;
                            return;
                        }
                    }
                }
            } else if (dynamic_cast<NIdentifier*>(node->indexExpr) != nullptr) {
                auto identifier = dynamic_cast<NIdentifier*>(node->indexExpr);
                if (identifier == nullptr) {
                    std::cout << "TypeError: identifier is not correct";
                    std::cout << ")" << std::endl;
                    throw SemanticError("TypeError: identifier is not correct", Position(-1, -1));
                    return;
                }

                for (auto field : *structType->fields) {
                    if (field->name == identifier->name) {
                        node->indexExpr->type = field->type;
                        node->indexExpr->visit(this);
                        std::cout << "Type approved, identifier type: ";
                        identifier->type->visit(this->prettyPrinter);
                        std::cout << ")" << std::endl;
                        return;
                    }
                }
            } else {
                std::cout << "TypeError: indexExpr is not a function call or identifier";
                std::cout << ")" << std::endl;
                throw SemanticError("TypeError: Struct has no such field", Position(-1, -1));
                return;
            }
        }
        std::cout << "TypeError: expr is not a table or struct";
        std::cout << ")" << std::endl;
        throw SemanticError("TypeError: Expression is not correct", Position(-1, -1));
    }

    virtual void visitNDoStatement(NDoStatement* node) {
        symtab_storage->symtab->scope_started();
        node->block->visit(this);
        symtab_storage->symtab->scope_ended();
    }

    virtual void visitNAssignmentStatement(NAssignmentStatement* node) {
        std::cout << "AssignmentStatement(";
        node->visit(this->prettyPrinter);

        std::cout << "lhs: ";
        node->ident->visit(this);

        std::cout << "rhs: ";
        if (node->expression == nullptr) {
            std::cout << "TypeError: rhs is not defined";
            std::cout << ")" << std::endl;
            throw SemanticError("TypeError: rhs is not defined", Position(-1, -1));
            return;
        }

        node->expression->visit(this);
        if (not compareTypes(node->ident->type, node->expression->type)) {
            if (node->ident->type == nullptr and node->expression->type != nullptr) {
                node->type = node->expression->type;
                std::cout << "Deduced type: ";
                node->type->visit(this->prettyPrinter);
            } else {
                std::cout << "TypeError: type mismatch, rhs type: ";
                if (node->expression->type == nullptr) {
                    std::cout << "not defined";
                } else {
                    node->expression->type->visit(this->prettyPrinter);
                }
                std::cout << ", but should be ";
                node->ident->type->visit(this->prettyPrinter);
                throw SemanticError("TypeError: type mismatch", Position(-1, -1));
            }
        } else if (node->ident->type == nullptr) {
            // both types are not defined
            std::cout << "TypeError: both types are not defined";
            throw SemanticError("TypeError: both types are not defined", Position(-1, -1));
        } else {
            std::cout << "Type approved, type: ";
            node->ident->type->visit(this->prettyPrinter);
        }
        std::cout << ")" << std::endl;
    }

    virtual void visitNBlock(NBlock* node) {
        for (auto statement : node->statements) {
            statement->visit(this);
        }
        if (node->returnExpr != nullptr) {
            node->returnExpr->visit(this);
        }
    }

    virtual void visitNStructDeclaration(NStructDeclaration* node) {
        std::cout << "StructDeclaration(";
        node->visit(this->prettyPrinter);
        symtab_storage->symtab->scope_started();
        for (auto method : node->methods)
        {
            method->visit(this);
        }
        for (auto field : node->fields) {
            field->visit(this);
        }
        symtab_storage->symtab->scope_ended();
        // make a struct type for the struct
        auto fieldlist = NDeclarationStatement::toIdentifierList(&(node->fields));
        auto methodlist = NFunctionDeclaration::toIdentifierList(&(node->methods));
        auto struct_type = new NStructType(new NIdentifier(&node->id->name, node->position), fieldlist, methodlist);
        node->id->type = struct_type;
        std::cout << ")" << std::endl;
    }

    virtual void visitNType(NType* node) {
    }

    virtual void visitNStringType(NStringType* node) {
    }

    virtual void visitNBoolType(NBoolType* node) {
    }

    virtual void visitNNumType(NNumType* node) {
    }

    virtual void visitNNilType(NNilType* node) {
    }

    virtual void visitNTableType(NTableType* node) {
    }

    virtual void visitNFunctionType(NFunctionType* node) {
    }

    virtual void visitNStructType(NStructType* node) {
    }

    virtual void visitNAnyType(NAnyType *node) {}
};

class SymbolTableFillerVisitor : public SymtabVisitor {
   public:
    SymbolTableFillerVisitor() {
        this->name = "Symbol Table Filler";
        auto type = new NFunctionType(
            new IdentifierList({new NIdentifier("a", new NStringType()),
                                new NIdentifier("param", new NNumType())}),
            new typeList({new NNilType()})
        );
        auto entry = new SymbolTableEntry(
            "printf",
            type,
            Position(0, 0));
        symtab_storage->symtab->declare(entry);
        type->varargs = true;
    }

    virtual void visitNNum(NNum* node) {}

    virtual void visitNNil(NNil* node) {}

    virtual void visitNBool(NBool* node) {}

    virtual void visitNString(NString* node) {}

    virtual void visitNIdentifier(NIdentifier* node) {}

    virtual void visitNBinaryOperatorExpression(NBinaryOperatorExpression* node) {
        node->lhs->visit(this);
        node->rhs->visit(this);
    }

    virtual void visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) {
        node->rhs->visit(this);
    }

    virtual void visitNTableConstructor(NTableConstructor* node) {}

    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) {
        auto type = new NFunctionType(
            NDeclarationStatement::toIdentifierList(node->arguments),
            node->return_type);
        symtab_storage->symtab->declare(
            new SymbolTableEntry(node->id->name, type, Position(node->position)),
            true);

        symtab_storage->symtab->scope_started();
        for (auto arg : *node->arguments) {
            symtab_storage->symtab->declare(
                new SymbolTableEntry(arg->ident->name, arg->ident->type, Position(node->position)),
                false);
        }

        node->block->visit(this);
        symtab_storage->symtab->scope_ended();
    }

    virtual void visitNWhileStatement(NWhileStatement* node) {
        symtab_storage->symtab->scope_started();
        node->block->visit(this);
        symtab_storage->symtab->scope_ended();
    }

    virtual void visitNDoStatement(NDoStatement* node) {
        symtab_storage->symtab->scope_started();
        node->block->visit(this);
        symtab_storage->symtab->scope_ended();
    }

    virtual void visitNIfStatement(NIfStatement* node) {
        for (auto block : node->conditionBlockList) {
            symtab_storage->symtab->scope_started();
            block->second->visit(this);
            symtab_storage->symtab->scope_ended();
        }

        if (node->elseBlock != nullptr) {
            symtab_storage->symtab->scope_started();
            node->elseBlock->visit(this);
            symtab_storage->symtab->scope_ended();
        }
    }

    virtual void visitNNumericForStatement(NNumericForStatement* node) {
        symtab_storage->symtab->scope_started();
        node->block->visit(this);
        symtab_storage->symtab->scope_ended();
    }

    virtual void visitNGenericForStatement(NGenericForStatement* node) {
        symtab_storage->symtab->scope_started();
        node->block->visit(this);
        symtab_storage->symtab->scope_ended();
    }

    virtual void visitNRepeatUntilStatement(NRepeatUntilStatement* node) {
        symtab_storage->symtab->scope_started();
        node->block->visit(this);
        symtab_storage->symtab->scope_ended();
    }

    virtual void visitNDeclarationStatement(NDeclarationStatement* node) {
        SymbolTableEntry* entry = new SymbolTableEntry(node->ident->name, nullptr, node->position);
        symtab_storage->symtab->declare(entry, true);
    }

    virtual void visitNReturnStatement(NReturnStatement* node) {}

    virtual void visitNBlock(NBlock* node) {
        for (auto stmt : node->statements) {
            stmt->visit(this);
        }

        if (node->returnExpr != nullptr) {
            node->returnExpr->visit(this);
        }
    }

    virtual void visitNExpression(NExpression* node) { return; }

    virtual void visitNStructDeclaration(NStructDeclaration* node) {
        IdentifierList* field_idents = new IdentifierList();
        IdentifierList* method_idents = new IdentifierList();
        for (auto field_ident : node->fields)
            field_idents->push_back(field_ident->ident);
        for (auto method_ident : node->methods)
            method_idents->push_back(method_ident->id);

        auto type_entity = new NStructType(new NIdentifier(&node->id->name, node->position), field_idents, method_idents);
        SymbolTableEntry* entry = new SymbolTableEntry(node->id->name, type_entity, node->position);
        symtab_storage->symtab->declare(entry, true);

        symtab_storage->symtab->scope_started();
        for (auto field : node->fields) {
            field->visit(this);
        }
        for (auto method : node->methods) {
            method->visit(this);
        }
        symtab_storage->symtab->scope_ended();
    }
    virtual void visitNExpressionCall(NExpressionCall* node) { return; }
    virtual void visitNType(NType* node) { return; }
    virtual void visitNStringType(NStringType* node) { return; }
    virtual void visitNNumType(NNumType* node) { return; }
    virtual void visitNBoolType(NBoolType* node) { return; }
    virtual void visitNNilType(NNilType* node) { return; }
    virtual void visitNTableType(NTableType* node) { return; }
    virtual void visitNFunctionType(NFunctionType* node) { return; }
    virtual void visitNStructType(NStructType* node) { return; }
    virtual void visitNAnyType(NAnyType *node) {}
    virtual void visitNAccessKey(NAccessKey* node) {}
    virtual void visitNAssignmentStatement(NAssignmentStatement* node) {}
};

class DeclaredBeforeUseCheckerVisitor : public SymtabVisitor {
   public:
    DeclaredBeforeUseCheckerVisitor() {
        this->name = "Declare before use checker";
    }

    virtual void visitNNum(NNum* node) {}

    virtual void visitNNil(NNil* node) {}

    virtual void visitNBool(NBool* node) {}

    virtual void visitNString(NString* node) {}

    virtual SymbolTableEntry* check_symtab(NIdentifier* node, SymbolTable* symtab) {
        for (auto entry : symtab->entries) {
            if (entry->name == node->name) {
                std::cout << entry->name << "(";
                std::cout << entry->position.lineno << ":" << entry->position.colno << "-";
                std::cout << node->position.lineno << ":" << node->position.colno << ")" << std::endl;
                if (entry->position.lineno < node->position.lineno) {
                    std::cout << entry->name << " ok" << std::endl;
                    return entry;
                }
            }
        }
        if (symtab->parent != nullptr) {
            return check_symtab(node, symtab->parent);
        } else {
            throw new SemanticError("Identifier " + node->name + " not found", node->position);
        }
    }

    virtual void visitNIdentifier(NIdentifier* node) {
        // temporary try-catch just to print the line
        // do smth with it, it's impossible to compile it later
        try {
            check_symtab(node, symtab_storage->symtab);
        } catch (SemanticError* e) {
            std::cout << e->what() << std::endl;
        }
    }

    virtual void visitNBinaryOperatorExpression(NBinaryOperatorExpression* node) {
        node->lhs->visit(this);
        node->rhs->visit(this);
    }

    virtual void visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) {
        node->rhs->visit(this);
    }

    virtual void visitNTableConstructor(NTableConstructor* node) {}

    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) {
        if (node->arguments == nullptr) {
            std::cerr << "Arguments are null for function " << node->id->name << std::endl;
            return;
        }
        for (auto arg : *node->arguments) {
            if (arg->ident->type == nullptr) {
                std::cerr << "Argument type is null for ";
                std::cerr << node->id->name << ":" << arg->ident->name << std::endl;
                return;
            }
            arg->ident->type->visit(this);
        }

        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();

        if (node->return_type == nullptr) {
            std::cerr << "Return type is null for function " << node->id->name << std::endl;
            return;
        }
        for (auto return_type : *node->return_type) {
            if (return_type == nullptr) {
                std::cerr << "Return type is null for function " << node->id->name << std::endl;
                continue;
            }
            return_type->visit(this);
        }
    }

    virtual void visitNWhileStatement(NWhileStatement* node) {
        node->condition->visit(this);
        node->block->visit(this);
    }

    virtual void visitNDoStatement(NDoStatement* node) {
        node->block->visit(this);
    }

    virtual void visitNIfStatement(NIfStatement* node) {
        for (auto block : node->conditionBlockList) {
            symtab_storage->symtab->enter_scope();
            block->second->visit(this);
            symtab_storage->symtab->exit_scope();
        }

        if (node->elseBlock != nullptr) {
            symtab_storage->symtab->enter_scope();
            node->elseBlock->visit(this);
            symtab_storage->symtab->exit_scope();
        }
    }

    virtual void visitNNumericForStatement(NNumericForStatement* node) {
        node->start->visit(this);
        node->end->visit(this);
        if (node->step != nullptr) {
            node->step->visit(this);
        }
        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();
    }

    virtual void visitNGenericForStatement(NGenericForStatement* node) {
        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();
    }
    virtual void visitNRepeatUntilStatement(NRepeatUntilStatement* node) {
        node->condition->visit(this);
        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();
    }

    virtual void visitNDeclarationStatement(NDeclarationStatement* node) {
        if (node->ident->type != nullptr)
            node->ident->type->visit(this);
        if (node->expression != nullptr)
            node->expression->visit(this);
    }

    virtual void visitNReturnStatement(NReturnStatement* node) {
        node->expression->visit(this);
    }

    virtual void visitNBlock(NBlock* node) {
        for (auto stmt : node->statements) {
            stmt->visit(this);
        }

        if (node->returnExpr != nullptr) {
            node->returnExpr->visit(this);
        }
    }

    virtual void visitNExpression(NExpression* node) {}

    virtual void visitNStructDeclaration(NStructDeclaration* node) {
        symtab_storage->symtab->enter_scope();
        for (auto field : node->fields) {
            field->visit(this);
        }
        for (auto method : node->methods) {
            std::cout << "method " << method->id->name << std::endl;
            method->visit(this);
        }
        symtab_storage->symtab->exit_scope();
    }
    virtual void visitNExpressionCall(NExpressionCall* node) {
        node->expr->visit(this);
        for (auto expr : node->exprlist) {
            expr->visit(this);
        }
    }
    virtual void visitNType(NType* node) { return; }
    virtual void visitNStringType(NStringType* node) { return; }
    virtual void visitNNumType(NNumType* node) { return; }
    virtual void visitNBoolType(NBoolType* node) { return; }
    virtual void visitNNilType(NNilType* node) { return; }
    virtual void visitNTableType(NTableType* node) { return; }
    virtual void visitNFunctionType(NFunctionType* node) { return; }
    virtual void visitNStructType(NStructType* node) {
        try {
            auto entry = this->check_symtab(node->name, symtab_storage->symtab);
            if (entry == nullptr) {
                throw new SemanticError("Entry for type " + node->name->name + " is None", node->name->position);
            }

            std::cout << typeid(*entry->type).name() << " " << typeid(NStructType*).name() << std::endl;

            if (typeid(*entry->type).name() != typeid(NStructType).name()) {
                throw new SemanticError("Type " + node->name->name + " is not a struct: " + std::string(*entry->type), node->name->position);
            }

        } catch (SemanticError* e) {
            std::cout << e->what() << std::endl;
        }
    }
    virtual void visitNAnyType(NAnyType *node) {}
    virtual void visitNAccessKey(NAccessKey* node) {}
    virtual void visitNAssignmentStatement(NAssignmentStatement* node) {}
};

using namespace llvm;

class LLVMTypes {
public:
    static llvm::Type *str_type(LLVMContext *ctx) {
        return llvm::PointerType::getInt8PtrTy(*ctx);
    }
    static llvm::Type *num_type(LLVMContext *ctx) {
        return llvm::Type::getFloatTy(*ctx);
    }
    static llvm::Type *bool_type(LLVMContext *ctx) {
        return llvm::IntegerType::getInt1Ty(*ctx);
    }
};

class CodeGenVisitor : public SymtabVisitor {
   private:
    llvm::Type *getLLVMType(NType *type) {
        llvm::Type* return_type = builder->getVoidTy();

        if (type == nullptr) {
            return builder->getVoidTy();
        }
        if (typeid(*type) == typeid(NStringType)) {
            return_type = LLVMTypes::str_type(context);
        }
        else if (typeid(*type) == typeid(NNumType)) {
            return_type = LLVMTypes::num_type(context);
        } else if (typeid(*type) == typeid(NBoolType)) {
            return_type = LLVMTypes::bool_type(context);
        // } else if (typeid(node->return_type) == typeid(NStringType)) {
            // return_type = LLVMTypes::str_type(context);
            // TODO: types
        }

        return return_type;
    }

   public:
    llvm::LLVMContext* context;
    llvm::Module* module;
    llvm::IRBuilder<>* builder;
    llvm::Function* main;
    BasicBlock* block_main;
    std::map<std::string, llvm::Value *> NamedValues;

    CodeGenVisitor() {
        this->name = "Code Generation Visitor";
        this->context = new llvm::LLVMContext();
        this->module = new llvm::Module("Main", *context);
        this->builder = new llvm::IRBuilder<>(*context);

        Function* func_main = Function::Create(FunctionType::get(Type::getVoidTy(*context), false), GlobalValue::ExternalLinkage, "main", module);
        std::vector<Type *> printfArgsTypes({Type::getInt8PtrTy(*context)});
        Function *print = Function::Create(FunctionType::get(Type::getInt64Ty(*context), printfArgsTypes, true), GlobalValue::ExternalLinkage, "printf", module);
        auto entry = symtab_storage->symtab->lookup_or_throw("printf", 1);
        auto entry_type = dynamic_cast<NFunctionType *>(entry->type);
        if (entry_type == nullptr) {
            throw SemanticError("Cannot get function type for 'printf'", Position(0, 0));
        }
        entry_type->llvm_value = print;
        // Function *print = Function::Create(FunctionType::get(Type::getVoidTy(*context), false), GlobalValue::ExternalLinkage, "printf", module);

        this->main = func_main;
        block_main = BasicBlock::Create(*context, "entry", func_main);
        this->builder->SetInsertPoint(block_main);
    }

    virtual void visitNNum(NNum* node) {
        llvm::Value *ir = llvm::ConstantFP::get(*context, llvm::APFloat(node->value));
        node->llvm_value = ir;
    }

    virtual void visitNBool(NBool* node) {
        node->llvm_value = builder->getInt1(node->value);
    }

    virtual void visitNString(NString* node) {
        auto str = node->value;
        auto charType = llvm::IntegerType::get(*this->context, 8);

        std::vector<llvm::Constant *> chars(str.length());
        for(unsigned int i = 0; i < str.size(); i++) {
          chars[i] = llvm::ConstantInt::get(charType, str[i]);
        }

        chars.push_back(llvm::ConstantInt::get(charType, 0));

        auto stringType = llvm::ArrayType::get(charType, chars.size());

        auto globalDeclaration = (llvm::GlobalVariable*) module->getOrInsertGlobal("." + node->value, stringType);
        globalDeclaration->setInitializer(llvm::ConstantArray::get(stringType, chars));
        globalDeclaration->setConstant(true);
        globalDeclaration->setLinkage(llvm::GlobalValue::LinkageTypes::PrivateLinkage);
        globalDeclaration->setUnnamedAddr (llvm::GlobalValue::UnnamedAddr::Global);

        node->llvm_value = llvm::ConstantExpr::getBitCast(globalDeclaration, charType->getPointerTo());
    }

    virtual void visitNNil(NNil* node) {
        node->llvm_value = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(*context));
    }

    virtual bool load_required(SymbolTableEntry *entry) {
        bool is_function = dynamic_cast<NFunctionType *>(entry->type) != nullptr;
        bool is_struct = dynamic_cast<NStructType *>(entry->type) != nullptr;

        return not is_function and not is_struct;
    }

    virtual void visitNIdentifier(NIdentifier* node) {
        auto entry = symtab_storage->symtab->lookup_or_throw(node->name, node->position.lineno + 1);
        node->llvm_value = entry->value;
        if (this->load_required(entry)) {
            node->llvm_value = this->builder->CreateLoad(static_cast<AllocaInst *>(entry->value)->getAllocatedType(), entry->value);
        }
    }

    virtual void visitNBinaryOperatorExpression(NBinaryOperatorExpression* node) {
        node->lhs->visit(this);
        node->rhs->visit(this);
        switch (node->op) {
            case BinOpType::ADD:
                node->llvm_value = this->builder->CreateFAdd(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::SUBSTRACT:
                node->llvm_value = this->builder->CreateFSub(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::MULTIPLY:
                node->llvm_value = this->builder->CreateFMul(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::DIVIDE:
                node->llvm_value = this->builder->CreateSDiv(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::MODULO:
                node->llvm_value = this->builder->CreateSRem(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::POWER:
                //??
                break;
            case BinOpType::EQUAL:
                node->llvm_value = this->builder->CreateFCmpUEQ(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::NOT_EQUAL:
                node->llvm_value = this->builder->CreateFCmpUNE(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::LESS_THAN:
                node->llvm_value = this->builder->CreateFCmpULT(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::LESS_THAN_OR_EQUAL:
                node->llvm_value = this->builder->CreateFCmpULE(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::GREATER_THAN:
                node->llvm_value = this->builder->CreateFCmpUGT(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::GREATER_THAN_OR_EQUAL:
                node->llvm_value = this->builder->CreateFCmpUGE(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::AND:
                node->llvm_value = this->builder->CreateLogicalAnd(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::OR:
                node->llvm_value = this->builder->CreateLogicalOr(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            case BinOpType::FLOOR_DIVIDE:
                node->llvm_value = this->builder->CreateFDiv(node->lhs->llvm_value, node->rhs->llvm_value);
                break;
            default:
                throw SemanticError("Unknown binary operator", node->position);
        }
    }

    virtual void visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) {
        node->rhs->visit(this);
        // Value *OperandV = node->rhs->llvm_value;
        // Function *func = Function::Create(std::string("unary") + std::to_string(node->op));
        // node->llvm_value = this->builder->CreateCall(func, OperandV, "unop");
    }

    virtual void visitNTableConstructor(NTableConstructor* node) {}

    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) {
        symtab_storage->symtab->enter_scope();

        std::string name = node->id->name;
        llvm::Type* return_type;
        std::vector<Type*> parameter_types;

        if (node->return_type != nullptr) { 
            return_type = getLLVMType(node->return_type->at(0));
        } else {
            return_type = getLLVMType(nullptr);
        }

        if (node->arguments == nullptr) {
            parameter_types = std::vector<Type*>(1, builder->getVoidTy());
        }
        else {
            parameter_types = std::vector<Type*>();
            for(NDeclarationStatement *arg: *node->arguments) {
                NType* n_type = arg->ident->type;
                Type* type = getLLVMType(n_type);
                parameter_types.push_back(type);
            }
        }

        FunctionType* functionType = FunctionType::get(return_type, parameter_types, false);
        Function* function = Function::Create(functionType, GlobalValue::ExternalLinkage, name, module);
        int i = 0;
        for(auto arg: *node->arguments) {
            function->getArg(i)->setName(arg->ident->name);
            i++;
        }

        BasicBlock* block = BasicBlock::Create(*context, name, function);
        this->builder->SetInsertPoint(block);
        node->block->visit(this);

        this->builder->SetInsertPoint(block_main);

        symtab_storage->symtab->exit_scope();
    }

    virtual void visitNWhileStatement(NWhileStatement* node) {
        llvm::Function* func = this->builder->GetInsertBlock()->getParent();

        llvm::BasicBlock* conditionBlock = llvm::BasicBlock::Create(*context, "while_condition", func);
        llvm::BasicBlock* whileBlock = llvm::BasicBlock::Create(*context, "while_block", func);
        llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "while_exit", func);

        this->builder->CreateBr(conditionBlock);
        this->builder->SetInsertPoint(conditionBlock);

        node->condition->visit(this);

        this->builder->CreateCondBr(node->condition->llvm_value, whileBlock, afterBlock);

        this->builder->SetInsertPoint(whileBlock);
        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();

        this->builder->CreateBr(conditionBlock);
        this->builder->SetInsertPoint(afterBlock);
    }


    virtual void visitNRepeatUntilStatement(NRepeatUntilStatement* node) {
        llvm::Function* func = this->builder->GetInsertBlock()->getParent();

        llvm::BasicBlock* repeatBlock = llvm::BasicBlock::Create(*context, "repeat_block", func);
        llvm::BasicBlock* conditionBlock = llvm::BasicBlock::Create(*context, "repeat_condition", func);
        llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "repeat_exit", func);

        this->builder->CreateBr(repeatBlock);
        this->builder->SetInsertPoint(repeatBlock);

        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();

        this->builder->CreateBr(conditionBlock);
        this->builder->SetInsertPoint(conditionBlock);

        node->condition->visit(this);

            this->builder->CreateCondBr(node->condition->llvm_value, repeatBlock, afterBlock);

        this->builder->SetInsertPoint(afterBlock);
    }

    virtual void visitNDoStatement(NDoStatement* node) {
        llvm::Function* func = this->builder->GetInsertBlock()->getParent();

        llvm::BasicBlock* doBlock = llvm::BasicBlock::Create(*context, "do_block", func);
        llvm::BasicBlock* afterBlock = llvm::BasicBlock::Create(*context, "do_exit", func);

        this->builder->CreateBr(doBlock);
        this->builder->SetInsertPoint(doBlock);

        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();

        this->builder->CreateBr(afterBlock);
        this->builder->SetInsertPoint(afterBlock);
    }

    virtual void visitNIfStatement(NIfStatement* node) {
        // create then and else blocks.
        // where do we get the "function" instance?
        BasicBlock* thenBlock = BasicBlock::Create(*context, "thenBlock", main);
        BasicBlock* elseBlock = BasicBlock::Create(*context, "elseBlock", main);

        for (auto block : node->conditionBlockList) {
            symtab_storage->symtab->enter_scope();
            // visit the condition
            // TODO how to take its Value* like here:
            // Value* condition = builder->CreateICmpSGT(arg, value33, "compare.result");
            block->first->visit(this);
            Value* condition = block->first->llvm_value;
            // create the condition branch
            this->builder->CreateCondBr(condition, thenBlock, elseBlock);
            // set the insert point to thenBlock
            this->builder->SetInsertPoint(thenBlock);
            block->second->visit(this);
            symtab_storage->symtab->exit_scope();
        }

        if (node->elseBlock != nullptr) {
            symtab_storage->symtab->enter_scope();
            node->elseBlock->visit(this);
            symtab_storage->symtab->exit_scope();
        }
    }

    virtual void visitNNumericForStatement(NNumericForStatement* node) {
    }


    virtual void visitNGenericForStatement(NGenericForStatement* node) {
        symtab_storage->symtab->enter_scope();
        node->block->visit(this);
        symtab_storage->symtab->exit_scope();
    }

    virtual void visitNDeclarationStatement(NDeclarationStatement* node) {
        node->expression->visit(this);
        if (node->expression->llvm_value == nullptr) {
            throw SemanticError("Expression value is null", node->position);
        }
        auto entry = symtab_storage->symtab->lookup_or_throw(node->ident->name, node->position.lineno + 1);
        if (entry->value == nullptr) {
            AllocaInst *alloca = this->builder->CreateAlloca(node->expression->llvm_value->getType(), 0, node->ident->name);
            entry->value = alloca;
        }
        node->llvm_value = this->builder->CreateStore(node->expression->llvm_value, entry->value);
    }

    virtual void visitNReturnStatement(NReturnStatement* node) {
        node->expression->visit(this);
    }

    virtual void visitNBlock(NBlock* node) {
        auto func = builder->GetInsertBlock()->getParent();
        Value *last_stmt = llvm::ConstantFP::get(*context, APFloat(0.0));
        NStatement *last_stmt_node = nullptr;
        int stmt_num = 0;
        for (auto stmt : node->statements) {
            stmt->visit(this);
            if (stmt->llvm_value == nullptr) {
                continue;
            }
            last_stmt = stmt->llvm_value;
            last_stmt_node = stmt;
            stmt_num++;
        }

        Value *return_expr_llvm = last_stmt;
        if (node->returnExpr != nullptr) {
            node->returnExpr->visit(this);
            return_expr_llvm = node->returnExpr->llvm_value;
        }

        if (return_expr_llvm != nullptr && dynamic_cast<NReturnStatement*>(last_stmt_node) != nullptr) {
            this->builder->CreateRet(return_expr_llvm);
        } else {
            if (node->returnExpr != nullptr && func->getName() == "main") {
                this->builder->CreateRetVoid();
            }
        }

        std::string err;
        if (verifyFunction(*func, new raw_string_ostream(err))) {
            std::cerr << "\033[1;31m" << err << "\033[0m" << std::flush;
        }
    }


    virtual void visitNExpression(NExpression* node) {}

    virtual void visitNStructDeclaration(NStructDeclaration* node) {
        symtab_storage->symtab->enter_scope();
        for (auto field : node->fields) {
            field->visit(this);
        }
        for(auto method : node->methods) {
            std::cout << "method " << method->id->name << std::endl;
            method->visit(this);
        }
        symtab_storage->symtab->exit_scope();
    }
    virtual void visitNExpressionCall(NExpressionCall* node) {
        node->expr->visit(this);
        std::vector<llvm::Value *> args;
        for (auto expr : node->exprlist) {
            expr->visit(this);
            args.push_back(expr->llvm_value);
        }
        NFunctionType *function_type = dynamic_cast<NFunctionType *>(node->expr->type);
        bool is_function = function_type != nullptr;
        if (!is_function) {
            throw SemanticError("Cannot generate code for struct call yet", Position(-1, -1));
        }
        auto func = function_type->llvm_value;
        node->llvm_value = this->builder->CreateCall(func, args);
    }
    virtual void visitNType(NType* node) { return; }
    virtual void visitNStringType(NStringType* node) { return; }
    virtual void visitNNumType(NNumType* node) { return; }
    virtual void visitNBoolType(NBoolType* node) { return; }
    virtual void visitNNilType(NNilType* node) { return; }
    virtual void visitNTableType(NTableType* node) { return; }
    virtual void visitNFunctionType(NFunctionType* node) { return; }
    virtual void visitNStructType(NStructType* node) {
        try {
            auto entry = symtab_storage->symtab->lookup_or_throw(node->name->name, node->name->position.lineno);

            if (typeid(entry->type) != typeid(NStructType *)) {
                std::string type = "unknown";
                if (entry->type != nullptr) {
                    type = std::string(*entry->type);
                }
                throw new SemanticError("Type " + node->name->name + " is not a struct: " + type, node->name->position);
            }

        } catch(SemanticError *e) {
            std::cout << e->what() << std::endl;
        }
    }
    virtual void visitNAnyType(NAnyType *node) {}
    virtual void visitNAccessKey(NAccessKey* node) {}
    virtual void visitNAssignmentStatement(NAssignmentStatement* node) {}
    virtual void cleanup() {
        std::string err;
        if (verifyModule(*this->module, new raw_string_ostream(err))) {
            std::cerr << "\033[1;31m" << err << "\033[0m" << std::flush;
        }
    }
};
