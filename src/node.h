#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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
class NIdentifier;
class NBinaryOperatorExpression;
class NUnaryOperatorExpression;
class NTableField;
class NTableConstructor;
class NWhileStatement;
class NDoStatement;
class NRepeatUntilStatement;
class NIfStatement;
class NNumericForStatement;
class NGenericForStatement;
class NDeclarationStatement;
class NAssignmentStatement ;
class NReturnStatement;
class NTypeIdent;
class NFunctionDeclaration;
class NAccessKey;
class NExpressionCall;
class NFunctionArgument;
class Visitor;
class PrettyPrintVisitor;
class NTypedVar;
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
class SymbolTableEntry;
class SymbolTable;
class ScopedSymbolTable;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NIdentifier*> IdentifierList;
typedef std::vector<NVariableDeclaration*> VariableList;
typedef std::pair<NExpression*, NBlock*> conditionBlock;
typedef std::pair<NIdentifier*, NExpression*> keyvalPair;
typedef std::vector<NFunctionArgument*> functionArguments;
typedef std::vector<NTypedVar*> typedVarList;
typedef std::vector<NType*> typeList;

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
    virtual void visitNTableField(NTableField* node) = 0;
    virtual void visitNTableConstructor(NTableConstructor* node) = 0;
    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) = 0;
    virtual void visitNAccessKey(NAccessKey* node) = 0;
    virtual void visitNExpressionCall(NExpressionCall* node) = 0;
    virtual void visitNFunctionArgument(NFunctionArgument* node) = 0;
    virtual void visitNWhileStatement(NWhileStatement* node) = 0;
    virtual void visitNRepeatStatement(NRepeatUntilStatement* node) = 0;
    virtual void visitNDoStatement(NDoStatement* node) = 0;
    virtual void visitNIfStatement(NIfStatement* node) = 0;
    virtual void visitNNumericForStatement(NNumericForStatement* node) = 0;
    virtual void visitNGenericForStatement(NGenericForStatement* node) = 0;
    virtual void visitNAssignmentStatement(NAssignmentStatement * node) = 0;
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
    virtual void visitNTypedVar(NTypedVar* node) = 0;
};


class Position {
public:
    int lineno;
    int colno;

    Position (int lineno, int colno) : lineno(lineno), colno(colno) {}
};

class SymbolTableEntry {
public:
    std::string name;
    Position position;

    SymbolTableEntry(std::string name, Position position) : name(name), position(position) {}
};


class SymbolTable {
public:
    SymbolTable *parent;
    std::vector<SymbolTable *>children;
    std::vector<SymbolTableEntry *>entries;

    virtual SymbolTableEntry *lookup(std::string name, int above_lineno) = 0;
    virtual SymbolTableEntry *declare(SymbolTableEntry *entry) = 0;
    virtual void scope_started() = 0;
    virtual void scope_ended() = 0;
};


class SymbolTableStorage {
public:
    SymbolTable *symtab;

    SymbolTableStorage(SymbolTable *symtab) : symtab(symtab) {}
};

extern SymbolTableStorage *symtab_storage;


class ScopedSymbolTable : public SymbolTable {
public:
    virtual SymbolTableEntry *lookup(std::string name, int above_lineno) {
        for(auto entry: this->entries) {
            bool same_name = entry->name == name;
            bool declared_above = entry->position.lineno < above_lineno;
            if (same_name and declared_above) {
                return entry;
            }
        }

        return nullptr;
    }

    virtual SymbolTableEntry *declare(SymbolTableEntry *entry) {
        SymbolTableEntry *prev_entry = this->lookup(entry->name, entry->position.lineno);
        if (prev_entry != nullptr) {
            std::cerr << "Declare " << "'" << entry->name << "'";
            std::cerr << " on position " << entry->position.lineno << ":" << entry->position.colno;
            std::cerr << ", but it is already declared at position " << prev_entry->position.lineno << ":" << prev_entry->position.colno << std::endl;
            return nullptr;
        }
        std::cout << "Declare " << "'" << entry->name << "'";
        std::cout << " at position " << entry->position.lineno << ":" << entry->position.colno << std::endl;
        this->entries.push_back(entry);
        return entry;
    }

