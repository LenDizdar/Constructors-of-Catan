#include "Board.h"

void Board::rolled(int dieNum) {
    for (auto& tile : tiles) {
        tile.roll(dieNum);
    }
}

string Board::getDesc() {
    // Printing the board can wait, we need building implementation first.
    // (for colours)
    return "";
}
