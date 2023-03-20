#include <iostream>
#include <vector>
#include <string>
#include <sstream>

// #include <llvm/IR/Value.h>

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;
class Node;
class NExpression;
class NStatement;
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
class NRepeatUntilStatement;
class NIfStatement;
class NNumericForStatement;
class NGenericForStatement;
class NDeclarationStatement;
class NTypeIdent;
class NFunctionDeclaration;
class NFunctionArgument;
class Visitor;
class PrettyPrintVisitor;

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NIdentifier*> IdentifierList;
typedef std::vector<NVariableDeclaration*> VariableList;
typedef std::pair<NExpression, NBlock> conditionBlock;
typedef std::vector<NFunctionArgument*> functionArguments;

class Visitor {
public:
    virtual void visitNNum(NNum* node) = 0;
    virtual void visitNNil(NNil* node) = 0;
    virtual void visitNBool(NBool* node) = 0;
    virtual void visitNString(NString* node) = 0;
    virtual void visitNIdentifier(NIdentifier* node) = 0;
    virtual void visitNBinaryOperatorExpression(NBinaryOperatorExpression* node) = 0;
    virtual void visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) = 0;
    virtual void visitNTableField(NTableField* node) = 0;
    virtual void visitNTableConstructor(NTableConstructor* node) = 0;
    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) = 0;
    virtual void visitNFunctionArgument(NFunctionArgument* node) = 0;
    virtual void visitNWhileStatement(NWhileStatement* node) = 0;
    virtual void visitNRepeatStatement(NRepeatUntilStatement* node) = 0;
    virtual void visitNIfStatement(NIfStatement* node) = 0;
    virtual void visitNNumericForStatement(NNumericForStatement* node) = 0;
    virtual void visitNGenericForStatement(NGenericForStatement* node) = 0;
    virtual void visitNDeclarationStatement(NDeclarationStatement* node) = 0;
    virtual void visitNBlock(NBlock* node) = 0;
    virtual void visitNExpression(NExpression* node) = 0;
};

class Node {
public:
    virtual ~Node() {}
    // virtual llvm::Value* codeGen(CodeGenContext* context) { }
    virtual std::string repr() = 0;
    virtual void visit(Visitor* v) = 0;
};

class NExpression : public Node {
public:
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NExpression(nothing)";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNExpression(this);
    }
};

class NStatement : public Node {
};

class NBlock : public Node {
public:
    StatementList statements;
    // also possible expression for return statement
    NExpression *returnExpr;

    NBlock() :
        statements({}), returnExpr(nullptr) {}

    NBlock(StatementList statements, NExpression *returnExpr) :
        statements(statements), returnExpr(returnExpr) { }
    
    NBlock(StatementList statements) :
        statements(statements) { }

    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NBlock(\n  statements=[" << std::endl;
        for (auto stmt: statements) {
            oss << "    " << stmt->repr() << std::endl;
        }

        oss << "  ]\n)";

        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNBlock(this);
    }
};


class NNum : public NExpression {
public:
    long double value;
    NNum(long double value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NNum(value=" << this->value << ")";
        return oss.str();
    }
    virtual void visit(Visitor* v) {
        v->visitNNum(this);
    }
};

class NNil : public NExpression {
public:
    NNil() { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NNil()";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNNil(this);
    }
};

class NBool : public NExpression {
public:
    bool value;
    NBool(bool value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NBool(value=" << this->value << ")";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNBool(this);
    }
};

class NString : public NExpression {
public:
    std::string *value;
    NString(std::string *value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NString(value=" << this->value->c_str() << ")";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNString(this);
    }
};

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string* name) : name(*name) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NIdentifier(name=" << this->name << ")";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNIdentifier(this);
    }
};

class NBinaryOperatorExpression : public NExpression {
public:
    NExpression* lhs;
    int op;
    NExpression* rhs;
    NBinaryOperatorExpression(NExpression* lhs, int op, NExpression* rhs) :
        lhs(lhs), op(op), rhs(rhs) { }
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NBinaryOperatorExpression";
        oss << "(lhs=" << this->lhs->repr();
        oss << ", op=" << this->op;
        oss << ", rhs=" << this->rhs->repr() << ")";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNBinaryOperatorExpression(this);
    }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
};

class NUnaryOperatorExpression : public NExpression {
public:
    int op;
    NExpression* rhs;
    NUnaryOperatorExpression(int op, NExpression* rhs) :
         op(op), rhs(rhs) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NUnaryOperatorExpression(op=" << this->op << ", rhs=" << this->rhs->repr() << ")";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNUnaryOperatorExpression(this);
    }
};

