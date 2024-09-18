#ifndef SEMANTIC_ANALYZER_H
#define SEMANTIC_ANALYZER_H

#include <map>
#include <stack>
#include <string>

using namespace std;

class SemanticAnalyzer {
private:
    // Pilha de tabelas de símbolos, onde cada mapa representa um escopo
    std::stack<std::map<std::string, std::string>> symbolTableStack;

public:
    // Construtor
    SemanticAnalyzer();

    // Gerenciamento de escopos
    void enterScope();  // Entrar em um novo escopo
    void exitScope();   // Sair do escopo atual

    // Declaração e uso de identificadores
    bool declareIdentifier(const std::string& identifier, const std::string& type);
    bool isDeclared(const std::string& identifier);
};

#endif