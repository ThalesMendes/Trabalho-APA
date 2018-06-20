//
// Created by Thales Castro on 20/06/2018.
//

#include <HeuristicaGulosa.h>
#include <ctime>
#include <cmath>
#include <No.h>
#include "HeuristicaGulosa.h"
#include "iostream"

using namespace std;

/********************************************//**
 * \brief Função para teste da heurística gulosa
 *
 * \return    Não há retorno;
 *
 * A função chama a função conjunto dominante minimo com os parâmetros adequados
 ***********************************************/
void HeuristicaGulosa::teste_heuristica_gulosa()
{
    float* media =  new float();
    cout << " COMECO DO TESTE HEURISTICA GULOSA ----------------------------------------------------------------------" << endl << endl;

    int x = conjunto_Dominante_Minimo(0.0,1, media);
    cout<< "O RESULTADO FOI: "<<x<<endl;

    cout << " FIM DO TESTE HEURISTICA GULOSA ----------------------------------------------------------------------" << endl  << endl << endl;
}


/********************************************//**
 * \Funcao de cálculo para o problema de conjunto dominante mínimo
 *
 * \Parâmetro: Alpha, ajuste do valor randomico da heurística.
 * \Parâmetro: Iteracoes, quantidade de iterações que deverao ser testadas.
 * \Parâmetro: Media, para cálculo da média das soluções.
 * \Retorna Best, o melhor valor de solução do problema.
 *
 * A função irá chamar iteração vezes a funcao aux_Conjunto_Dominante_Minimo. Ao final, irá identificar e  retornar o melhor resultado dentre essas iterações
 ***********************************************/
int HeuristicaGulosa::conjunto_Dominante_Minimo(float alpha, int iteracoes, float* media2)
{
    int vet[iteracoes];
    float matTempo[iteracoes];

    float media;
    int soma = 0;
    int best;

    for(int i = 0; i < iteracoes; i++)
    {

        float time1 = clock();


        vet[i] = aux_Conjunto_Dominante_Minimo(alpha);

        valor_Testes[num_Testes] = vet[i];

        num_Testes++;
        float time2 = clock();

        matTempo[i] = time2 - time1;

        if(i == 0)
        {
            best = vet[i];
        }
        else
        {
            if(best>vet[i])
            {
                best = vet[i];
            }
        }
    }

    for(int i = 0; i< iteracoes; i++)
    {
        soma +=vet[i];
    }
    media = soma/iteracoes;
    int parcial[iteracoes];
    for(int i = 0; i< iteracoes; i++)
    {
        parcial[i]= (vet[i]-media)*(vet[i]-media);
    }

    int somaFinal = 0;
    for(int i = 0; i < iteracoes; i++)
    {

        somaFinal += parcial[i];
    }

    double desvio = sqrt(somaFinal / iteracoes);

    *media2 = media;

    /*cout << " A media para alpha "<< alpha << "e " << iteracoes << " iteracoes foi de: " << media << endl;
    cout << " O desvio padrao para alpha "<< alpha << "e " << iteracoes << " iteracoes foi de: " << desvio << endl;*/
    for(int i = 0; i< iteracoes; i++)
    {

        //cout << "Resultado com alpha " << alpha <<  " : " << vet[i] << "   Tempo de execução: " << matTempo[i] << endl;
    }
    // cout << "teste best :" << best << endl;
    return best;
}



/********************************************//**
 * \ Funcão para construção de uma solução para o problema de conjunto dominante mínimo com peso.
 *
 * \Parâmetro: Alpha,para ajuste do fator randômico da heurística.
 * \Retorna o valor de solução para o problema proposto
 *
 * Inicialmente, todos os ids dos nós são copiados para uma estrutura auxiliar. Dois casos em particular são analisados: se o grau do nó é 0,
 * ele estará na solução; se o grau do nó é 1, é avaliado o melhor custo benefício para se incluir na solução, ele ou seu vizinho.
 * Ao final, repete-se até encontrar a solução:  o nó de melhor custo benefício(grau do no dividido por seu peso) é inserido na solução.
 ***********************************************/

