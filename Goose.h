#ifndef GOOSE_H
#define GOOSE_H

#include "Tile.h"

class Goose {
    Tile *blocking;
    public:
        Goose(Tile *blocking) : blocking{blocking} {}
        void move(Tile* dest);
};

#endif