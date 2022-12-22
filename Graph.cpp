/*
Matheus Cardoso Faesy 202065065A
*/
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>

using namespace std;

/**************************************************************************************************
 * Defining the Graph's methods
 **************************************************************************************************/

// Constructor
Graph::Graph()
{
    this->first_node = nullptr;
    this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    delete next_node;
    this->first_node = nullptr;
    this->last_node = nullptr;
}

/// cometando pois get target id não existe
/*void Graph::printGraph(ofstream &output_file)
{
    Node *p = this->first_node;
    Edge *aux = p->getFirstEdge();

    output_file << "strict graph{" << endl;
    while (p != nullptr)
    {

        aux = p->getFirstEdge();
        while (aux != nullptr)
        {

            output_file << p->getId() << " -- " << aux->getpn_fim() << endl;
            aux = aux->getNextEdge();
        }
        p = p->getProxNode();
    }
    output_file << "}" << endl;
}*/

// Getters

int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{
    return this->number_edges / 2;
}
// Function that verifies if the graph is directed

Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/

// implementacao abaixo:

void Graph::insertNode()
{
    // so cria o no e deixa ele no espaço
    Node *p = new Node();
    if (this->first_node == NULL)
    {
        p->setAntNode(NULL);
        p->setProxNode(NULL);
        p->setid(0);
        this->first_node = p;
        this->last_node = p;
    }
    else
    {
        p->setProxNode(NULL);
        p->setAntNode(this->last_node);
        this->last_node->setProxNode(p);
        this->last_node = p;
        p->setid(p->getAntNode()->getId() + 1);
    }
    this->order++;
}

bool Graph::verificaAresta(int id, int pn_fim)
{
    Node *p = getNode(id);

    for (Edge *aux = p->getFirstEdge(); aux != NULL; aux = aux->getproxEdge())
    {
        if (aux->getpn_fim() == pn_fim)
            return true;
    }
    return false;
}

void Graph::removeNode(int id) // pfv dps me ajudem a revisar esse removeNode
{
    Node *p;
    if (this->last_node != nullptr)
    {
        if (this->first_node == this->last_node)
        {
            this->first_node = nullptr;
            p = nullptr;
        }
        else
        {
            Node *previousN = this->first_node;
            Node *nextN;
            Node *aux;
            Edge *sup;
            int count_edges = 0;

            p = getNode(id);

            while (p != previousN->getProxNode())
            {
                previousN->getProxNode();
            }
            nextN = p->getProxNode();

            previousN->getProxNode();
            if (previousN->getProxNode() == nullptr)
            {
                last_node = previousN;
            }

            for (Node *i = first_node; i != nullptr; i->getProxNode())
            {
                Edge *k = i->getFirstEdge();
                while (k != nullptr)
                {
                    sup = k;
                    k->getproxEdge();

                    if (k->getpn_fim() == p->getId())
                    {
                        sup->setproxEdge(k->getproxEdge());
                        k = nullptr;
                        k = sup->getproxEdge();
                    }
                }
            }

            p->removeAllEdges();
            p = nullptr;
        }
        order--;
    }
    else
        cout << "ERRO: o grafo esta vazio!" << endl;
}

bool Graph::searchNode(int id)
{
    // so verifica se exste o no ali ou nao

    for (Node *p = this->first_node; p != nullptr; p = p->getProxNode())
    {
        if (p->getId() == id)
        {
            return true;
        }
    }
    return false;
}

Node* Graph::searchNode_ByID(int id)
{
    // so verifica se exste o no ali ou nao

    for (Node *p = this->first_node; p != nullptr; p = p->getProxNode())
    {
        if (p->getId() == id)
        {
            return p;
        }
    }
    return NULL;
}

Node *Graph::getNode(int id)
{
    // pega o no na lista de nos
    Node *p = first_node;
    if (searchNode(id))
    {
        while (p != nullptr && p->getId() != id)
        {
            p = p->getProxNode();
        }
        return p;
    }
    return p;
}

Node *Graph::searchNode_ByNome(string nome)
{

    for (Node *a = this->first_node; a != NULL; a = a->getProxNode())
    {
        for (int i = 0; i < nome.size(); i++)
        {
            if (a->getNome()[i] == nome[i])
            {
            }
            else
            {
                break;
            }

            if (i == nome.size()-1)
            {
                return a;
            }
        }
    }
    return NULL;
}
