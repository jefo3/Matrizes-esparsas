//Jeferson Gonçalves Noronha Soriano - 471110
//Emanuel Moraes Rodrigues - 433706


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>
#include "Matriz.h"
using namespace std;

int main(){
  vector<Matriz*> matrizes;
  

	while(true) {
		string cmd;
		getline(cin, cmd);

		std::stringstream ss{ cmd };
		vector<string> tokens;
		string buffer;

		while(ss >> buffer) {
			tokens.push_back(buffer);
		}

		if(tokens[0] == "libera" || tokens[0] == "exit") {
			for(int i = 0; i < matrizes.size(); ++i) {
				delete matrizes[i];
				matrizes[i] = nullptr;
			}
			matrizes.clear();
			break;
		}
		// cria a matriz
    else if(tokens[0] == "create") {
        Matriz *m = new Matriz();
			  matrizes.push_back( m );
        if(m != nullptr) cout << "matriz " <<  matrizes.size()-1 << " criada" << endl;
		}

    //ler arquivo [k]
    else if(tokens[0] == "lerArquivo"){
        int k = std::stoi(tokens[1]);
        cout << "Digite o nome do arquivo (junto com o .txt)" << endl;
        string nome_do_arquivo;
  
        getline(cin, nome_do_arquivo);
       

        matrizes[k]->lerMatriz(nome_do_arquivo);

        matrizes[k]->imprime();

    }
		// imprime [k]
		else if(tokens[0] == "imprime") {
			int k = std::stoi(tokens[1]);
			matrizes[k]->imprime();
		}
		// soma [p] [q] 
		else if(tokens[0] == "soma") {
        int p = std::stoi(tokens[1]);
        int q = std::stoi(tokens[2]);
        Matriz *C = matrizes[p]->soma(matrizes[p], matrizes[q]);
        
        if(C == nullptr) 
            cout << "nao foi possivel somar" << endl;
        else {
            C->imprime();
            delete C;
        }
		}
    // multiplica [p] [q] 
		else if(tokens[0] == "multiplica") {
        int p = std::stoi(tokens[1]);
        int q = std::stoi(tokens[2]);
        Matriz *C = matrizes[p]->multiplica(matrizes[p], matrizes[q]);
        if(C == nullptr) 
          cout << "nao foi possivel multiplicar" << endl;
          
        else {
            C->imprime();
            delete C;
        }
		}
		else {
			cout << "comando inexistente" << endl;
		}
	}

	return 0;
}