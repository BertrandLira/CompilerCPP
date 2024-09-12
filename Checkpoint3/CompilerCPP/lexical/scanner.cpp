#include "scanner.h"
#include <optional>

using namespace std;

Scanner::Scanner(){

}

Scanner::Scanner(string source){
    pos = 0;
    col = 0;
    row = 1;

    ifstream file(source);

    if(!file.is_open()){
        cout << "Erro ao abrir o arquivo!";
    }else{
        string bufferTemp((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        buffer = bufferTemp;
    }

    cout << "buffer size: " << buffer.size() << endl;

}

int Scanner::getRow(){
    return this->row;
}

int Scanner::getCol(){
    return this->col;
}


char Scanner::nextChar(){
    col++;
    return buffer[pos++];
}

bool Scanner::isLetter(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool Scanner::isDigit(char c){
    return (c >= '0' && c <= '9');
}

bool Scanner::isEOF(){
    if(pos >= buffer.size()){
        return true;
    }

    return false;
}

bool Scanner::isMathOperator(char c){
    return  c == '+' || c == '-' || c == '*' || c == '/';
}

// bool Scanner::isRelationalOperator(char c){
//     return c == '>' || c == '<';
// }

bool Scanner::isParentheses(char c){
    return c == '(' || c == ')';
}

bool Scanner::isComentario(char c) {
		return c == '#';
}

bool Scanner::isSpace(char c){
    return c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\0';
}

void Scanner::isNewLine(char c){
    if(c == '\n'){
        col = 0;
        row++;
    }
}

bool Scanner::isBrackets(char c){
    return c == '{' || c == '}';
}

bool Scanner::isReservedWord(string content){
    for (int i = 0; i < reserved_word.size(); ++i) {
            if (reserved_word[i] == content) {
                return true;
            }
        }
        return false;
}

void Scanner::back(){
    pos--;
    col--;
}

optional<Token> Scanner::nextToken() {
    state = 0;
    char currentChar;
    string content = "";

    while(true){

        currentChar = nextChar();
        
        switch(state){
            case 0:
                if(isComentario(currentChar)){ //ignorar comentarios
                    while(currentChar != '\n'){
                        currentChar = nextChar();
                    }

                }
                if(isSpace(currentChar)){ //ignorar espaços, quebras de linha, etc
                    state = 0;
                    isNewLine(currentChar);
                    if(isEOF()) return nullopt;

                }else if(isLetter(currentChar)){ //formacao de identificadores
                    state = 1;
                    content += currentChar;
                }else if(isMathOperator(currentChar)){ //identificacao de operadores matematicos
                    state = 3;
                    content += currentChar;
                }else if(currentChar == ':'){ //identificacao de := (atribuicao)
                    state = 4;
                    content += currentChar;
                }else if(currentChar == '<'){ //identificacao de operadores relacionais
                    state = 5;
                    content += currentChar;
                }else if(currentChar == '>'){
                    state = 15;
                    content += currentChar;
                }else if(currentChar == '!'){ //identificacao de !=
                    state = 12;
                    content += currentChar;
                }else if(isParentheses(currentChar)){ //identificacao de ()
                    state = 6;
                    content += currentChar;
                }else if(isBrackets(currentChar)){ //identificacao de {}
                    state = 11;
                    content += currentChar;
                }else if(isDigit(currentChar)){ //formacao de numero
                    state = 7;
                    content += currentChar;
                }else if(currentChar == ';'){ //identificacao de um ;
                    state = 13;
                    content += currentChar;
                }else if(currentChar == '='){
                    state = 16;
                    content += currentChar;
                }else if(currentChar == '.'){
                    state = 17;
                    content += currentChar;
                }else if(currentChar == ','){
                    state = 18;
                    content += currentChar;
                }else{ //caractere nao permitido
                    cout << "Caractere nao permitido: " << currentChar << endl;
                    cout << "Linha: " << row << "\nColuna: " << col-1 << endl;
                    throw runtime_error("ERRO LÉXICO");
                }
                break;
                
            case 1:
                if(isLetter(currentChar) || isDigit(currentChar) || currentChar == '_'){ //formacao de identificadores
                    state = 1;
                    content += currentChar;
                }else{
                    back();
                    state = 2;
                }            
                break;

            case 2: //estado final de identificadores
                back(); // FIZ UMA ALTERAÇÃO AQUI, CASO DE ERRADO, ANTES TINHA UM BACK DENTRO DO IF E UM FORA
                // VER DEPOIS SE NAO DEU ALGUM PROBLEMA
                if(isReservedWord(content)){ //identificacao de palavras reservadas
                    return Token(TokenType::RESERVADA, content);
                }
                return Token(TokenType::IDENTIFICADOR, content);                
            
            case 3: //estado final de operadores matematicos
                back();
                return Token(TokenType::OPERADOR_MATEMATICO, content);
            
            case 4: //estado final de operador de atribuicao
                if(currentChar == '='){
                    content += currentChar;
                    return Token(TokenType::OPERADOR_ATRIBUICAO, content); 
                }else{
                    back();
                    return Token(TokenType::DOIS_PONTOS, content);
                }
            
            case 5: //estado final de operadores relacionais
                if(currentChar == '=' || currentChar == '>'){
                    content += currentChar;
                    return Token(TokenType::OPERADOR_RELACIONAL, content);
                }else{
                    back();
                    return Token(TokenType::OPERADOR_RELACIONAL, content);
                }
            
            case 6: //estado final de parenteses
                back();
                return Token(TokenType::PARENTESES, content);
            
            case 7: //formacao de numeros
                if(isDigit(currentChar)){
                    state = 7;
                    content += currentChar;
                }else if(currentChar == '.'){
                    state = 8;
                    content += currentChar;
                }else if(!isLetter(currentChar)){
                    state = 10;
                    back();
                }else{
                    cout << "Ma formacao de numero: " << content + currentChar << endl;
                    cout << "Linha: " << row << "\nColuna: " << col-1 << endl;
                    throw runtime_error("ERRO LÉXICO");
                }
                break;
            
            case 8: //formacao de numeros
                if(isDigit(currentChar)){
                    state = 9;
                    content += currentChar;
                }else{
                    cout << "Ma formacao de numero: " << content + currentChar << endl;
                    cout << "Linha: " << row << "\nColuna: " << col-1 << endl;
                    throw runtime_error("ERRO  LÉXICO");
                }
                break;
            
            case 9: //formacao de numeros
                if(isDigit(currentChar)){
                    state = 9;
                    content += currentChar;
                }else if(!isLetter(currentChar)){
                    state = 14;
                    back();
                }else{
                    cout << "Ma formacao de numero: " << content + currentChar << endl;
                    cout << "Linha: " << row << "\nColuna: " << col-1 << endl;
                    throw runtime_error("ERRO LÉXICO");
                }
                break;
            
            case 10: //estado final de numeros
                back();
                return Token(TokenType::NUMERO_INTEIRO, content);
            
            case 11: //e
                back();
                return Token(TokenType::CHAVES, content);
            
            case 12:
                if(currentChar == '='){
                    content += currentChar;
                    return Token(TokenType::OPERADOR_RELACIONAL, content);
                }else{
                    cout << "Ma formacao de operador: " << content + currentChar << endl;
                    cout << "Linha: " << row << "\nColuna: " << col-1 << endl;
                    throw runtime_error("ERRO LÉXICO");
                }
            
            case 13:
                back();
                return Token(TokenType::PONTO_VIRGULA, content);
            
            case 14:
                back();
                return Token(TokenType::NUMERO_REAL, content);
            
            case 15: //estado final de operadores relacionais
                if(currentChar == '='){
                    content += currentChar;
                    return Token(TokenType::OPERADOR_RELACIONAL, content);
                }else{
                    back();
                    return Token(TokenType::OPERADOR_RELACIONAL, content);
                }
            
            case 16:
                back();
                return Token(TokenType::OPERADOR_RELACIONAL, content);
            
            case 17:
                back();
                return Token(TokenType::PONTO_FINAL, content);
            
            case 18:
                back();
                return Token(TokenType::VIRGULA, content);

            default:
                break;
        }    
    }
}
