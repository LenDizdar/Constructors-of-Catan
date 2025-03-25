#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <string>

#include "Vertex.h"
#include "Edge.h"
#include "Tile.h"

class Board {

    std::string getLineTop(int left, int edge, int right);
    std::string getLineMiddle(int left, int tile, int right);
    
    protected:
        std::vector<Vertex> vertices;
        std::vector<Edge> edges;
        std::vector<Tile> tiles;
    public:
        void rolled(int dieNum);
        std::string getDesc();
};

#endif
