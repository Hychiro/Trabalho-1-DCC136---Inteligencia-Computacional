/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Grasp.h"
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

Cluster::Cluster(float peso, float limiteInferior, float limiteSuperior)
{
    this->peso = peso;
    this->limiteInferior = limiteInferior;
    this->limiteSuperior = limiteSuperior;

    this->first_node = nullptr;
    this->last_node = nullptr;
}

Cluster::Cluster(){
    this->peso = 0;
    this->limiteInferior = 0;
    this->limiteSuperior = 0;

    this->first_node = nullptr;
    this->last_node = nullptr;
}

Cluster::~Cluster()
{
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
    //pega o no na lista de nos
    Node *p = first_node;
    if (searchNode(id))
    {
        while (p != NULL && p->getId() != id)
        {
            p = p->getNextNode();
        }
        return p;
    }
    return p;
}


void Cluster::addNode(int id,float peso)
{
    // so cria o no e deixa ele no espaço
    Node *p = new Node(id);
    p->setWeight(peso);
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
    delete p;
}

void Cluster::addEdge(int id, int target_id, float peso)
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

        }
    }
}

void Cluster::addAresta(int id,Graph *grafo){

    Node *analisadoG;
    analisadoG=grafo->getNode(id);
    Node *analisadoC;
    analisadoC=getLastNode();
    for (Node *aux=getFirstNode();aux!=nullptr;aux=aux->getNextNode()){

        if(analisadoG->searchEdge(aux->getId())){//contenção de erro
        analisadoC->insertEdge(aux->getId(),analisadoG->searchEdgeWeight(aux->getId()));//inserir aresta
        aux->insertEdge(analisadoC->getId(),analisadoG->searchEdgeWeight(aux->getId()));
        }else{
            cout<<"DEU MERDA TA --add aresta "<<endl;
        }
    }

}

float Cluster::setPeso(float valor)
{
    this->peso = valor;
}

float Cluster::setLimiteInferior(float valor)
{
    this->limiteInferior = valor;
}

float Cluster::setLimiteSuperior(float valor)
{
    this->limiteSuperior = valor;
}

Node *Cluster::searchNode(int id)
{
    // so verifica se exste o no ali ou nao

    for (Node *p = this->first_node; p != NULL; p = p->getNextNode())
    {
        if (p->getId() == id)
        {
            return p;
        }
    }
    return nullptr;
}

bool Cluster::verificaAresta(int id, int target_id)
{
    Node *p = getNode(id);
    for (Edge *g = p->getFirstEdge(); g != NULL; g = g->getNextEdge())
    {

        if (g->getTargetId() == target_id)
        {
            return true;
        }
    }
    return false;
}
