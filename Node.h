/*
Matheus Cardoso Faesy 202065065A
*/


#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class

using namespace std;

// Definition of the Node class
class Node{

    // Attributes
    private:
        Edge* first_edge;
        Edge* last_edge;
        int id;
        char nome[20];
        int km;
        char cidade[20];
        int tempoHotel;
        unsigned int in_degree;
        unsigned int out_degree;
        Node* next_node;

    public:
        // Constructor
        Node(int id);
        // Destructor
        ~Node();
        // Getters
        Edge* getFirstEdge();
        Edge* getLastEdge();
        int getId();
        int getInDegree();
        int getOutDegree();
        Node* getNextNode();
        // Setters
        void setNextNode(Node* node);
        void setFirstEdge(Edge* edge);
        void setLastEdge(Edge* edge);
        // Other methods
        bool searchEdge(int target_id);
        void insertEdge(int pn_fim,int pn_inicio, float kmTotal, float duracaoInspecao, float tMaxInspecao, float tMinInspecao, float ultimainspecao);
        void removeAllEdges();
        int removeEdge(int id, bool directed, Node* target_node);
        void incrementOutDegree();
        void decrementOutDegree();
        void incrementInDegree();
        void decrementInDegree();
        Edge* getEdge(int id);
        
        Edge* hasEdgeBetween(int target_id);
        // Auxiliar methods

};

#endif // NODE_H_INCLUDED
