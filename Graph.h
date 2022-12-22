/*
Hiero Henrique Barcelos Costa 202065136A
Matheus Cardoso Faesy 202065065A
*/
/**************************************************************************************************
 * Implementation of the TAD Graph
 **************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>
#include <sstream>
#include <string>

using namespace std;

class Graph
{

    // Atributes
private:
    int order;
    int number_edges;
    Node *first_node;
    Node *last_node;
public:
    // Constructor
    Graph();

    // Destructor
    ~Graph();
    // Getters
    int getOrder();
    int getNumberEdges();
    Node *getFirstNode();
    Node *getLastNode();
    bool getConexGraph();
    // Other methods
    Node* searchNode_ByNome(string nome);
    void setOrder(int a){this->order=a;};
    void insertNode();
    void removeNode(int id);
    bool searchNode(int id);
    Node *getNode(int id);
    Node* searchNode_ByID(int id);
    
    bool verificaAresta(int id, int target_id);

    void printGraph(ofstream &output_file);

};

#endif // 