class NTableField : public Node {
public:
    NExpression* key;
    NExpression* value;
    NIdentifier* id;
    NTableField(NExpression* key, NExpression* value, NIdentifier* id) :
        key(key), value(value), id(id) { }
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NTableField(id=" << this->id->repr();
        oss << ", key=" << this->key->repr() << ", value=" << this->value->repr() << ")";
        return oss.str();
    }
    
    virtual void visit(Visitor* v) {
        v->visitNTableField(this);
    }
};


class NTableConstructor : public NExpression {
public:
    IdentifierList fieldlist;
    NTableConstructor() { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NTableConstructor(fixme)";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNTableConstructor(this);
    }
};

class NWhileStatement : public NStatement {
public:
    NExpression* condition;
    NBlock* block;
    NWhileStatement(NExpression* condition, NBlock* block) :
        condition(condition), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NWhileStatement(fixme)";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNWhileStatement(this);
    }
};

class NRepeatUntilStatement : public NStatement {
public:
    NExpression* condition;
    NBlock* block;
    NRepeatUntilStatement(NExpression* condition, NBlock* block) :
        condition(condition), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NRepeatUntil(fixme)";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNRepeatStatement(this);
    }
};

class NIfStatement : public NStatement {
public:
    std::vector<conditionBlock *> conditionBlockList;
    NBlock* elseBlock;
    NIfStatement(std::vector<conditionBlock *> conditionBlockList, NBlock* elseBlock) :
        conditionBlockList(conditionBlockList), elseBlock(elseBlock) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NIf(fixme)";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNIfStatement(this);
    }
};

class NNumericForStatement : public NStatement {
public:
    NIdentifier* id;
    NExpression* start;
    NExpression* end;
    NExpression* step;
    NBlock* block;
    NNumericForStatement(NIdentifier* id, NExpression* start, NExpression* end, NExpression* step, NBlock* block) :
        id(id), start(start), end(end), step(step), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NNumericFor(fixme)";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNNumericForStatement(this);
    }
};

class NGenericForStatement : public NStatement {
public:
    IdentifierList identifiers;
    ExpressionList expressions;
    NBlock* block;
    NGenericForStatement(IdentifierList identifiers, ExpressionList expressions, NBlock* block) :
        identifiers(identifiers), expressions(expressions), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext* context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NGenericFor(fixme)";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNGenericForStatement(this);
    }
};


class NDeclarationStatement : public NStatement {
public:
    NIdentifier *ident;
    NIdentifier *type;
    NExpression *expression;
    NDeclarationStatement(NIdentifier *ident, NExpression *expression) :
        ident(ident), type(nullptr), expression(expression) { }

    NDeclarationStatement(NIdentifier *ident, NIdentifier *type, NExpression *expression) :
        ident(ident), type(type), expression(expression) { }

    virtual std::string repr() {
        std::ostringstream oss;

        // oss << "NDeclarationStatement(statements=[\n";
        // for (auto stmt: this->statements) {
        //     oss << stmt->repr() <<", ";
        // }

        // oss << "],\nexpressions=[";
        // for (auto expr: this->expressions) {
        //     oss << expr->repr() <<", ";
        // }

        // oss << "])";

        oss << "NDeclarationStatement(ident=" << this->ident->repr();
        std::string type = "`To be deduced`";
        if (this->type != nullptr) {
            type = this->type->repr();
        }
        oss << ", type=" << type;
        oss << ", expr=" << this->expression->repr();

        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNDeclarationStatement(this);
    }
};

class NFunctionArgument: public NStatement {
public:
    NIdentifier *id;
    NIdentifier *type;

    NFunctionArgument(NIdentifier *id, NIdentifier *type) :
        id(id), type(type) { }

    // virtual llvm::Value* codeGen(CodeGenContext* context);

    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NFunctionArgument(id=" << this->id->repr();
        oss << ", type=" << this->type->repr();
        oss << ")";
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNFunctionArgument(this);
    }
};

class NFunctionDeclaration : public NStatement {
public:
    NIdentifier *return_type;
    NIdentifier *id;
    functionArguments arguments;
    NBlock *block;

    NFunctionDeclaration(NIdentifier *return_type, NIdentifier *id, 
            functionArguments *arguments, NBlock *block) :
        return_type(return_type), id(id), arguments(*arguments), block(block) { }

    // virtual llvm::Value* codeGen(CodeGenContext* context);

    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NFunctionDeclaration(id=" << this->id->repr();
        oss << ", return_type=" << this->return_type->repr();
        oss << ", block=" << this->block->repr();
        return oss.str();
    }

