#include "parser.h"
#include "../semantic/SemanticAnalyzer.h"
#include "../semantic/TypeChecker.h"

Parser::Parser(Scanner scan){
    this->sc = scan;
}
TokenType varType1, varType2;

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
    semanticAnalyzer.enterScope();  // Inicia escopo global

    nextTokenPrint();
    
    if(tk->getText() == "program"){
        nextTokenPrint();
        
        if(tk->getType() == TokenType::IDENTIFICADOR){
            // Declara o identificador 'program' no escopo global
            if (!semanticAnalyzer.declareIdentifier(tk->getText(), "program")) {
                cout << "Erro: Identificador 'program' já declarado." << endl;
                throw runtime_error("ERRO SEMANTICO");
            }

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

    semanticAnalyzer.exitScope();  // Finaliza escopo global
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
        TokenType varTipo = tipo();
        typeChecker.setVariableType(varTipo); 
        
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
            TokenType varTipo = tipo();
            typeChecker.setVariableType(varTipo); 
            
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
        semanticAnalyzer.declareIdentifier(tk->getText(), "variavel");
        typeChecker.declareVariable(tk->getText());
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
            semanticAnalyzer.declareIdentifier(tk->getText(), "variavel");
            typeChecker.declareVariable(tk->getText());
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

TokenType Parser::tipo(){ 
    if(tk->getText() == "integer"){
        nextTokenPrint();
        return TokenType::INTEGER;
    }
    else if(tk->getText() == "real"){
        nextTokenPrint();
        return TokenType::REAL;
    }
    else if(tk->getText() == "boolean"){
        nextTokenPrint();
        return TokenType::BOOLEAN;
    }
    else{
        errorMessageType(130, "'integer', 'real' ou 'boolean'");
        nextTokenPrint();
    }

    return TokenType::INVALID_TYPE;
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
    semanticAnalyzer.enterScope();

    if(tk->getText() == "procedure"){
        nextTokenPrint();
        if(tk->getType() == TokenType::IDENTIFICADOR){

            semanticAnalyzer.declareIdentifier(tk->getText(), "procedure");

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
    semanticAnalyzer.exitScope(); 
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
        semanticAnalyzer.enterScope();

        nextTokenPrint();
        comando_opicional(); 

        if(tk->getText() != "end"){
            errorMessage(241, "'end'");
            
        }
        
        nextTokenPrint();
        
        semanticAnalyzer.exitScope();
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
        string varName = tk->getText(); 
        variavel();

        if(tk->getText() == ":="){

            nextTokenPrint();            
            varType1 = tk->getType();
            if(varType1 == TokenType::IDENTIFICADOR){
                string varName1 = tk->getText();
                varType1 = typeChecker.getVariableType(varName1);
            }
            expressao();

            if(!typeChecker.checkAssignment(varName, varType1)){ 
                cout << "Erro de tipo: atribuicao invalida para a varivel " << varName << endl;
            } 
        
        }else
            ativacao_procedimento();
        
    } else {
        errorMessageType(360, "comando");

    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::ativacao_procedimento(){

    if(tk->getText() == "("){

        if (!semanticAnalyzer.isDeclared(tk->getText())) {
            cout << "Erro: Procedimento '" << tk->getText() << "' nao declarado." << endl;
            throw runtime_error("ERRO SEMANTICO");
        }

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
    if (tk->getType() == TokenType::IDENTIFICADOR) {
        // Verificar se o identificador foi declarado
        if (!semanticAnalyzer.isDeclared(tk->getText())) {
            cout << "Erro: identificador '" << tk->getText() << "' nao declarado antes do uso." << endl;
            throw runtime_error("ERRO SEMANTICO");
        }
    } else {
        errorMessageType(386, "identificador");
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
        varType2 = tk->getType();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::op_aditivo(){
    string op = tk->getText();

    if(op == "+" || op == "-" || op == "or"){
        nextTokenPrint();
        varType2 = tk->getType();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::op_multiplicativo(){
    string op = tk->getText();

    if(op == "*" || op == "/" || op == "and"){

        nextTokenPrint();
        varType2 = tk->getType();
        return;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::expressao(){
    expressao_simples();

    if(first_op_relacional(tk->getText())){
        op_relacional();
        expressao_simples();

        if(!typeChecker.checkRelationalOperation(varType1, varType2)){
            cout << "Erro de tipo: operacao relacional invalida" << endl;
        }
    }
} 

///////////////////////////////////////////////////////////////////////////////

void Parser::expressao_simples(){
    
    if (tk->getType() == TokenType::IDENTIFICADOR) {
        if (!semanticAnalyzer.isDeclared(tk->getText())) {
            cout << "Erro: Identificador '" << tk->getText() << "' nao declarado." << endl;
            throw runtime_error("ERRO SEMANTICO");
        }
    }

    sinal();
    termo();
    expressao_simples2();
    
    if(!typeChecker.checkRelationalOperation(varType1, varType2)){
            cout << "Erro de tipo: tipos invalidos para operacao" << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::expressao_simples2(){

    if(tk->getText() == "+" || tk->getText() == "-" || tk->getText() == "or"){
        op_aditivo();
        termo();
        expressao_simples2();

        if(!typeChecker.checkRelationalOperation(varType1, varType2)){
            cout << "Erro de tipo: tipos invalidos para operacao" << endl;
        }
        
    }else{
        return;

    }
}

///////////////////////////////////////////////////////////////////////////////

void Parser::sinal(){
    
    if(tk->getText() == "+" || tk->getText() == "-"){
        nextTokenPrint();
        varType1 = tk->getType();
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
        //varType2 = tk->getType();
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
    }else if(tk->getType() == TokenType::INTEGER || tk->getType() == TokenType::REAL){
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
