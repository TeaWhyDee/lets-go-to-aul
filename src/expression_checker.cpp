#include "node.h";
#include <iostream>

enum BasicType {
    nnil, nnum, nbool, nstring
};

BasicType checkExpression(NExpression *expr) {
    if (typeid(*expr) == typeid(NNill)) {
        return BasicType::nnil;
    } else if (typeid(*expr) == typeid(NNum)) {
        return BasicType::nnum;
    } else if (typeid(*expr) == typeid(NBool)) {
        return BasicType::nbool;
    } else if (typeid(*expr) == typeid(NString)) {
        return BasicType::nstring;
    } else if (typeid(*expr) == typeid(NBinaryOperatorExpression)) {
        return checkBinaryExpression(dynamic_cast<NBinaryOperatorExpression*>(expr));
    }
}

BasicType checkBinaryExpression(NBinaryOperatorExpression *expr) {
    const BasicType type1 = checkExpression(&((*expr).lhs));
    const BasicType type2 = checkExpression(&((*expr).rhs));
    if (type1 == BasicType::nnum && type2 ==  BasicType::nnum) {
        return BasicType::nnum;
    }
    throw std::invalid_argument("Incorrect types in the binary expression: " + std::to_string(type1) + " and " + std::to_string(type2) + " expected to be NNum");
}

