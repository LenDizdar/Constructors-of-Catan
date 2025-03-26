#include "Board.h"
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

void Board::rolled(int dieNum) {
    for (auto& tile : tiles) {
        tile.roll(dieNum);
    }
}

Tile* Board::findGoose() {
    for (auto& tile : tiles) {
        if (tile.getIsBlocked()) {
            return &tile;
        }
    }
    return nullptr;
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

string Board::gooseString(int tileIdx) {
    if (tiles.at(tileIdx).getIsBlocked()) {
        return "  GEESE  ";
    } else {
        return "         ";
    }
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
    oss << setw(2) << tiles.at(0).getRollNumStr() << "  " << getLineTop(4, 4, 5) << endl;
    oss << "                  |         |" << gooseString(0)<< "|         |" << endl;
    oss << "                 " << getLineMiddle(5, 1, 6);
    oss << "        " << getLineMiddle(7, 2, 8) << endl;
    oss << "                  | " << tiles.at(1).getResourceName() << "  |";
    oss << "         | " << tiles.at(2).getResourceName() << "  |" << endl;
    oss << "      " << getLineTop(6, 9, 7);
    oss << "  " << setw(2) << tiles.at(1).getRollNumStr() << "  ";
    oss << getLineTop(8, 10, 9);
    oss << "  " << setw(2) << tiles.at(2).getRollNumStr() << "  ";
    oss << getLineTop(10, 11, 11) << endl;
    oss << "        |         |" << gooseString(1)<< "|         |" << gooseString(2) << "|         |" << endl;
    oss << "       " << getLineMiddle(12, 3, 13);
    oss << "        " << getLineMiddle(14, 4, 15);
    oss << "        " << getLineMiddle(16, 5, 17) << endl;
    oss << "        | " << setw(2) << tiles.at(3).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(4).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(5).getResourceName() << "  |" << endl;
    oss << "      |" << setw(2) << vertices.at(12).getName();
    oss << "|  " << setw(2) << tiles.at(3).getRollNumStr();
    oss << "  " << getLineTop(13, 18, 14);
    oss << "  " << setw(2) << tiles.at(4).getRollNumStr();
    oss << "  " <<  getLineTop(15, 19, 16);
    oss << "  " << setw(2) << tiles.at(5).getRollNumStr();
    oss << "  |" << setw(2) << vertices.at(17).getName() << setw(0) << "|" << endl;
    oss << "        |" << gooseString(3)<< "|         |" << gooseString(4)<< "|         |" << gooseString(5)<< "|" << endl;
    oss << "       " << setw(2) << edges.at(20).getName();
    oss << "        " << getLineMiddle(21, 6, 22);
    oss << "        " << getLineMiddle(23, 7, 24);
    oss << "        " << setw(2) << edges.at(25).getName() << endl;
    oss << "        |         | " << tiles.at(6).getResourceName();
    oss << "  |         | " << tiles.at(7).getResourceName();
    oss << "  |         |" << endl;
    oss << "      " << getLineTop(18, 26, 19);
    oss << "  " << setw(2) << tiles.at(6).getRollNumStr() << "  ";
    oss << getLineTop(20, 27, 21);
    oss << "  " << setw(2) << tiles.at(7).getRollNumStr() << "  ";
    oss << getLineTop(22, 28, 23) << endl;
    oss << "        |         |" << gooseString(6)<< "|         |" << gooseString(7)<< "|         |" << endl;
    oss << "       " << getLineMiddle(29, 8, 30);
    oss << "        " << getLineMiddle(31, 9, 32);
    oss << "        " << getLineMiddle(33, 10, 34) << endl;
    oss << "        | " << setw(2) << tiles.at(8).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(9).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(10).getResourceName() << "  |" << endl;
    oss << "      |" << setw(2) << vertices.at(24).getName();
    oss << "|  " << setw(2) << tiles.at(8).getRollNumStr();
    oss << "  " << getLineTop(25, 35, 26);
    oss << "  " << setw(2) << tiles.at(9).getRollNumStr();
    oss << "  " <<  getLineTop(27, 36, 28);
    oss << "  " << setw(2) << tiles.at(10).getRollNumStr();
    oss << "  |" << setw(2) << vertices.at(29).getName() << setw(0) << "|" << endl;
    oss << "        |" << gooseString(8)<< "|         |" << gooseString(9)<< "|         |" << gooseString(10)<< "|" << endl;
    oss << "       " << setw(2) << edges.at(37).getName();
    oss << "        " << getLineMiddle(38, 11, 39);
    oss << "        " << getLineMiddle(40, 12, 41);
    oss << "        " << setw(2) << edges.at(42).getName() << endl;
    oss << "        |         | " << tiles.at(11).getResourceName();
    oss << "  |         | " << tiles.at(12).getResourceName();
    oss << "  |         |" << endl;
    oss << "      " << getLineTop(30, 43, 31);
    oss << "  " << setw(2) << tiles.at(11).getRollNumStr() << "  ";
    oss << getLineTop(32, 44, 33);
    oss << "  " << setw(2) << tiles.at(12).getRollNumStr() << "  ";
    oss << getLineTop(34, 45, 35) << endl;
    oss << "        |         |" << gooseString(11)<< "|         |" << gooseString(12)<< "|         |" << endl;
    oss << "       " << getLineMiddle(46, 13, 47);
    oss << "        " << getLineMiddle(48, 14, 49);
    oss << "        " << getLineMiddle(50, 15, 51) << endl;
    oss << "        | " << setw(2) << tiles.at(13).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(14).getResourceName();
    oss << "  |         | " << setw(2) << tiles.at(15).getResourceName() << "  |" << endl;
    oss << "      |" << setw(2) << vertices.at(36).getName();
    oss << "|  " << setw(2) << tiles.at(13).getRollNumStr();
    oss << "  " << getLineTop(37, 52, 38);
    oss << "  " << setw(2) << tiles.at(14).getRollNumStr();
    oss << "  " <<  getLineTop(39, 53, 40);
    oss << "  " << setw(2) << tiles.at(15).getRollNumStr();
    oss << "  |" << setw(2) << vertices.at(41).getName() << setw(0) << "|" << endl;
    oss << "        |" << gooseString(13)<< "|         |" << gooseString(14)<< "|         |" << gooseString(15)<< "|" << endl;
    oss << "       " << setw(2) << edges.at(54).getName();
    oss << "        " << getLineMiddle(55, 16, 56);
    oss << "        " << getLineMiddle(57, 17, 58);
    oss << "        " << setw(2) << edges.at(59).getName() << endl;
    oss << "        |         | " << tiles.at(16).getResourceName();
    oss << "  |         | " << tiles.at(17).getResourceName();
    oss << "  |         |" << endl;
    oss << "      " << getLineTop(42, 60, 43);
    oss << "  " << setw(2) << tiles.at(16).getRollNumStr() << "  ";
    oss << getLineTop(44, 61, 45);
    oss << "  " << setw(2) << tiles.at(17).getRollNumStr() << "  ";
    oss << getLineTop(46, 62, 47) << endl;
    oss << "                  |" << gooseString(16)<< "|         |" << gooseString(17)<< "|" << endl;
    oss << "                 " << setw(2) << edges.at(63).getName();
    oss << "        " << getLineMiddle(64, 18, 65);
    oss << "        " << setw(2) << edges.at(66).getName() << endl;
    oss << "                  |         | " << tiles.at(18).getResourceName();
    oss << "  |         |" << endl;
    oss << "                " << getLineTop(48, 67, 49);
    oss << "  " << setw(2) << tiles.at(18).getRollNumStr() << "  ";
    oss << getLineTop(50, 68, 51) << endl;
    oss << "                            |" << gooseString(18)<< "|" << endl;
    oss << "                           " << edges.at(69).getName();
    oss << "        " << edges.at(70).getName() << endl;
    oss << "                            |         |" << endl;    
    oss << "                          " << getLineTop(52, 71, 53) << endl;

    return oss.str();
}

void Board::connect() {

    // Hard code all connections :(
    // Tiles observers
    tiles.at(0).attach(&vertices.at(0));
    tiles.at(0).attach(&vertices.at(1));
    tiles.at(0).attach(&vertices.at(3));
    tiles.at(0).attach(&vertices.at(4));
    tiles.at(0).attach(&vertices.at(8));
    tiles.at(0).attach(&vertices.at(9));

    tiles.at(1).attach(&vertices.at(2));
    tiles.at(1).attach(&vertices.at(3));
    tiles.at(1).attach(&vertices.at(7));
    tiles.at(1).attach(&vertices.at(8));
    tiles.at(1).attach(&vertices.at(13));
    tiles.at(1).attach(&vertices.at(14));

    tiles.at(2).attach(&vertices.at(4));
    tiles.at(2).attach(&vertices.at(5));
    tiles.at(2).attach(&vertices.at(9));
    tiles.at(2).attach(&vertices.at(10));
    tiles.at(2).attach(&vertices.at(15));
    tiles.at(2).attach(&vertices.at(16));

    tiles.at(3).attach(&vertices.at(6));
    tiles.at(3).attach(&vertices.at(7));
    tiles.at(3).attach(&vertices.at(12));
    tiles.at(3).attach(&vertices.at(13));
    tiles.at(3).attach(&vertices.at(18));
    tiles.at(3).attach(&vertices.at(19));

    tiles.at(4).attach(&vertices.at(8));
    tiles.at(4).attach(&vertices.at(9));
    tiles.at(4).attach(&vertices.at(14));
    tiles.at(4).attach(&vertices.at(15));
    tiles.at(4).attach(&vertices.at(20));
    tiles.at(4).attach(&vertices.at(21));

    tiles.at(5).attach(&vertices.at(10));
    tiles.at(5).attach(&vertices.at(11));
    tiles.at(5).attach(&vertices.at(16));
    tiles.at(5).attach(&vertices.at(17));
    tiles.at(5).attach(&vertices.at(22));
    tiles.at(5).attach(&vertices.at(23));

    tiles.at(6).attach(&vertices.at(13));
    tiles.at(6).attach(&vertices.at(14));
    tiles.at(6).attach(&vertices.at(19));
    tiles.at(6).attach(&vertices.at(20));
    tiles.at(6).attach(&vertices.at(25));
    tiles.at(6).attach(&vertices.at(26));

    tiles.at(7).attach(&vertices.at(15));
    tiles.at(7).attach(&vertices.at(16));
    tiles.at(7).attach(&vertices.at(21));
    tiles.at(7).attach(&vertices.at(22));
    tiles.at(7).attach(&vertices.at(27));
    tiles.at(7).attach(&vertices.at(28));

    tiles.at(8).attach(&vertices.at(18));
    tiles.at(8).attach(&vertices.at(19));
    tiles.at(8).attach(&vertices.at(24));
    tiles.at(8).attach(&vertices.at(25));
    tiles.at(8).attach(&vertices.at(30));
    tiles.at(8).attach(&vertices.at(31));

    tiles.at(9).attach(&vertices.at(20));
    tiles.at(9).attach(&vertices.at(21));
    tiles.at(9).attach(&vertices.at(26));
    tiles.at(9).attach(&vertices.at(27));
    tiles.at(9).attach(&vertices.at(32));
    tiles.at(9).attach(&vertices.at(33));

    tiles.at(10).attach(&vertices.at(22));
    tiles.at(10).attach(&vertices.at(23));
    tiles.at(10).attach(&vertices.at(28));
    tiles.at(10).attach(&vertices.at(29));
    tiles.at(10).attach(&vertices.at(34));
    tiles.at(10).attach(&vertices.at(35));

    tiles.at(11).attach(&vertices.at(25));
    tiles.at(11).attach(&vertices.at(26));
    tiles.at(11).attach(&vertices.at(31));
    tiles.at(11).attach(&vertices.at(32));
    tiles.at(11).attach(&vertices.at(37));
    tiles.at(11).attach(&vertices.at(38));

    tiles.at(12).attach(&vertices.at(27));
    tiles.at(12).attach(&vertices.at(28));
    tiles.at(12).attach(&vertices.at(33));
    tiles.at(12).attach(&vertices.at(34));
    tiles.at(12).attach(&vertices.at(39));
    tiles.at(12).attach(&vertices.at(40));

    tiles.at(13).attach(&vertices.at(30));
    tiles.at(13).attach(&vertices.at(31));
    tiles.at(13).attach(&vertices.at(36));
    tiles.at(13).attach(&vertices.at(37));
    tiles.at(13).attach(&vertices.at(42));
    tiles.at(13).attach(&vertices.at(43));

    tiles.at(14).attach(&vertices.at(32));
    tiles.at(14).attach(&vertices.at(33));
    tiles.at(14).attach(&vertices.at(38));
    tiles.at(14).attach(&vertices.at(39));
    tiles.at(14).attach(&vertices.at(44));
    tiles.at(14).attach(&vertices.at(45));

    tiles.at(15).attach(&vertices.at(34));
    tiles.at(15).attach(&vertices.at(35));
    tiles.at(15).attach(&vertices.at(40));
    tiles.at(15).attach(&vertices.at(41));
    tiles.at(15).attach(&vertices.at(46));
    tiles.at(15).attach(&vertices.at(47));

    tiles.at(16).attach(&vertices.at(37));
    tiles.at(16).attach(&vertices.at(38));
    tiles.at(16).attach(&vertices.at(43));
    tiles.at(16).attach(&vertices.at(44));
    tiles.at(16).attach(&vertices.at(48));
    tiles.at(16).attach(&vertices.at(49));

    tiles.at(17).attach(&vertices.at(39));
    tiles.at(17).attach(&vertices.at(40));
    tiles.at(17).attach(&vertices.at(45));
    tiles.at(17).attach(&vertices.at(46));
    tiles.at(17).attach(&vertices.at(50));
    tiles.at(17).attach(&vertices.at(51));

    tiles.at(18).attach(&vertices.at(44));
    tiles.at(18).attach(&vertices.at(45));
    tiles.at(18).attach(&vertices.at(49));
    tiles.at(18).attach(&vertices.at(50));
    tiles.at(18).attach(&vertices.at(52));
    tiles.at(18).attach(&vertices.at(53));

}