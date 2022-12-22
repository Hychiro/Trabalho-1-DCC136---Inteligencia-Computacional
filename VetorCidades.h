/*
Matheus Cardoso Faesy 202065065A
*/
#ifndef VetorCidades_H_INCLUDED
#define VetorCidades_H_INCLUDED

#include "Cidade.h"
#include <iostream>

using namespace std;

class VetorCidades{
// Attributes
    private:

    Cidade *prim_cidade;
    Cidade *ultima_cidade;
    public:
    VetorCidades(){
        this->prim_cidade=NULL;
        this->ultima_cidade=NULL;
    };

    void Adiciona_Cidade(string nome,float* distancias){

    Cidade *a=new Cidade;
    char b[30];

    for(int i=0;i<30;i++){
            b[i]=nome[i];
        }
    a->setnome(b);

    a->setdistancias(distancias);

    if(this->prim_cidade==NULL){
        a->setid(0);
        a->set_prox_Cidade(NULL);
        a->set_ant_Cidade(NULL);
        this->prim_cidade=a;
        this->ultima_cidade=a;
        }else{
        a->set_prox_Cidade(NULL);
        this->ultima_cidade->set_prox_Cidade(a);
        a->set_ant_Cidade(this->ultima_cidade);
        this->ultima_cidade=a;
        a->setid(a->get_ant_cidade()->getid()+1);
        }
    };

    Cidade* get_prim_cidade(){
        return this->prim_cidade;
    };

    Cidade* get_ultima_cidade(){
        return this->ultima_cidade;
    };
};
    
#endif 

