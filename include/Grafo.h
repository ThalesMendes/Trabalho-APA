#ifndef GRAFO_H
#define GRAFO_H
#include "Aresta.h"
#include "No.h"
#include <iostream>
#include "stdio.h"
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <cmath>
#include <time.h>

using namespace std;

class Grafo
{
public:
    Grafo(string nome_arquivo);
    Grafo();
    void insere_No(int id);
    void insere_No(int id,float peso);
    void insere_Aresta(int id1, int id2, float peso);
    void imprime();
    ~Grafo();

    list<No> get_Nos() { return this->Nos; }

private:
    void aux_Insere_Aresta(int id1, int id2, float peso);
    void le_Grafo(string nome);
    void aux_Le_Grafo(string nome);
    bool existe_No(int identificacao);

	int valor_Testes[3000]; ///< Armazena os valores dos testes para a Heuristica.
	int num_Testes;		   ///< Numero de vezes que a heuristica foi testada.
    int qtd_De_Nos;	   	   ///< Armazena Quantidade de N�s.
    bool flag_Direcionado; ///< Valor l�gico que indica se o grafo � direcionado ou n�o.
    bool flag_Ponderado;   ///< Valor l�gico que indica ponderado.
    list<No> Nos;		   ///< Lista de N�s do Grafo.
    void verifica_Desvio_Padrao();
};

#endif // GRAFO_H
