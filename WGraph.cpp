/*
 * Thomas Kim
 * 2405924
 * chukim@chapman.edu
 * CPSC-350-01
 * PA6
 * WGraph File that creates a weighted graph for the matrix*/
#include "WGraph.h"
#include <ostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "PQueue.h"
#include "position.h"
using namespace std;
//default constructor
WGraph::WGraph(){
  m_size = 0;
  m_adj = NULL;
  m_conn = NULL;
}
//overloaded constructor
WGraph::WGraph(unsigned int sz){
  m_size = sz;
  //allocate sz * sz adj matrix
  m_adj = new double*[sz];
  m_conn = new double*[sz];
  for(int i = 0; i < m_size; ++i){
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  //start with edges
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_adj[i][j] = std::numeric_limits<double>::max(); //essentially infinity
      m_conn[i][j] = std::numeric_limits<double>::max();
    }
  }
}
//default deconstructor
WGraph::~WGraph(){

  for(int i = 0; i < m_size; i++){
      delete[] m_adj[i];
      delete[] m_conn[i];
      delete[] newCons[i];
  }
  delete m_adj;
  delete m_conn;
  delete newCons;
}
//adds edge and the weight to the m_adj matrix
void WGraph::addEdge(VertexID i, VertexID j, double w){
  if(i < m_size && j < m_size){
    m_adj[i][j] = w;
    m_adj[j][i] = w;
  }
}
//removes an edge given a vertex location
void WGraph::removeEdge(VertexID i, VertexID j){
  if(i < m_size && j < m_size){
    m_adj[i][j] = std::numeric_limits<double>::max();
    m_adj[j][i] = std::numeric_limits<double>::max();
  }
}
//checks if there is an adjacent
bool WGraph::areAdjacent(VertexID i, VertexID j){
  return (m_adj[i][j] < std::numeric_limits<double>::max());
}
//calculates Floyd Warshael Algorithim
//doesnt apply to this project
void WGraph::calcFW(){ //runtime complexity O(v^3)
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
    }
  }
  for(int im = 0; im < m_size; ++ im){ //intermediate points --> transitive closure
    for(int source = 0; source < m_size; ++source){ //source = starting point
      for(int sink = 0; sink <m_size; ++sink){ //sink = ending point
        if(source == sink){
          continue;
        }else if(m_conn[source][im] != std::numeric_limits<double>::max() &&
          m_conn[im][sink] != std::numeric_limits<double>::max() &&
          m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){
           m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
        }
      }
    }
  }
}
//gets the cheapest weight that there is
double WGraph::cheapestCost(VertexID i, VertexID j){
  return m_conn[i][j]; //constant
}
//calculates the minimum spanning tree
void WGraph::computeMST() {
    //keeps track of how many edges there are
    int numEdges = 0;
    double minCost = 0.0;
    int vertexSum;
    //creating a vertex that allows for the amount of nodes to be inserted for union later on
    int *vertex = new int[m_size];
    //populating the vertex
    for (int i = 0; i < m_size; i++) {
        vertex[i] = i;
        vertexSum += vertex[i];
    }
    //initiating the newCons matrix
    //populating the newCons matrix with 0.0 so that later down on the road that 0.0 can be replaced with some other weight
    this->newCons = new double *[m_size];
    for (int i = 0; i < m_size; i++) {
        this->newCons[i] = new double[m_size];
        for (int j = 0; j < m_size; j++) {
            this->newCons[i][j] = 0.0;
        }
    }
    //creating a queue that hold the position class
    PQueue<position *> *PQ = new PQueue<position *>(true);
    for (int i = 0; i < m_size; i++) {
        for (int j = 0; j < m_size; j++) {
            double weight = this->m_adj[i][j];
            if (weight != 0.0) {
                //creates a position instance
                //hold the row and col number and the weight at that specific location
                position *pos = new position(i, j, weight);
                //add that position to the queue
                PQ->add(pos);
            }
        }
    }

    //while the priority queue is not empty the position at the top will be removed and return it's contents

    while (!PQ->isEmpty() && numEdges <= m_size) {
        //position is set to which ever position was at the top
        position *newPos = PQ->removeTop();
        double weighted = newPos->getWeight();
        int rowX = newPos->getRow();
        int colY = newPos->getCol();
        cout << setprecision(2) << fixed;

        cout << "Weight: " << weighted << " at (" << rowX << ", " << colY << ")" << endl;




            //this is where the unification process starts
            //if the row location is not equal to the column location on the vertex
            //then the vertex is switched
            if (vertex[rowX] != vertex[colY]) {
                for (int i = 0; i < m_size; i++) {

                    if (vertex[i] == colY) {
                        vertex[i] = vertex[rowX];

                    }
                }

                this->newCons[rowX][colY] = weighted;
                this->newCons[colY][rowX] = weighted;
                numEdges +=1;
            }

        }
        //now calculates the minimum cost by traversing through the newCons matrix and adding it to the minCost variable
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                minCost += this->newCons[i][j];
            }
        }
        //minCost is divided here due to the fact that the matrix is symmetrical, so it is double of what it has to be
        minCost /= 2.0;
        //prints the newCons matrix with all the connections that are connected through Kruskal's method.
        cout << endl;
        cout << "Kruskal Adjacency Matrix" << endl;
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                //set precision to 2 to make minCost cout to look better
                cout << setprecision(2) << fixed;
                cout << this->newCons[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Min cost: " << minCost << endl;
    }







