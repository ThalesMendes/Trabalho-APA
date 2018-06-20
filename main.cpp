#include <iostream>
#include "Grafo.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Grafo g("teste.txt");

    g.imprime();

//    g.teste_Heuristica_Gulosa();

    return 0;

}
