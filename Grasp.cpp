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

void Grasp::Clusterizar(Graph *grafo, Instancia *atual, Instancia *analizada, Instancia *melhorAnalizada, Instancia *movimentoAnterior)
{
    int clo = clock();
    int nmenos4 = ((grafo->getOrder()/4) - 1)*1000;
    bool repetir = true;
    do
    {

        this->Centroides(grafo);

        this->CompletarLI1(grafo);
        // for (int i = 0; i < grafo->getNumCluster(); i++)
        // {
        //     // cout << "Cluster "<<i<< " LimiteInferior e Superior: " << grafo->getCluster(i)->getLimiteInferior() << "--" << grafo->getCluster(i)->getLimiteSuperior()<<endl;
        // }
        repetir = true;
        //this->imprime(grafo);
        if (grafo->clustersViaveis2())
        {

            repetir = false;
        }
        else
        {

            grafo->resetaClusters();

            for (int k = 0; k < grafo->getOrder(); k++)
            {
                grafo->listaDeNosLivres[k] = true;
            }
        }

    } while (repetir);

    this->CompletarLS1(grafo);

    this->Completar(grafo);

    this->CompletarVerticesLivres(grafo);

    // this->imprime(grafo);
    //cout<<"nmenos4 "<<nmenos4<<endl;
    while (nmenos4>(clock() - clo))
    {
        // cout<<"Busca local: "<<i<<endl;
        this->buscaLocal(grafo, atual, analizada, melhorAnalizada, movimentoAnterior);
        atual->setInstancia(0, 0, 0);
        analizada->setInstancia(0, 0, 0);
        melhorAnalizada->setInstancia(0, 0, 0);
    }

    cout << "tempo de execucao da iteração: " << (clock() - clo) << " millisegundos" << endl;
    // this->imprime(grafo);
}

void Grasp::imprime(Graph *grafo)
{

    cout << endl;
    // cout << "Melhor Instancia: " << grafo->melhorInstancia << endl;
    for (int i = 0; i < grafo->getNumCluster(); i++)
    {
        cout << "Cluster " << i << " Nos : ";
        for (Node *a = grafo->getCluster(i)->getFirstNode(); a != nullptr; a = a->getNextNode())
        {
            cout << a->getId() << ", ";
        }
        cout << " Peso: " << grafo->getCluster(i)->getPeso() << "    Qualidade = " << grafo->getCluster(i)->calculaQualidade() << " Numero de nos " << grafo->getCluster(i)->getNumNodes() << endl;
    }
    cout << "Qualidade do Grafo: " << this->calculaSolucao(grafo) << endl;
    if (grafo->clustersViaveis2())
    {
        cout << "Solucao Viavel" << endl;
    }
    else
    {
        cout << "Solucao Nao Viavel" << endl;
    }
    cout << endl;
}

