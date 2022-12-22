/**************************************************************************************************
 * Implementation of the TAD Edge
**************************************************************************************************/
/*
Matheus Cardoso Faesy 202065065A
*/
#ifndef EDGE_H_INCLUDED
#define EDGE_H_INCLUDED

#include <string>
#include <iostream>
using namespace std;

// Definition of the Edge class
class Edge{

    // Attributes
    private:
        int pn_fim;
        int pn_inicio;
        Edge* prox_edge;
        Edge* ant_edge;
        float kmTotal;
        float duracaoInspecao;
        float tMaxInspecao;
        float tMinInspecao;
        int ultimainspecao;
        bool bidirecional;
        char regiao[30];
        char ramal[40];

    public:
        int id;
        // Constructor
        Edge(int pn_inicio,int pn_fim,int id);
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
        Edge* getproxEdge();
        Edge* getantEdge();
        bool is_bidirecional(){return this->bidirecional;}
        char* getRegiao(){return this->regiao;}
        char* getRamal(){return this->ramal;}
        // Setters
        void setRegiao(string a){for(int i=0;i<30;i++){this->regiao[i]=a[i];}}
        void setRamal(string a){for(int i=0;i<40;i++){this->ramal[i]=a[i];}}
        void setpn_fim(int pn_fim);
        void setpn_inicio(int pn_inicio);
        void setkmTotal(float kmTotal);
        void setduracaoInspecao(float duracaoInspecao);
        void settMaxInspecao(float tMaxInspecao);
        void settMinInspecao(float tMinInspecao);
        void setultimainspecao(float ultimainspecao);
        void setproxEdge(Edge* edge);
        void setantEdge(Edge* edge);
        void setdirecao(bool direcao){this->bidirecional=direcao;}
        ; 

}; 

#endif // EDGE_H_INCLUDED