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

bool verificaTipoLeitura(string input_file_name)
{
    if (input_file_name[2] >= '0' && input_file_name[2] <= '9')
    {
        return false;
    }
    return true;
}

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

Graph *leituraInstancia(ifstream &input_file, ofstream &output_file)
{
    /*

    // Variáveis para auxiliar na criação dos nós no Grafo

    int ordem;
    int clusters;

    float pesoAresta;
    int verticeA;
    int verticeB;
    int separator1 = 0;
    int separator2 = 0;
    int separator3 = 0;
    int separator4 = 0;
    string tipoCluster = "";
    string primeiraLinha = "";
    string ordemS = "";
    string clustersS = "";
    string charAnalizado = "";
    string limitesClusters = "";
    string pesoNos = "";
    // Pegando a ordem do grafo

    getline(input_file, primeiraLinha, '\n');

    separator1 = primeiraLinha.find_first_of(' ');
    separator4 = primeiraLinha.find_first_of('W');
    separator2 = primeiraLinha.find_first_of(' ', separator1 + 1);
    separator3 = primeiraLinha.find_first_of(' ', separator2 + 1);

    for (int i = 0; i < separator1; i++)
    {
        charAnalizado = (primeiraLinha[i]);
        ordemS = ordemS.append(charAnalizado);
    }

    for (int i = separator1 + 1; i < separator2; i++)
    {
        charAnalizado = (primeiraLinha[i]);

        clustersS = clustersS.append(charAnalizado);
    }

    for (int i = separator2; i < separator3; i++)
    {
        charAnalizado = (primeiraLinha[i]);
        tipoCluster = tipoCluster.append(charAnalizado);
    }
    cout << "tipoCluster" << tipoCluster << endl;
    for (int i = separator3; i < separator4; i++)
    {
        charAnalizado = (primeiraLinha[i]);
        limitesClusters = limitesClusters.append(charAnalizado);
    }
    cout << "limitesClusters" << limitesClusters << endl;
    for (int i = separator4 + 1; i < primeiraLinha.length(); i++)
    {
        charAnalizado = (primeiraLinha[i]);
        pesoNos = pesoNos.append(charAnalizado);
    }
    cout << "pesoNos" << pesoNos << endl;
    ordem = transformacaoS(ordemS);

    clusters = transformacaoS(clustersS);

    int limiteInferiorSuperior[clusters][2];

    int alturaDoTexto = 0;

    for (int i = 0; i < clusters; i++)
    {
        string aux = "";

        while (alturaDoTexto <= limitesClusters.find_first_of(' ', alturaDoTexto) && alturaDoTexto < limitesClusters.length())
        {
            charAnalizado = (limitesClusters[alturaDoTexto]);

            if (charAnalizado != " ")
            {
                aux = aux.append(charAnalizado);
                alturaDoTexto++;
            }
            else if (alturaDoTexto == 0 && charAnalizado == " ")
            {
                alturaDoTexto++;
            }
            else
            {
                alturaDoTexto++;
                break;
            }
        }

        int valor = transformacaoS(aux);
        limiteInferiorSuperior[i][0] = valor;

        aux = "";
        while (alturaDoTexto <= limitesClusters.find_first_of(' ', alturaDoTexto) && alturaDoTexto < limitesClusters.length())
        {
            charAnalizado = (limitesClusters[alturaDoTexto]);

            if (charAnalizado != " ")
            {
                aux = aux.append(charAnalizado);
                alturaDoTexto++;
            }
            else
            {
                alturaDoTexto++;
                break;
            }
        }

        valor = transformacaoS(aux);
        limiteInferiorSuperior[i][1] = valor;
    }

    // Criando objeto grafo
    Graph *grafo = new Graph(ordem, clusters, limiteInferiorSuperior);
    alturaDoTexto = 0;
    int pesoVertice[ordem];

    for (int i = 0; i < ordem; i++)
    {
        string aux = "";

        while (alturaDoTexto <= pesoNos.find_first_of(' ', alturaDoTexto) && alturaDoTexto < pesoNos.length())
        {
            charAnalizado = (pesoNos[alturaDoTexto]);
            if (charAnalizado != " ")
            {
                aux = aux.append(charAnalizado);
                alturaDoTexto++;
            }
            else if (alturaDoTexto == 0 && charAnalizado == " ")
            {
                alturaDoTexto++;
            }
            else
            {
                alturaDoTexto++;
                break;
            }
        }
        int valor = transformacaoS(aux);

        pesoVertice[i] = valor;
    }

    for (int i = 0; i < ordem; i++)
    {
        // cout<<"pesoVertice "<<i<<": "<<pesoVertice[i]<<endl;
        grafo->getNode(i)->setWeight(pesoVertice[i]);
    }
    ////

    float matrixPesoArestas[ordem][ordem];

    for (int k = 0; k < ordem; k++)
    {
        for (int j = 0; j < ordem; j++)
        {
            matrixPesoArestas[k][j] = -1;
        }
    }

    int coluna = 1;
    int linha = 0;
    // Leitura de arquivo

    while (input_file >> verticeA >> verticeB >> pesoAresta)
    {
        // cout << "verticeA " << verticeA << " verticeB " << verticeB << " pesoAresta " << pesoAresta << endl;
        matrixPesoArestas[verticeA][verticeB] = pesoAresta;
        matrixPesoArestas[verticeB][verticeA] = pesoAresta;
    }

    for (int o = 0; o < ordem; o++)
    {
        for (int p = 0; p < ordem; p++)
        {
            if (!grafo->verificaAresta(o, p) && o != p)
            {
                grafo->insertEdge(o, p, matrixPesoArestas[o][p]);
            }
        }
    }

    for (int i = 0; i < grafo->getOrder(); i++)
    {
        // cout<<"Peso do No "<<i<<": "<<grafo->getNode(i)->getWeight()<<endl;
    }

    return grafo;
    */
}

