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
        Node* next_node;

    public:
        // Constructor
        Cluster(float peso,  float limiteInferior, float limiteSuperior);
        // Destructor
        ~Cluster();
        // Getters
        float getPeso();
        float getLimiteInferior();
        float getLimiteSuperior();

        Node* getNextNode();

        // Setters
        void setNextNode(Node* node);
        
        float setPeso(float valor);
        float setLimiteInferior(float valor);
        float setLimiteSuperior(float valor);
};
#endif // CLUSTER_H_INCLUDED
