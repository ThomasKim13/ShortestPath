#include "WGraph.h"
#include <iostream>
#include <fstream>
#include "PQueue.h"
#include "WGraph.h"
using namespace std;
int main(int argc, char* argv[]){
    WGraph* WG;
    double weight;
    string line;
    ifstream inFile;
    inFile.open(argv[1]);
    getline(inFile,line);
    int graphSize = stoi(line);
    WG = new WGraph(graphSize);
    //adding edges to m_adj variable in WG
    for(int i = 0; i < graphSize; i++){
        for(int j = 0; j < graphSize; j++){
            inFile >> weight;
            WG->addEdge(i,j,weight);
        }
    }
    WG->computeMST();

    inFile.close();







    return 0;
}