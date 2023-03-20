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
class NNill;
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

typedef std::vector<NStatement*> StatementList;
typedef std::vector<NExpression*> ExpressionList;
typedef std::vector<NIdentifier*> IdentifierList;
typedef std::vector<NVariableDeclaration*> VariableList;
typedef std::pair<NExpression, NBlock> conditionBlock;
typedef std::vector<NFunctionArgument> functionArguments;

class Node {
public:
    virtual ~Node() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
    virtual std::string repr() = 0;
};

class NExpression : public Node {
public:
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NExpression(nothing)";
        return oss.str();
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

    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NBlock(\n  statements=[" << std::endl;
        for (auto stmt: statements) {
            oss << "    " << stmt->repr() << std::endl;
        }

        oss << "  ]\n)";

        return oss.str();
    }
};


class NNum : public NExpression {
public:
    long double value;
    NNum(long double value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NNum(value=" << this->value << ")";
        return oss.str();
    }
};

class NNill : public NExpression {
public:
    NNill() { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NNill()";
        return oss.str();
    }
};

class NBool : public NExpression {
public:
    bool value;
    NBool(bool value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::stringstream oss;
        oss << "NBool(value=" << this->value << ")";
        return oss.str();
    }
};

class NString : public NExpression {
public:
    std::string *value;
    NString(std::string *value) : value(value) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NString(value=" << this->value->c_str() << ")";
        return oss.str();
    }
};

class NIdentifier : public NExpression {
public:
    std::string name;
    NIdentifier(const std::string& name) : name(name) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NIdentifier(name=" << this->name << ")";
        return oss.str();
    }
};

class NBinaryOperatorExpression : public NExpression {
public:
    NExpression& lhs;
    int op;
    NExpression& rhs;
    NBinaryOperatorExpression(NExpression& lhs, int op, NExpression& rhs) :
        lhs(lhs), op(op), rhs(rhs) { }
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NBinaryOperatorExpression";
        oss << "(lhs=" << this->lhs.repr();
        oss << ", op=" << this->op;
        oss << ", rhs=" << this->rhs.repr() << ")";
        return oss.str();
    }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NUnaryOperatorExpression : public NExpression {
public:
    int op;
    NExpression& rhs;
    NUnaryOperatorExpression(int op, NExpression& rhs) :
         op(op), rhs(rhs) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NUnaryOperatorExpression(op=" << this->op << ", rhs=" << this->rhs.repr() << ")";
        return oss.str();
    }
};

class NTableField : public Node {
public:
    NExpression& key;
    NExpression& value;
    NIdentifier& id;
    NTableField(NExpression& key, NExpression& value, NIdentifier& id) :
        key(key), value(value), id(id) { }
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NTableField(id=" << this->id.repr();
        oss << ", key=" << this->key.repr() << ", value=" << this->value.repr() << ")";
        return oss.str();
    }
};


class NTableConstructor : public NExpression {
public:
    IdentifierList fieldlist;
    NTableConstructor() { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NTableConstructor(fixme)";
        return oss.str();
    }
};

class NWhileStatement : public NStatement {
public:
    NExpression& condition;
    NBlock& block;
    NWhileStatement(NExpression& condition, NBlock& block) :
        condition(condition), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NWhileStatement(fixme)";
        return oss.str();
    }
};

class NRepeatUntilStatement : public NStatement {
public:
    NExpression& condition;
    NBlock& block;
    NRepeatUntilStatement(NExpression& condition, NBlock& block) :
        condition(condition), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NRepeatUntil(fixme)";
        return oss.str();
    }
};

class NIfStatement : public NStatement {
public:
    std::vector<conditionBlock *> conditionBlockList;
    NBlock& elseBlock;
    NIfStatement(std::vector<conditionBlock *> conditionBlockList, NBlock& elseBlock) :
        conditionBlockList(conditionBlockList), elseBlock(elseBlock) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NIf(fixme)";
        return oss.str();
    }
};

class NNumericForStatement : public NStatement {
public:
    NIdentifier& id;
    NExpression& start;
    NExpression& end;
    NExpression& step;
    NBlock& block;
    NNumericForStatement(NIdentifier& id, NExpression& start, NExpression& end, NExpression& step, NBlock& block) :
        id(id), start(start), end(end), step(step), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NNumericFor(fixme)";
        return oss.str();
    }
};

