//Jeferson Gonçalves Noronha Soriano - 471110
//Emanuel Moraes Rodrigues - 433706

#include <iostream>
#include <fstream>
#include <sstream>
#include "Matriz.h"

using namespace std;

struct Node {
    Node * direita;
    Node * abaixo;
    int linha;
    int coluna;
    double valor;

    ~Node() { std::cout << "no com valor " << valor << " liberado" << std::endl; }
};

Matriz::Matriz(){
   
    head = new Node;
    head->direita = head;
    head->abaixo = head;
    head->valor = 7777;
    head->linha = -1;
    head->coluna = -1;

}

// Destrutor: libera memoria alocada
Matriz::~Matriz(){
    
    Node *primeiroElemento = head->abaixo;
    Node *aux = primeiroElemento->direita;
    
    //aqui deleta todos os nos da matriz
    while(primeiroElemento != head){
        while (aux != primeiroElemento){
            Node *aux2 = aux;
            aux = aux->direita;

            delete aux2;
        }

        primeiroElemento = primeiroElemento->abaixo;
        aux = primeiroElemento->direita;
        
    }

    Node *headLinha = head->abaixo;
    Node *headColuna = head->direita;

    //aqui deleta todos os no cabeça das linhas e colunas
    while(headColuna != head && headLinha != head){
        Node *aux = headLinha;
        headLinha = headLinha->abaixo;
        delete aux;

        Node *aux2 = headColuna;
        headColuna = headColuna->direita;
        delete aux2;

    }

    delete head;
    cout << "matriz liberada" << endl;
} 

/*
    Esse metodo le, de um arquivo de entrada, os elementos diferentes de zero de uma
    matriz e monta a estrutura especificada anteriormente. Considere que a entrada
    consiste dos valores de m e n (n´umero de linhas e de colunas da matriz) seguidos
    de triplas (i, j, valor) para os elementos diferentes de zero da matriz.
*/
void Matriz::lerMatriz(std::string file){
    ifstream arq;
    string linha;

    arq.open(file);
    
    if(arq.is_open()){
        

        int i = 1;

        int l, c, valor;
        while(getline(arq, linha)){
            std::stringstream convert;
            convert << linha;

            

            if(i == 1){
                convert >> l >> c;
                criarNosCabecaMatriz(l , c);
            }else{
                
                convert >> l >> c >> valor;
                
                insere(l, c, valor);


            }

            i++;
        }

        arq.close();


    }

}


//Esse metodo imprime (uma linha da matriz por linha na saıda) a matriz A, inclusive
//os elementos iguais a zero.
void Matriz::imprime(){
    Node *primeiroLinha = head->abaixo;
    
    Node *aux = nullptr;


    int i = 1, j = 1;
    while(i <= linha){
        aux = primeiroLinha->direita;
        while(j <= coluna){
            
            if(aux->linha == i && aux->coluna == j){
                cout << aux->valor << " ";
                aux = aux->direita;
            }else{
                cout << "0" << " ";
            }

            j++;
        }

        if(primeiroLinha->direita->linha == i || primeiroLinha->direita->linha == -1){
            primeiroLinha = primeiroLinha->abaixo;
        }

        i++;

        //reiniciando os valores
        j = 1;
       

        cout << endl;
    }

   
    
}


//Esse metodo insere o valor v na linha i, coluna j da matriz A.
void Matriz::insere(int i, int j, double v){
    //verificar se ja num existe no nessa posicão q esta querendo inserir
    //se tiver, so subistituir o valor para o novo
    Node *existe = procurarNo(i, j);
    if(existe != nullptr){
        existe->valor = v;
        
        return;
    }

    
    Node *headLinha = head;
    Node *headColuna = head;
    
    //pegar referencia do no cabeça da linha
    for(int l = 1; l <= i; l++){
        headLinha = headLinha->abaixo;
    }

     //pegar referencia do no cabeça da coluna
    for(int c = 1; c <= j ; c++){
        headColuna = headColuna->direita;
    }

    //depois q tem referencia do nó cabeça da linha e da coluna, é so inserir
    //primeiro a referencia da linha é organzado
    //depois a referencia da coluna é arrumada
    Node *aux = headColuna;
    Node *aux2 = headLinha;


    if(aux->abaixo->coluna != -1){
        
        while(aux->abaixo->linha < i){
            aux = aux->abaixo;

            if(aux->abaixo->coluna == -1){
                break;
            }
        }

    }


    Node *novo = new Node;
    
    novo->valor = v;
    novo->linha = i;
    novo->coluna = j;
    novo->abaixo = aux->abaixo;

    aux->abaixo = novo;

    if(aux2->direita->linha != -1){

        while(aux2->direita->coluna < j){
            aux2 = aux2->direita;

            if(aux2->direita->linha == -1){
                break;
            }
        }

    }
    

    novo->direita = aux2->direita;
    aux2->direita = novo;

}


