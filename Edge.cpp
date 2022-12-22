/*
Matheus Cardoso Faesy 202065065A
*/
#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Edge's methods
**************************************************************************************************/

// Constructor
Edge::Edge(int pn_inicio, int pn_fim,int id){

    this->id=id;
    this->pn_fim = pn_fim;
    this->pn_inicio = pn_inicio;
    this->prox_edge = NULL;
    this->ant_edge = NULL;
    this->kmTotal=0;
    this->duracaoInspecao=0;
    this->tMaxInspecao=0;
    this->tMinInspecao=0;
    this->ultimainspecao=0;

}

// Destructor
Edge::~Edge(){

    if (this->prox_edge != nullptr){
        delete this->prox_edge;
        this->prox_edge = nullptr;
    }

}

// Getters
int Edge::getpn_fim(){

    return this->pn_fim;

}

int Edge::getpn_inicio(){

    return this->pn_inicio;

}

Edge* Edge::getproxEdge(){

    return this->prox_edge;

}

Edge* Edge::getantEdge(){

    return this->ant_edge;

}

float Edge::getkmTotal(){
return this->kmTotal;
}
float Edge::getduracaoInspecao(){
return this->duracaoInspecao;
}
float Edge::gettMaxInspecao(){
return this->tMaxInspecao;
}
float Edge::gettMinInspecao(){
return this->tMinInspecao;
}
float Edge::getultimainspecao(){
return this->ultimainspecao;
}

// Setters
void Edge::setproxEdge(Edge* edge){

    this->prox_edge = edge;

}

void Edge::setantEdge(Edge* edge){

    this->ant_edge = edge;

}

void Edge::setpn_fim(int pn_fim){
    this->pn_fim=pn_fim;
}

void Edge::setpn_inicio(int pn_inicio){
this->pn_inicio=pn_inicio;
}

void Edge::setkmTotal(float kmTotal){
this->kmTotal = kmTotal;
}
void Edge::setduracaoInspecao(float duracaoInspecao){
this->duracaoInspecao = duracaoInspecao;
}
void Edge::settMaxInspecao(float tMaxInspecao){
this->tMaxInspecao = tMaxInspecao;
}
void Edge::settMinInspecao(float tMinInspecao){
this->tMinInspecao = tMinInspecao;
}
void Edge::setultimainspecao(float ultimainspecao){
this->ultimainspecao = ultimainspecao;
}

