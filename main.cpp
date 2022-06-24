/*
Hiero Henrique Barcelos Costa 202065136A
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

Graph *leituraInstancia(ifstream &input_file, ofstream &output_file)
{

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

    // Criando objeto grafo
    Graph *grafo = new Graph(ordem, clusters);

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

    for (int i = 0; i < clusters; i++)
    {
        grafo->getCluster(i).setLimiteInferior(limiteInferiorSuperior[i][0]);

        grafo->getCluster(i).setLimiteSuperior(limiteInferiorSuperior[i][1]);
    }
    alturaDoTexto = 0;
    int pesoVertice[ordem];

    for (int i = 0; i < ordem; i++)
    {
        string aux = "";

        while (alturaDoTexto < pesoNos.find_first_of(' ', alturaDoTexto) && alturaDoTexto < pesoNos.length())
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
        cout << "verticeA " << verticeA << " verticeB " << verticeB << " pesoAresta " << pesoAresta << endl;
        matrixPesoArestas[verticeA][verticeB] = pesoAresta;
        matrixPesoArestas[verticeB][verticeA] = pesoAresta;
    }

    for (int o = 0; o < ordem; o++)
    {
        for (int p = 0; p < ordem; p++)
        {
            if (!grafo->verificaAresta(o, p) && o!=p)
            {
                grafo->insertEdge(o, p, matrixPesoArestas[o][p]);
            }
        }
    }

    return grafo;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Teste Unico" << endl;
    cout << "[2] 10 repetições" << endl;
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
        int clo = clock();
        graph->printGraph(output_file);
        output_file << "tempo de execucao: " << (clock() - clo) << " millisegundos" << endl;

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
    if (argc != 3)
    {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file>" << endl;
        return 1;
    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if (input_file_name.find("_") <= input_file_name.size())
    {
        string instance = input_file_name.substr(0, input_file_name.find(""));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    // Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    Graph *graph;

    if (input_file.is_open())
    {

        graph = leituraInstancia(input_file, output_file);
    }
    else
        cout << "Unable to open " << argv[1];

    mainMenu(output_file, graph);

    // Fechando arquivo de entrada
    input_file.close();

    // Fechando arquivo de saída
    output_file.close();

    return 0;
}
