/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/
/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int target_id;
        Edge* next_edge;
        float peso;

    public:
        // Constructor
        Edge(int target_id);
        // Destructor
        ~Edge();
        // Getters
        int getTargetId();
        Edge* getNextEdge();
        float getPeso();
        // Setters
        void setNextEdge(Edge* edge);
        void setPeso(float peso); 

}; 

#endif // EDGE_H_INCLUDED