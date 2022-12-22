/*
Matheus Cardoso Faesy 202065065A
*/
#include "Cidade.h"
#include <iostream>

using namespace std;

// Constructor
Cidade::Cidade(){


}

// Destructor
Cidade::~Cidade(){

}

//getters
    int Cidade::getid(){
        return this->id;
    }
    char* Cidade::getnome(){
        return this->nome;
    }
    float* Cidade::getdistancias(){
        return this->distancias;
    }
//setters
    void Cidade::setid(int id){
        this->id=id;
    }
    void Cidade::setnome(char* nome){
        for(int i=0;i<30;i++){
            this->nome[i]=nome[i];
        }
    }
    void Cidade::setdistancias(float* distancias){
        for(int i=0;i<26;i++){
            this->distancias[i]=distancias[i];
        }
    }