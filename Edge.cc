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

void Edge::setVertex(Vertex* v1) {

    if (vertices[0]) {

        vertices[1] = v1;

    } else {

        vertices[0] = v1;

    }

}
