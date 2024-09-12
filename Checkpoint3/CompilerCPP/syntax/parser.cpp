#include "parser.h"

Parser::Parser(Scanner scan){
    this->sc = scan;
}

void Parser::programa(){
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == "program"){
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getType() == TokenType::IDENTIFICADOR){
            tk = sc.nextToken();
            cout << "chamou next token: " << tk->getText() << endl; //
            if(tk->getText() == ";"){
                declaracao_variaveis(); //RETORNA NEXT TOKEN
                lista_subprogramas(); //RETORNA NEXT TOKEN
                comando_composto(); //NAO RETORNA
                tk = sc.nextToken();
                cout << "chamou next token: " << tk->getText() << endl; //
                if(tk->getText() != "."){
                    cout << "20 Esperava '.', encontrou:" << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
                    throw runtime_error("ERRO SINTATICO");
                }
            }else{
                cout << "24 Esperava ';', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
                throw runtime_error("ERRO SINTATICO");
            }
        }else{
            cout << "28 Esperava um identificador, encontrou: " << tokenTypeToString(tk->getType()) << "(" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
            throw runtime_error("ERRO SINTATICO");
        }
    }else{
        cout << "32 Esperava 'program', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
        throw runtime_error("ERRO SINTATICO");
    }
}

void Parser::declaracao_variaveis(){ //PODE RETORNAR NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == "var"){
        lista_declaracao_variaveis(); //RETORNA
    } else {
        return;
    }
}

void Parser::lista_declaracao_variaveis(){ //PODE RETORNAR NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //
    lista_identificadores(); //RETORNA

    //tk = sc.nextToken();
    //cout << "chamou next token: " << tk->getText() << endl; //
    if(tk->getText() == ":"){
        tipo();
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() == ";"){
            lista_declaracao_variaveis2(); //RETORNA
        }else{
            cout << "58 Esperava ';', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
        throw runtime_error("ERRO SINTATICO");
        }
    }else{
        cout << "62 Esperava ':', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
        throw runtime_error("ERRO SINTATICO");
    }

}

void Parser::lista_declaracao_variaveis2(){ //PODE RETORNAR NEXT TOKEN

    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //
    if(tk->getType() == TokenType::IDENTIFICADOR){
        lista_identificadores(); //RETORNA
        //tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() == ":"){
            tipo(); //NAO RETORNA
            tk = sc.nextToken();
            cout << "chamou next token: " << tk->getText() << endl; //
            if(tk->getText() == ";"){
                lista_declaracao_variaveis2(); //RETORNA
            }else{
                cout << "80 Esperava ';', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
                throw runtime_error("ERRO SINTATICO");
            }
        }else{
            cout << "84 Esperava ':', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
            throw runtime_error("ERRO SINTATICO");
        }
        
    } else {
        return;
    }

}

void Parser::lista_identificadores(){ //PODE RETORNAR NEXT TOKEN

    if(tk->getType() == TokenType::IDENTIFICADOR){
        lista_identificadores2(); //PODE RETORNAR
    
    }else{
        cout << "100 Esperava um identificador, encontrou: " << tokenTypeToString(tk->getType()) << "(" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
            throw runtime_error("ERRO SINTATICO");
    }
}

void Parser::lista_identificadores2(){ //PODE RETORNAR O NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //
        
    if(tk->getText() == ","){
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getType() == TokenType::IDENTIFICADOR){
            lista_identificadores2(); //PODE RETORNAR
        }else{
            cout << "113 Esperava um identificador, encontrou: " << tokenTypeToString(tk->getType()) << "(" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
            throw runtime_error("ERRO SINTATICO");
        }
    }else{
        return;
    }

}

void Parser::tipo(){ //NAO RETORNA NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() != "integer" && tk->getText() != "real" && tk->getText() != "boolean"){
        cout << "126 Esperava 'integer', 'real' ou 'boolean', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
        throw runtime_error("ERRO SINTATICO");
    }
}

void Parser::lista_subprogramas(){ //PODE RETORNAR O NEXT TOKEN
    lista_subprogramas2(); //PODE RETORNAR

}

void Parser::lista_subprogramas2(){ //PODE RETORNAR O NEXT TOKEN
    //tk = sc.nextToken();
    //cout << "chamou next token: " << tk->getText() << endl; //
    if(tk->getText() == "procedure"){
        declaracao_subprograma(); //NAO RETORNA NEXT TOKEN
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() == ";"){
            lista_subprogramas2();
           
        }

    }else{
        return;
    }
}

void Parser::declaracao_subprograma(){ //NAO RETORNA NEXT TOKEN

    if(tk->getText() == "procedure"){
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getType() == TokenType::IDENTIFICADOR){
            argumentos();  //RETORNA
            if(tk->getText() == ";"){
                declaracao_variaveis(); //RETORNA
                lista_subprogramas(); //RETORNA
                //tk = sc.nextToken();
                cout << "chamou next token: " << tk->getText() << endl; //
                comando_composto(); //NAO RETORNA NEXT TOKEN
            }else{
                cout << "163 Esperava ';', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
                throw runtime_error("ERRO SINTATICO");
            }
            
        }else{
            cout << "168 Esparava um identificador, encontrou: " << tokenTypeToString(tk->getType()) << "(" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
            throw runtime_error("ERRO SINTATICO");
        }
    }else{
        cout << "172 Esperava 'procedure', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
        throw runtime_error("ERRO SINTATICO");
    }
}

