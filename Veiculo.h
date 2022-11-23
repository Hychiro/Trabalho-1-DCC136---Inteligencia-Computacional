/*
Matheus Cardoso Faesy 202065065A
*/
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include <thread>
#include <time.h>
#include <sstream>
#include <cstdlib>
#include <stdio.h>

#ifndef VEICULO_H_INCLUDED
#define VEICULO_H_INCLUDED

using namespace std;

class Veiculo{
// Attributes
    private:
        int id;
        int idNoAtual;
        int kmDaUltimaInspecao;
        int tDaultimaInspecaoSemestral;
        int tDaultimaInspecaoAnual;
        int tDaultimaFeria;
        list<Node> proximosPn;

    public:
//getters
    int getid();
    int getidNoAtual();
    int getkmDaUltimaInspecao();
    int gettDaultimaInspecaoSemestral();
    int gettDaultimaInspecaoAnual();
    int gettDaultimaFeria();
//setters
    void setid(int id);
    void setidNoAtual(int idNoAtual);
    void setkmDaUltimaInspecao(int kmDaUltimaInspecao);
    void settDaultimaInspecaoSemestral(int tDaultimaInspecaoSemestral);
    void settDaultimaInspecaoAnual(int tDaultimaInspecaoAnual);
    void settDaultimaFeria(int tDaultimaFeria);


    
};
#endif // EDGE_H_INCLUDED