//Essa funcao recebe como parametro as matrizes A e B, devolvendo uma matriz C
//que eh a soma de A com B.
Matriz *Matriz::soma(Matriz *A, Matriz *B){
    if(A->linha == B->linha && A->coluna == B->coluna){
        
        Matriz *c = new Matriz();
        c->criarNosCabecaMatriz(A->linha, B->coluna);

        int i = 1, j = 1;
        double valorA = 0;
        double valorB = 0;

        //a valor da celula i j da matriz A sera somada com o valor celula i j da matriz B
        while(i <= A->linha){
            while(j <= A->coluna){
                
                
                valorA = A->procurar(i, j);
                valorB = B->procurar(i, j); 

                if((valorA + valorB) != 0){
                    c->insere(i, j, (valorA+valorB));
                }

                j++;
            }
            i++;

            //reiniciando os valores
            j = 1;
        }

        return c;
    }
    
    return nullptr;
}

//Esse metodo recebe como parametro as matrizes A e B, devolvendo uma matriz C
//que eh o produto de A por B
Matriz *Matriz::multiplica(Matriz *A, Matriz *B){
    if(A->coluna == B->linha){
        
        Matriz *c = new Matriz();
        c->criarNosCabecaMatriz(A->linha, B->coluna);


        int i = 1, j = 1, x = 1;
        
        double valorA = 0;
        double valorB = 0;
        double valorC = 0;
        
        //para fazer a multiplicação de matrizes
        //temos que multiplicar a linhas da primeira matriz com as colunas da segunda matriz
            //uma matriz A 2x2 e uma matriz B 2x2
            //a primeira linnha da matriz A será multiplicada e somada pela duas colunas da matriz b
            //a segunda linnha da matriz A será multiplicada e somada pela duas colunas da matriz b 
        while(i <= A->linha){
            while(j <= B->coluna){
                while(x <= A->coluna){
                    valorA = A->procurar(i, x);
                    valorB = B->procurar(x, j); 
                    valorC = c->procurar(i, j);
                
                    if(((valorA * valorB)+valorC) != 0){
                        c->insere(i, j, ((valorA*valorB) + valorC));
                    }

                    x++;
                }
                
                

                j++;
                //reiniciando os valores
                x = 1;
            }
            i++;

            //reiniciando os valores
            j = 1;
        }

        return c;
    }
    
    return nullptr;
}




//essa função retorna o valor contido na celula i j
double Matriz::procurar(int l, int c){
    Node *primeiroLinha = head->abaixo;
    Node *aux = nullptr;


    int i = 1, j = 1;
    while(i <= linha ){

        aux = primeiroLinha->direita;

        while(j <= coluna){

            if(l== i && j == c){

                if(aux->linha == i && aux->coluna == j){
                    return aux->valor;
                }else{
                    return 0;
                }
            
            }
            
            if(aux->linha == i && aux->coluna == j){
                aux = aux->direita;
            }

            j++;
        }

        if(primeiroLinha->direita->linha == i || primeiroLinha->direita->linha == -1){
            primeiroLinha = primeiroLinha->abaixo;
        }

        i++;

        //reiniciando os valores
        j = 1;
       
    }
}

//essa função procura um no nos indices i j
Node *Matriz::procurarNo(int l, int c){
    
    Node *primeiroLinha = head->abaixo;
    Node *aux = nullptr;


    int i = 1, j = 1;
    while(i <= linha ){

        aux = primeiroLinha->direita;

        while(j <= coluna){

            if(l== i && j == c){

                if(aux->linha == i && aux->coluna == j){
                    return aux;
                }else{
                    return nullptr;
                }
            
            }
            
            if(aux->linha == i && aux->coluna == j){
                aux = aux->direita;
            }

            j++;
        }

        if(primeiroLinha->direita->linha == i || primeiroLinha->direita->linha == -1){
            primeiroLinha = primeiroLinha->abaixo;
        }

        i++;

        //reiniciando os valores
        j = 1;
       
    }
    
    return nullptr;
}


//essa função cria os no cabeça da matriz( nos cabeça das linhas e colunas ) e armazena a dimissão da matriz
void Matriz::criarNosCabecaMatriz(int l, int c){
    linha = l;
    coluna = c;


     //criar os no cabeça da linha
    for(int j = 1; j <= coluna; j++ ){
        Node *cabeca = new Node;

        if(j == 1){
            head->direita = cabeca;
            
            cabeca->direita = head;
            cabeca->abaixo = cabeca;
            cabeca->coluna = -1;
            cabeca->valor = 7777;

            continue;
        }

        Node *aux = head;

        while(aux->direita != head){
            aux = aux->direita;
        }

        aux->direita = cabeca;
        
        cabeca->abaixo = cabeca;
        cabeca->direita = head;
        cabeca->coluna = -1;
        cabeca->valor = 7777;
        
    }


    //criar os no cabeça da coluna
    for(int i = 1; i <= linha; i++ ){

        Node *cabeca = new Node;

        if(i == 1){
            head->abaixo = cabeca;
            
            cabeca->abaixo = head;
            cabeca->direita = cabeca;
            cabeca->linha = -1;
            cabeca->valor = 7777;

            continue;
        }

        Node *aux = head;

        while(aux->abaixo != head){
            aux = aux->abaixo;
        }

        aux->abaixo = cabeca;
        
        cabeca->abaixo = head;
        cabeca->direita = cabeca;
        cabeca->linha = -1;
        cabeca->valor = 7777;
        

    }

}