void Parser::argumentos(){ //PODE RETORNAR O NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == "("){
        lista_parametros(); //RETORNA
        //tk = sc.nextToken();
        //cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() != ")"){
            cout << "184 Esperava ')', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
            throw runtime_error("ERRO SINTATICO");
        }
    }else{
        return;
    }
}

void Parser::lista_parametros(){ //PODE RETORNAR O NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getType() == TokenType::IDENTIFICADOR){

        lista_identificadores();
        //tk = sc.nextToken();
        //cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() == ":"){
            tipo();
            lista_parametros2(); //RETORNA
        }else{
            cout << "203 Esperava ':', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
            throw runtime_error("ERRO SINTATICO");
        }
    }else{
        cout << "207 Esparava um identificador, encontrou: " << tokenTypeToString(tk->getType()) << "(" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
        throw runtime_error("ERRO SINTATICO");
    }

    
}

void Parser::lista_parametros2(){ //PODE RETORNAR O NEXT TOKEN

    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == ";"){
        lista_identificadores(); //RETORNA
        //tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //   
        if(tk->getText() == ":"){
            tipo(); //NAO RETORNA
            lista_parametros2(); //RETORNA

        }else{
            cout << "226 Esperava ':', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
            throw runtime_error("ERRO SINTATICO");
        }
    
    }else{
        return;
    }
}

void Parser::comando_composto(){ //NAO RETORNA O NEXT TOKEN
    //tk = sc.nextToken();
    //cout << "chamou next token: " << tk->getText() << endl; //
    if(tk->getText() == "begin"){
        comando_opicional(); //RETORNA
        //tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() != "end"){
            cout << "241 Esperava 'end', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
            throw runtime_error("ERRO SINTATICO");
        }
    }else{
        cout << "245 Esperava 'begin', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
        throw runtime_error("ERRO SINTATICO");

    }
}

void Parser::comando_opicional(){ //RETORNA NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //
    string wrd = tk->getText();
    TokenType tkType = tk->getType();

    if(wrd == "if" || wrd == "while" || wrd == "begin" || tkType == TokenType::IDENTIFICADOR){
        lista_comandos(); //RETORNA
    }else{
        return;
    }

}

void Parser::lista_comandos(){ //RETORNA
    comando(); //RETORNA
    lista_comandos2();
}

void Parser::lista_comandos2(){ //RETORNA
    //tk = sc.nextToken();
    //cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == ";"){
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //

        comando(); //RETORNA
        lista_comandos2();
    
    }else {
        return;
    }
}
 
void Parser::comando(){ //RETORNA NEXT TOKEN
        //tk = sc.nextToken();
        //cout << "chamou next token: " << tk->getText() << endl; // VER SE DA ERRO

        if(tk->getText() == "if"){
            expressao(); //RETORNA
            //tk = sc.nextToken();
            //cout << "chamou next token: " << tk->getText() << endl; //
            if(tk->getText() == "then"){
                tk = sc.nextToken();
                cout << "chamou next token: " << tk->getText() << endl;
                comando(); //RETORNA
                parte_else(); //RETORNA
            }else{
                cout << "326 Esperava 'then', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
                throw runtime_error("ERRO SINTATICO");

            }

        }else if (tk->getText() == "while"){
            expressao(); //RETORNA
            //tk = sc.nextToken();
            //cout << "chamou next token: " << tk->getText() << endl; //
            if(tk->getText() == "do"){
                comando(); //RETORNA
            }else{
                cout << "302 Esperava 'do', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
                throw runtime_error("ERRO SINTATICO");
            }

        }else if(tk->getText() == "begin"){
            comando_composto(); //NAO RETORNA
        

        }else { //VERIFICAR SE ESSE ELSE ESTA CERTO
            variavel(); //NAO RETORNA
            tk = sc.nextToken();
            cout << "chamou next token: " << tk->getText() << endl; //
            if(tk->getText() == ":="){
                expressao(); //RETORNA
                if(tk->getText() != ";" && tk->getText() != "end"){
                    cout << "353 Esperava ';' ou 'end', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
                    throw runtime_error("ERRO SINTATICO");
                }
            
            }else if(tk->getType() == TokenType::IDENTIFICADOR){
                ativacao_procedimento(); //NAO RETORNA 
            }else{
                cout << "360 Esperava 'Identificador', encontrou: " << tokenTypeToString(tk->getType()) << " (" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
                throw runtime_error("ERRO SINTATICO");            }
        }
}

