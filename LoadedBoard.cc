#include "LoadedBoard.h"
#include <sstream>

using namespace std;

LoadedBoard::LoadedBoard(string saveInfo) : Board{} {

    istringstream iss{saveInfo};

    for (int i = 0; i < 19; i++) {

        int resource, roll;
        iss >> resource >> roll;

        switch(resource) {
            case 0:
                tiles.emplace_back(Tile(Resource::BRICK, roll, i));
                break;
            case 1:
                tiles.emplace_back(Tile(Resource::ENERGY, roll, i));
                break;
            case 2:
                tiles.emplace_back(Tile(Resource::GLASS, roll, i));
                break;
            case 3:
                tiles.emplace_back(Tile(Resource::HEAT, roll, i));
                break;
            case 4:
                tiles.emplace_back(Tile(Resource::WIFI, roll, i));
                break;
            case 5:
                tiles.emplace_back(Tile(0,0,0,0,0,7, i));
                break;
        }

    }

    //Creating verticies
    for (int i = 0; i < 54; ++i) {

        vertices.emplace_back(i);

    }

    //Creating edges
    for (int i = 0; i < 72; ++i) {

        edges.emplace_back(i);

    }

    connect();

}
