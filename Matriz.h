//Jeferson Gonçalves Noronha Soriano - 471110
//Emanuel Moraes Rodrigues - 433706


#ifndef MATRIZ_H
#define MATRIZ_H

struct Node;

class Matriz {
     

    public:
        // Construtor: aloca matriz com l linhas e c colunas
        Matriz();

        // Destrutor: libera memoria alocada
        ~Matriz(); 

        /*
            Esse metodo le, de um arquivo de entrada, os elementos diferentes de zero de uma
            matriz e monta a estrutura especificada anteriormente. Considere que a entrada
            consiste dos valores de m e n (n´umero de linhas e de colunas da matriz) seguidos
            de triplas (i, j, valor) para os elementos diferentes de zero da matriz.
        */
        void lerMatriz(std::string file);


        //Esse metodo imprime (uma linha da matriz por linha na saıda) a matriz A, inclusive
        //os elementos iguais a zero.
        void imprime();
        

        //Esse metodo insere o valor v na linha i, coluna j da matriz A.
        void insere(int i, int j, double v);


        //Essa funcao recebe como parametro as matrizes A e B, devolvendo uma matriz C
        //que eh a soma de A com B.
        Matriz *soma(Matriz *A, Matriz *B);

        //Esse metodo recebe como parametro as matrizes A e B, devolvendo uma matriz C
        //que eh o produto de A por B
        Matriz *multiplica(Matriz *A, Matriz *B);


        //essa função procura um no nos indices i j
        Node *procurarNo(int l, int c);
        
        //essa função cria os no cabeça da matriz( nos cabeça das linhas e colunas ) e armazena a dimissão da matriz
        void criarNosCabecaMatriz(int l, int c);


private:
    // Ponteiro para o no cabeca da matriz
    Node *head;

    int linha;
    int coluna;

    //essa função retorna o valor contido na celula i j
    double procurar(int l, int c);

    
};

#endif
