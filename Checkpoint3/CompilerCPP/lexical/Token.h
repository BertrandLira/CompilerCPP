#ifndef TOKEN_H
#define TOKEN_H
#include <vector>
#include <string>
#include "../utils/TokenType.cpp"

using namespace std;

class Token
{
    private:
        TokenType type;
        string text;
    
    public:
        Token();
        Token(TokenType type, string text);

        TokenType getType();
        string getText();

        void toString() const;

};

#endif // TOKEN_H
