/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/
/*
Matheus Cardoso Faesy 202065065A
*/
#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int pn_fim;
        int pn_inicio;
        Edge* next_edge;
        float kmTotal;
        float duracaoInspecao;
        float tMaxInspecao;
        float tMinInspecao;
        int ultimainspecao;

    public:
        // Constructor
        Edge(int pn_fim,int pn_inicio);
        // Destructor
        ~Edge();
        // Getters
        int getpn_fim();
        int getpn_inicio();
        float getkmTotal();
        float getduracaoInspecao();
        float gettMaxInspecao();
        float gettMinInspecao();
        float getultimainspecao();
        int getTargetId();
        Edge* getNextEdge();
        // Setters
        void setpn_fim(int pn_fim);
        void setpn_inicio(int pn_inicio);
        void setkmTotal(float kmTotal);
        void setduracaoInspecao(float duracaoInspecao);
        void settMaxInspecao(float tMaxInspecao);
        void settMinInspecao(float tMinInspecao);
        void setultimainspecao(float ultimainspecao);
        void setNextEdge(Edge* edge);
        ; 

}; 

#endif // EDGE_H_INCLUDED