#include <fstream>
#include <iostream>
#include <optional>
#include "../syntax/parser.cpp"
#include "../semantic/SemanticAnalyzer.cpp"

using namespace std;

int main(int argc, char* argv[]){
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <source_file>" << endl;
        return 1;
    }
    
    string sourceFile = argv[1];
    Scanner sc = Scanner(sourceFile);
    optional<Token> tk;
	Parser parser = Parser(sc);
		
    while(true) {
        if(sc.isEOF()) {
            break;
        }

        tk = sc.nextToken();
        if(tk == nullopt){
            break;
        }
        

        tk->toString();
       
    }

    cout << "Lexical Compilation Successful" << endl;

    parser.programa();

    cout << "Parsing Compilation Successful" << endl;

    return 0;
}