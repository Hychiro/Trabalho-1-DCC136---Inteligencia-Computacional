/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
/**************************************************************************************************

**************************************************************************************************/

#ifndef INSTANCIA_H_INCLUDED
#define INSTANCIA_H_INCLUDED
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Instancia
{
private:
    int idCluster;
    int idNo;
    float melhorInstancia;

public:
    Instancia(){
        this->idCluster = 0;
        this->idNo = 0;
        this->melhorInstancia = 0;
    };

    ~Instancia();

    int getIdCluster(){
        return  this->idCluster;
    };
    int getIdNo(){
        return  this->idNo;
    };
    float getMelhorInstancia(){
        return  this->melhorInstancia;
    };

    void setInstancia(int idCluster, int idNo, float melhorInstancia)
    {
        this->idCluster = idCluster;
        this->idNo = idNo;
        this->melhorInstancia = melhorInstancia;
    };
};
#endif // INSTANCIA_H_INCLUDED