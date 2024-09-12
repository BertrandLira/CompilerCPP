// tokentype.h
#ifndef TOKENTYPE_H
#define TOKENTYPE_H
#include <string>

enum class TokenType {
    IDENTIFICADOR,
    NUMERO_INTEIRO,
    NUMERO_REAL,
    OPERADOR_MATEMATICO,
    OPERADOR_RELACIONAL,
    OPERADOR_ATRIBUICAO,
    PARENTESES,
    CHAVES,
    RESERVADA,
    PONTO_VIRGULA,
    DOIS_PONTOS,
    PONTO_FINAL,
    VIRGULA
};

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::IDENTIFICADOR:
            return "Identificador";
        case TokenType::NUMERO_INTEIRO:
            return "Numero inteiro";
        case TokenType::NUMERO_REAL:
            return "Numero real";
        case TokenType::OPERADOR_MATEMATICO:
            return "Operador Matematico";
        case TokenType::OPERADOR_RELACIONAL:
            return "Operador Relacional";
        case TokenType::OPERADOR_ATRIBUICAO:
            return "Operador de Atribuicao";
        case TokenType::PARENTESES:
            return "Parenteses";
        case TokenType::RESERVADA:
            return "Palavra Reservada";
        case TokenType::CHAVES:
            return "Chaves";
        case TokenType::PONTO_VIRGULA:
            return "Ponto e virgula";
        case TokenType::DOIS_PONTOS:
            return "Dois pontos";
        case TokenType::PONTO_FINAL:
            return "Ponto final";
        case TokenType::VIRGULA:
            return "Virgula";
        default:
            return "Desconhecido";
    }
}

#endif // TOKENTYPE_H
