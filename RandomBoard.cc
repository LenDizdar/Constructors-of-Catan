#include "RandomBoard.h"
#include <random>
#include <algorithm>
#include <iostream>

using namespace std;

RandomBoard::RandomBoard(default_random_engine rand) : Board{} {
    
    //Creating tiles
    vector<int> resources = 
    {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4};
    shuffle(resources.begin(), resources.end(), rand);

    vector<int> rolls = 
    {2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12};
    shuffle(rolls.begin(), rolls.end(), rand);

    for (int i = 0; i < 19; ++i) {

        //Checking for Park
        if (rolls.at(i) != 7) {

            int resourceType = resources.back();
            resources.pop_back();

            switch(resourceType) {
                case 0:
                    tiles.emplace_back(Tile(Resource::BRICK, rolls.at(i), i));
                    break;
                case 1:
                    tiles.emplace_back(Tile(Resource::ENERGY, rolls.at(i), i));
                    break;
                case 2:
                    tiles.emplace_back(Tile(Resource::GLASS, rolls.at(i), i));
                    break;
                case 3:
                    tiles.emplace_back(Tile(Resource::HEAT, rolls.at(i), i));
                    break;
                case 4:
                    tiles.emplace_back(Tile(Resource::WIFI, rolls.at(i), i));
                    break;
            }

        } else {

            tiles.emplace_back(Tile(0,0,0,0,0,7,i));

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
