#include <iostream>
#include <vector>
// #include <llvm/IR/Value.h>

class CodeGenContext;
class NStatement;
class NExpression;
class NVariableDeclaration;

typedef std::vector<NStatement *> StatementList;
typedef std::vector<NExpression *> ExpressionList;
typedef std::vector<NIdentifier *> IdentifierList;
typedef std::vector<NVariableDeclaration *> VariableList;
typedef std::pair<NExpression, NBlock> conditionBlock;

class Node
{
public:
    virtual ~Node() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context) { }
};

class NExpression : public Node
{
};

class NStatement : public Node
{
};

class NBlock : public NExpression
{
public:
    StatementList statements;
    // also possible expression for return statement
    NExpression *returnExpr;
    NBlock(StatementList statements, NExpression *returnExpr) : statements(statements), returnExpr(returnExpr) {}

    NBlock(StatementList statements) : statements(statements) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NNum : public NExpression
{
public:
    long double value;
    NNum(long double value) : value(value) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NNill : public NExpression
{
public:
    NNill() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBool : public NExpression
{
public:
    bool value;
    NBool(bool value) : value(value) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NString : public NExpression
{
public:
    std::string value;
    NString(std::string value) : value(value) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NIdentifier : public NExpression
{
public:
    std::string name;
    NIdentifier(const std::string &name) : name(name) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NBinaryOperatorExpression : public NExpression
{
public:
    int op;
    NExpression &lhs;
    NExpression &rhs;
    NBinaryOperatorExpression(NExpression &lhs, int op, NExpression &rhs) : lhs(lhs), rhs(rhs), op(op) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NUnaryOperatorExpression : public NExpression
{
public:
    int op;
    NExpression &rhs;
    NUnaryOperatorExpression(int op, NExpression &rhs) : rhs(rhs), op(op) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class TableField : public Node
{
public:
    NExpression &key;
    NExpression &value;
    NIdentifier &id;
    TableField(NExpression &key, NExpression &value) : key(key), value(value) {}
    TableField(NIdentifier &id, NExpression &value) : id(id), value(value) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NTableConstructor : public NExpression
{
public:
    IdentifierList fieldlist;
    NTableConstructor() {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NWhileStatement : public NStatement
{
public:
    NExpression &condition;
    NBlock &block;
    NWhileStatement(NExpression &condition, NBlock &block) : condition(condition), block(block) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NRepeatUntilStatement : public NStatement
{
public:
    NExpression &condition;
    NBlock &block;
    NRepeatUntilStatement(NExpression &condition, NBlock &block) : condition(condition), block(block) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NIfStatement : public NStatement
{
public:
    std::vector<conditionBlock> conditionBlockList;
    NBlock &elseBlock;
    NIfStatement(std::vector<conditionBlock> conditionBlockList, NBlock &elseBlock) : conditionBlockList(conditionBlockList), elseBlock(elseBlock) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NNumericForStatement : public NStatement
{
public:
    NIdentifier &id;
    NExpression &start;
    NExpression &end;
    NExpression &step;
    NBlock &block;
    NNumericForStatement(NIdentifier &id, NExpression &start, NExpression &end, NExpression &step, NBlock &block) : id(id), start(start), end(end), step(step), block(block) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NGenericForStatement : public NStatement
{
public:
    IdentifierList idList;
    ExpressionList exprList;
    NBlock &block;
    NGenericForStatement(IdentifierList idList, ExpressionList exprList, NBlock &block) : idList(idList), exprList(exprList), block(block) {}
    // virtual llvm::Value* codeGen(CodeGenContext& context);
};

class NDeclarationStatement : public NStatement
{
public:
    StatementList statlist;
    ExpressionList exprList;
    NDeclarationStatement(StatementList statements, ExpressionList exprList) : statlist(statements), exprList(exprList) {}
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

// // class NFunctionDeclaration : public NStatement {
// // public:
// //     const NIdentifier& type;
// //     const NIdentifier& id;
// //     VariableList arguments;
// //     NBlock& block;
// //     NFunctionDeclaration(const NIdentifier& type, const NIdentifier& id,
// //             const VariableList& arguments, NBlock& block) :
// //         type(type), id(id), arguments(arguments), block(block) { }
// //     // virtual llvm::Value* codeGen(CodeGenContext& context);
// // };
