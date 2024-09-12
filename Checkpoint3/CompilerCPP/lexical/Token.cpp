#include "Token.h"

Token::Token(){
}

Token::Token(TokenType type, string text){
    this->text = text;
    this->type = type;
}

TokenType Token::getType(){
    return this->type;
}

string Token::getText(){
    return this->text;
}

void Token::toString() const{
   cout << "Token [type = " + tokenTypeToString(type) + ", text = " + text + "]" << endl;
}