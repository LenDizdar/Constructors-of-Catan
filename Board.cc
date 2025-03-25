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

string Board::getLineTop(int left, int edge, int right) {

    ostringstream oss;

    oss << "|" << setw(2) << vertices.at(left).getName();
    oss << setw(0) << "|--";
    oss << setw(2) << edges.at(edge).getName();
    oss << setw(0) << "--|";
    oss << setw(2) << vertices.at(right).getName();
    oss << setw(0) << "|";
    
    return oss.str();

}

string Board::getLineMiddle(int left, int tile, int right) {

    ostringstream oss;

    oss << setw(2) << edges.at(left).getName() << "   ";
    oss << setw(2) << tile << "   ";
    oss << setw(2) << edges.at(right).getName();

    return oss.str();

}

string Board::getDesc() {
    // Printing the board can wait, we need building implementation first.
    // (for colours)
    ostringstream oss;

    //Have to hard code all this :(
    oss << "                          " << getLineTop(0, 0, 1) << endl;
    oss << "                            |         |" << endl;
    oss << "                           " << getLineMiddle(1, 0, 2) << endl;
    oss << "                            | " << tiles.at(0).getResourceName() << "  |" << endl;
    oss << "                " << getLineTop(2, 3, 3) << "  ";
    oss << setw(2) << tiles.at(0).getRollNum() << "  " << getLineTop(4, 4, 5) << endl;
    oss << "                  |         |         |         |" << endl;
    oss << "                 " << getLineMiddle(5, 1, 6);
    oss << "        " << getLineMiddle(7, 2, 8) << endl;
    oss << "                  | " << tiles.at(1).getResourceName() << "  |";
    oss << "         | " << tiles.at(2).getResourceName() << "  |" << endl;
    oss << "      " << getLineTop(6, 9, 7);
    oss << "  " << setw(2) << tiles.at(1).getRollNum() << "  ";
    oss << getLineTop(8, 10, 9);
    oss << "  " << setw(2) << tiles.at(2).getRollNum() << "  ";
    oss << getLineTop(10, 11, 11) << endl;
    oss << "        |         |         |         |         |         |" << endl;
    oss << "       " << getLineMiddle(12, 3, 13);
    oss << "        " << getLineMiddle(14, 4, 15);
    oss << "        " << getLineMiddle(16, 5, 17) << endl;
    oss << "        | " << setw(2) << tiles.at(3).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(4).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(5).getResourceName() << "  |" << endl;


    return oss.str();
}
