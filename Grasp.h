/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
/**************************************************************************************************

**************************************************************************************************/

#ifndef GRASP_H_INCLUDED
#define GRASP_H_INCLUDED
#include "Graph.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Grasp
{
public:
    void Clusterizar(Graph *grafo);
    void Centroides(Graph *grafo);
    void CompletarLI1(Graph *grafo);
    void CompletarLS1(Graph *grafo);
    void CompletarPiorCaso(Graph *grafo);
};
#endif // GRASP_INCLUDED