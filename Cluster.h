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
    float peso;
    float limiteInferior;
    float limiteSuperior;
    Node *first_node;
    Node *last_node;

public:
    // Constructor
    Cluster( float limiteInferior, float limiteSuperior);
    Cluster();
    // Destructor
    ~Cluster();
    // Getters
    float getPeso();
    float getLimiteInferior();
    float getLimiteSuperior();

    Node *getFirstNode();
    Node *getLastNode();

    Node *getNode(int id);
    // Setters
    void addNode(int id, float peso);
    void addAresta(int id, Node *analisado);
    void addEdge(int id, int target_id, float peso);

    void setPeso(float valor);
    void setLimiteInferior(float valor);
    void setLimiteSuperior(float valor);

    Node *searchNode(int id);

    bool verificaAresta(int id, int target_id);
};
#endif // CLUSTER_H_INCLUDED
