#include "Board.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

void Board::rolled(int dieNum) {
    for (auto& tile : tiles) {
        tile.roll(dieNum);
    }
}

string Board::getLine(int left, int edge, int right) {

    ostringstream oss;

    oss << "|" << setw(2) << vertices.at(left).getName();
    oss << setw(0) << "|--";
    oss << setw(2) << edges.at(edge).getName();
    oss << setw(0) << "--|";
    oss << setw(2) << vertices.at(right).getName();
    oss << setw(0) << "|";
    
    return oss.str();

}

string Board::getDesc() {
    // Printing the board can wait, we need building implementation first.
    // (for colours)
    ostringstream oss;

    //Have to hard code all this :(
    oss << "                          " << getLine(0, 0, 1);

    return oss.str();
}
