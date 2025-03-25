#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string>

#include "Vertex.h"
#include "Edge.h"
#include "Tile.h"

using namespace std;

class Board {
    
    protected:
        vector<Vertex> vertices;
        vector<Edge> edges;
        vector<Tile> tiles;
    public:
        void rolled(int dieNum);
        string getDesc();
};

#endif
