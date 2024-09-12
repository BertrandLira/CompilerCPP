#include <fstream>
#include <iostream>
#include <optional>
#include "../syntax/parser.cpp"

using namespace std;

int main(){
    Scanner sc = Scanner("source_code.txt");
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

    return 0;
}