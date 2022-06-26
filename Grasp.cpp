/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include "Grasp.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <string>
#include <bits/stdc++.h>

using namespace std;

void Grasp::Clusterizar(Graph *grafo)
{

    srand(time(NULL));

    this->Centroides(grafo);

    this->CompletarLI1(grafo);

    this->CompletarLS1(grafo);

    this->Completar(grafo);

    for(int i=0;i<grafo->getNumCluster();i++){
    cout<<"Cluster "<<i<<" Peso: "<<grafo->getCluster(i)->getPeso()<<endl;
    }
}

void Grasp::Centroides(Graph *grafo)
{
    int Ncentroides = 0;
    Ncentroides = grafo->getNumCluster();
    int Nvertices = 0;
    Nvertices = grafo->getOrder();
    int centroides[Ncentroides];

    for (int i = 0; i < Ncentroides; i++)
    { // sorteia os centroides
        centroides[i] = rand() % Nvertices;
    }
    for (int j = Ncentroides - 1; j > 0; j--)
    { // verifica se algum sorteio foi repetido
        for (int i = 0; i < j; i++)
        {
            while (centroides[j] == centroides[i])
            {
                centroides[j] = rand() % Nvertices;
            }
        }
    }

    for (int i = 0; i < Ncentroides; i++)
    {
        float aux = grafo->getNode(centroides[i])->getWeight();
        grafo->getCluster(i)->addNode(centroides[i], aux);
    }
}

void Grasp::CompletarLI1(Graph *grafo)
{
    int Nvertices = 0;
    Nvertices = grafo->getOrder();
    int Nclusters = 0;
    Nclusters = grafo->getNumCluster();
    Node *verticeAnalisado;
    Node *verticeAux;
    bool noLivreAnt[Nvertices];
    bool repete = false;
    for (int i = 0; i < Nvertices; i++)
    { // faz uma copia dos nos livres antes da iteração
        noLivreAnt[i] = grafo->listaDeNosLivres[i];
    }

    do
    {
        repete = false;
        for (int i = 0; i < Nvertices; i++)
        { // para todo nó 1 a 1

            if (grafo->listaDeNosLivres[i] == true)
            { // se o nó for livre

                float clustersViaveis[Nclusters];
                for (int p = 0; p < Nclusters; p++)
                {
                    clustersViaveis[p] = 0;
                }

                verticeAnalisado = grafo->getNode(i);

                for (Edge *arestaAnalisada = verticeAnalisado->getFirstEdge(); arestaAnalisada != nullptr; arestaAnalisada = arestaAnalisada->getNextEdge()) // verifica todos caminhos desse nó
                {
                    verticeAnalisado = grafo->getNode(arestaAnalisada->getTargetId());

                    for (int o = 0; o < Nclusters; o++) // para todos clusters
                    {
                        for (verticeAux = grafo->getCluster(o)->getFirstNode(); verticeAux != nullptr; verticeAux = verticeAux->getNextNode()) // para cada vertice nesse cluster
                        {
                            if (verticeAnalisado->getWeight() == verticeAux->getWeight()) // se for igual ao vertice analisado
                            {
                                if (grafo->getCluster(o)->getPeso() < grafo->getCluster(o)->getLimiteInferior()){ // se o peso do cluster for menor que o limite inferior
                                    clustersViaveis[o] = clustersViaveis[o] + arestaAnalisada->getPeso(); 
                                    //cout<<"Cluster "<<o<<" agora tem viabilidade: "<< clustersViaveis[o]<<endl; 
                                    }     
                            }
                        }
                    }
                }

                int melhorCluster = -1;
                int maiorValor = 0;
                for (int k = 0; k < Nclusters; k++)
                {
                    if (clustersViaveis[k] > maiorValor)
                    {
                        melhorCluster = k;
                        maiorValor = clustersViaveis[k];
                    }
                }
                if(melhorCluster==-1 || maiorValor==0){
                }else if (clustersViaveis[melhorCluster] > 0)
                {
                    float aux = grafo->getNode(i)->getWeight();
                    grafo->getCluster(melhorCluster)->addNode(i, aux); // adiciona o nó no cluster
                    grafo->getCluster(melhorCluster)->addAresta(i, grafo->getNode(i));
                    grafo->listaDeNosLivres[i] = false;
                }
            }
        }
        for (int i = 0; i < Nvertices; i++)
        { // faz uma copia dos nos livres apos a iteração
        noLivreAnt[i] = grafo->listaDeNosLivres[i];
        }

        for (int i = 0; i < Nvertices; i++)
        { // faz uma copia dos nos livres antes da iteração
            if (noLivreAnt[i] != grafo->listaDeNosLivres[i])
            { // se os nós livres mudaram em alguma maneira repete
                repete = true;
            }
        }
    } while (repete);
}

