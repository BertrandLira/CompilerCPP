#ifndef SINTATICO_H
#define SINTATICO_H
#include <vector>
#include <string>
#include "../lexical/scanner.cpp"
#include "../semantic/TypeChecker.cpp"
#include "../semantic/SemanticAnalyzer.cpp"

using namespace std;

class Parser
{
    private:
        Scanner sc;
        optional<Token> tk;
        TypeChecker typeChecker;
        SemanticAnalyzer semanticAnalyzer;

    public:
        Parser(Scanner scan);

        void errorMessageType(int linha, string t);
        void errorMessage(int linha, string c);
        void nextTokenPrint();
        void programa();
        void declaracao_variaveis();
        void lista_declaracao_variaveis();
        void lista_declaracao_variaveis2();
        void lista_identificadores();
        void lista_identificadores2();
        TokenType tipo();
        void declaracao_subprograma();
        void lista_subprogramas();
        void lista_subprogramas2();
        void argumentos();
        void lista_parametros();
        void lista_parametros2();
        void comando_composto();
        void comando_opicional();
        void lista_comandos();
        void lista_comandos2();
        void comando();
        void parte_else();
        void variavel();
        void ativacao_procedimento();
        void lista_expressoes();
        void lista_expressoes2();
        void expressao();
        void expressao_simples();
        void expressao_simples2();
        void termo();
        void termo2();
        void fator();
        void sinal();
        void op_relacional();
        void op_aditivo();
        void op_multiplicativo();

        bool first_op_relacional(string op);

};

#endif // SINTATICO_H
