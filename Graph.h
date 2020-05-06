#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "Path.h"
#include <vector>

class Graph
{
public:
    Graph();
    Graph(int vertexnum,std::string *vertices,int** adjmatrix);
    Graph(const Graph& other);
    ~Graph();

    void clear();
    int getEdgeCost(int v1, int v2);    //adjacent edges as parameter
    int traversePath(Path &currentPath);    //returns cost of path, sets path cost in path object
    void addVertex(std::string newEntry);
    void addEdge(std::string v1, std::string v2,int weight);
    void removeEdge(std::string v1, std::string v2);
    std::string getVertex(int index);   
    int getIndex(std::string s);    //-1 for not found
    

    void displayMatrix();   //debug display

private:
    // Members
    std::vector<std::string> m_vertices;
    int **m_adjacencymatrix;
    int m_vertexcount;
};

#endif // GRAPH_H