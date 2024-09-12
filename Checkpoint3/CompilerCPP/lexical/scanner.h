#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <vector>
#include <fstream>
#include "Token.cpp"

using namespace std;

class Scanner
{
    private:
        int state;
        int pos;
        int col;
        int row;
        string buffer;
        vector<string> reserved_word = {"program", "var", "integer", "real", "boolean", "procedure", "begin", "end", "if", "then", "else", "while", "do", "not", "true", "false"};

    public:
        Scanner();
        Scanner(string source);
        optional<Token> nextToken();
        int getRow();
        int getCol();
        char nextChar();
        bool isEOF();
        bool isLetter(char c);
        bool isDigit(char c);
        bool isMathOperator(char c);
        bool isRelationalOperator(char c);
        bool isParentheses(char c);
        bool isComentario(char c);
        bool isSpace(char c);
        bool isBrackets(char c);
        void isNewLine(char c);
        bool isReservedWord(string content);
        void back();

};

#endif // SCANNER_H
