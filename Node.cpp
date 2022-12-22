/*
Matheus Cardoso Faesy 202065065A
*/
#include "Node.h"
#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Node's methods
 **************************************************************************************************/

// Constructor
Node::Node()
{
    this->in_degree = 0;
    this->out_degree = 0;
    this->first_edge = NULL;
    this->last_edge = NULL;
    this->prox_node = NULL;
    this->ant_node = NULL;
};

// Destructor
Node::~Node()
{
    if (this->prox_node != nullptr)
    {
        // cout<<"entra aqui 1.1"<<endl;
        delete this->prox_node;
        // cout<<"entra aqui 1.2"<<endl;
        prox_node->removeAllEdges();
        // cout<<"entra aqui 1.3"<<endl;
        this->prox_node = nullptr;
    }
};

// Getters
Edge *Node::getFirstEdge()
{

    return this->first_edge;
}

Edge *Node::getLastEdge()
{

    return this->last_edge;
}

int Node::getId()
{

    return this->id;
}

int Node::getInDegree()
{

    return this->in_degree;
}

int Node::getOutDegree()
{

    return this->out_degree;
}

Node *Node::getProxNode()
{

    return this->prox_node;
}

Node *Node::getAntNode()
{

    return this->ant_node;
}

// Setters

void Node::setProxNode(Node *next_node)
{

    this->prox_node = next_node;
}

void Node::setAntNode(Node *next_node)
{

    this->ant_node = next_node;
}

void Node::setFirstEdge(Edge *edge)
{
    this->first_edge = edge;
}
void Node::setLastEdge(Edge *edge)
{
    this->last_edge = edge;

}

// Other methods


void Node::insertEdge(int pn_inicio,int pn_fim, float kmTotal, float duracaoInspecao, float tMaxInspecao, float tMinInspecao, float ultimainspecao,int id,string ramal,string regiao)
{
    // Verifies whether there are at least one edge in the node
    if (this->first_edge != NULL)
    {
        // Allocating the new edge and keeping the integrity of the edge list
        Edge *edge = new Edge(pn_inicio, pn_fim,id);
        edge->setkmTotal(kmTotal);
        edge->setduracaoInspecao(duracaoInspecao);
        edge->settMaxInspecao(tMaxInspecao);
        edge->settMinInspecao(tMinInspecao);
        edge->setultimainspecao(ultimainspecao);
        edge->setRamal(ramal);
        edge->setRegiao(regiao);

        this->last_edge->setproxEdge(edge); 

        edge->setantEdge(this->last_edge);
        edge->setproxEdge(NULL);
        this->last_edge = edge;
    }
    else
    {
        // Allocating the new edge and keeping the integrity of the edge list
        this->first_edge = new Edge(pn_inicio, pn_fim,id);
        this->first_edge->setkmTotal(kmTotal);
        this->first_edge->setduracaoInspecao( duracaoInspecao);
        this->first_edge->settMaxInspecao(tMaxInspecao);
        this->first_edge->settMinInspecao(tMinInspecao);
        this->first_edge->setultimainspecao(ultimainspecao);
        this->first_edge->setRamal(ramal);
        this->first_edge->setRegiao(regiao);
        this->last_edge = this->first_edge;

        this->last_edge->setproxEdge(NULL);
        this->last_edge->setantEdge(NULL);
    }
}

void Node::removeAllEdges()
{
    // Verifies whether there are at least one edge in the node
    if (this->first_edge != nullptr)
    {
        // cout<<"entra aqui 1.2.1"<<endl;
        Edge *aux = this->first_edge;
        // cout<<"entra aqui 1.2.2"<<endl;
        //  Removing all edges of the node
        delete aux;
        // cout<<"entra aqui 1.2.3"<<endl;
    }

    this->first_edge = nullptr;
    this->last_edge = nullptr;
}

int Node::removeEdge(int id, bool directed, Node *target_node)
{
    // Verifies whether the edge to remove is in the node
    if (this->searchEdge(id))
    {

        Edge *aux = this->first_edge;
        Edge *previous = NULL;
        // Searching for the edge to be removed
        while (aux->getpn_fim()!= id)
        {

            previous = aux;
            aux = aux->getproxEdge();
        }
        // Keeping the integrity of the edge list
        if (previous != NULL)
            previous->setproxEdge(aux->getproxEdge());

        else
            this->first_edge = aux->getproxEdge();

        if (aux == this->last_edge)
            this->last_edge = previous;

        if (aux->getproxEdge() == this->last_edge)
            this->last_edge = aux->getproxEdge();

        delete aux;
        // Verifies whether the graph is directed
        if (directed)
            this->decrementOutDegree();

        else
        {

            this->decrementInDegree();
            target_node->decrementInDegree();
        }

        return 1;
    }

    return 0;
}

bool Node::searchEdge(int target_id)
{
    // Verifies whether there are at least one edge in the node
    if (this->first_edge != NULL)
    {
        // Searching for a specific edge of target id equal to target id
        for (Edge *aux = this->first_edge; aux != NULL; aux = aux->getproxEdge()){
            if (aux->getpn_fim() == target_id)
                return true;
            if(aux->is_bidirecional() == true){
                if(aux->getpn_inicio() == target_id){
                    return true;
                }
            }
        }
    }

    return false;
}

void Node::incrementInDegree()
{

    this->in_degree++;
}

void Node::incrementOutDegree()
{

    this->out_degree++;
}

void Node::decrementInDegree()
{

    this->in_degree--;
}

void Node::decrementOutDegree()
{

    this->out_degree--;
}

Edge *Node::hasEdgeBetween(int target_id)
{

    for (Edge *aux = this->first_edge; aux != NULL; aux = aux->getproxEdge()){
            if (aux->getpn_fim() == target_id)
                return aux;
            if(aux->is_bidirecional() == true){
                if(aux->getpn_inicio() == target_id){
                    return aux;
                }
            }
        }
    return nullptr;
}
