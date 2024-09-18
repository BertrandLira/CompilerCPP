#include <iostream>
#include <map>
#include <stack>
#include <string>
#include "SemanticAnalyzer.h"

    // Construtor: começa com o escopo global
    SemanticAnalyzer::SemanticAnalyzer() {
        enterScope();
    }

    // Entrar em um novo escopo
    void SemanticAnalyzer::enterScope() {
        symbolTableStack.push(map<string, string>());
        cout << "Entrando no escopo" << endl;

    }

    // Sair do escopo atual
    void SemanticAnalyzer::exitScope() {
        if (!symbolTableStack.empty()) {
            symbolTableStack.pop();
            cout << "Saindo do escopo" << endl;
        } else {
            cout << "Erro: Tentativa de sair de um escopo inexistente." << std::endl;
        }
    }

    // Declarar um novo identificador no escopo atual
    bool SemanticAnalyzer::declareIdentifier(const string& identifier, const string& type) {
        // Verifica se o identificador já foi declarado no escopo atual
        if (symbolTableStack.top().find(identifier) != symbolTableStack.top().end()) {
            cout << "Erro: Identificador \"" << identifier << "\" ja declarado neste escopo." << std::endl;
            throw runtime_error("ERRO SEMANTICO");
        } else {
            symbolTableStack.top()[identifier] = type;
            cout << "Lendo identificador" << identifier << endl;
            return true;
        }
    }

    // Verificar se um identificador foi declarado em algum escopo anterior
    bool SemanticAnalyzer::isDeclared(const string& identifier) {
        stack<map<string, string>> tempStack = symbolTableStack;
        
        // Percorre os escopos de cima para baixo (do mais recente ao mais antigo)
        while (!tempStack.empty()) {
            if (tempStack.top().find(identifier) != tempStack.top().end()) {
                cout << "Identificador declarado" << identifier << endl;
                return true;
            }
            tempStack.pop();
        }

        return false;
    }