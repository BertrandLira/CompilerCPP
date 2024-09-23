#include "TypeChecker.h"
#include "../utils/TokenType.cpp"

TypeChecker::TypeChecker() {}

void TypeChecker::declareVariable(const std::string& name) {
    variableTable[name] = TokenType::INVALID_TYPE;
    //printf("Variavel %s declarada com sucesso\n", name.c_str());
}
void TypeChecker::setVariableType(TokenType type) {
    for (auto& pair : variableTable) {
        if (pair.second == TokenType::INVALID_TYPE){
            pair.second = type;
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
    //printf("Tipo da variavel %s: %s\n", varName.c_str(), tokenTypeToString(varType).c_str());
    //printf("Tipo do valor: %s\n", tokenTypeToString(valueType).c_str());

    if (varType != valueType) {
        if(varType == TokenType::REAL && valueType == TokenType::INTEGER){
            //printf("Atribuicao de inteiro para real\n");
            return true;
        }
        return false;
    }
    //printf("Atribuicao de %s para %s\n", tokenTypeToString(valueType).c_str(), tokenTypeToString(varType).c_str());
    return true;
}
bool TypeChecker::checkRelationalOperation(TokenType v1Type, TokenType v2Type) {
    //printf("v1Type: %s\n", tokenTypeToString(v1Type).c_str());
    //printf("v2Type: %s\n", tokenTypeToString(v2Type).c_str());
    if(v1Type == v2Type){
        return true;
    }
    else if(v1Type == TokenType::INTEGER && v2Type == TokenType::REAL || v1Type == TokenType::REAL && v2Type == TokenType::INTEGER){
        return true;
    }
    else if(v1Type == TokenType::IDENTIFICADOR || v1Type == TokenType::BOOLEAN && v1Type == TokenType::IDENTIFICADOR|| v2Type == TokenType::BOOLEAN){
        return true;
    }
    else if((v1Type == TokenType::IDENTIFICADOR || v1Type == TokenType::INTEGER || v1Type == TokenType::REAL ) &&
            (v2Type == TokenType::IDENTIFICADOR || v2Type == TokenType::INTEGER || v2Type == TokenType::REAL )){
        return true;
    }
    else{
        printf("Erro: Tipos incompativeis\n");
        return false;   
    }
}
