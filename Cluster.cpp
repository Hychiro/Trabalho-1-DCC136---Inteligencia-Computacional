/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
#include "Cluster.h"
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

Cluster::Cluster(int id, float limiteInferior, float limiteSuperior)
{
    this->idCluster = id;
    this->peso = 0;
    this->limiteInferior = limiteInferior;
    this->limiteSuperior = limiteSuperior;
    this->numNodes = 0;
    this->first_node = nullptr;
    this->last_node = nullptr;
}

Cluster::Cluster(int id)
{
    this->idCluster = id;
    this->peso = 0;
    this->limiteInferior = 0;
    this->limiteSuperior = 0;
    this->numNodes = 0;
    this->first_node = nullptr;
    this->last_node = nullptr;
}
Cluster::~Cluster()
{
}

Cluster *Cluster::getNextCluster()
{

    return this->nextCluster;
}

void Cluster::setNextCluster(Cluster *next_Cluster)
{

    this->nextCluster = next_Cluster;
}

float Cluster::getPeso()
{
    return this->peso;
}

float Cluster::getLimiteInferior()
{
    return this->limiteInferior;
}

float Cluster::getLimiteSuperior()
{
    return this->limiteSuperior;
}

Node *Cluster::getFirstNode()
{

    return this->first_node;
}

Node *Cluster::getLastNode()
{
    return this->last_node;
}

Node *Cluster::getNode(int id)
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

int Cluster::getNumNodes()
{
    return this->numNodes;
}

void Cluster::addNode(int id, float peso)
{
    // so cria o no e deixa ele no espaço
    Node *p = new Node(id);
    p->setWeight(peso);
    setPeso(getPeso() + peso);
    this->numNodes++;
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
    //delete p;
}

bool Cluster::viavel()
{
    if (this->peso > this->limiteSuperior)
    {
        return false;
    }

    if (this->peso < this->limiteInferior)
    {
        return false;
    }

    return true;
}

float Cluster::calculaQualidade()
{
    float valor = 0;
    for (Node *i = this->first_node; i != nullptr; i = i->getNextNode())
    {
        for (Edge *j = i->getFirstEdge(); j != nullptr; j = j->getNextEdge())
        {
            valor = valor + j->getPeso();
        }
    }
    return valor / 2;
}

void Cluster::addEdge(int id, int target_id, float peso)
{
    // junta os nos entre si

    Node *p = getNode(id);
    Node *sup = getNode(target_id);
    p->insertEdge(target_id, peso);
    sup->insertEdge(id, peso);
}

void Cluster::removeNode(int id) // pfv dps me ajudem a revisar esse removeNode
{
    this->peso = this->peso - this->getNode(id)->getWeight();

    Node *p = getNode(id);
    Node *previousN = this->first_node;
    Node *nextN;
    Edge *previousE;
    Edge *nextE;
    int count_edges = 0;
    this->numNodes--;
    bool verify = false;


    for (Node *i = this->getFirstNode(); i != nullptr; i = i->getNextNode())
    {
        //cout<<"remove node 1"<<endl;
        Edge *aux = i->getFirstEdge();
        if (i->getLastEdge() != nullptr)
        {
            //cout<<"remove node 2"<<endl;

            if (i->getFirstEdge() == i->getLastEdge() && aux->getTargetId() == p->getId())
            {
                //cout<<"remove node 3"<<endl;
                aux=nullptr;
                i->setFirstEdge(nullptr);
                i->setLastEdge(nullptr);
            }
            else if (i->getFirstEdge()->getTargetId() == p->getId())
            {
                //cout<<"remove node 4"<<endl;
                nextE = aux->getNextEdge();
                //cout<<"remove node 4.1"<<endl;
                i->setFirstEdge(nextE);
                //cout<<"remove node 4.2"<<endl;
                aux->setNextEdge(nullptr);
                //cout<<"remove node 4.3"<<endl;
                aux=nullptr;
                //cout<<"remove node 4.4"<<endl;
            }
            else
            {
                //cout<<"remove node 5"<<endl;
                while (aux != nullptr)
                {
                    if (aux->getTargetId() == p->getId())
                    {
                        verify = true;
                        break;
                    }
                    previousE = aux;
                    aux = aux->getNextEdge();
                }
                if (verify)
                {
                    //cout<<"remove node 6"<<endl;
                    nextE = aux->getNextEdge();

                    previousE->setNextEdge(nextE);
                    if (nextE == nullptr)
                    {
                        i->setLastEdge(previousE);
                    }
                    aux->setNextEdge(nullptr);
                    aux=nullptr;
                }
                verify = false;
            }
            // last edg

            //delete aux;
        }
    }
    //cout<<"remove node 7"<<endl;

    if (this->last_node != nullptr)
    {
        //cout<<"remove node 8"<<endl;
        if (this->first_node == this->last_node)
        {

            this->first_node = nullptr;
            delete p;
        }
        else if (this->getFirstNode() == p)
        {
            nextN = p->getNextNode();
            this->first_node = nextN;
            p->setNextNode(nullptr);
            delete p;
        }
        else
        {
            //cout<<"remove node 9"<<endl;

            while (p != previousN->getNextNode())
            {
                previousN = previousN->getNextNode();
            }
            nextN = p->getNextNode();

            previousN->setNextNode(nextN);
            if (nextN == nullptr)
            {
                last_node = previousN;
            }
            p->setNextNode(nullptr);
            delete p;
           // cout<<"remove node 10"<<endl;
        }
        //cout<<"remove node 11"<<endl;
    }
    else
        cout << "ERRO: o grafo esta vazio!" << endl;

        //cout<<"remove node 12"<<endl;
}



void Cluster::addAresta(int id, Node *analisado)
{

    for (Node *p = this->getFirstNode(); p != nullptr; p = p->getNextNode())
    {
        Edge *aux = analisado->hasEdgeBetween(p->getId());
        if (aux != nullptr)
        {
            addEdge(id, p->getId(), aux->getPeso());
        }
    }
}

void Cluster::setPeso(float valor)
{
    this->peso = valor;
}

void Cluster::setLimiteInferior(float valor)
{
    this->limiteInferior = valor;
}

void Cluster::setLimiteSuperior(float valor)
{
    this->limiteSuperior = valor;
}

void Cluster::setFirstNode(Node *node)
{
    this->first_node = node;
}

void Cluster::setLastNode(Node *node)
{
    this->last_node = node;
}

bool Cluster::searchNode(int id)
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

bool Cluster::verificaAresta(int id, int target_id)
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
