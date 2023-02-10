//
// Created by Thomas Kim on 12/8/22.
//

#ifndef WGRAPH_POSITION_H
#define WGRAPH_POSITION_H


class position {
    //public class methods
public:
    position();
    ~position();
    position(int r, int c, double w);
    double getWeight();
    int getCol();
    int getRow();
    //private variables
private:
    int col;
    int row;
    double weight;

};


#endif //WGRAPH_POSITION_H
