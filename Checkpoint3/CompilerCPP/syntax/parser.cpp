#include "parser.h"
<<<<<<< Updated upstream
#include "../semantic/semanticAnalyzer.h"
//SemanticAnalyzer semanticAnalyzer;
=======
>>>>>>> Stashed changes

Parser::Parser(Scanner scan){
    this->sc = scan;
}

void Parser::nextTokenPrint(){
    tk = sc.nextToken();
    cout << "Chamou next token: " << tk->getText() << endl;    
}

void Parser::errorMessage(int linha, string c){
    cout << linha << " Esperava " << c << ", encontrou: " << tk->getText() << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl;
    throw runtime_error("ERRO SINTATICO");
}

void Parser::errorMessageType(int linha, string t){
    cout << linha << " Esperava " << t << ", encontrou: " << tokenTypeToString(tk->getType()) << "(" << tk->getText()  << ")" << " na linha " << sc.getRow() << " e coluna " << sc.getCol() << endl; 
    throw runtime_error("ERRO SINTATICO");
}

///////////////////////////////////////////////////////////////////////////////

void Parser::programa(){
    nextTokenPrint();
    
    if(tk->getText() == "program"){
        nextTokenPrint();
        
        if(tk->getType() == TokenType::IDENTIFICADOR){
<<<<<<< Updated upstream
=======
            
>>>>>>> Stashed changes
            nextTokenPrint();
            
            if(tk->getText() == ";"){
                nextTokenPrint();

                declaracao_variaveis();
                cout << "Declaracao de variaveis - OK. Saiu com o token: " << tk->getText() << endl;
                
                lista_subprogramas();
                cout << "Lista de subprogramas - OK. Saiu com o token: " << tk->getText() << endl;
                 
                comando_composto();
                cout << "Comando composto - OK. Saiu com o token: " << tk->getText() << endl; 

                if(tk->getText() != "."){
                    errorMessage(20, "'.'");
                }

            }else{
                errorMessage(24, "';'");
            }

        }else{
            errorMessageType(28, "identificador");
        }

    }else{
        errorMessage(32, "'program'");
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::declaracao_variaveis(){
    
    if(tk->getText() == "var"){
        nextTokenPrint();
        lista_declaracao_variaveis(); 
    } else {
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_declaracao_variaveis(){ 
     
    lista_identificadores();

    if(tk->getText() == ":"){
        nextTokenPrint();
        tipo();
        
        
        if(tk->getText() == ";"){
            nextTokenPrint();
            lista_declaracao_variaveis2();
        
        }else{
            errorMessage(58, "';'");
        
        }
        
    }else{
        errorMessage(62, "':'");
    }

}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_declaracao_variaveis2(){ 

    
    if(tk->getType() == TokenType::IDENTIFICADOR){
        lista_identificadores(); 

        if(tk->getText() == ":"){
            nextTokenPrint();
            tipo(); 
            
            if(tk->getText() == ";"){
                nextTokenPrint();
                lista_declaracao_variaveis2(); 
            
            }else{
                errorMessage(80, "';'");
            
            }
            
        }else{
            errorMessage(84, "':'");
        
        }
        
    } else {
        return;
    }

}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_identificadores(){ 

    if(tk->getType() == TokenType::IDENTIFICADOR){
<<<<<<< Updated upstream
=======
       
>>>>>>> Stashed changes
        nextTokenPrint();
        lista_identificadores2(); 
    
    }else{
         errorMessageType(100, "identificador");

    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_identificadores2(){ 
     
    if(tk->getText() == ","){
        nextTokenPrint();
        
        if(tk->getType() == TokenType::IDENTIFICADOR){
<<<<<<< Updated upstream
=======
           
>>>>>>> Stashed changes
            nextTokenPrint();
            lista_identificadores2(); 
            
        }else{
            errorMessageType(113, "identificador");

        }

    }else{
        return;
    }

}

///////////////////////////////////////////////////////////////////////////////

void Parser::tipo(){ 
    
    if(tk->getText() != "integer" && tk->getText() != "real" && tk->getText() != "boolean"){
        errorMessage(126, "'integer', 'real' ou 'boolean'");
    }

    nextTokenPrint();
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_subprogramas(){ 

    if(tk->getText() == "procedure"){
        declaracao_subprograma(); 
        
        if(tk->getText() == ";"){
            nextTokenPrint();
            lista_subprogramas();
        }

    }else{
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::declaracao_subprograma(){ 
<<<<<<< Updated upstream

    if(tk->getText() == "procedure"){
        nextTokenPrint();
        if(tk->getType() == TokenType::IDENTIFICADOR){
=======
  
    if(tk->getText() == "procedure"){
        nextTokenPrint();
        if(tk->getType() == TokenType::IDENTIFICADOR){
                       
>>>>>>> Stashed changes
            nextTokenPrint();
            argumentos();
             
            if(tk->getText() == ";"){
                nextTokenPrint();
                declaracao_variaveis();
                lista_subprogramas();
                comando_composto();
                
                
            }else{
                errorMessage(163, ";");
                
            }
            
        }else{
            errorMessageType(168, "identificador");
            
        }
    }else{
        errorMessage(172, "'procedure'");
        
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::argumentos(){

    if(tk->getText() == "("){
        nextTokenPrint();
        lista_parametros();

        if(tk->getText() != ")"){
            errorMessage(184, "')'");
            
        }
        
        nextTokenPrint();
        
    }else{
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_parametros(){

    if(tk->getType() == TokenType::IDENTIFICADOR){
        lista_identificadores();

        if(tk->getText() == ":"){
            nextTokenPrint();
            tipo();
            lista_parametros2();

        }else{
            errorMessage(203, "':'");

        }
        
    }else{
        errorMessage(207, "identificador");

    }

    
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_parametros2(){

    if(tk->getText() == ";"){
        nextTokenPrint();
        lista_identificadores();

        if(tk->getText() == ":"){
            nextTokenPrint();
            tipo(); 
            lista_parametros2(); 

        }else{
            errorMessage(226, "':'");

        }
    
    }else{
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::comando_composto(){ 

    if(tk->getText() == "begin"){
<<<<<<< Updated upstream
=======
   
>>>>>>> Stashed changes
        nextTokenPrint();
        comando_opicional(); 

        if(tk->getText() != "end"){
            errorMessage(241, "'end'");
            
        }
        
        nextTokenPrint();
        
<<<<<<< Updated upstream
        
=======
>>>>>>> Stashed changes
    }else{
        errorMessage(245, "'begin'");

    }

}

///////////////////////////////////////////////////////////////////////////////

void Parser::comando_opicional(){
    string wrd = tk->getText();
    TokenType tkType = tk->getType();

    if(wrd == "if" || wrd == "while" || wrd == "begin" || tkType == TokenType::IDENTIFICADOR){
        lista_comandos(); 
    
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_comandos(){
    comando();
    lista_comandos2();
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_comandos2(){ 

    if(tk->getText() == ";"){
        nextTokenPrint();
        comando(); 
        lista_comandos2();
    
    }else {
        return;
    }
    
}
 
///////////////////////////////////////////////////////////////////////////////
 
void Parser::comando(){ 
    
    //IF
    if(tk->getText() == "if"){
        nextTokenPrint();
        expressao();

        if(tk->getText() == "then"){
            nextTokenPrint();
            comando(); 
            parte_else(); 
            
        }else{
            errorMessage(326, "'then'");

        }

    //WHILE
    }else if (tk->getText() == "while" ){
        nextTokenPrint();
        expressao();

        if(tk->getText() == "do"){
            nextTokenPrint();
            comando();

        }else{
            errorMessage(302, "'do'");
            
        }

    //BEGIN
    }else if(tk->getText() == "begin"){
        comando_composto();

    //NENHUM DOS ANTERIORES
    }else if(tk->getType() == TokenType::IDENTIFICADOR){
        variavel(); 
        
        if(tk->getText() == ":="){
            nextTokenPrint();
            expressao(); 
        
        }else 
            ativacao_procedimento();
        
    } else {
        errorMessageType(360, "comando");

    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::ativacao_procedimento(){

    if(tk->getText() == "("){
        nextTokenPrint();
        lista_expressoes();

        if(tk->getText() != ")"){
            errorMessage(374, "')'");            
        }

        nextTokenPrint();
    
    }

}

///////////////////////////////////////////////////////////////////////////////

void Parser::variavel(){

    if(tk->getType() != TokenType::IDENTIFICADOR){
        errorMessageType(386, " identificador");
    }

    nextTokenPrint();
    
}

///////////////////////////////////////////////////////////////////////////////

void Parser::parte_else(){

    if(tk->getText() == "else"){
        nextTokenPrint();
        comando();
        
    }
    
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_expressoes(){
    expressao();
    lista_expressoes2();
}

///////////////////////////////////////////////////////////////////////////////

void Parser::lista_expressoes2(){

    if(tk->getText() == ","){
        nextTokenPrint();
        expressao();
        lista_expressoes2();
    }else{
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

bool Parser::first_op_relacional(string op){
    if(op == "=" || op == "<" || op == ">" || op == "<=" || op == ">=" || op == "<>"){ //talvez colocar and
        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////////////////////

void Parser::op_relacional(){
    string op = tk->getText();

    if(op == "=" || op == "<" || op == ">" || op == "<=" || op == ">=" || op == "<>"){ //talvez colocar and
        nextTokenPrint();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::op_aditivo(){
    string op = tk->getText();

    if(op == "+" || op == "-" || op == "or"){
        nextTokenPrint();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::op_multiplicativo(){
    string op = tk->getText();

    if(op == "*" || op == "/" || op == "and"){
        nextTokenPrint();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::expressao(){ 
    expressao_simples();

    if(first_op_relacional(tk->getText())){
        op_relacional();
        expressao_simples();
        
    }else{
        return;
        
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::expressao_simples(){
    
    sinal();
    termo();
    expressao_simples2();
}

///////////////////////////////////////////////////////////////////////////////

void Parser::expressao_simples2(){

    if(tk->getText() == "+" || tk->getText() == "-" || tk->getText() == "or"){
        op_aditivo();
        termo();
        expressao_simples2();
        
    }else{
        return;

    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::sinal(){
    
    if(tk->getText() == "+" || tk->getText() == "-"){
        nextTokenPrint();
        return;
    }

}

///////////////////////////////////////////////////////////////////////////////

void Parser::termo(){
    fator();
    termo2();
}

///////////////////////////////////////////////////////////////////////////////

void Parser::termo2(){ 

    if(tk->getText() == "*" || tk->getText() == "/" || tk->getText() == "and"){
        op_multiplicativo();
        fator(); 
        termo2(); 
        
    }else{
        return;
    
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::fator(){

    //IDENTIFICADOR
    if(tk->getType() == TokenType::IDENTIFICADOR){
        nextTokenPrint();
        
        if(tk->getText() == "("){
            nextTokenPrint();
            lista_expressoes(); 

            if(tk->getText() != ")"){
                errorMessage(528, "')'");            
            }

            nextTokenPrint();
            
        }else{
            return;
            
        }

    //ABRE PARENTESES
    }else if(tk->getText() == "("){
        nextTokenPrint();
        expressao();

        if(tk->getText() != ")"){
            errorMessage(539, "')'");
        }
        
        nextTokenPrint();
        
    //NOT
    }else if(tk->getText() == "not"){
        nextTokenPrint();
        fator(); 

    //NUMERO
    }else if(tk->getType() == TokenType::NUMERO_INTEIRO || tk->getType() == TokenType::NUMERO_REAL){
        nextTokenPrint();
        return;

    //BOOLEANO
    }else if(tk->getText() == "true" || tk->getText() == "false"){
        nextTokenPrint();
        return;

    //NENHUM DOS ANTERIORES
    }else{
        errorMessageType(549, "fator (Identificador, numero, valor booleano, 'not' ou '(' )");
    }
}
