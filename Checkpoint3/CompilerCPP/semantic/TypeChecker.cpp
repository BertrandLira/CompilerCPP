#include "TypeChecker.h"
#include "../utils/TokenType.cpp"

TypeChecker::TypeChecker() {}

void TypeChecker::declareVariable(const std::string& name) {
    variableTable[name] = TokenType::INVALID_TYPE;
    printf("---     Variavel %s declarada com sucesso\n", name.c_str());
}
void TypeChecker::setVariableType(TokenType type) {
    for (auto& pair : variableTable) {
        if (pair.second == TokenType::INVALID_TYPE){
            pair.second = type;
            printf("---  Variavel %s atualizada para o tipo %s \n", pair.first.c_str(), tokenTypeToString(type).c_str());
        }
    }
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