void Parser::ativacao_procedimento(){ //NAO RETORNA NEXT TOKEN

    if(tk->getType() == TokenType::IDENTIFICADOR){
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() == "("){
            lista_expressoes(); //RETORNA

            if(tk->getText() != ")"){
                cout << "374 Esperava ')', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
                throw runtime_error("ERRO SINTATICO");            }
        
        }else{
            return;
        }
    }
}

void Parser::variavel(){ //NAO RETORNA

    if(tk->getType() != TokenType::IDENTIFICADOR){
        cout << "386 Esperava um 'Identificador', encontrou: " << tokenTypeToString(tk->getType()) << " (" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
        throw runtime_error("ERRO SINTATICO");
    }
    
}

void Parser::parte_else(){ //RETORNA
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == "else"){
        comando(); //RETORNA
    }else{
        return;
    }
}

void Parser::lista_expressoes(){ //RETORNA
    expressao(); //RETORNA
    lista_expressoes2(); //RETORNA
}

void Parser::lista_expressoes2(){ //RETORNA NEXT TOKEN
    //tk = sc.nextToken();
    //cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == ","){
        expressao(); //RETORNA
        lista_expressoes2(); //RETORNA
    }else{
        return;
    }
}

bool Parser::first_op_relacional(string op){ //NAO RETORNA
    if(op == "=" || op == "<" || op == ">" || op == "<=" || op == ">=" || op == "<>"){
        return true;
    }

    return false;
}

void Parser::op_relacional(){
    string op = tk->getText();

    if(op == "=" || op == "<" || op == ">" || op == "<=" || op == ">=" || op == "<>"){
        //tk = sc.nextToken();
        //cout << "chamou next token: " << tk->getText() << endl; //
        return;
    }else{
        cout << "ERRO";
    }
}

void Parser::op_aditivo(){
    string op = tk->getText();

    if(op == "+" || op == "-" || op == "or"){
        //tk = sc.nextToken();
        //cout << "chamou next token: " << tk->getText() << endl; //
        return;
    }
}


void Parser::op_multiplicativo(){
    string op = tk->getText();

    if(op == "*" || op == "/" || op == "and"){
        //tk = sc.nextToken();
        //cout << "chamou next token: " << tk->getText() << endl; //
        return;
    }
}

void Parser::expressao(){ //RETORNA NEXT TOKEN
    expressao_simples(); //RETORNA

    if(first_op_relacional(tk->getText())){
        op_relacional(); //NAO RETORNA
        expressao_simples(); //RETORNA
    }else{
        return;
    }
}

void Parser::expressao_simples(){ //RETORNA
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //
    sinal(); //NAO RETORNA
    termo(); //RETORNA
    expressao_simples2(); //RETORNA
}

void Parser::expressao_simples2(){ //RETORNA
    if(tk->getText() == "+" || tk->getText() == "-" || tk->getText() == "or"){
        op_aditivo(); //NAO RETORNA
        termo(); //RETORNA
        expressao_simples2(); //RETORNA
    }else{
        return;
    }
}

void Parser::sinal(){ //NAO RETORNA NEXT TOKEN
    if(tk->getText() == "+" || tk->getText() == "-"){
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        return;
    }else{
        //cout << "447 Esperava '+' ou '-', encontrou " << tokenTypeToString(tk->getType()) << " (" << tk->getText()  << ")" <<  " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
        //throw runtime_error("ERRO SINTATICO");
    }

}

void Parser::termo(){ //RETORNA
    fator();
    termo2(); //RETORNA
}

void Parser::termo2(){ //RETORNA NEXT TOKEN
    tk = sc.nextToken();
    cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getText() == "*" || tk->getText() == "/" || tk->getText() == "and"){
        op_multiplicativo();
        fator(); //NAO RETORNA
        termo2(); //RETORNA
    }else{
        return;
    }
}

void Parser::fator(){ //NAO RETORNA
    //tk = sc.nextToken();
    //cout << "chamou next token: " << tk->getText() << endl; //

    if(tk->getType() == TokenType::IDENTIFICADOR){
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() == "("){
            lista_expressoes(); //RETORNA
            if(tk->getText() != ")"){
                cout << "528 Esperava ')', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
                throw runtime_error("ERRO SINTATICO");            
            }
        }else{
            return;
        }
    }else if(tk->getText() == "("){
        expressao(); //RETORNA
        tk = sc.nextToken();
        cout << "chamou next token: " << tk->getText() << endl; //
        if(tk->getText() != ")"){
            cout << "539 Esperava ')', encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
            throw runtime_error("ERRO SINTATICO");
        }
    }else if(tk->getText() == "not"){
        fator(); //NAO RETORNA
    }else if(tk->getType() == TokenType::NUMERO_INTEIRO || tk->getType() == TokenType::NUMERO_REAL){
        return;
    }else if(tk->getText() == "true" || tk->getText() == "false"){
        return;
    }else{
        cout << "549 Esperava um fator (Identificador, numero, valor booleano, 'not' ou '(' ). Encontrado "; 
        cout << tk->getText() << " do tipo " << tokenTypeToString(tk->getType()) << " (" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
        throw runtime_error("ERRO SINTATICO");
    }
}