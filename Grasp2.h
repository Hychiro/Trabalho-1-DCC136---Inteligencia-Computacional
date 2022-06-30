/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
/**************************************************************************************************

**************************************************************************************************/

#ifndef GRASP2_H_INCLUDED
#define GRASP2_H_INCLUDED
#include "Graph.h"
#include "Instancia.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Grasp2
{
public:
    void Clusterizar(Graph *grafo,Instancia* atual,Instancia* analizada,Instancia* melhorAnalizada, Instancia *movimentoAnterior);
    void Centroides(Graph *grafo);
    void CompletarLI1(Graph *grafo);
    void CompletarLS1(Graph *grafo);
    void CompletarPiorCaso(Graph *grafo);
    void Completar(Graph *grafo);
    void verticesRandom(Graph *grafo);
    void imprime(Graph *grafo);
    void guarda(Graph *grafo,ofstream &output_file);
    void CompletarVerticesLivres(Graph *grafo);
    void buscaLocal2(Graph *grafo);

    bool verificaTroca(Graph *grafo, int idClusterExcedente, int idClusterAlvo, int idNo);
    void troca(Graph *grafo, int idClusterExcedente, int idClusterAlvo, int idNo);
    void ajuste(Graph *grafo);

    float calculaSolucao(Graph *grafo);
    void buscaLocal(Graph *grafo,Instancia *atual,Instancia *analizada,Instancia *melhorAnalizada, Instancia *movimentoAnterior);
    bool desbalanceadoS(Cluster * cluster);

    void pertubacao(Graph *grafo);
    void swap(Graph *grafo, int idCluster1, int idCluster2, int idNo1, int idNo2);

    float calculaQualidadeMelhorSolucao(Graph *grafo);
    
};
#endif // GRASP2_INCLUDED