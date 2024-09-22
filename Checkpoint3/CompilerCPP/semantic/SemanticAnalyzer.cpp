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
            std::cout << "Saindo do escopo. Removendo variaveis locais." << std::endl;
            symbolTableStack.pop();
        } else {
            std::cout << "Erro: Nenhum escopo para sair." << std::endl;
        }
    }

    // Declarar um novo identificador no escopo atual
    bool SemanticAnalyzer::declareIdentifier(const std::string& identifier, const std::string& type) {
        if (type == "procedure") {
            // Declara a procedure no escopo global
            if (globalSymbolTable.find(identifier) != globalSymbolTable.end()) {
                std::cout << "Erro: Procedure '" << identifier << "' já declarada no escopo global." << std::endl;
                throw runtime_error("ERRO SEMANTICO");
                return false;
            }
            globalSymbolTable[identifier] = type;
            std::cout << "Procedure '" << identifier << "' declarada como '" << type << "' no escopo global." << std::endl;
            return true;
        } else {
            // Declara variáveis no escopo local (topo da pilha)
            if (!symbolTableStack.empty()) {
                std::map<std::string, std::string>& currentScope = symbolTableStack.top();
                if (currentScope.find(identifier) != currentScope.end()) {
                    std::cout << "Erro: Variável '" << identifier << "' já declarada no escopo atual." << std::endl;
                    throw runtime_error("ERRO SEMANTICO");
                    return false;
                }
                currentScope[identifier] = type;
                std::cout << "Variavel '" << identifier << "' declarada como '" << type << "' no escopo atual." << std::endl;
                return true;
            }
        }
        std::cout << "Erro: Não há escopo disponível para declarar o identificador '" << identifier << "'." << std::endl;
        return false;
    }


    // Verificar se um identificador foi declarado em algum escopo anterior
    bool SemanticAnalyzer::isDeclared(const std::string& identifier) {
        // Primeiro, verificar no escopo global (procedures)
        if (globalSymbolTable.find(identifier) != globalSymbolTable.end()) {
            std::cout << "Identificador '" << identifier << "' encontrado no escopo global." << std::endl;
            return true;
        }

        // Depois, verificar nos escopos locais (variáveis)
        std::stack<std::map<std::string, std::string>> tempStack = symbolTableStack;
        while (!tempStack.empty()) {
            auto it = tempStack.top().find(identifier);
            if (it != tempStack.top().end()) {
                std::cout << "Identificador '" << identifier << "' encontrado no escopo local." << std::endl;
                return true;
            }
            tempStack.pop();
        }

        std::cout << "Identificador '" << identifier << "' não declarado." << std::endl;
        return false;
    }


    std::string SemanticAnalyzer::getIdentifierType(const std::string& identifier) {
        // Primeiro, verificar no escopo global
        auto itGlobal = globalSymbolTable.find(identifier);
        if (itGlobal != globalSymbolTable.end()) {
            std::cout << "Encontrado identificador global '" << identifier << "' com tipo '" << itGlobal->second << "'." << std::endl;
            return itGlobal->second;
        }

        // Depois, verificar nos escopos locais
        std::stack<std::map<std::string, std::string>> tempStack = symbolTableStack;
        while (!tempStack.empty()) {
            auto it = tempStack.top().find(identifier);
            if (it != tempStack.top().end()) {
                std::cout << "Encontrado identificador '" << identifier << "' com tipo '" << it->second << "'." << std::endl;
                return it->second;
            }
            tempStack.pop();
        }

        std::cout << "Identificador '" << identifier << "' não encontrado." << std::endl;
        return "";
    }