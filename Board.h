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
    std::string gooseString(int tileIdx);
    
    protected:
        std::vector<Vertex> vertices;
        std::vector<Edge> edges;
        std::vector<Tile> tiles;
        void connect();
    public:
        void rolled(int dieNum);
        std::string getDesc();
        Vertex& getVertex(int index) { return vertices.at(index); }
        Edge& getEdge(int index) { return edges.at(index); }
        Tile* getTile(int index) { return &tiles.at(index); }
        Tile* findGoose();
        std::string saveOutput();
};

#endif
