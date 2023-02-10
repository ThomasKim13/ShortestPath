#ifndef WGraph_H
#define WGraph_H
#include <cstdlib>
#include <deque>
#include <set>
#include <stack>
#include <iostream>
#include <limits>
#include <string>
#include "PQueue.h"
using namespace std;
//a weighted, undirected WGraph implemented with adjacency matrix
//fixed size
typedef unsigned int VertexID;
class WGraph{
    //public methods
public:
    WGraph();
    WGraph(unsigned int sz);
    ~WGraph();
    void addEdge(VertexID i, VertexID j, double w);
    void removeEdge(VertexID i, VertexID j);
    bool areAdjacent(VertexID i, VertexID j);
    double cheapestCost(VertexID i, VertexID j);
    void calcFW();
    void createAdj(string inFile);
    void computeMST();
    //private variables
private:
    double** m_adj; //is there an edge between two vertices and what's the weight of the edge
    double** newCons;
    double** newArr;
    double** m_conn; //more general, is there a path between a start and a finish and
    unsigned int m_size; //nodes in WGraph (fixed)
};
#endif