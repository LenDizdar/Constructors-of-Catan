#ifndef TILE_H
#define TILE_H
#include "ResourceList.h"
#include "Subject.h"
#include <string>
#include "Builder.h"

class Tile : public Subject {
    int rollNum;
    bool isBlocked;
    int index;
    friend class Goose;
    public:
        Tile(int brick, int energy, int glass, int heat, int wifi, int rollNum, int index); // Constructor
                                                                      
        Tile(Resource r, int rollNum, int index); // Constructor for a tile with a single resource
                                                  // (tile as they are in the base Catan game)

        void roll(int dieRoll); // Will update the Verticies observing the Tile if the rolled
                                // number is the number on the tile

        std::string getResourceName() const; // Returns the name of the resource, but as
                                             // a string. Will return "PARK" if Tile
                                             // has no resources

        int getResourceInt() const; // Same as above but with an int

        int getRollNum() const { return rollNum; } // Getter

        std::string getRollNumStr() const; // Getter (but a string)

        bool getIsBlocked() const { return isBlocked; } // Getter

        int getIndex() const { return index; } // Getter

        std::vector<Builder*>getBuildersOnTile();
};

#endif