class NGenericForStatement : public NStatement {
public:
    IdentifierList identifiers;
    ExpressionList expressions;
    NBlock& block;
    NGenericForStatement(IdentifierList identifiers, ExpressionList expressions, NBlock& block) :
        identifiers(identifiers), expressions(expressions), block(block) { }
    // virtual llvm::Value* codeGen(CodeGenContext& context);
    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NGenericFor(fixme)";
        return oss.str();
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
};

class NFunctionArgument: public NStatement {
public:
    NIdentifier *id;
    NIdentifier *type;

    NFunctionArgument(NIdentifier *id, NIdentifier *type) :
        id(id), type(type) { }

    // virtual llvm::Value* codeGen(CodeGenContext& context);

    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NFunctionArgument(id=" << this->id->repr();
        oss << ", type=" << this->type->repr();
        oss << ")";
        return oss.str();
    }

};

class NFunctionDeclaration : public NStatement {
public:
    NIdentifier *return_type;
    NIdentifier *id;
    functionArguments *arguments;
    NBlock *block;

    NFunctionDeclaration(NIdentifier *return_type, NIdentifier *id, 
            functionArguments *arguments, NBlock *block) :
        return_type(return_type), id(id), arguments(arguments), block(block) { }

    // virtual llvm::Value* codeGen(CodeGenContext& context);

    virtual std::string repr() {
        std::ostringstream oss;
        oss << "NFunctionDeclaration(id=" << this->id->repr();
        oss << ", return_type=" << this->return_type->repr();
        oss << ", block=" << this->block->repr();
        return oss.str();
    }
};

// class NFuncStatement : public NStatement {
// public:
//     NIdentifier& id;
//     std::vector<NIdentifier> argList;
//     NBlock& block;
//     NFuncStatement(NIdentifier& id, std::vector<NIdentifier> argList, NBlock& block) :
//         id(id), argList(argList), block(block) { }
//     // virtual llvm::Value* codeGen(CodeGenContext& context);
// };

// class NDouble : public NExpression {
// public:
//     double value;
//     NDouble(double value) : value(value) { }
//     // virtual llvm::Value* codeGen(CodeGenContext& context);
// };

// class NIdentifier : public NExpression {
// public:
//     std::string name;
//     NIdentifier(const std::string& name) : name(name) { }
//     // virtual llvm::Value* codeGen(CodeGenContext& context);
// };

// // class NMethodCall : public NExpression {
// // public:
// //     const NIdentifier& id;
// //     ExpressionList arguments;
// //     NMethodCall(const NIdentifier& id, ExpressionList& arguments) :
// //         id(id), arguments(arguments) { }
// //     NMethodCall(const NIdentifier& id) : id(id) { }
// //     // virtual llvm::Value* codeGen(CodeGenContext& context);
// // };

// // class NBinaryOperator : public NExpression {
// // public:
// //     int op;
// //     NExpression& lhs;
// //     NExpression& rhs;
// //     NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
// //         lhs(lhs), rhs(rhs), op(op) { }
// //     // virtual llvm::Value* codeGen(CodeGenContext& context);
// // };

// // class NAssignment : public NExpression {
// // public:
// //     NIdentifier& lhs;
// //     NExpression& rhs;
// //     NAssignment(NIdentifier& lhs, NExpression& rhs) : 
// //         lhs(lhs), rhs(rhs) { }
// //     // virtual llvm::Value* codeGen(CodeGenContext& context);
// // };

// class NBlock : public NExpression {
// public:
//     StatementList statements;
//     NBlock() { }
//     // virtual llvm::Value* codeGen(CodeGenContext& context);
// };

// // class NExpressionStatement : public NStatement {
// // public:
// //     NExpression& expression;
// //     NExpressionStatement(NExpression& expression) : 
// //         expression(expression) { }
// //     // virtual llvm::Value* codeGen(CodeGenContext& context);
// // };

// class NDeclaration : public NStatement {
// public:
//     // const NIdentifier& type;
//     NIdentifier& id;
//     NExpression assignmentExpr;
//     // Ndeclaration(const NIdentifier& type, NIdentifier& id) :
//     //     type(type), id(id) { }
//     NDeclaration(NIdentifier& id, NExpression assignmentExpr) :
//         id(id), assignmentExpr(assignmentExpr) { }
//     // virtual llvm::Value* codeGen(CodeGenContext& context);
// };