    virtual void scope_started() {
        std::cout << "Scope started" << std::endl;
        auto child = new ScopedSymbolTable();
        child->parent = this;
        this->children.push_back(child);
        extern SymbolTableStorage *symtab_storage;
        symtab_storage->symtab = child;
    }

    virtual void scope_ended() {
        // current symbol table is the parent
        std::cout << "Scope ended" << std::endl;
        symtab_storage->symtab = symtab_storage->symtab->parent;
    }
};

class Node {
   public:
    virtual ~Node() {}
    virtual void visit(Visitor* v) = 0;
};

class NStatement : public Node {};

class NExpression : public NStatement {
   public:
    NType* type = nullptr;
    virtual void visit(Visitor* v) { v->visitNExpression(this); }
};

class NBlock : public Node {
   public:
    StatementList statements;
    // also possible expression for return statement
    NExpression* returnExpr;

    NBlock() : statements({}), returnExpr(nullptr) {}

    NBlock(StatementList statements, NExpression* returnExpr)
        : statements(statements), returnExpr(returnExpr) {}

    NBlock(StatementList statements) : statements(statements) {}

    virtual void visit(Visitor* v) { v->visitNBlock(this); }
};

class NType : public Node {
   public:
    virtual void visit(Visitor* v) {
        v->visitNType(this);
    }
};

class NStringType : public NType {
   public:
    NStringType() {}

    virtual void visit(Visitor* v) {
        v->visitNStringType(this);
    }
};

class NNumType : public NType {
   public:
    NNumType() {}

    virtual void visit(Visitor* v) {
        v->visitNNumType(this);
    }
};

class NBoolType : public NType {
   public:
    NBoolType() {}

    virtual void visit(Visitor* v) {
        v->visitNBoolType(this);
    }
};

class NNilType : public NType {
   public:
    NNilType() {}

    virtual void visit(Visitor* v) {
        v->visitNNilType(this);
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
};

class NFunctionType : public NType {
   public:
    typedVarList* argumentTypes;
    typeList* returnTypes;

    NFunctionType(typedVarList* argumentTypes, typeList* returnTypes) : argumentTypes(argumentTypes), returnTypes(returnTypes) {}

    virtual void visit(Visitor* v) {
        v->visitNFunctionType(this);
    }
};

class NStructType : public NType {
   public:
    NIdentifier* name;
    typedVarList fields;
    typedVarList methods;
    NStructType(typedVarList fields, typedVarList methods) : fields(fields), methods(methods) {}

    NStructType(NIdentifier* name) : name(name), fields({}), methods({}) {}

    virtual void visit(Visitor* v) {
        v->visitNStructType(this);
    }
};

class NNum : public NExpression {
   public:
    long double value;
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

class NIdentifier : public NExpression {
   public:
    std::string name;
    NIdentifier(const std::string* name) : name(*name) {}

    virtual void visit(Visitor* v) { v->visitNIdentifier(this); }
};

class NBinaryOperatorExpression : public NExpression {
   public:
    NExpression* lhs;
    int op;
    NExpression* rhs;
    NBinaryOperatorExpression(NExpression* lhs, int op, NExpression* rhs)
        : lhs(lhs), op(op), rhs(rhs) {}

    virtual void visit(Visitor* v) { v->visitNBinaryOperatorExpression(this); }
};

class NUnaryOperatorExpression : public NExpression {
   public:
    int op;
    NExpression* rhs;
    NUnaryOperatorExpression(int op, NExpression* rhs) : op(op), rhs(rhs) {}

    virtual void visit(Visitor* v) { v->visitNUnaryOperatorExpression(this); }
};

class NTableField : public Node {
   public:
    NExpression* key;
    NExpression* value;
    NIdentifier* id;
    NTableField(NExpression* key, NExpression* value, NIdentifier* id)
        : key(key), value(value), id(id) {}

