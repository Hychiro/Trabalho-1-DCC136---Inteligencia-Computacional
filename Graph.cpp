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

    this->first_Cluster = nullptr;
    this->last_Cluster = nullptr;
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
    insertAllClusters();
    Cluster *p;
    for (int i = 0; i < numClusters; i++)
    {
        p = getCluster(i);
        p->setLimiteSuperior(aux[i][1]);
        p->setLimiteInferior(aux[i][0]);
    }
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    delete next_node;
    this->first_node = nullptr;
    this->last_node = nullptr;
}

Cluster *Graph::getCluster(int id)
{
    Cluster *p = first_Cluster;
    if (searchCluster(id))
    {
        while (p != nullptr && p->getidCluster() != id)
        {
            p = p->getNextCluster();
        }
        return p;
    }
    return p;
}
Cluster *Graph::getClusterMelhorSol(int id)
{
    Cluster *p = first_Cluster2;
    if (searchClusterMelhorSol(id))
    {
        while (p != nullptr && p->getidCluster() != id)
        {
            p = p->getNextCluster();
        }
        return p;
    }
    return p;
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

            output_file << p->getId() << " -- " << aux->getTargetId() << "  [ label = " << aux->getPeso() << " ]" << endl;
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

bool Graph::clustersViaveis1()
{

    for (Cluster *i = this->first_Cluster; i != nullptr; i = i->getNextCluster())
    {
        if (!(i->viavel()))
        { // se o cluster n for viavel
            return false;
        }
    }

    int k = 0;
    for (int i = 0; i < this->getOrder(); i++)
    {
        if (this->listaDeNosLivres[i] == true)
        {
            k++;
        }
    }
    if (k > 0)
    {
        return false;
    }

    return true;
}

bool Graph::clustersViaveis2()
{
    Cluster *i;
    for (int k = 0; k < getNumCluster(); k++)
    {
        i = getCluster(k);
        if (!(i->viavel()))
        { // se o cluster n for viavel
            // cout << "Cluster "<<i->getidCluster()<< "inviavel"<<endl;
            return false;
        }
        // cout << "Cluster "<<i->getidCluster()<< "Viavel"<<endl;
    }

    return true;
}

bool Graph::clustersViaveis3()
{
    Cluster *i;
    for (int k = 0; k < getNumCluster(); k++)
    {
        i = getClusterMelhorSol(k);
        if (!(i->viavel()))
        { // se o cluster n for viavel
            // cout << "Cluster "<<i->getidCluster()<< "inviavel"<<endl;
            return false;
        }
        // cout << "Cluster "<<i->getidCluster()<< "Viavel"<<endl;
    }

    return true;
}

void Graph::insertAllClusters()
{
    for (int i = 0; i < this->numClusters; i++)
    {
        Cluster *p = new Cluster(i);
        Cluster *q = new Cluster(i);
        if (this->first_Cluster == nullptr)
        {
            this->first_Cluster = p;
            this->first_Cluster2 = q;
        }
        else
        {
            this->last_Cluster->setNextCluster(p);
            this->last_Cluster2->setNextCluster(q);
        }
        this->last_Cluster = p;
        this->last_Cluster2 = q;
    }
}

bool Graph::verificaAresta(int id, int target_id)
{
    Node *p = getNode(id);
    for (Edge *g = p->getFirstEdge(); g != nullptr; g = g->getNextEdge())
    {

        if (g->getTargetId() == target_id)
        {
            return true;
        }
    }
    return false;
}

void Graph::insertEdge(int id, int target_id, float peso)
{
    // junta os nos entre si
    if (searchNode(id)) //<-- ta sendo direcionado prestar atenção nisso.
    {

        if (!verificaAresta(id, target_id))
        {
            Node *p = getNode(id);
            Node *sup = getNode(target_id);
            p->insertEdge(target_id, peso);
            sup->insertEdge(id, peso);
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

bool Graph::searchCluster(int id)
{
    // so verifica se exste o no ali ou nao

    for (Cluster *p = this->first_Cluster; p != nullptr; p = p->getNextCluster())
    {
        if (p->getidCluster() == id)
        {
            return true;
        }
    }
    return false;
}
bool Graph::searchClusterMelhorSol(int id)
{
    // so verifica se exste o no ali ou nao

    for (Cluster *p = this->first_Cluster2; p != nullptr; p = p->getNextCluster())
    {
        if (p->getidCluster() == id)
        {
            return true;
        }
    }
    return false;
}

int Graph::getNumCluster()
{
    return this->numClusters;
}

void Graph::resetaClusters()
{
    Cluster *a;
    for (int i = 0; i < getNumCluster(); i++)
    {
        a = getCluster(i);
        a->setPeso(0);
        a->setNumNodes(0);

        Node *next_node = a->getFirstNode();
        // cout<<"entra aqui 1"<<endl;
        if (next_node != nullptr)
        {

            delete next_node;

            // cout<<"entra aqui 2"<<endl;
            a->setFirstNode(nullptr);
            a->setLastNode(nullptr);
        }
    }
}
void Graph::resetaClusterMelhorSol()
{
    Cluster *a;
    for (int i = 0; i < getNumCluster(); i++)
    {
        a = getClusterMelhorSol(i);
        a->setPeso(0);
        a->setNumNodes(0);

        Node *next_node = a->getFirstNode();
        // cout<<"entra aqui 1"<<endl;
        if (next_node != nullptr)
        {

            delete next_node;

            // cout<<"entra aqui 2"<<endl;
            a->setFirstNode(nullptr);
            a->setLastNode(nullptr);
        }
    }
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

void Graph::atualizaMelhorSolucao()
{
    Cluster *clusterLista1;
    Cluster *clusterLista2;

    for (int i = 0; i < this->numClusters; i++)
    {
        clusterLista1 = getCluster(i);
        clusterLista2 = getClusterMelhorSol(i);
        clusterLista2->setLimiteInferior(clusterLista1->getLimiteInferior());
        clusterLista2->setLimiteSuperior(clusterLista1->getLimiteSuperior());
        for (Node *p = clusterLista1->getFirstNode(); p != nullptr; p = p->getNextNode())
        {
            clusterLista2->addNode(p->getId(), p->getWeight());
        }
    }
}