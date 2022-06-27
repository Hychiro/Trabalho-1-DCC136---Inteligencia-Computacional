/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
/**************************************************************************************************

**************************************************************************************************/

#ifndef GRASP_H_INCLUDED
#define GRASP_H_INCLUDED
#include "Graph.h"
#include "Instancia.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Grasp
{
public:
    void Clusterizar(Graph *grafo,Instancia* atual,Instancia* analizada,Instancia* melhorAnalizada);
    void Centroides(Graph *grafo);
    void CompletarLI1(Graph *grafo);
    void CompletarLS1(Graph *grafo);
    void CompletarPiorCaso(Graph *grafo);
    void Completar(Graph *grafo);
    void verticesRandom(Graph *grafo);
    void imprime(Graph *grafo);

    bool verificaTroca(Graph *grafo, int idClusterExcedente, int idClusterAlvo, int idNo);
    void troca(Graph *grafo, int idClusterExcedente, int idClusterAlvo, int idNo);
    void ajuste(Graph *grafo);

    float calculaSolucao(Graph *grafo);
    void buscaLocal(Graph *grafo,Instancia *atual,Instancia *analizada,Instancia *melhorAnalizada);
    bool desbalanceadoS(Cluster * cluster);
};
#endif // GRASP_INCLUDED