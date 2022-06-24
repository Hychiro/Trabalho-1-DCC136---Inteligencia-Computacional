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
#include "Node.h"
#include "Edge.h"
#include <thread>
#include <time.h>
#include <sstream>
#include <cstdlib>
#include <stdio.h>

using namespace std;

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

    for (int i = separator1; i < separator2; i++)
    {
        charAnalizado = (primeiraLinha[i]);
        clustersS = clustersS.append(charAnalizado);
    }

    for (int i = separator2; i < separator3; i++)
    {
        charAnalizado = (primeiraLinha[i]);
        tipoCluster = tipoCluster.append(charAnalizado);
    }
    for (int i = separator3; i < separator4; i++)
    {
        charAnalizado = (primeiraLinha[i]);
        limitesClusters = limitesClusters.append(charAnalizado);
    }
    for (int i = separator4 + 1; i < primeiraLinha.length(); i++)
    {
        charAnalizado = (primeiraLinha[i]);
        pesoNos = pesoNos.append(charAnalizado);
    }

    ordem = transformacaoS(ordemS);
    clusters = transformacaoS(clustersS);

    int limiteInferiorSuperior[clusters][2];

    int alturaDoTexto = 0;

    for (int i = 0; i < clusters; i++)
    {
        string aux = "";

        while (alturaDoTexto < limitesClusters.find_first_of(' ', alturaDoTexto) && alturaDoTexto < limitesClusters.length())
        {
            charAnalizado = (limitesClusters[alturaDoTexto]);
            aux = aux.append(charAnalizado);
            alturaDoTexto++;
        }
        int valor = transformacaoS(aux);

        limiteInferiorSuperior[i][0] = valor;

        aux = "";
        while (alturaDoTexto < limitesClusters.find_first_of(' ', alturaDoTexto) && alturaDoTexto < limitesClusters.length())
        {
            charAnalizado = (limitesClusters[alturaDoTexto]);
            aux = aux.append(charAnalizado);
            alturaDoTexto++;
        }
        valor = transformacaoS(aux);
        limiteInferiorSuperior[i][1] = valor;
    }

    alturaDoTexto = 0;
    int pesoVertice[ordem];

    for (int i = 0; i < ordem; i++)
    {
        string aux = "";

        while (alturaDoTexto < pesoNos.find_first_of(' ', alturaDoTexto) && alturaDoTexto < pesoNos.length())
        {
            charAnalizado = (pesoNos[alturaDoTexto]);
            aux = aux.append(charAnalizado);
            alturaDoTexto++;
        }
        int valor = transformacaoS(aux);

        pesoVertice[i] = valor;
    }
    ////

    int matrixPesoArestas[ordem][ordem];

    for (int k = 0; k < ordem; k++)
    {
        for (int j = 0; j < ordem; j++)
        {
            matrixPesoArestas[k][j] = -1;
        }
    }
    // Criando objeto grafo
    Graph *graph = new Graph(ordem, clusters);
    int coluna = 1;
    int linha = 0;
    // Leitura de arquivo
    while (input_file >> verticeA >> verticeB >> pesoAresta)
    {

        matrixPesoArestas[verticeA][verticeB] = pesoAresta;
        matrixPesoArestas[verticeB][verticeA] = pesoAresta;
    }

    for (int o = 0; o < ordem; o++)
    {
        for (int p = 0; p < ordem; p++)
        {
            if (!graph->verificaAresta(o, p))
            {
                graph->insertEdge(o, p, matrixPesoArestas[o][p]);
            }
        }
    }

    return graph;
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

int transformacaoC(char cAnalizada)
{
    int valor = cAnalizada - '0';

    return valor;
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1]  Algoritmo Guloso" << endl;
    cout << "[2] Algoritmo Guloso Randomizado" << endl;
    cout << "[3] Algoritmo Guloso Randomizado Reativo" << endl;
    cout << "[4] Printando o Grafo " << endl;
    cout << "[5] Densidade de Arestas do Grafo " << endl;
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

        output_file << "Algoritmo Guloso" << endl;

        Graph *novoGrafo = graph->guloso(output_file);

        Graph *ag = novoGrafo->agmPrim(output_file);
        output_file << "Quantidade minima de rotulos: " << ag->getNumRotulos() << endl;

        output_file << "tempo de execucao: " << (clock() - clo) << " millisegundos" << endl;
        ag->printGraph(output_file);
        break;
    }
    // Algoritmo Guloso Randomizado;
    case 2:
    {
        output_file << "Algoritmo Guloso Radomizado" << endl;

        float alfa;
        cout << "Digite o alfa:" << endl;
        cin >> alfa;

        int numdInteracoes;
        cout << "Digite o numero de Iteracoes:" << endl;
        cin >> numdInteracoes;
        srand((unsigned)time(NULL));

        // typedef std::chrono::high_resolution_clock Clock;
        // typedef std::chrono::milliseconds milliseconds;
        // Clock::time_point t0 = Clock::now();
        int clo = clock();

        Graph *novoGrafo = graph->gulosoRandomizadoAux(alfa, 0, numdInteracoes, output_file);
        output_file << "Iteracao do melhor Resultado: " << novoGrafo->melhorInstancia << endl;
        Graph *ag = novoGrafo->agmPrim(output_file);
        output_file << "Quantidade minima de rotulos usando alfa(" << alfa << "): " << ag->getNumRotulos() << endl;
        // Clock::time_point t1 = Clock::now();
        // milliseconds ms = std::chrono::duration_cast<milliseconds>(t1 - t0);
        output_file << "tempo de execucao: " << (clock() - clo) << " millisegundos" << endl;
        ag->printGraph(output_file);

        break;
    }
    // Algoritmo Guloso Radomizado Reativo
    case 3:
    {

        srand((unsigned)time(NULL));

        Graph *novoGrafo = graph->gulosoRandomizadoReativoAux(0, output_file);

        Graph *ag = novoGrafo->agmPrim(output_file);
        output_file << "Quantidade minima de rotulos para o conjunto de alfas digitado: " << ag->getNumRotulos() << endl;

        ag->printGraph(output_file);
        break;
    }

    case 4:
    {

        graph->printGraph(output_file);

        break;
    }
    case 5:
    {
        float arestas = (float)graph->getNumberEdges();
        float vertices = (float)graph->getOrder();
        float densidade = arestas / ((vertices * (vertices - 1)) / 2);
        output_file << "Densidade de Arestas do Grafo: " << densidade << endl;
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
        system("cls");
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
    if (input_file_name.find("v") <= input_file_name.size())
    {
        string instance = input_file_name.substr(input_file_name.find("v"));
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
