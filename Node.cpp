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
Node::Node(int id)
{

    this->id = id;
    this->in_degree = 0;
    this->out_degree = 0;
    this->first_edge = NULL;
    this->last_edge = NULL;
    this->next_node = NULL;
};

// Destructor
Node::~Node()
{
    if (this->next_node != nullptr)
    {
        // cout<<"entra aqui 1.1"<<endl;
        delete this->next_node;
        // cout<<"entra aqui 1.2"<<endl;
        next_node->removeAllEdges();
        // cout<<"entra aqui 1.3"<<endl;
        this->next_node = nullptr;
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

Node *Node::getNextNode()
{

    return this->next_node;
}

// Setters

void Node::setNextNode(Node *next_node)
{

    this->next_node = next_node;
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
void Node::insertEdge(int pn_fim,int pn_inicio, float kmTotal, float duracaoInspecao, float tMaxInspecao, float tMinInspecao, float ultimainspecao)
{
    // Verifies whether there are at least one edge in the node
    if (this->first_edge != NULL)
    {
        // Allocating the new edge and keeping the integrity of the edge list
        Edge *edge = new Edge(pn_fim, pn_inicio);
        edge->setkmTotal(kmTotal);
        edge->setduracaoInspecao(duracaoInspecao);
        edge->settMaxInspecao(tMaxInspecao);
        edge->settMinInspecao(tMinInspecao);
        edge->setultimainspecao(ultimainspecao);
        this->last_edge->setNextEdge(edge);
        this->last_edge = edge;
    }
    else
    {
        // Allocating the new edge and keeping the integrity of the edge list
        this->first_edge = new Edge(pn_fim, pn_inicio);
        this->first_edge->setkmTotal(kmTotal);
        this->first_edge->setduracaoInspecao( duracaoInspecao);
        this->first_edge->settMaxInspecao(tMaxInspecao);
        this->first_edge->settMinInspecao(tMinInspecao);
        this->first_edge->setultimainspecao(ultimainspecao);
        this->last_edge = this->first_edge;
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
        while (aux->getTargetId() != id)
        {

            previous = aux;
            aux = aux->getNextEdge();
        }
        // Keeping the integrity of the edge list
        if (previous != NULL)
            previous->setNextEdge(aux->getNextEdge());

        else
            this->first_edge = aux->getNextEdge();

        if (aux == this->last_edge)
            this->last_edge = previous;

        if (aux->getNextEdge() == this->last_edge)
            this->last_edge = aux->getNextEdge();

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
        for (Edge *aux = this->first_edge; aux != NULL; aux = aux->getNextEdge())
            if (aux->getTargetId() == target_id)
                return true;
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

    for (Edge *auxEdge = this->first_edge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
    {
        if (auxEdge->getTargetId() == target_id)
            return auxEdge;
    }
    return nullptr;
}
