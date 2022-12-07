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

using namespace std;

int transformacaoC(char cAnalizada)
{
    int valor = cAnalizada - '0';

    return valor;
}

int transformacaoS(string sAnalizada)
{
    int tam = sAnalizada.length();
    int valor = 0;

    for (int i = 0; i < sAnalizada.length(); i++)
    {
        valor = valor + transformacaoC(sAnalizada[i]) * pow(10, tam - 1);
        tam--;
    }
    return valor;
}

template<typename T>
int nthSubstrg(int n, const basic_string<T>& s,
               const basic_string<T>& p,
               bool repeats = false) {
   string::size_type i = s.find(p);
   string::size_type adv = (repeats) ? 1 : p.length();

   int j;
   for (j = 1; j < n && i != basic_string<T>::npos; ++j)
      i = s.find(p, i+adv);

   if (j == n)
     return(i);
   else
     return(-1);
}

Graph *leituraInstancia(ifstream &input_file, ofstream &output_file) // Leitura dos Dados
{
    string primeiraLinha = "";

    string regiao;
    string ramal;
    string aux_km_in;
    float km_in;
    string aux_km_fim;
    float km_fim;
    string pn_in;
    string pn_fim;
    string aux_km_total;
    float km_total;
    string aux_low_ciclo;
    float low_ciclo;
    string aux_upper_ciclo;
    float upper_ciclo;
    string aux_ultimainspecao;
    float ultimainspecao;
    string aux_dia_ultimainspecao;
    float dia_ultimainspecao;
    string aux_mes_ultimainspecao;
    float mes_ultimainspecao;
    string aux_ano_ultimainspecao;
    float ano_ultimainspecao;
    string sentido;
    string cidade_in;
    string cidade_fim;
    string hotel_in;
    string hotel_fim;

    string aux_t_hotel_in;
    string aux_t_min_hotel_in;
    string aux_t_hor_hotel_in;
    float t_min_hotel_in;
    float t_hor_hotel_in;

    string aux_t_hotel_fim;
    string aux_t_min_hotel_fim;
    string aux_t_hor_hotel_fim;
    float t_min_hotel_fim;
    float t_hor_hotel_fim;

    string aux_t_inspecao;
    string aux_t_hor_inspecao;
    float t_hor_inspecao;
    string aux_t_min_inspecao;
    float t_min_inspecao;

    string parametro_virgula = ",";
    string parametro_barra = "/";
    string parametro_doispontos = ":";

    string charAnalizado;

    int contador_linha = 0;

    while (getline(input_file, primeiraLinha, '\n'))
    {
        if(contador_linha==0){
            contador_linha++;
        }else{

        regiao = "";
        ramal = "";
        aux_km_in = "";
        km_in = 0;
        aux_km_fim = "";
        km_fim = 0;
        pn_in = "";
        pn_fim = "";
        aux_km_total = "";
        km_total = 0;
        aux_low_ciclo = "";
        low_ciclo = 0;
        aux_upper_ciclo = "";
        upper_ciclo = 0;
        aux_ultimainspecao="";
        ultimainspecao = 0;
        aux_dia_ultimainspecao = "";
        dia_ultimainspecao = 0;
        aux_mes_ultimainspecao = "";
        mes_ultimainspecao = 0;
        aux_ano_ultimainspecao = "";
        ano_ultimainspecao = 0;
        sentido = "";
        cidade_in = "";
        cidade_fim = "";
        hotel_in = "";
        hotel_fim = "";

        aux_t_hotel_in= "";
        aux_t_min_hotel_in= "";
        aux_t_hor_hotel_in= "";
        t_min_hotel_in= 0;
        t_hor_hotel_in= 0;

        aux_t_hotel_fim= "";
        aux_t_min_hotel_fim= "";
        aux_t_hor_hotel_fim= "";
        t_min_hotel_fim= 0;
        t_hor_hotel_fim= 0;
        
        string aux_t_inspecao = "";
        aux_t_hor_inspecao = "";
        t_hor_inspecao = 0;
        aux_t_min_inspecao = "";
        t_min_inspecao = 0;

        charAnalizado = "";

        for (int i = 0; i < nthSubstrg(1,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
            regiao = regiao.append(charAnalizado);
        }

        for (int i = nthSubstrg(1,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(2,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           ramal = ramal.append(charAnalizado);
        }

        for (int i = nthSubstrg(2,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(3,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           aux_km_in = aux_km_in.append(charAnalizado);
        }
        km_in = strtof(aux_km_in.c_str(),nullptr);

        for (int i = nthSubstrg(3,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(4,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           aux_km_fim = aux_km_fim.append(charAnalizado);
        }
        km_fim = strtof(aux_km_fim.c_str(),nullptr);

        for (int i = nthSubstrg(4,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(5,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           pn_in = pn_in.append(charAnalizado);
        }

        for (int i = nthSubstrg(5,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(6,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           pn_fim = pn_fim.append(charAnalizado);
        }

        for (int i = nthSubstrg(6,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(7,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           aux_km_total = aux_km_total.append(charAnalizado);
        }
        km_total = strtof(aux_km_total.c_str(),nullptr);

        for (int i = nthSubstrg(7,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(8,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           aux_low_ciclo = aux_low_ciclo.append(charAnalizado);
        }
        low_ciclo = strtof(aux_low_ciclo.c_str(),nullptr);

        for (int i = nthSubstrg(8,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(9,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           aux_upper_ciclo = aux_upper_ciclo.append(charAnalizado);
        }
        upper_ciclo = strtof(aux_upper_ciclo.c_str(),nullptr);



        for (int i = nthSubstrg(9,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(10,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
           aux_ultimainspecao = aux_ultimainspecao.append(charAnalizado);
        }
        for (int i = 0; i < nthSubstrg(1,aux_ultimainspecao, parametro_barra); i++)
        {
            charAnalizado = (aux_ultimainspecao[i]);
           aux_dia_ultimainspecao = aux_dia_ultimainspecao.append(charAnalizado);
        }
        dia_ultimainspecao = strtof(aux_dia_ultimainspecao.c_str(),nullptr);
        for (int i = nthSubstrg(1,aux_ultimainspecao, parametro_barra)+1; i < nthSubstrg(2,aux_ultimainspecao, parametro_barra); i++)
        {
            charAnalizado = (aux_ultimainspecao[i]);
           aux_mes_ultimainspecao = aux_mes_ultimainspecao.append(charAnalizado);
        }
        mes_ultimainspecao = strtof(aux_mes_ultimainspecao.c_str(),nullptr);
        for (int i = nthSubstrg(2,aux_ultimainspecao, parametro_barra)+1; i < aux_ultimainspecao.size(); i++)
        {
            charAnalizado = (aux_ultimainspecao[i]);
           aux_ano_ultimainspecao = aux_ano_ultimainspecao.append(charAnalizado);
        }
        ano_ultimainspecao = strtof(aux_ano_ultimainspecao.c_str(),nullptr);



        for (int i = nthSubstrg(10,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(11,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          sentido = sentido.append(charAnalizado);
        }

        for (int i = nthSubstrg(11,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(12,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          cidade_in = cidade_in.append(charAnalizado);
        }

        for (int i = nthSubstrg(12,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(13,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          cidade_fim = cidade_fim.append(charAnalizado);
        }

        for (int i = nthSubstrg(13,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(14,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          hotel_in = hotel_in.append(charAnalizado);
        }

        for (int i = nthSubstrg(14,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(15,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          hotel_fim = hotel_fim.append(charAnalizado);
        }


        for (int i = nthSubstrg(17,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(18,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          aux_t_hotel_in = aux_t_hotel_in.append(charAnalizado);
        }
        for (int i = 0; i < nthSubstrg(1,aux_t_hotel_in, parametro_doispontos); i++)
        {
            charAnalizado = (aux_t_hotel_in[i]);
           aux_t_hor_hotel_in = aux_t_hor_hotel_in.append(charAnalizado);
        }
        t_hor_hotel_in = strtof(aux_t_hor_hotel_in.c_str(),nullptr);
        for (int i = nthSubstrg(1,aux_t_hotel_in, parametro_doispontos)+1; i < aux_t_hotel_in.size(); i++)
        {
            charAnalizado = (aux_t_hotel_in[i]);
           aux_t_min_hotel_in = aux_t_min_hotel_in.append(charAnalizado);
        }
        t_min_hotel_in = strtof(aux_t_min_hotel_in.c_str(),nullptr);



        for (int i = nthSubstrg(18,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(19,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          aux_t_hotel_fim = aux_t_hotel_fim.append(charAnalizado);
        }
        for (int i = 0; i < nthSubstrg(1,aux_t_hotel_fim, parametro_doispontos); i++)
        {
            charAnalizado = (aux_t_hotel_fim[i]);
           aux_t_hor_hotel_fim = aux_t_hor_hotel_fim.append(charAnalizado);
        }
        t_hor_hotel_fim = strtof(aux_t_hor_hotel_fim.c_str(),nullptr);
        for (int i = nthSubstrg(1,aux_t_hotel_fim, parametro_doispontos)+1; i < aux_t_hotel_fim.size(); i++)
        {
            charAnalizado = (aux_t_hotel_fim[i]);
           aux_t_min_hotel_fim = aux_t_min_hotel_fim.append(charAnalizado);
        }
        t_min_hotel_fim = strtof(aux_t_min_hotel_fim.c_str(),nullptr);



        for (int i = nthSubstrg(20,primeiraLinha, parametro_virgula)+1; i < nthSubstrg(21,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
          aux_t_inspecao = aux_t_inspecao.append(charAnalizado);
        }
        for (int i = 0; i < nthSubstrg(1,aux_t_inspecao, parametro_doispontos); i++)
        {
            charAnalizado = (aux_t_inspecao[i]);
           aux_t_hor_inspecao = aux_t_hor_inspecao.append(charAnalizado);
        }
        t_hor_inspecao = strtof(aux_t_hor_inspecao.c_str(),nullptr);
        if(t_hor_inspecao==12){
            t_hor_inspecao=0;
        }
        for (int i = nthSubstrg(1,aux_t_inspecao, parametro_doispontos)+1; i < aux_t_inspecao.size(); i++)
        {
            charAnalizado = (aux_t_inspecao[i]);
           aux_t_min_inspecao = aux_t_min_inspecao.append(charAnalizado);
        }
        t_min_inspecao = strtof(aux_t_min_inspecao.c_str(),nullptr);





        contador_linha++;
        }
    }

    return NULL;
}

void aux_leituraInstancia2(float* distancias, int coluna,string linhaAtual){

    string charAnalizado="";
    string parametro_virgula=",";
    string aux_dist="";
    if(coluna==25){
        for (int i = nthSubstrg(coluna+1,linhaAtual, parametro_virgula)+1; i < linhaAtual.size(); i++)
        {
            charAnalizado = (linhaAtual[i]);
            aux_dist = aux_dist.append(charAnalizado);
        }
        distancias[coluna] = strtof(aux_dist.c_str(),nullptr);
    }

    for (int i = nthSubstrg(coluna+1,linhaAtual, parametro_virgula)+1; i < nthSubstrg(coluna+2,linhaAtual, parametro_virgula); i++)
        {
            charAnalizado = (linhaAtual[i]);
            aux_dist = aux_dist.append(charAnalizado);
        }
        distancias[coluna] = strtof(aux_dist.c_str(),nullptr);

}

Graph *leituraInstancia2(ifstream &input_file, ofstream &output_file)
{
    string primeiraLinha ="";
    int contador_linha = 0;
    string parametro_virgula =",";
    string charAnalizado= "";
    string cidade_nome ="";

    string aux_dist;
    float distancias[26];

    while (getline(input_file, primeiraLinha, '\n'))
    {
        if(contador_linha==0){

        }else{
        for(int i=0;i<26;i++){distancias[i]=0;}
        aux_dist="";
        cidade_nome ="";

            for (int i = 0; i < nthSubstrg(1,primeiraLinha, parametro_virgula); i++)
        {
            charAnalizado = (primeiraLinha[i]);
            cidade_nome = cidade_nome.append(charAnalizado);
        }
            for(int coluna=0;coluna<26;coluna++){
            aux_leituraInstancia2(distancias, coluna,primeiraLinha);
            }


            cout<<"Distancias "<<cidade_nome<<":"<<endl;
            for(int i=0;i<26;i++){
               cout<<distancias[i]<<" ; ";
                }
                cout<<endl;


        }
        contador_linha++;
    }
    
    return NULL;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Executar" << endl;
    cout << "[2] Menus de Testes Especificos" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionar(int selecao, Graph *graph, ofstream &output_file)
{
    switch (selecao)
    {
    // Algoritmo Guloso;
    case 1:
    {
        break;
    }
    // Algoritmo Guloso Randomizado;
    case 2:
    {
        break;
    }

    default:
    {
        cout << " Error!!! invalid option!!" << endl;
    }
    }
}

int mainMenu(ofstream &output_file, Graph *graph)
{

    int selecao = 1;

    while (selecao != 0)
    {
        // system("cls");
        selecao = menu();

        if (output_file.is_open())
            selecionar(selecao, graph, output_file);

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;
    }

    return 0;
}

int main(int argc, char const *argv[])
{

    // Verificação se todos os parâmetros do programa foram entrados
    if (argc != 4)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file_Dados> <input_file_cidades> <output_file>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_Dados(argv[1]);
    string input_file_cidades(argv[2]);

    string instance;

    // Abrindo arquivo de entrada
    ifstream input_file1;
    ifstream input_file2;
    ofstream output_file;
    input_file1.open(argv[1], ios::in);
    input_file2.open(argv[2], ios::in);
    output_file.open(argv[3], ios::out | ios::trunc);

    Graph *graph;

    if (input_file1.is_open())
    {
        graph = leituraInstancia(input_file1, output_file);
    }
    else
        cout << "Unable to open " << argv[1];
    input_file1.close();

    if (input_file2.is_open())
    {
        graph = leituraInstancia2(input_file2, output_file);
    }
    else
        cout << "Unable to open " << argv[2];

    input_file2.close();

    // mainMenu(output_file, graph);

    // Fechando arquivo de saída
    output_file.close();

    return 0;
}
