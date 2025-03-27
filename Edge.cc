#include "Edge.h"
#include "Road.h"

using namespace std;

Edge::~Edge() = default;

Edge::Edge(Edge&& other) {
    road = move(other.road);
    vertices[0] = other.vertices[0];
    vertices[1] = other.vertices[1];
    index = other.index;
}

string Edge::getName() const {

    if (road) {

        return road->getColour() + "R";

    }

    string s = to_string(index);
    return s;

}

void Edge::setVerticies(Vertex* v1, Vertex* v2) {

    vertices[0] = v1;
    vertices[1] = v2;

}
