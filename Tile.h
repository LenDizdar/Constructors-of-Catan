#ifndef TILE_H
#define TILE_H
#include "ResourceList.h"
#include "Subject.h"
#include <string>

class Tile : public Subject {
    int rollNum;
    bool isBlocked;
    friend class Goose;
    public:
        Tile(int brick, int energy, int glass, int heat, int wifi, int rollNum); // Constructor
                                                                      
        Tile(Resource r, int rollNum); // Constructor for a tile with a single resource
                                       // (tile as they are in the base Catan game)

        void roll(int dieRoll); // Will update the Verticies observing the Tile if the rolled
                                // number is the number on the tile

        std::string getResourceName() const; // Returns the name of the resource, but as
                                             // a string. Will return "PARK" if Tile
                                             // has no resources

        int getRollNum() const { return rollNum; } // Getter

        std::string getRollNumStr() const; // Getter (but a string)

        bool getIsBlocked() const { return isBlocked; } // Getter
};

#endif
