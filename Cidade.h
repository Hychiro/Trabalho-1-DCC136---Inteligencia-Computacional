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
    int distancias[26];
    public:
    //getters
    Cidade();
    ~Cidade();
    int getid();
    char* getnome();
    int* getdistancias();
    //setters
    void setid(int id);
    void setnome(char* nome);
    void setdistancias(int* distancias);
};
#endif // EDGE_H_INCLUDED
