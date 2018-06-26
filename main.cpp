#include <iostream>
#include <HeuristicaGulosa.h>
#include "Grafo.h"

using namespace std;

int main()
{
    srand(time(NULL));

    Grafo g("instancia.txt");
    g.imprime();

    //HeuristicaGulosa heuristicaGulosa(g);
    //heuristicaGulosa.teste_heuristica_gulosa();

    return 0;

}
