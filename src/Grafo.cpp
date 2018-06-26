#include "Grafo.h"

/********************************************//**
 * \Construtor da classe Grafo.
 *
 * \Parâmetro: Nome do arquivo de entrada do Grafo.
 * \Sem valor de Retorno.
 *
 * Inicializa a qtd_De_Nos com 0 e chama a função de leitura do Grafo.
 ***********************************************/
Grafo::Grafo(string nome_arquivo)
{
    qtd_De_Nos = 0;
    num_Testes = 0;

    cout << "O grafo será lido para Heurística? " << endl << "s para SIM, n para NAO: " ;
    char t = 's';
    if(t != 's')
        le_Grafo(nome_arquivo);
    else
    {
        cout << "PASSOU" << endl;
        aux_Le_Grafo(nome_arquivo);
    }

}

/********************************************//**
 * \Construtor do Grafo sem parâmetros.
 *
 * \Sem valor de retorno
 *
 * Construtor para casos que sejam criados Grafos sem que seja necessário leitura(Ex: Retornar componentes conexas).
 ***********************************************/
Grafo::Grafo()
{
    qtd_De_Nos = 0;
}


/********************************************//**
 * \Insere nós no grafo.
 *
 * \Paramêtro: id que vai identificar o nó.
 * \Sem valor de  retorno.
 *
 * Aumento a variável qtd_De_Nos + 1 e insere o novo nó com o id passado no final da lista de nos do grafo.
 ***********************************************/
void Grafo::insere_No(int id)
{
    qtd_De_Nos += 1;
    Nos.push_back(No(id));
}
/********************************************//**
 * \Insere nó ponderado no grafo.
 *
 * \Parâmetro: id que vai identificar o nó.
 * \Parâmetro: peso do nó.
 * \Sem valor de  retorno.
 *
 * Aumento a variável qtd_De_Nos + 1 e insere o novo nó com o id passado no final da lista de nos do grafo.
 ***********************************************/
void Grafo::insere_No(int id, float peso)
{
    qtd_De_Nos += 1;
    No* insere = new No(id);
    insere->set_Peso_No(peso);
    Nos.push_back(*insere);
}

/********************************************//**
 * \ Cria uma nova aresta/arco.
 *
 * \Parâmetro: id1 corresponde a um dos nós da nova aresta.
 * \Parâmetro: id2 corresponde a um dos nós da nova aresta.
 * \Parâmetro que corresponde ao peso da nova aresta a ser criada.
 * \Sem valor de retorno.
 *
 * Dado id1, id2 e peso, é criada uma nova aresta/arco entre esses dois nós se, e somente se, os nós já foram inseridos na Lista de Nós.
 ***********************************************/
void Grafo::insere_Aresta(int id1,int id2, float peso)
{
    if(existe_No(id1) && existe_No(id2))
    {
        if(!flag_Ponderado)
            peso = 1.0;
        aux_Insere_Aresta(id1,id2,peso);
    }
    else
        cout << "Nao existe tais vertices" << endl;
}

/********************************************//**
 * \Imprime o grafo.
 *
 * \Sem valor de retorno.
 *
 * Imprime os nos e seus respectivos adjacentes.
 ***********************************************/
void Grafo::imprime()
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
    {
        cout << i->get_Id() << " :";
        i->imprime_Adjacentes();
    }
}


/********************************************//**
 * \brief Funcao verifica desvio padrao
 *
 * \return    Não há retorno.
 *
 * A função calcula o desvio padrão referentes a todos os testes rodados na execução do programa.
 ***********************************************/
void Grafo::verifica_Desvio_Padrao()
{
    int soma = 0;
    int somaFinal = 0;
    int media;
    for(int i = 0; i < num_Testes; i++)
    {
        soma+= valor_Testes[i];
    }
    media = soma/num_Testes;
    for(int i = 0; i<num_Testes; i++)
    {
        somaFinal += (valor_Testes[i]-media)*(valor_Testes[i]-media);
    }
    cout << "O DEVIO PADRAO PARA TODOS OS TESTES DESTA INSTANCIA FOI: " << sqrt(somaFinal/num_Testes) << endl;

}



/********************************************//**
 * \Insere nova aresta/arco no Grafo.
 *
 * \Parâmetro: id1 corresponde a um dos nós da nova aresta/arco.
 * \Parâmetro: id2 corresponde a um dos nós da nova aresta/arco.
 * \Parâmetro: peso da nova aresta/arco.
 * \Sem valor de Retorno.
 *
 * Dado id1, id2 e peso, é criada uma nova aresta/arco entre esses dois nós. Caso não exista nós com respectivos id's eles serão criados.
 ***********************************************/
