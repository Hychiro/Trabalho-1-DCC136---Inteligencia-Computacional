/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
#ifndef CLUSTER_H_INCLUDED
#define CLUSTER_H_INCLUDED

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
    Cluster(float peso, float limiteInferior, float limiteSuperior);
    // Destructor
    ~Cluster();
    // Getters
    float getPeso();
    float getLimiteInferior();
    float getLimiteSuperior();

    Node *getFirstNode();
    Node *getLastNode();

    Node* getNode(int id);
    // Setters
    void addNode(int id);
    void addEdge(int id, int target_id, float peso);

    float setPeso(float valor);
    float setLimiteInferior(float valor);
    float setLimiteSuperior(float valor);

    Node *searchNode(int id);

    bool verificaAresta(int id, int target_id);
};
#endif // CLUSTER_H_INCLUDED
