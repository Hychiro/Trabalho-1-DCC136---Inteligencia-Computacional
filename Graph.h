/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
/**************************************************************************************************
 * Implementation of the TAD Graph
 **************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Graph
{

    // Atributes
private:
    int order;
    int number_edges;
    int numClusters;
    Node *first_node;
    Node *last_node;
public:
    bool *listaDeNosLivres;
    float melhorInstancia;
    // Constructor
    Graph(int order, int numCluster, int aux[][2]);

    // Destructor
    ~Graph();
    // Getters
    void resetaClusters();
    int getOrder();
    int getNumberEdges();
    Node *getFirstNode();
    Node *getLastNode();
    bool getConexGraph();
    // Other methods
    void insertNode(int id);
    void insertEdge(int id, int pn_fim,int pn_inicio,int kmTotal,int duracaoInspecao,int tMaxInspecao,int tMinInspecao,int ultimainspecao);
    void removeNode(int id);
    bool searchNode(int id);
    Node *getNode(int id);
    
    void insertAllNodes();
    void insertAllClusters();
    bool verificaAresta(int id, int target_id);

    void printGraph(ofstream &output_file);

private:
    // Auxiliar methods
};

#endif // GRAPH_H_INCLUDED