void Grafo::aux_Insere_Aresta(int id1,int id2,float peso)
{
    No* pont_id1 = 0;
    No* pont_id2 = 0;

    list<No>::iterator it;
    ///< Percorre a Lista de Nós e seta os ponteiros criados para os nós, caso existam.
    for(it = Nos.begin(); it != Nos.end(); it++)
    {
        if(it->get_Id() == id1)
            pont_id1 = &*it;
        if(it->get_Id() == id2)
            pont_id2 = &*it;
    }
    ///< Se o ponteiro ainda aponta para nulo, então passará a apontar para novo nó que será incluído no final da Lista de Nós.
    ///< Insere a aresta/arco na adjacencia do nó.
    ///< Aresta/arco id2-id1 é incluída se, e somente se, o grafo não for direcionado.
    if(pont_id1 == nullptr)
    {
        Nos.push_back(No(id1));
        pont_id1 = &Nos.back();
        pont_id1->add_Adjacente(id2,peso);
        qtd_De_Nos++;

        if(pont_id2 == nullptr)
        {
            Nos.push_back(No(id2));
            pont_id2 = &Nos.back();
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
            qtd_De_Nos++;
        }
        else
        {
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
        }
    }
    else
    {
        pont_id1->add_Adjacente(id2,peso);
        if(pont_id2 == 0)
        {
            Nos.push_back(No(id2));
            pont_id2 = &Nos.back();
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
            qtd_De_Nos++;
        }
        else
        {
            if(!flag_Direcionado)
                pont_id2->add_Adjacente(id1,peso);
        }
    }
}

/********************************************//**
 * \Lê uma instancia de grafo
 *
 * \O parâmetro 'nome' leva o nome do arquivo a ser lido.
 *
 * \Sem valor de retorno.
 *
 * A função le o arquivo com o nome que foi passado por parâmetro, cria nos e adjacências para os mesmo de acordo com o .txt em questão.
 ***********************************************/
void Grafo::le_Grafo(string nome)
{
    std::ifstream arq_grafo(nome.c_str());
    int qtd_aux;
    arq_grafo >> qtd_aux;
    arq_grafo >> flag_Direcionado;
    arq_grafo >> flag_Ponderado;

    int id1,id2;
    float peso;
    if(!flag_Ponderado)
    {
        while(!arq_grafo.eof())
        {
            arq_grafo >> id1 >> id2;
            aux_Insere_Aresta(id1,id2,1.0);
        }
    }
    else
    {
        while(!arq_grafo.eof())
        {
            arq_grafo >> id1 >> id2;
            arq_grafo >> peso;
            aux_Insere_Aresta(id1,id2, peso);
        }
    }
    arq_grafo.close();
}


void Grafo::aux_Le_Grafo(string nome)
{

    cout << nome << endl;
    std::ifstream arq_grafo(nome.c_str());
    int qtd_aux;
    if(!arq_grafo )
    {
        cout <<"Erro de leitura" << endl;
    }
    else
    {
        arq_grafo >> qtd_aux;

        int id1,id2;
        float peso;
        int variavelAux;


        for(int i = 0; i < qtd_aux; i++)
        {
            id1 = i;
            arq_grafo >> peso;
            insere_No(id1,peso);

        }
        for(int i = 0; i<qtd_aux*qtd_aux; i++)
        {
            arq_grafo >>variavelAux;
            if(variavelAux==1)
            {
                insere_Aresta((int)(i/qtd_aux),i%qtd_aux,1.0);
            }

        }
        arq_grafo.close();

    }

}


/********************************************//**
 * \Verifica a existência de determinado no
 *
 * \O parâmetro 'identificacao' tem o valor do id do No que eu estou a procura.
 * \Retorno um bool com true para existência do no em questão e false caso não.
 *
 *
 ***********************************************/
bool Grafo::existe_No(int identificacao)
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        if(i->get_Id() == identificacao)
            return true;

    return false;
}

/********************************************//**
 * \brief This is a brief description.
 *
 * \param	p1 The first parameter.
 * \param	p2 The second parameter.
 * \return	Return value.
 *
 * This is a detailed description.
 ***********************************************/

Grafo::~Grafo()
{
    list<No>::iterator i;
    for(i = Nos.begin(); i != Nos.end(); i++)
        delete &*i;

    Nos.clear();
}

