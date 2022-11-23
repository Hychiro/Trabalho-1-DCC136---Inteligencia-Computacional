/*
Hiero Henrique Barcelos Costa 202065136A
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
Graph::Graph(int order, int numClusters, int aux[][2])
{

    this->order = order;

    this->first_node = nullptr;
    this->last_node = nullptr;
    this->number_edges = 0;
    this->melhorInstancia = -1;
    this->numClusters = numClusters;

    this->listaDeNosLivres = new bool[order];

    for (int i = 0; i < order; i++)
    {
        listaDeNosLivres[i] = true;
    }
    insertAllNodes();
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    delete next_node;
    this->first_node = nullptr;
    this->last_node = nullptr;
}

void Graph::printGraph(ofstream &output_file)
{
    Node *p = this->first_node;
    Edge *aux = p->getFirstEdge();

    output_file << "strict graph{" << endl;
    while (p != nullptr)
    {

        aux = p->getFirstEdge();
        while (aux != nullptr)
        {

            output_file << p->getId() << " -- " << aux->getTargetId() << endl;
            aux = aux->getNextEdge();
        }
        p = p->getNextNode();
    }
    output_file << "}" << endl;
}

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

void Graph::insertNode(int id)
{
    // so cria o no e deixa ele no espaço
    Node *p = new Node(id);
    if (this->first_node == nullptr)
    {
        this->first_node = p;
    }
    else
    {
        this->last_node->setNextNode(p);
    }
    this->last_node = p;
    this->last_node->setNextNode(nullptr);
    this->order++;
    // delete p;
}
void Graph::insertAllNodes()
{
    for (int i = 0; i < this->order; i++)
    {
        Node *p = new Node(i);
        if (this->first_node == nullptr)
        {
            this->first_node = p;
        }
        else
        {
            this->last_node->setNextNode(p);
        }
        this->last_node = p;
    }
}



bool Graph::verificaAresta(int id, int pn_fim)
{
    Node *p = getNode(id);
    for (Edge *g = p->getFirstEdge(); g != nullptr; g = g->getNextEdge())
    {

        if (g->getTargetId() == pn_fim)
        {
            return true;
        }
    }
    return false;
}

void Graph::insertEdge(int id, int pn_fim,int pn_inicio,int kmTotal,int duracaoInspecao,int tMaxInspecao,int tMinInspecao,int ultimainspecao)
{
    // junta os nos entre si
    if (searchNode(id)) //<-- ta sendo direcionado prestar atenção nisso.
    {

        if (!verificaAresta(id, pn_fim))
        {
            Node *p = getNode(id);
            Node *sup = getNode(pn_fim);
            p->insertEdge(pn_fim,pn_inicio, kmTotal, duracaoInspecao, tMaxInspecao, tMinInspecao, ultimainspecao);
            sup->insertEdge(pn_fim,pn_inicio,kmTotal, duracaoInspecao, tMaxInspecao, tMinInspecao, ultimainspecao);
            this->number_edges += 1;
        }
    }
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

            while (p != previousN->getNextNode())
            {
                previousN->getNextNode();
            }
            nextN = p->getNextNode();

            previousN->setNextNode(nextN);
            if (previousN->getNextNode() == nullptr)
            {
                last_node = previousN;
            }

            for (Node *i = first_node; i != nullptr; i->getNextNode())
            {
                Edge *k = i->getFirstEdge();
                while (k != nullptr)
                {
                    sup = k;
                    k->getNextEdge();

                    if (k->getTargetId() == p->getId())
                    {
                        sup->setNextEdge(k->getNextEdge());
                        k = nullptr;
                        k = sup->getNextEdge();
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

    for (Node *p = this->first_node; p != nullptr; p = p->getNextNode())
    {
        if (p->getId() == id)
        {
            return true;
        }
    }
    return false;
}

Node *Graph::getNode(int id)
{
    // pega o no na lista de nos
    Node *p = first_node;
    if (searchNode(id))
    {
        while (p != nullptr && p->getId() != id)
        {
            p = p->getNextNode();
        }
        return p;
    }
    return p;
}