    virtual void visit(Visitor* v) {
        v->visitNFunctionDeclaration(this);
    }
};

// add visitor pattern for code generation for AST Nodes



class PrettyPrintVisitor : public Visitor {
public:
    PrettyPrintVisitor() { }

    virtual void visitNNum(NNum* node) {
        std::cout << node->value;
    }

    virtual void visitNNil(NNil* node) {
        std::cout << "nil";
    }

    virtual void visitNBool(NBool* node) {
        std::cout << node->value;
    }

    virtual void visitNString(NString* node) {
        std::cout << "\"" << node->value << "\"";
    }

    virtual void visitNIdentifier(NIdentifier* node) {
        std::cout << node->name;
    }

    virtual void visitNBinaryOperatorExpression(NBinaryOperatorExpression* node) {
        std::cout << "(";
        node->lhs->visit(this);
        std::cout << " " << node->op << " ";
        node->rhs->visit(this);
        std::cout << ")";
    }

    virtual void visitNUnaryOperatorExpression(NUnaryOperatorExpression* node) {
        std::cout << "(" << node->op;
        node->rhs->visit(this);
        std::cout << ")";
    }

    virtual void visitNTableField(NTableField* node) {
        std::cout << "[";
        node->key->visit(this);
        std::cout << "] = ";
        node->value->visit(this);
    }

    virtual void visitNTableConstructor(NTableConstructor* node) {
        std::cout << "{";
        for (auto field: node->fieldlist) {
            field->visit(this);
            std::cout << ", ";
        }
        std::cout << "}";
    }

    virtual void visitNFunctionDeclaration(NFunctionDeclaration* node) {
        std::cout << "function";
        std::cout << node->id->name << "(";
        for (auto arg: node->arguments) {
            arg->visit(this);
            std::cout << ", ";
        }
        std::cout << ") ";
        std::cout << "-> " << node->return_type->name << " ";
        node->block->visit(this);
        std::cout << " end";
    }

    virtual void visitNFunctionArgument(NFunctionArgument* node) {
        std::cout << node->id->name << ": " << node->type->name;
    }

    virtual void visitNWhileStatement(NWhileStatement* node) {
        std::cout << "while ";
        node->condition->visit(this);
        std::cout << " do ";
        node->block->visit(this);
        std::cout << " end";
    }

    virtual void visitNRepeatStatement(NRepeatUntilStatement* node) {
        std::cout << "repeat ";
        node->block->visit(this);
        std::cout << " until ";
        node->condition->visit(this);
    }

    virtual void visitNIfStatement(NIfStatement* node) {
        std::cout << "if ";
        for (auto clause: node->conditionBlockList) {
            // clause.first is the condition
            clause->first.visit(this);
            std::cout << " then ";
            clause->second.visit(this);
            if (clause != node->conditionBlockList.back()) {
                std::cout << " elseif ";
            }
        }
        if (node->elseBlock != nullptr) {
            std::cout << " else ";
            node->elseBlock->visit(this);
        }
    }
    
    virtual void visitNNumericForStatement(NNumericForStatement* node) {
        std::cout << "for " << node->id->name << " = ";
        node->start->visit(this);
        std::cout << ", ";
        node->end->visit(this);
        std::cout << ", ";
        node->step->visit(this);
        std::cout << " do ";
        node->block->visit(this);
        std::cout << " end";
    }

    virtual void visitNGenericForStatement(NGenericForStatement* node) {
        std::cout << "for ";
        for (auto ident: node->identifiers) {
            ident->visit(this);
            std::cout << ", ";
        }
        std::cout << " in ";
        for (auto expr: node->expressions) {
            expr->visit(this);
            std::cout << ", ";
        }
        std::cout << " do ";
        node->block->visit(this);
        std::cout << " end";
    }

    virtual void visitNDeclarationStatement(NDeclarationStatement* node) {
        node->ident->visit(this);
        if (node->type != nullptr) {
            std::cout << ": " << node->type->name;
        }
        std::cout << " = ";
        node->expression->visit(this);
    }

    virtual void visitNBlock(NBlock* node) {
        for (auto statement: node->statements) {
            statement->visit(this);
            for (auto statement: node->statements) {
                statement->visit(this);
            }
        }
        if (node->returnExpr) {
            std::cout << "return ";
            node->returnExpr->visit(this);
        }
    }

    virtual void visitNExpression(NExpression* node) {
        std::cout << "NOT_IMPLEMENTED_EXPRESSION";
    }
};