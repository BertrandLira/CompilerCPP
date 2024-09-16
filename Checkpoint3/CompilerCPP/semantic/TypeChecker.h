#ifndef TYPE_CHECKER_H
#define TYPE_CHECKER_H
#include <string>
#include <unordered_map>
#include "../lexical/token.h"

class TypeChecker {
public:
    TypeChecker();

    void declareVariable(const std::string& name, TokenType type);
    TokenType getVariableType(const std::string& name);
    bool checkAssignment(const std::string& varName, TokenType valueType);
    bool checkArithmeticOperation(TokenType v1Type, TokenType v2Type, TokenType& resultType);
    bool checkRelationalOperation(TokenType v1Type, TokenType v2Type);
    bool checkLogicalOperation(TokenType valueType);

private:
    std::unordered_map<std::string, TokenType> variableTable;
};

#endif
