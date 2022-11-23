/*
Matheus Cardoso Faesy 202065065A
*/
#include "Veiculo.h"
#include <iostream>

using namespace std;

// Constructor
Veiculo::Veiculo(){

}

// Destructor
Veiculo::~Veiculo(){

}

//getters
int Veiculo::getid(){
return this->id;
}
int Veiculo::getidNoAtual(){
return this->idNoAtual;
}
int Veiculo::getkmDaUltimaInspecao(){
return this->kmDaUltimaInspecao;
}
int Veiculo::gettDaultimaInspecaoSemestral(){
return this->tDaultimaInspecaoSemestral;
}
int Veiculo::gettDaultimaInspecaoAnual(){
return this->tDaultimaInspecaoAnual;
}
int Veiculo::gettDaultimaFeria(){
return this->tDaultimaFeria;
}
//setters

void Veiculo::setid(int id){
this->id=id;
}
void Veiculo::setidNoAtual(int idNoAtual){
this->idNoAtual=idNoAtual;
}
void Veiculo::setkmDaUltimaInspecao(int kmDaUltimaInspecao){
this->kmDaUltimaInspecao=kmDaUltimaInspecao;
}
void Veiculo::settDaultimaInspecaoSemestral(int tDaultimaInspecaoSemestral){
this->tDaultimaInspecaoSemestral=tDaultimaInspecaoSemestral;
}
void Veiculo::settDaultimaInspecaoAnual(int tDaultimaInspecaoAnual){
this->tDaultimaInspecaoAnual=tDaultimaInspecaoAnual;
}
void Veiculo::settDaultimaFeria(int tDaultimaFeria){
this->tDaultimaFeria=tDaultimaFeria;
}