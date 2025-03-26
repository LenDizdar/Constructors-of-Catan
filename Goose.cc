#include "Goose.h"

void Goose::move(Tile* dest) {
    blocking->isBlocked = false;
    dest->isBlocked = true;
    blocking = dest;
}