void Grasp::CompletarLS1(Graph *grafo)
{
    int Nvertices = 0;
    Nvertices = grafo->getOrder();
    int Nclusters = 0;
    Nclusters = grafo->getNumCluster();
    Node *verticeAnalisado;
    Node *verticeAux;
    bool noLivreAnt[Nvertices];
    bool repete = false;
    for (int i = 0; i < Nvertices; i++)
    { // faz uma copia dos nos livres antes da iteração
        noLivreAnt[i] = grafo->listaDeNosLivres[i];
    }

    do
    {
        repete = false;
        for (int i = 0; i < Nvertices; i++)
        { // para todo nó 1 a 1

            if (grafo->listaDeNosLivres[i] == true)
            { // se o nó for livre

                float clustersViaveis[Nclusters];
                for (int p = 0; p < Nclusters; p++)
                {
                    clustersViaveis[p] = 0;
                }

                verticeAnalisado = grafo->getNode(i);

                for (Edge *arestaAnalisada = verticeAnalisado->getFirstEdge(); arestaAnalisada != nullptr; arestaAnalisada = arestaAnalisada->getNextEdge()) // verifica todos caminhos desse nó
                {
                    verticeAnalisado = grafo->getNode(arestaAnalisada->getTargetId());

                    for (int o = 0; o < Nclusters; o++) // para todos clusters
                    {
                        for (verticeAux = grafo->getCluster(o)->getFirstNode(); verticeAux != nullptr; verticeAux = verticeAux->getNextNode()) // para cada vertice nesse cluster
                        {
                            if (verticeAnalisado->getWeight() == verticeAux->getWeight()) // se for igual ao vertice analisado
                            {
                                if ((grafo->getCluster(o)->getPeso() + grafo->getNode(i)->getWeight()) < grafo->getCluster(o)->getLimiteSuperior()) // se o peso do cluster + o peso da aresta for menor que o limite superior
                                    clustersViaveis[o] = clustersViaveis[o] + arestaAnalisada->getPeso(); 
                                         
                            }
                        }
                    }
                }

                int melhorCluster = -1;
                int maiorValor = 0;
                for (int k = 0; k < Nclusters; k++)
                {
                    if (clustersViaveis[k] > maiorValor)
                    {
                        melhorCluster = k;
                        maiorValor = clustersViaveis[k];
                    }
                }
                if(melhorCluster==-1 || maiorValor==0){
                }else if (clustersViaveis[melhorCluster] > 0)
                {
                    float aux = grafo->getNode(i)->getWeight();
                    grafo->getCluster(melhorCluster)->addNode(i, aux); // adiciona o nó no cluster
                    grafo->getCluster(melhorCluster)->addAresta(i, grafo->getNode(i));
                    grafo->listaDeNosLivres[i] = false;
                }
            }
        }
        for (int i = 0; i < Nvertices; i++)
        { // faz uma copia dos nos livres apos a iteração
        noLivreAnt[i] = grafo->listaDeNosLivres[i];
        }

        for (int i = 0; i < Nvertices; i++)
        { // faz uma copia dos nos livres antes da iteração
            if (noLivreAnt[i] != grafo->listaDeNosLivres[i])
            { // se os nós livres mudaram em alguma maneira repete
                repete = true;
            }
        }
    } while (repete);
}


void Grasp::Completar(Graph *grafo)
{
    int Nvertices = 0;
    Nvertices = grafo->getOrder();
    int Nclusters = 0;
    Nclusters = grafo->getNumCluster();
    Node *verticeAnalisado;
    Node *verticeAux;
    bool noLivreAnt[Nvertices];
    bool repete = false;
    for (int i = 0; i < Nvertices; i++)
    { // faz uma copia dos nos livres antes da iteração
        noLivreAnt[i] = grafo->listaDeNosLivres[i];
    }

    do
    {
        repete = false;
        for (int i = 0; i < Nvertices; i++)
        { // para todo nó 1 a 1

            if (grafo->listaDeNosLivres[i] == true)
            { // se o nó for livre
            cout<<"Aconteceu o improvavel"<<endl;

                bool clustersViaveis[Nclusters];
                for (int p = 0; p < Nclusters; p++)
                {
                    clustersViaveis[p] = false;
                }

                verticeAnalisado = grafo->getNode(i);

                for (Edge *arestaAnalisada = verticeAnalisado->getFirstEdge(); arestaAnalisada != nullptr; arestaAnalisada = arestaAnalisada->getNextEdge()) // verifica todos caminhos desse nó
                {
                    verticeAnalisado = grafo->getNode(arestaAnalisada->getTargetId());

                    for (int o = 0; o < Nclusters; o++) // para todos clusters
                    {
                        for (verticeAux = grafo->getCluster(o)->getFirstNode(); verticeAux != nullptr; verticeAux = verticeAux->getNextNode()) // para cada vertice nesse cluster
                        {
                            if (verticeAnalisado->getWeight() == verticeAux->getWeight()) // se for igual ao vertice analisado
                            {
                                clustersViaveis[o] = true; 
                                         
                            }
                        }
                    }
                }

                int melhorCluster = -1;
                int menorPeso = 10000000;
                for (int k = 0; k < Nclusters; k++)
                {
                    if (clustersViaveis[k] == true)
                    {
                        if(grafo->getCluster(k)->getPeso() < menorPeso){
                        melhorCluster = k;
                        menorPeso = grafo->getCluster(k)->getPeso();
                        }
                    }
                }
                if(melhorCluster==-1 || menorPeso == 10000000){
                }else if (clustersViaveis[melhorCluster] == true)
                {
                    float aux = grafo->getNode(i)->getWeight();
                    grafo->getCluster(melhorCluster)->addNode(i, aux); // adiciona o nó no cluster
                    grafo->getCluster(melhorCluster)->addAresta(i, grafo->getNode(i));
                    grafo->listaDeNosLivres[i] = false;
                }
            }
        }
        for (int i = 0; i < Nvertices; i++)
        { // faz uma copia dos nos livres apos a iteração
        noLivreAnt[i] = grafo->listaDeNosLivres[i];
        }

        for (int i = 0; i < Nvertices; i++)
        { // faz uma copia dos nos livres antes da iteração
            if (noLivreAnt[i] != grafo->listaDeNosLivres[i])
            { // se os nós livres mudaram em alguma maneira repete
                repete = true;
            }
        }
    } while (repete);
}