    virtual void visit(Visitor* v) { v->visitNTableField(this); }
};

class NTableConstructor : public NExpression {
   public:
    // Two different ways to create a table
    std::vector<keyvalPair*> keyvalPairList; // Either one of these
    ExpressionList expressionList;           // or both are nullptr!!
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

    virtual void visit(Visitor* v) { v->visitNRepeatStatement(this); }
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
    ExpressionList expressions;
    NBlock* block;
    NGenericForStatement(IdentifierList identifiers, ExpressionList expressions,
                         NBlock* block)
        : identifiers(identifiers), expressions(expressions), block(block) {}

    virtual void visit(Visitor* v) { v->visitNGenericForStatement(this); }
};

class NTypedVar : public NStatement {
   public:
    NIdentifier* ident;
    NType* type;

    static typedVarList* fromTypeList(typeList* types) {
        typedVarList* typedVarList = new std::vector<NTypedVar*>();
        for (auto type : *types) {
            typedVarList->push_back(new NTypedVar(type));
        }
        return typedVarList;
    }

    NTypedVar(NIdentifier* ident, NType* type)
        : ident(ident), type(type) {}

    NTypedVar(NType* type) : ident(nullptr), type(type) {}

    virtual void visit(Visitor* v) { v->visitNTypedVar(this); }
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
        : ident(ident), type(nullptr), expression(expression) {}

    NAssignmentStatement(NExpression* ident, NType* type,
                          NExpression* expression)
        : ident(ident), type(type), expression(expression) {}

    virtual void visit(Visitor* v) { v->visitNAssignmentStatement(this); }
};

class NDeclarationStatement : public NStatement {
   public:
    NIdentifier* ident;
    NType* type;
    NExpression* expression;
    Position position;
    NDeclarationStatement(NIdentifier* ident, NExpression* expression, Position position)
        : ident(ident), type(nullptr), expression(expression), position(position) {}

    NDeclarationStatement(NIdentifier* ident, NType* type,
                          NExpression* expression, Position position)
        : ident(ident), type(type), expression(expression), position(position) {}

    virtual void visit(Visitor* v) { v->visitNDeclarationStatement(this); }
};

class NFunctionArgument : public NStatement {
   public:
    NIdentifier* id;
    NIdentifier* type;

    NFunctionArgument(NIdentifier* id, NIdentifier* type)
        : id(id), type(type) {}

    virtual void visit(Visitor* v) { v->visitNFunctionArgument(this); }
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
    //    TODO initialize function_type
    NType* function_type;
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
        Position position
    ):  return_type(return_type),
        id(id),
        arguments(arguments),
        block(block),
        position(position)
    {
        this->function_type = fromFunctionDeclaration(arguments, return_type);
    }

    NFunctionType* fromFunctionDeclaration(std::vector<NDeclarationStatement*>* arguments, typeList* returnTypes) {
        typedVarList* argumentTypes = new typedVarList();
        for (auto arg : *arguments) {
            argumentTypes->push_back(new NTypedVar(arg->ident, arg->type));
        }
        return new NFunctionType(argumentTypes, returnTypes);
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
    PrettyPrintVisitor() : tabs(0) {this->name = "Pretty Print";}
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
        std::cout << ", op=" << node->op << ", rhs=";
        node->rhs->visit(this);
        std::cout << ")";
    }

    virtual void visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) {
        std::cout << "NUnaryOperatorExpression(op=" << node->op << ", rhs=";
        node->rhs->visit(this);
        std::cout << ")";
    }

