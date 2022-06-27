/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/

#ifndef CLUSTER_H_INCLUDED
#define CLUSTER_H_INCLUDED

#include "Node.h"

using namespace std;

// Definition of the Edge class
class Cluster
{
    // Attributes
private:
    int idCluster;
    float peso;
    float limiteInferior;
    float limiteSuperior;
    Node *first_node;
    Node *last_node;
    Cluster *nextCluster;
    int numNodes;

public:
    // Constructor
    Cluster(int id, float limiteInferior, float limiteSuperior);
    Cluster(int id);
    // Destructor
    ~Cluster();
    // Getters
    float getPeso();
    float getLimiteInferior();
    float getLimiteSuperior();
    int getNumNodes();
    bool viavel();
    float calculaQualidade();

    Node *getFirstNode();
    Node *getLastNode();

    Node *getNode(int id);
    Cluster *getNextCluster();
    // Setters
    void addNode(int id, float peso);
    void addAresta(int id, Node *analisado);
    void addEdge(int id, int target_id, float peso);
    void removeNode(int id);

    void setPeso(float valor);
    void setLimiteInferior(float valor);
    void setLimiteSuperior(float valor);
    int getidCluster(){
        return this->idCluster;
    };
    void setNextCluster(Cluster* cluster);
    void setFirstNode(Node * node);
    void setLastNode(Node * node);
    void setNumNodes(int valor){
        this->numNodes=valor;
    };
    bool searchNode(int id);

    bool verificaAresta(int id, int target_id);
};
#endif // CLUSTER_H_INCLUDED
