#include "Vertex.h"
#include "Edge.h"
#include "Subject.h"

void Vertex::notify(Subject& whoNotified) {
    /* UNCOMMENT WHEN BUILDING IMPLEMENTED
    if (residence) {
        residence->setLastResource(whoNotified.getResList());
        residence->notifyObservers();
    }
    */
}

bool Vertex::canBuildOn(Builder& builder) {
    /* UNCOMMENT WHEN BUIDLER AND BUILDING IMPLEMENTED
    bool isAttached = false;

    for (auto& edge : edges) {
        if (edge) {
            // check if the builder has a road connected to this vertex
            if (edge.getRoad()->getColour() == builder->getColour) {
                isAttached = true;
            }

            // check if there are any buildings adjacent to or on the vertex
            for (auto& vertex : edge->getVertices()) {
                if (vertex && vertex->getBuilding()) {
                    return false;
                }
            }
        }
    }
    return isAttached;
    */
    return false;
}