#include "Goose.h"

void Goose::move(Tile* dest) {
    if (blocking) { blocking->isBlocked = false; }
    if (dest) { dest->isBlocked = true; }
    blocking = dest;
}