int HeuristicaGulosa::aux_Conjunto_Dominante_Minimo(float alpha)
{

    list<No>::iterator i;
    int contador = 0;

    list<int> listaAux;


    for(i = Nos.begin(); i != Nos.end(); i++)
    {

        listaAux.push_back(i->get_Id());

        i->set_Grau_No_Heuristica();
        if(i->get_Id()==(get_Qtd_Nos()-1))
        {
            break;
        }

    }

    int contador2 = 0;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        if(i->get_Grau_No_Heuristica()==0)
        {
            contador += i->get_Peso_No();
            listaAux.remove(i->get_Id());
            exclui_No_Heuristica(i->get_Id());
        }
        else
        {
            if(i->get_Grau_No_Heuristica()==1)
            {
                int *lista = i->lista_Adjacencias();
                int* lista2;
                list<No>::iterator j;
                for(j = Nos.begin(); j != Nos.end(); j++)
                {
                    if(j->get_Id() == lista[0])
                    {
                        if(((i->get_Grau_No_Heuristica())/(i->get_Peso_No()))>((j->get_Grau_No_Heuristica())/(j->get_Peso_No())))
                        {
                            lista2 = j->lista_Adjacencias();
                            int t = j->get_Grau_No();
                            for(int k =0; k< t; k++)
                            {
                                if(std::find(listaAux.begin(), listaAux.end(), lista2[k]) != listaAux.end())
                                {
                                    listaAux.remove(lista2[k]);
                                    exclui_No_Heuristica(lista2[k]);
                                }
                            }
                            listaAux.remove(j->get_Id());
                            exclui_No_Heuristica(j->get_Id());
                            contador += j->get_Peso_No();
                        }
                        else
                        {
                            contador += i->get_Peso_No();
                            exclui_No_Heuristica(i->get_Id());
                            listaAux.remove(i->get_Id());
                        }
                    }
                }
                delete[]lista;
                delete[]lista2;
            }
        }
    }

    int tamanho = (int)(listaAux.size()*alpha);
    int posicao;

    while(!listaAux.empty())
    {
        tamanho = (int)(listaAux.size()*alpha);
        int aux2 = rand();

        int* vet = new int[listaAux.size()];

        int MaiorGrau;

        for(i = Nos.begin(); i != Nos.end(); i++)
        {

            if(i->get_Id() == listaAux.front())
            {
                MaiorGrau = (i->get_Grau_No_Heuristica()/i->get_Peso_No());
            }
        }

        for(int k = 0; k <= tamanho; k++)
        {
            vet[k]=listaAux.front();
        }


        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            if(std::find(listaAux.begin(), listaAux.end(), i->get_Id()) != listaAux.end())
            {
                if((i->get_Grau_No_Heuristica()/i->get_Peso_No())>= MaiorGrau)
                {
                    MaiorGrau = (i->get_Grau_No_Heuristica()/i->get_Peso_No());
                    for(int k = tamanho; k>0; k--)
                    {
                        vet[k] = vet[k-1];
                    }
                    vet[0]=i->get_Id();
                }
            }
        }

        if(tamanho>0)
        {
            posicao = aux2%(tamanho);
        }else{posicao=0;}


        int *lista2;

        for(i = Nos.begin(); i != Nos.end(); i++)
        {
            if(i->get_Id() == vet[posicao])
            {
                lista2 = i->lista_Adjacencias();
                int t = i->get_Grau_No();

                for(int j =0; j< t; j++)
                {
                    if(std::find(listaAux.begin(), listaAux.end(), lista2[j]) != listaAux.end())
                    {


                        listaAux.remove(lista2[j]);


                        exclui_No_Heuristica(lista2[j]);


                    }
                }
                contador += i->get_Peso_No();
                exclui_No_Heuristica(i->get_Id());
                listaAux.remove(i->get_Id());
            }

        }

        delete[] vet;
    }

    listaAux.clear();

    return contador;
}



void HeuristicaGulosa::exclui_No_Heuristica(int id)
{
    list<No>::iterator i;
    if(i != Nos.end() && !flag_Direcionado)
    {
        for(i = Nos.begin(); i != Nos.end(); i++)
            if(verifica_Adjacentes(id, i->get_Id())==true)
                i->diminui_Grau_No_Heuristica();
    }
}


/********************************************//**
 * \Verifica se nó com id2 é adjacente ao nó com id1.
 *
 * \Parâmetro: id1 que corresponde ao nó ao qual será verificado a adjacência.
 * \Parâmetro: id2 que corresponde ao nó que se quer saber ser adjacente ou não à id1.
 * \Retorna um booleano que indica se id2 é adjacente de id1.
 *
 * A Lista de nós é percorrida até se encontrar id1.
 * No nó id1 é vericado se id2 está nas suas adjacências.
 * Se sim, retorna true. Senão false.
 ***********************************************/
bool HeuristicaGulosa::verifica_Adjacentes(int id1, int id2)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        if(i->get_Id() == id1)
            return i->encontra_Adjacente(id2);

    return false;
}


/********************************************//**
 * \Retorna a quantidade de nós.
 *
 * Retorna um inteiro com valor igual a quantidade de nos do grafo.
 *
 * Função retorna a variável qtd_De_Nos que contém a quantidade de nos existentes no grafo.
 ***********************************************/
int HeuristicaGulosa::get_Qtd_Nos()
{
    return qtd_De_Nos;
}