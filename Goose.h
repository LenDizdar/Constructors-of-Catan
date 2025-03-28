#ifndef GOOSE_H
#define GOOSE_H

#include "Tile.h"

class Goose {
    Tile *blocking;
    public:
        Goose(Tile *blocking) : blocking{blocking} { if (blocking) blocking->isBlocked = true; }
        void move(Tile* dest);
        int getIndex() { return blocking ? blocking->getIndex() : 0; }
};

#endif