void Grasp::guarda(Graph *grafo,ofstream &output_file)
{

    output_file << endl;
    // cout << "Melhor Instancia: " << grafo->melhorInstancia << endl;
    for (int i = 0; i < grafo->getNumCluster(); i++)
    {
        output_file << "Cluster " << i << " Nos : ";
        for (Node *a = grafo->getCluster(i)->getFirstNode(); a != nullptr; a = a->getNextNode())
        {
            output_file << a->getId() << ", ";
        }
        output_file << " Peso: " << grafo->getCluster(i)->getPeso() << "    Qualidade = " << grafo->getCluster(i)->calculaQualidade() << " Numero de nos " << grafo->getCluster(i)->getNumNodes() << endl;
    }
    output_file << "Qualidade do Grafo: " << this->calculaSolucao(grafo) << endl;
    if (grafo->clustersViaveis2())
    {
        output_file << "Solucao Viavel" << endl;
    }
    else
    {
        output_file << "Solucao Nao Viavel" << endl;
    }
    output_file << endl;
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

void Grasp::CompletarVerticesLivres(Graph *grafo)
{

    // cout << "entra no completar" << endl;

    bool algumVerticeLivre = false;

    for (int i = 0; i < grafo->getOrder(); i++)
    {
        if (grafo->listaDeNosLivres[i] == true)
        {
            algumVerticeLivre = true;
        }
    }

    while (algumVerticeLivre)
    {
        algumVerticeLivre = false;

        int verticeAnalisado;
        int clusterSorteado;

        for (int i = 0; i < grafo->getOrder(); i++)
        {
            if (grafo->listaDeNosLivres[i] == true)
            {
                verticeAnalisado = i;
                break;
            }
        }

        int contador = 0;

        do
        {

            clusterSorteado = contador;

            if (contador > grafo->getNumCluster())
            { // adiciona o nó no cluster de menor peso
                int menorCluster = grafo->getCluster(0)->getPeso();
                int menorCluster2 = -1;
                for (int i = 0; i < grafo->getNumCluster(); i++)
                {
                    if (grafo->getCluster(i)->getPeso() < menorCluster)
                    {
                        menorCluster = grafo->getCluster(i)->getPeso();
                        menorCluster2 = i;
                    }
                }

                grafo->getCluster(menorCluster2)->addNode(verticeAnalisado, grafo->getNode(verticeAnalisado)->getWeight());
                grafo->getCluster(menorCluster2)->addAresta(verticeAnalisado, grafo->getNode(verticeAnalisado));
                grafo->listaDeNosLivres[verticeAnalisado] = false;

                break;
            }

            contador++;

        } while ((grafo->getCluster(clusterSorteado)->getLimiteSuperior()) <= (grafo->getCluster(clusterSorteado)->getPeso() + grafo->getNode(verticeAnalisado)->getWeight()));

        grafo->getCluster(clusterSorteado)->addNode(verticeAnalisado, grafo->getNode(verticeAnalisado)->getWeight());
        grafo->getCluster(clusterSorteado)->addAresta(verticeAnalisado, grafo->getNode(verticeAnalisado));
        grafo->listaDeNosLivres[verticeAnalisado] = false;

        for (int i = 0; i < grafo->getOrder(); i++)
        {
            if (grafo->listaDeNosLivres[i] == true)
            {
                algumVerticeLivre = true;
            }
        }
    }
    // cout << "sai do completar" << endl;
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
                // cout << "Aconteceu o improvavel" << endl;

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
                    // cout << "Adicionando No " << ordemVertices[i] << " No Cluster " << melhorCluster << " Novo Peso = " << grafo->getCluster(melhorCluster)->getPeso() << endl;
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
            // s
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
    // cout<<"Troca 1"<<endl;
    grafo->getCluster(idClusterAlvo)->addNode(idNo, grafo->getNode(idNo)->getWeight());
    // cout<<"Troca 2"<<endl;
    grafo->getCluster(idClusterAlvo)->addAresta(idNo, grafo->getNode(idNo));
    // cout<<"Troca 3"<<endl;
    grafo->getCluster(idClusterExcedente)->removeNode(idNo);
}

float Grasp::calculaSolucao(Graph *grafo)
{
    float soma = 0;

    for (int i = 0; i < grafo->getNumCluster(); i++)
    {
        soma = soma + grafo->getCluster(i)->calculaQualidade();
    }

    return soma;
}

bool Grasp::desbalanceadoS(Cluster *cluster)
{

    float limiteSCluster = cluster->getLimiteSuperior();

    float pesoCluster = cluster->getPeso();

    if (pesoCluster > limiteSCluster)
    {

        return true;
    }

    return false;
}

void Grasp::buscaLocal(Graph *grafo, Instancia *atual, Instancia *analizada, Instancia *melhorAnalizada, Instancia *movimentoAnterior)
{
    // declaração de variaveis

    Cluster *clusterAtual;
    int valorAleatorio = 0;
    float limiteSCluster = 0;
    float limiteICluster = 0;
    float pesoCluster = 0;
    float valorSolAutual = 0;
    float pesoClusterPosADDNode = 0;
    float valorMelhorSol;
    bool movimentoAnteriorPossivel = false;
    if (grafo->clustersViaveis2())
    {
        valorMelhorSol = calculaSolucao(grafo);
    }
    for (int i = 0; i < grafo->getNumCluster(); i++)
    {

        clusterAtual = grafo->getCluster(i);

        while (desbalanceadoS(clusterAtual))
        {
            // verificação para caso esteja balanceado não seja
            valorMelhorSol = 0;

            // cout << "Tentando Balancear Cluster " << clusterAtual->getidCluster() << endl;
            valorAleatorio = rand() % grafo->getCluster(i)->getNumNodes();

            int k = 0;
            Node *p = grafo->getCluster(i)->getFirstNode();
            // cout<<endl;
            // cout<<"id do p: "<<p->getId()<<endl;
            // cout<<endl;
            // cout << "Valor Aleatorio: " << valorAleatorio << endl;
            // cout << "Cluster " << i << " ";

            // pega o no aleatorio
            while (k < valorAleatorio)
            {
                p = p->getNextNode();
                k++;
            }
            // cout<<endl;
            // cout<<"id do p: "<<p->getId()<<endl;
            // cout<<endl;
            // cout << "No analisado: " << p->getId() << endl;

            // controle de movimento
            atual->setInstancia(i, p->getId(), valorMelhorSol);
            // movimentoAnterior->setInstancia(i, p->getId(), valorMelhorSol);
            melhorAnalizada->setInstancia(i, p->getId(), valorMelhorSol);
            analizada->setInstancia(i, p->getId(), valorMelhorSol);

            // cout << "passou do processo de instanciacao" << endl;

            // realização do movimento caso o grafo seja capaz de receber aquele node
            for (int l = 0; l < grafo->getNumCluster(); l++)
            {
                if (i != l)
                {
                    if (verificaTroca(grafo, i, l, p->getId()))
                    {
                        // cout << "no Cluster " << l;
                        // cout << " tem espaco para esse no";

                        // cout << " e a troca e viavel";
                        // cout<<endl<<i<<" __ "<<l<<" __ "<<p->getId()<<endl;
                        troca(grafo, i, l, p->getId());
                        // cout << " _1 ";
                        valorSolAutual = calculaSolucao(grafo);
                        // cout << " _2 ";
                        troca(grafo, l, i, p->getId());
                        // cout << " _3 ";
                        analizada->setInstancia(l, p->getId(), valorSolAutual);
                        // cout << " _4 ";

                        pesoClusterPosADDNode = grafo->getCluster(l)->getPeso() + p->getWeight();

                        if (pesoClusterPosADDNode < grafo->getCluster(l)->getLimiteSuperior() && pesoClusterPosADDNode >= grafo->getCluster(l)->getLimiteInferior())
                        {

                            if (melhorAnalizada->getMelhorInstancia() < analizada->getMelhorInstancia())
                            {
                                // cout << " e por enquanto e a melhor instancia" << endl;
                                melhorAnalizada->idCluster = l;
                                melhorAnalizada->idNo = p->getId();
                                melhorAnalizada->melhorInstancia = valorSolAutual;
                            }
                            else
                            {
                                movimentoAnteriorPossivel = true;

                                movimentoAnterior->idCluster = analizada->getIdCluster();
                                movimentoAnterior->idNo = analizada->getIdNo();
                                movimentoAnterior->melhorInstancia = analizada->getMelhorInstancia();
                            }
                        }
                        else
                        {
                            if (!movimentoAnteriorPossivel)
                            {
                                movimentoAnterior->idCluster = analizada->getIdCluster();
                                movimentoAnterior->idNo = analizada->getIdNo();
                                movimentoAnterior->melhorInstancia = analizada->getMelhorInstancia();
                            }

                            // cout << " mas a troca nao e viavel";
                        }
                    }
                    else
                    {
                        // cout << " nao tem espaco para esse no" << endl;
                    }
                }
            }
            if (melhorAnalizada->getIdCluster() != atual->getIdCluster())
            {
                if (verificaTroca(grafo, i, melhorAnalizada->getIdCluster(), p->getId()))
                {
                    // cout<<endl;
                    // cout << "a melhor instancia e o  cluster: "<<melhorAnalizada->getIdCluster()<<endl<<"No: "<<melhorAnalizada->getIdNo()<<endl<<"Peso: "<<melhorAnalizada->getMelhorInstancia()<< endl;
                    // cout<<endl;
                    troca(grafo, i, melhorAnalizada->getIdCluster(), p->getId());
                    pesoCluster = grafo->getCluster(i)->getPeso();
                }
            }
            else
            {
                troca(grafo, i, movimentoAnterior->getIdCluster(), p->getId());
                pesoCluster = grafo->getCluster(i)->getPeso();
                break;
            }
            // cout<<"0.1"<<endl;
        }
        // cout<<"0.2"<<endl;
    }

    // cout<<"1"<<endl;

    valorAleatorio = rand() % grafo->getNumCluster();
    // cout<<"1.1"<<endl;
    clusterAtual = grafo->getCluster(valorAleatorio);
    // cout<<"1.2"<<endl;
    limiteICluster = clusterAtual->getLimiteInferior();
    // cout<<"1.3"<<endl;
    limiteSCluster = clusterAtual->getLimiteSuperior();
    // cout<<"1.4"<<endl;
    pesoCluster = clusterAtual->getPeso();
    // cout<<"1.5"<<endl;
    // cout<<"cluster atual :"<<clusterAtual->getidCluster()<<endl;
    // cout<<"cluster atual numero de nos: "<<clusterAtual->getNumNodes()<<endl;
    // cout<<endl;

    valorAleatorio = (rand() % clusterAtual->getNumNodes());
    // cout<<"1.6"<<endl;
    int k = 0;
    Node *q = clusterAtual->getFirstNode();
    // cout<<"1.7"<<endl;

    // cout<<"2"<<endl;

    // pega o no aleatorio
    while (k < valorAleatorio)
    {
        q = q->getNextNode();
        k++;
    }

    // cout<<"3"<<endl;

    // controle de movimento
    valorMelhorSol = calculaSolucao(grafo);
    atual->setInstancia(clusterAtual->getidCluster(), q->getId(), valorMelhorSol);
    melhorAnalizada->setInstancia(clusterAtual->getidCluster(), q->getId(), valorMelhorSol);
    analizada->setInstancia(clusterAtual->getidCluster(), q->getId(), valorMelhorSol);
    // realização do movimento caso o grafo seja capaz de receber aquele node
    // cout<<"4"<<endl;
    for (int l = 0; l < grafo->getNumCluster(); l++)
    {
        if (clusterAtual->getidCluster() != l)
        {
            pesoClusterPosADDNode = grafo->getCluster(l)->getPeso() + q->getWeight();
            if (pesoClusterPosADDNode <= grafo->getCluster(l)->getLimiteSuperior() && pesoClusterPosADDNode >= grafo->getCluster(l)->getLimiteInferior())
            {
                if (verificaTroca(grafo, clusterAtual->getidCluster(), l, q->getId()))
                {
                    troca(grafo, clusterAtual->getidCluster(), l, q->getId());
                    valorSolAutual = calculaSolucao(grafo);
                    analizada->setInstancia(l, q->getId(), valorSolAutual);

                    troca(grafo, l, clusterAtual->getidCluster(), q->getId());

                    if (melhorAnalizada->getMelhorInstancia() < analizada->getMelhorInstancia())
                    {
                        melhorAnalizada = analizada;
                    }
                }
            }
        }
    }
    // cout<<"5"<<endl;
    if (clusterAtual->getLimiteInferior() < clusterAtual->getPeso() - q->getWeight())
    {
        if (atual->getMelhorInstancia() < melhorAnalizada->getMelhorInstancia())
        {
            // cout<<"========= Troca Efetivada ========"<<endl;
            troca(grafo, clusterAtual->getidCluster(), melhorAnalizada->getIdCluster(), q->getId());
            grafo->melhorInstancia = melhorAnalizada->getMelhorInstancia();
        }
        else
        {
            grafo->melhorInstancia = atual->getMelhorInstancia();
        }
        // cout<<"6"<<endl;
    }

    // cout<<"1"<<endl;
    // delete atual;
    // delete melhorAnalizada;
    // delete analizada;
    // cout<<"2"<<endl;

    // atualiza o peso do Cluster analizado
}
