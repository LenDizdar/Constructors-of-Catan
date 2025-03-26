#include "Vertex.h"
#include "Edge.h"
#include "Subject.h"
#include "Building.h"
#include "Builder.h"
#include "Road.h"
#include "Basement.h"
#include "House.h"
using namespace std;

Vertex::~Vertex() = default;

Vertex::Vertex(Vertex &&other) { 
    residence = move(other.residence);
    edges[0] = other.edges[0];
    edges[1] = other.edges[1];
    edges[2] = other.edges[2];
    index = other.index;
}

string Vertex::getName() const {

    if (residence) {

        return residence->getColour() + residence->getDesc();

    }

    string s = to_string(index);
    return s;

}

void Vertex::notify(Subject& whoNotified) {
    if (residence) {
        residence->setLastResource(whoNotified.getResList());
        residence->notifyObservers();
    }
}

bool Vertex::canBuildOn(Builder& builder) {
    bool isAttached = false;

    for (auto& edge : edges) {
        if (edge) {
            // check if the builder has a road connected to this vertex
            if (edge->getRoad()->getColour() == builder.getColour()) {
                isAttached = true;
            }

            // check if there are any buildings adjacent to or on the vertex
            for (auto& vertex : {edge->getVertices()[0], edge->getVertices()[1]}) {
                if (vertex && vertex->getBuilding()) {
                    return false;
                }
            }
        }
    }
    return isAttached;
}

void Vertex::improve() {
    if (residence) {
        if (dynamic_cast<Basement*>(&(*residence)) != nullptr) {
            residence = make_unique<House>(move(residence));
        } else if (dynamic_cast<House*>(&(*residence)) != nullptr) {
            residence = make_unique<Tower>(move(residence));
        }
    }
}
