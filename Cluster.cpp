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

    this->next_node = nullptr;
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

Node *Cluster::getNextNode()
{

    return this->next_node;
}

void Cluster::setNextNode(Node *next_node)
{
    this->next_node = next_node;
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
