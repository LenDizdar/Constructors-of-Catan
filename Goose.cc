#include "Goose.h"

void Goose::move(Tile* dest) {
    if (blocking) { blocking->isBlocked = false; }
    dest->isBlocked = true;
    blocking = dest;
}
