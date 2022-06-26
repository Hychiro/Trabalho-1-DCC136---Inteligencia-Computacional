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

    bool repetir = true;
    do
    {
        this->Centroides(grafo);
        this->CompletarLI1(grafo);
        repetir = true;
        if (grafo->clustersViaveis2())
        {
            repetir = false;
        }

    } while (repetir);

    this->CompletarLS1(grafo);

    this->Completar(grafo);

    this->imprime(grafo);

    this->ajuste(grafo);

    this->imprime(grafo);
}

void Grasp::imprime(Graph *grafo)
{

    cout << endl;
    for (int i = 0; i < grafo->getNumCluster(); i++)
    {
        cout << "Cluster " << i << " Nos : ";
        for (Node *a = grafo->getCluster(i)->getFirstNode(); a != nullptr; a = a->getNextNode())
        {
            cout << a->getId() << ", ";
        }
        cout << " Peso: " << grafo->getCluster(i)->getPeso() << "    Qualidade = " << grafo->getCluster(i)->calculaQualidade() << endl;
    }
    cout << endl;
}

void Grasp::Centroides(Graph *grafo)
{
    int Ncentroides = 0;
    Ncentroides = grafo->getNumCluster();
    int Nvertices = 0;
    Nvertices = grafo->getOrder();
    int centroides[Ncentroides];

    int i = 0, igual;
    do
    {
        centroides[i] = rand() % Nvertices;
        igual = 0;
        for (int j = 0; j < i; j++)
        {
            if (centroides[i] == centroides[j])
            {
                igual = 1;
            }
        }

        if (igual == 0)
            i++;
    } while (i < Ncentroides);

    for (int i = 0; i < Ncentroides; i++)
    {
        float aux = grafo->getNode(centroides[i])->getWeight();
        grafo->getCluster(i)->addNode(centroides[i], aux);
        grafo->listaDeNosLivres[centroides[i]] = false;
    }
}

