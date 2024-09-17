#include "TypeChecker.h"
#include "../utils/TokenType.cpp"

TypeChecker::TypeChecker() {}

void TypeChecker::declareVariable(const std::string& name, TokenType type) {
    variableTable[name] = type;
}

TokenType TypeChecker::getVariableType(const std::string& name) {
    if (variableTable.find(name) != variableTable.end()) {
        return variableTable[name];
    }
    return TokenType::IDENTIFICADOR;
}

bool TypeChecker::checkAssignment(const std::string& varName, TokenType valueType) {
    TokenType varType = getVariableType(varName);

    if (varType != valueType) {
        return false;
    }
    return true;
}

bool TypeChecker::checkArithmeticOperation(TokenType v1Type, TokenType v2Type, TokenType& resultType) {
    if (v1Type == TokenType::NUMERO_INTEIRO && v2Type == TokenType::NUMERO_INTEIRO) {
        resultType = TokenType::NUMERO_INTEIRO;
        return true; 
    }
    return false; 
}

bool TypeChecker::checkRelationalOperation(TokenType v1Type, TokenType v2Type) {
    return (v1Type == TokenType::NUMERO_INTEIRO && v2Type == TokenType::NUMERO_INTEIRO);
}

bool TypeChecker::checkLogicalOperation(TokenType valueType) {
    return (valueType == TokenType::RESERVADA); 
}
