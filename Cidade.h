/*
Matheus Cardoso Faesy 202065065A
*/
#ifndef CIDADE_H_INCLUDED
#define CIDADE_H_INCLUDED

using namespace std;

class Cidade{
// Attributes
    private:
    int id;
    char nome[30];
    float distancias[26];
    Cidade *prox_cidade;
    Cidade *ant_cidade;
    public:
    //getters
    Cidade();
    ~Cidade();
    int getid();
    char* getnome();
    float* getdistancias();
    Cidade* get_prox_cidade(){
        return this->prox_cidade;
    };
    Cidade* get_ant_cidade(){
        return this->ant_cidade;
    };
    //setters
    void set_ant_Cidade(Cidade *a){
        this->ant_cidade=a;
    };
    void set_prox_Cidade(Cidade *a){
        this->prox_cidade=a;
    };
    void setid(int id);
    void setnome(char* nome);
    void setdistancias(float* distancias);
};
#endif // EDGE_H_INCLUDED