void Grasp::verticesRandom(Graph *grafo)
{
    int ordemVertices[grafo->getOrder()];
    int i = 0, igual;
    do
    {
        ordemVertices[i] = rand() % grafo->getOrder();
        igual = 0;
        for (int j = 0; j < i; j++)
        {
            if (ordemVertices[i] == ordemVertices[j])
            {
                igual = 1;
            }
        }

        if (igual == 0)
            i++;
    } while (i < grafo->getOrder());
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

        int ordemVertices[grafo->getOrder()];
        int i = 0, igual;
        do
        {
            ordemVertices[i] = rand() % grafo->getOrder();
            igual = 0;
            for (int j = 0; j < i; j++)
            {
                if (ordemVertices[i] == ordemVertices[j])
                {
                    igual = 1;
                }
            }

            if (igual == 0)
                i++;
        } while (i < grafo->getOrder());

        for (int i = 0; i < Nvertices; i++)
        { // para todo nó 1 a 1

            if (grafo->listaDeNosLivres[ordemVertices[i]] == true)
            { // se o nó for livre

                float clustersViaveis[Nclusters];
                for (int p = 0; p < Nclusters; p++)
                {
                    clustersViaveis[p] = 0;
                }

                verticeAnalisado = grafo->getNode(ordemVertices[i]);

                for (Edge *arestaAnalisada = verticeAnalisado->getFirstEdge(); arestaAnalisada != nullptr; arestaAnalisada = arestaAnalisada->getNextEdge()) // verifica todos caminhos desse nó
                {
                    verticeAnalisado = grafo->getNode(arestaAnalisada->getTargetId());

                    for (int o = 0; o < Nclusters; o++) // para todos clusters
                    {
                        for (verticeAux = grafo->getCluster(o)->getFirstNode(); verticeAux != nullptr; verticeAux = verticeAux->getNextNode()) // para cada vertice nesse cluster
                        {
                            if (verticeAnalisado->getId() == verticeAux->getId()) // se for igual ao vertice analisado
                            {
                                if (grafo->getCluster(o)->getPeso() < grafo->getCluster(o)->getLimiteInferior())
                                { // se o peso do cluster for menor que o limite inferior
                                    clustersViaveis[o] = clustersViaveis[o] + arestaAnalisada->getPeso();
                                    // cout<<"Cluster "<<o<<" agora tem viabilidade: "<< clustersViaveis[o]<<endl;
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
                if (melhorCluster == -1 || maiorValor == 0)
                {
                }
                else
                {
                    // cout<<"Adicionando No "<<i<<" No Cluster "<<melhorCluster<<endl;
                    float aux = grafo->getNode(ordemVertices[i])->getWeight();
                    grafo->getCluster(melhorCluster)->addNode(ordemVertices[i], aux); // adiciona o nó no cluster
                    grafo->getCluster(melhorCluster)->addAresta(ordemVertices[i], grafo->getNode(ordemVertices[i]));
                    grafo->listaDeNosLivres[ordemVertices[i]] = false;
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

        int ordemVertices[grafo->getOrder()];
        int i = 0, igual;
        do
        {
            ordemVertices[i] = rand() % grafo->getOrder();
            igual = 0;
            for (int j = 0; j < i; j++)
            {
                if (ordemVertices[i] == ordemVertices[j])
                {
                    igual = 1;
                }
            }

            if (igual == 0)
                i++;
        } while (i < grafo->getOrder());

        for (int i = 0; i < Nvertices; i++)
        { // para todo nó 1 a 1

            if (grafo->listaDeNosLivres[ordemVertices[i]] == true)
            { // se o nó for livre

                float clustersViaveis[Nclusters];
                for (int p = 0; p < Nclusters; p++)
                {
                    clustersViaveis[p] = 0;
                }

                verticeAnalisado = grafo->getNode(ordemVertices[i]);

                for (Edge *arestaAnalisada = verticeAnalisado->getFirstEdge(); arestaAnalisada != nullptr; arestaAnalisada = arestaAnalisada->getNextEdge()) // verifica todos caminhos desse nó
                {
                    verticeAnalisado = grafo->getNode(arestaAnalisada->getTargetId());

                    for (int o = 0; o < Nclusters; o++) // para todos clusters
                    {
                        for (verticeAux = grafo->getCluster(o)->getFirstNode(); verticeAux != nullptr; verticeAux = verticeAux->getNextNode()) // para cada vertice nesse cluster
                        {
                            if (verticeAnalisado->getId() == verticeAux->getId()) // se for igual ao vertice analisado
                            {
                                if ((grafo->getCluster(o)->getPeso() + grafo->getNode(ordemVertices[i])->getWeight()) <= (grafo->getCluster(o)->getLimiteSuperior())) // se o peso do cluster + o peso da aresta for menor que o limite superior
                                    clustersViaveis[o] = (float)clustersViaveis[o] + arestaAnalisada->getPeso();
                            }
                        }
                    }
                }

                int melhorCluster = -1;
                float maiorValor = 0;
                for (int k = 0; k < Nclusters; k++)
                {
                    if (clustersViaveis[k] > maiorValor)
                    {
                        melhorCluster = k;
                        maiorValor = clustersViaveis[k];
                    }
                }
                if (melhorCluster == -1 || maiorValor == 0)
                {
                }
                else
                {
                    // cout<<"Adicionando No "<<i<<" No Cluster "<<melhorCluster<<endl;
                    float aux = grafo->getNode(ordemVertices[i])->getWeight();
                    grafo->getCluster(melhorCluster)->addNode(ordemVertices[i], aux); // adiciona o nó no cluster
                    grafo->getCluster(melhorCluster)->addAresta(ordemVertices[i], grafo->getNode(ordemVertices[i]));
                    grafo->listaDeNosLivres[ordemVertices[i]] = false;
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

        int ordemVertices[grafo->getOrder()];
        int i = 0, igual;
        do
        {
            ordemVertices[i] = rand() % grafo->getOrder();
            igual = 0;
            for (int j = 0; j < i; j++)
            {
                if (ordemVertices[i] == ordemVertices[j])
                {
                    igual = 1;
                }
            }

            if (igual == 0)
                i++;
        } while (i < grafo->getOrder());

        for (int i = 0; i < Nvertices; i++)
        { // para todo nó 1 a 1

            if (grafo->listaDeNosLivres[ordemVertices[i]] == true)
            { // se o nó for livre
                cout << "Aconteceu o improvavel" << endl;

                float clustersViaveis[Nclusters];
                for (int p = 0; p < Nclusters; p++)
                {
                    clustersViaveis[p] = 0;
                }

                verticeAnalisado = grafo->getNode(ordemVertices[i]);

                for (Edge *arestaAnalisada = verticeAnalisado->getFirstEdge(); arestaAnalisada != nullptr; arestaAnalisada = arestaAnalisada->getNextEdge()) // verifica todos caminhos desse nó
                {
                    verticeAnalisado = grafo->getNode(arestaAnalisada->getTargetId());

                    for (int o = 0; o < Nclusters; o++) // para todos clusters
                    {
                        for (verticeAux = grafo->getCluster(o)->getFirstNode(); verticeAux != nullptr; verticeAux = verticeAux->getNextNode()) // para cada vertice nesse cluster
                        {
                            if (verticeAnalisado->getId() == verticeAux->getId()) // se for igual ao vertice analisado
                            {
                                // cout<<"No "<<i<<" Tem caminho para o No "<<verticeAux->getId()<<" do Cluster "<<o<<endl;
                                clustersViaveis[o] = clustersViaveis[o] + arestaAnalisada->getPeso();
                            }
                        }
                    }
                }

                int melhorCluster = -1;
                int menorPeso = 10000000;
                for (int k = 0; k < Nclusters; k++)
                {
                    if (clustersViaveis[k] > 0)
                    {
                        if (grafo->getCluster(k)->getPeso() < menorPeso)
                        {
                            melhorCluster = k;
                            menorPeso = grafo->getCluster(k)->getPeso();
                        }
                    }
                }
                if (melhorCluster == -1 || menorPeso == 10000000)
                {
                }
                else if (clustersViaveis[melhorCluster] > 0) // para considerar ligações de custo 0 basta colocar >=
                {
                    float aux = grafo->getNode(ordemVertices[i])->getWeight();
                    grafo->getCluster(melhorCluster)->addNode(ordemVertices[i], aux); // adiciona o nó no cluster
                    grafo->getCluster(melhorCluster)->addAresta(ordemVertices[i], grafo->getNode(ordemVertices[i]));
                    grafo->listaDeNosLivres[ordemVertices[i]] = false;
                    cout << "Adicionando No " << ordemVertices[i] << " No Cluster " << melhorCluster << " Novo Peso = " << grafo->getCluster(melhorCluster)->getPeso() << endl;
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

bool Grasp::verificaTroca(Graph *grafo, int idClusterExcedente, int idClusterAlvo, int idNo)
{

    // verifica se existe caminho do No até o Cluster Alvo
    for (Node *a = grafo->getCluster(idClusterAlvo)->getFirstNode(); a != nullptr; a = a->getNextNode())
    {
        for (Edge *b = grafo->getNode(idNo)->getFirstEdge(); b != nullptr; b = b->getNextEdge())
        {
            if (b->getTargetId() == a->getId())
            {
                return true;
            }
        }
    }
    return false;
}

void Grasp::troca(Graph *grafo, int idClusterExcedente, int idClusterAlvo, int idNo)
{

     grafo->getCluster(idClusterExcedente)->removeNode(idNo);


     grafo->getCluster(idClusterAlvo)->addNode(idNo, grafo->getNode(idNo)->getWeight());

}

// void Grasp::ajuste(Graph *grafo)
// {
//     bool trocou = false;
//     while (!grafo->clustersViaveis2())
//     { // enquanto a solução n for viavel
//         // olhar cluster a cluster qual n é viavel
//         trocou = false;
//         cout << "teste 1" << endl;
//         for (int i = 0; i < grafo->getNumCluster(); i++)
//         {
//             if (trocou)
//                 break;
//             cout << "teste 2" << endl;
//             while (!grafo->getCluster(i)->viavel())
//             {
//                 // cout << "teste 3" << endl;
//                 if (trocou)
//                     break; // enquanto esse cluster n for viavel
//                 // this->imprime(grafo);

//                 // pegar o j-gésimo nó mais pesado desse cluster
//                 int noPesos[grafo->getOrder()];
//                 for (int j = 0; j < grafo->getOrder(); j++)
//                 { // olha pra todos vertices
//                     if (grafo->getCluster(i)->searchNode(j))
//                     {                                                               // se o vertice pertence ao cluster
//                         noPesos[j] = grafo->getCluster(i)->getNode(j)->getWeight(); // adiciona o peso no vetor
//                     }
//                     else
//                     {
//                         noPesos[j] = 0; // peso 0
//                     }
//                 }
//                 int maisPesado = -1;
//                 int maiorPeso = 0;
//                 for (int j = 0; j < grafo->getOrder(); j++)
//                 {
//                     if (noPesos[j] > maiorPeso)
//                     {
//                         maiorPeso = noPesos[j];
//                         maisPesado = j;
//                     }
//                 }

//                 // verificar cluster a cluster do mais leve ao mais pesado se tem como mandar ele pra la

//                 int ClusterPesos[grafo->getNumCluster()];
//                 for (int j = 0; j < grafo->getNumCluster(); j++)
//                 { // olha todos os clusters
//                     if (i == j)
//                     { // se o cluster q eu to olhando é o msm que eu quero viabilizar
//                         ClusterPesos[j] = 10000000;
//                     }
//                     else if (grafo->getCluster(j)->getPeso() < grafo->getCluster(j)->getLimiteSuperior())
//                     { // se o cluster q eu to olhando é viavel
//                         ClusterPesos[j] = grafo->getCluster(j)->getPeso();
//                     }
//                     else
//                     {
//                         ClusterPesos[j] = 10000000;
//                     }
//                 }
//                 int maisLeve = -1;
//                 int maiorLeve = 10000000;
//                 for (int j = 0; j < grafo->getNumCluster(); j++)
//                 {
//                     if (ClusterPesos[j] < maiorLeve)
//                     {
//                         maiorLeve = ClusterPesos[j];
//                         maisLeve = j;
//                     }
//                 }

//                 while (maisPesado != -1)
//                 {
//                     if (trocou)
//                         break;
//                     // cout << "teste 4" << endl;
//                     while (maisLeve != -1)
//                     {
//                         if (trocou)
//                             break;
//                         // cout << "teste 5" << endl;
//                         for (Node *a = grafo->getCluster(maisLeve)->getFirstNode(); a != nullptr; a = a->getNextNode())
//                         {
//                             if (trocou)
//                                 break; // olhe para todos nós desse cluster
//                             // cout << "teste 6" << endl;
//                             for (Edge *b = grafo->getCluster(i)->getNode(maisPesado)->getFirstEdge(); b != nullptr; b = b->getNextEdge())
//                             { // olhe para todos caminhos desse nó
//                                 //cout << "teste 7" << endl;
//                                 if (b->getTargetId() == a->getId())
//                                 { // se houver caminho
//                                     cout << "teste 8" << endl;
//                                     troca(grafo, i, maisLeve, maisPesado);
//                                     trocou = true;
//                                     // cout<<"teste 9"<<endl;
//                                     break;
//                                 }
//                             }
//                         }
//                         // cout<<"teste 5.1"<<endl;
//                         ClusterPesos[maisLeve] = 10000000;
//                         maisLeve = -1;
//                         maiorLeve = 10000000;
//                         for (int j = 0; j < grafo->getNumCluster(); j++)
//                         {
//                             if (ClusterPesos[j] < maiorLeve)
//                             {
//                                 maiorLeve = ClusterPesos[j];
//                                 maisLeve = j;
//                             }
//                         }
//                     }
//                     noPesos[maisPesado] = 0;
//                     maisPesado = -1;
//                     maiorPeso = 0;
//                     for (int j = 0; j < grafo->getOrder(); j++)
//                     {
//                         if (noPesos[j] > maiorPeso)
//                         {
//                             maiorPeso = noPesos[j];
//                             maisPesado = j;
//                         }
//                     }
//                 }
//             }
//         }
//     }
// }