Graph *leituraInstancia2(ifstream &input_file, ofstream &output_file)
{
 /*
    // Variáveis para auxiliar na criação dos nós no Grafo

    int ordem;
    int clusters;
    float limiteSClusters;
    int limiteIClusters = 0;
    float pesoAresta;

    // Pegando a ordem do grafo

    input_file >> ordem;
    input_file >> clusters;
    input_file >> limiteSClusters;

    cout << "Ordem: " << ordem << endl;
    cout << "Numero de clusters: " << clusters << endl;
    cout << "Limite Superior dos Clusters: " << limiteSClusters << endl;

    float pesoNos[ordem];

    for (int i = 0; i < ordem; i++)
    {
        input_file >> pesoNos[i];
    }
    cout << "Peso Nos: " << endl;
    for (int i = 0; i < ordem; i++)
    {
        cout << pesoNos[i] << " ";
    }
    cout << endl;

    float matrixPesoArestas[ordem][ordem];

    for (int k = 0; k < ordem; k++)
    {
        for (int j = 0; j < ordem; j++)
        {
            matrixPesoArestas[k][j] = -1;
        }
    }

    for (int k = 0; k < ordem; k++)
    {
        for (int j = 0; j < ordem; j++)
        {
            input_file >> matrixPesoArestas[k][j];
        }
    }

    for (int k = 0; k < ordem; k++)
    {
        for (int j = 0; j < ordem; j++)
        {
            input_file >> matrixPesoArestas[k][j];
        }
    }

    int limiteInferiorSuperior[clusters][2];

    for (int i = 0; i < clusters; i++)
    {
        limiteInferiorSuperior[i][0] = 0;
        limiteInferiorSuperior[i][1] = limiteSClusters;
    }

    // Criando objeto grafo
    Graph *grafo = new Graph(ordem, clusters, limiteInferiorSuperior);

    for (int i = 0; i < ordem; i++)
    {
        // cout<<"pesoVertice "<<i<<": "<<pesoVertice[i]<<endl;
        grafo->getNode(i)->setWeight(pesoNos[i]);
    }
    ////
    // Leitura de arquivo

    for (int o = 0; o < ordem; o++)
    {
        for (int p = 0; p < ordem; p++)
        {
            if (!grafo->verificaAresta(o, p) && o != p)
            {
                grafo->insertEdge(o, p, matrixPesoArestas[o][p]);
            }
        }
    }

    for (int i = 0; i < grafo->getOrder(); i++)
    {
        // cout<<"Peso do No "<<i<<": "<<grafo->getNode(i)->getWeight()<<endl;
    }

    return grafo; */
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
    if (argc != 6)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file_cidades> <input_file_vias> <input_file_PN> <input_file_veiculos> <output_file>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_cidades(argv[1]);
    string input_file_vias(argv[2]);
    string input_file_PN(argv[3]);
    string input_file_veiculos(argv[4]);

    string instance;

    // Abrindo arquivo de entrada
    ifstream input_file1;
    ifstream input_file2;
    ifstream input_file3;
    ifstream input_file4;
    ofstream output_file;
    input_file1.open(argv[1], ios::in);
    input_file2.open(argv[2], ios::in);
    input_file3.open(argv[3], ios::in);
    input_file4.open(argv[4], ios::in);
    output_file.open(argv[5], ios::out | ios::trunc);

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

    if (input_file3.is_open())
    {
            graph = leituraInstancia(input_file3, output_file);
    }
    else
        cout << "Unable to open " << argv[3];
        input_file3.close();

    if (input_file4.is_open())
    {
            graph = leituraInstancia(input_file4, output_file);
    }
    else
        cout << "Unable to open " << argv[4];
        input_file4.close();

    mainMenu(output_file, graph);

    // Fechando arquivo de saída
    output_file.close();

    return 0;
}
