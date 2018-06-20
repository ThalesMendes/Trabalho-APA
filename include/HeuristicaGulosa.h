//
// Created by Thales Castro on 20/06/2018.
//

#ifndef TRABALHO_APA_HEURISTICAGULOSA_H
#define TRABALHO_APA_HEURISTICAGULOSA_H

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

class HeuristicaGulosa {

public:
    void teste_heuristica_gulosa();
    int conjunto_Dominante_Minimo(float alpha, int iteracoes, float *media2);

private:
    int aux_Conjunto_Dominante_Minimo(float alpha);
    void exclui_No_Heuristica(int id);
    bool verifica_Adjacentes(int id1, int id2);
    int get_Qtd_Nos();

    int qtd_De_Nos;	   	   ///< Armazena Quantidade de N�s.
    bool flag_Direcionado; ///< Valor l�gico que indica se o grafo � direcionado ou n�o.
    list<No> Nos;		   ///< Lista de N�s do Grafo.
    int valor_Testes[3000]; ///< Armazena os valores dos testes para a Heuristica.
    int num_Testes;		   ///< Numero de vezes que a heuristica foi testada.
};


#endif //TRABALHO_APA_HEURISTICAGULOSA_H
