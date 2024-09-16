#include <iostream>
#include <map>
#include <stack>
#include <string>

class SemanticAnalyzer {
private:
    // Cada escopo é representado por uma tabela de símbolos (mapa de identificadores para seus tipos)
    std::stack<std::map<std::string, std::string>> symbolTableStack;

public:
    // Construtor: começa com o escopo global
    SemanticAnalyzer() {
        enterScope();
    }

    // Entrar em um novo escopo
    void enterScope() {
        symbolTableStack.push(std::map<std::string, std::string>());
    }

    // Sair do escopo atual
    void exitScope() {
        if (!symbolTableStack.empty()) {
            symbolTableStack.pop();
        } else {
            std::cerr << "Erro: Tentativa de sair de um escopo inexistente." << std::endl;
        }
    }

    // Declarar um novo identificador no escopo atual
    bool declareIdentifier(const std::string& identifier, const std::string& type) {
        // Verifica se o identificador já foi declarado no escopo atual
        if (symbolTableStack.top().find(identifier) != symbolTableStack.top().end()) {
            std::cerr << "Erro: Identificador \"" << identifier << "\" já declarado neste escopo." << std::endl;
            return false;
        } else {
            symbolTableStack.top()[identifier] = type;
            return true;
        }
    }

    // Verificar se um identificador foi declarado em algum escopo anterior
    bool isDeclared(const std::string& identifier) {
        std::stack<std::map<std::string, std::string>> tempStack = symbolTableStack;
        
        // Percorre os escopos de cima para baixo (do mais recente ao mais antigo)
        while (!tempStack.empty()) {
            if (tempStack.top().find(identifier) != tempStack.top().end()) {
                return true;
            }
            tempStack.pop();
        }
        return false;
    }

    // Usar um identificador
    void useIdentifier(const std::string& identifier) {
        if (!isDeclared(identifier)) {
            std::cerr << "Erro: Identificador \"" << identifier << "\" não foi declarado antes do uso." << std::endl;
        }
    }
};