#include "RandomBoard.h"

using namespace std;

RandomBoard::RandomBoard() : Board{} {

    //Creating tiles
    for (int i = 0; i < 19; ++i) {

        tiles.emplace_back(Tile(0,0,0,0,0,7));

    }

    //Creating verticies
    for (int i = 0; i < 54; ++i) {

        vertices.emplace_back(Vertex(i));

    }

    //Creating edges
    for (int i = 0; i < 72; ++i) {

        edges.emplace_back(Edge(i));

    }

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
