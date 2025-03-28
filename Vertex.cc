#include "Vertex.h"
#include "Edge.h"
#include "Subject.h"
#include "Building.h"
#include "Builder.h"
#include "Road.h"
#include "Basement.h"
#include "House.h"
#include "ResourceList.h"
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

        return residence->getColour().substr(0, 1) + residence->getDesc();

    }

    string s = to_string(index);
    return s;

}

void Vertex::notify(Subject& whoNotified) {
    if (residence) {
        residence->setLastResource(*(whoNotified.getResList()) * residence->getNumResources());
        residence->notifyObservers();
    }
}

bool Vertex::canBuildOn(Builder& builder) {
    bool isAttached = false;

    for (auto& edge : edges) {
        if (edge) {
            // check if the builder has a road connected to this vertex
            if (edge->getRoad() && edge->getRoad()->getColour() == builder.getColour()) {
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
        vector<Observer*> obs;
        
        if (dynamic_cast<Basement*>(&(*residence)) != nullptr) {
            for (auto& ob : obs) {
                residence->detach(ob);
            }
            residence = make_unique<House>(move(residence));
            for (auto& ob : obs) {
                residence->attach(ob);
            }
        } else if (dynamic_cast<House*>(&(*residence)) != nullptr) {
            for (auto& ob : obs) {
                residence->detach(ob);
            }
            residence = make_unique<Tower>(move(residence));
            for (auto& ob : obs) {
                residence->attach(ob);
            }
        }
    }
}

void Vertex::setEdges(Edge* e1, Edge* e2, Edge* e3) {

    edges[0] = e1;
    edges[1] = e2;
    edges[2] = e3;

    if (e1) {

        e1->setVertex(this);

    }

    if (e2) {

        e2->setVertex(this);

    }

    if (e3) {

        e3->setVertex(this);

    }

}
