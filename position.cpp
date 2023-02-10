//
// Created by Thomas Kim on 12/8/22.
//

#include "position.h"
#include <iostream>
using namespace std;
//default constructor
position::position() {
    row=0;
    col = 0;
    weight = 0.0;
}
//default deconstructor
position::~position() {
}
//overloaded constructor
position::position(int r, int c, double w) {
    row = r;
    col = c;
    weight = w;
}
//returns the weight
double position::getWeight() {
    return weight;
}
//returns the column #
int position::getCol() {
    return col;
}
//returns the row #
int position::getRow() {
    return row;
}
