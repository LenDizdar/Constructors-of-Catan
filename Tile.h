#ifndef TILE_H
#define TILE_H
#include "ResourceList.h"
#include "Subject.h"
#include <string>

class Tile : public Subject {
    int rollNum;
    bool isBlocked;
    public:
        Tile(int brick, int energy, int glass, int heat, int wifi, int rollNum);
        void roll(int dieRoll);
        std::string getResourceName() const;
        int getRollNum() const { return rollNum; }
        bool getIsBlocked() const { return isBlocked; }
};
#endif