    virtual void visitNTableField(NTableField* node) {
        std::cout << "NTableField(id=";
        node->id->visit(this);
        std::cout << ", key=";
        node->key->visit(this);
        std::cout << ", value=";
        node->value->visit(this);
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
        std::cout << ", return_types=";
        if (node->return_type != nullptr)
            for (auto type : *node->return_type) {
                type->visit(this);
                std::cout << ", ";
            }
        else
            std::cout << "nothing";
        std::cout << ", block=[\n\t";
        node->block->visit(this);
        std::cout << "], arguments=[";
        for (auto arg : *node->arguments) {
            arg->visit(this);
            if (arg != node->arguments->back()) std::cout << ", ";
        }
        std::cout << "])";
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

    virtual void visitNFunctionArgument(NFunctionArgument* node) {
        std::cout << "NFunctionArgument(id=";
        node->id->visit(this);
        std::cout << ", type=";
        node->type->visit(this);
        std::cout << ")";
    }

    virtual void visitNWhileStatement(NWhileStatement* node) {
        std::cout << "NWhileStatement(condition=";
        node->condition->visit(this);
        std::cout << ", block=\n\t";
        node->block->visit(this);
        std::cout << ")";
    }

    virtual void visitNRepeatStatement(NRepeatUntilStatement* node) {
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
        std::cout << "], expressions=[";
        for (auto expr : node->expressions) {
            expr->visit(this);
            if (expr != node->expressions.back()) {
                std::cout << ", ";
            }
        }
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
        if (node->type != nullptr) {
            std::cout << ", type=";
            node->type->visit(this);
        }
        std::cout << ", expr=";
        node->expression->visit(this);
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
        std::cout << "NFunctionType";
    }

    virtual void visitNStructType(NStructType* node) {
        // TODO: print struct type
        std::cout << "NStructType";
    }

    virtual void visitNTypedVar(NTypedVar* node) {
        std::cout << "NTypedVar(id=";
        node->ident->visit(this);
        std::cout << ", type=";
        node->type->visit(this);
        std::cout << ")";
    }
};

class SymbolTableFillerVisitor : public Visitor {
public:
    SymbolTableStorage *symtab_storage;

    SymbolTableFillerVisitor(SymbolTableStorage *symtab_storage) : symtab_storage(symtab_storage) { this->name = "Symbol Table Filler"; }

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

    virtual void visitNTableField(NTableField* node) {}

    virtual void visitNTableConstructor(NTableConstructor* node) {}

    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) {
        this->symtab_storage->symtab->declare(new SymbolTableEntry(node->id->name, Position(node->position)));

        this->symtab_storage->symtab->scope_started();
        for(auto arg: *node->arguments) {
            this->symtab_storage->symtab->declare(new SymbolTableEntry(arg->ident->name, Position(node->position)));
        }

        node->block->visit(this);
        this->symtab_storage->symtab->scope_ended();
    }

    virtual void visitNFunctionArgument(NFunctionArgument* node) {}

    virtual void visitNWhileStatement(NWhileStatement* node) {
        node->block->visit(this);
    }

    virtual void visitNRepeatStatement(NRepeatUntilStatement* node) {
        node->block->visit(this);
    }

    virtual void visitNDoStatement(NDoStatement* node) {
        node->block->visit(this);
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
        node->block->visit(this);
    }

    virtual void visitNGenericForStatement(NGenericForStatement* node) {
        node->block->visit(this);
    }

    virtual void visitNDeclarationStatement(NDeclarationStatement* node) {
        SymbolTableEntry *entry = new SymbolTableEntry(node->ident->name, node->position);
        this->symtab_storage->symtab->declare(entry);
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
        SymbolTableEntry *entry = new SymbolTableEntry(node->id->name, node->position);
        this->symtab_storage->symtab->declare(entry);
        this->symtab_storage->symtab->scope_started();
        for (auto field: node->fields) {
            field->visit(this);
        }
        for (auto method: node->methods) {
            method->visit(this);
        }
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
    virtual void visitNTypedVar(NTypedVar* node) { return; }
    virtual void visitNAccessKey(NAccessKey* node) {}
    virtual void visitNAssignmentStatement(NAssignmentStatement * node) { }
};
