/*
Matheus Cardoso Faesy 202065065A
*/


#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include "Edge.h" // Include of the Edge class
#include <string>

using namespace std;

// Definition of the Node class
class Node{

    // Attributes
    private:
        Edge* first_edge;
        Edge* last_edge;
        int id;
        char nome[40];
        float km;
        char cidade[20];
        char hotel[20];
        int tempoHotel;
        unsigned int in_degree;
        unsigned int out_degree;
        Node* prox_node;
        Node* ant_node;

    public:
        // Constructor
        Node();
        // Destructor
        ~Node();
        // Getters
        Edge* getFirstEdge();
        Edge* getLastEdge();
        int getId();
        int getInDegree();
        int getOutDegree();
        Node* getProxNode();
        Node* getAntNode();
        char* getNome(){return this->nome;};
        float get_km(){return this->km;}
        char* getCidade(){return this->cidade;};
        char* getHotel(){return this->hotel;};
        int get_tempoHotel(){return this->tempoHotel;}
        // Setters
        void set_tempoHotel(int a){this->tempoHotel=a;}
        void setHotel(string a){for(int i=0;i<20;i++){this->hotel[i]=a[i];}};
        void setCidade(string a){for(int i=0;i<20;i++){this->cidade[i]=a[i];}};
        void set_km(float a){this->km=a;};
        void setNome(string a){for(int i=0;i<40;i++){this->nome[i]=a[i];}}
        void setid(int id){this->id=id;};
        void setProxNode(Node* node);
        void setAntNode(Node* node);
        void setFirstEdge(Edge* edge);
        void setLastEdge(Edge* edge);
        // Other methods
        bool searchEdge(int target_id);
        void insertEdge(int pn_inicio,int pn_fim, float kmTotal, float duracaoInspecao, float tMaxInspecao, float tMinInspecao, float ultimainspecao,int id,string ramal,string regiao);
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
