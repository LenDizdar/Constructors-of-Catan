#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <vector>
#include "ResourceList.h"
#include "Observer.h"

// Change forward declaration to #include when Building is implemented
class Building;
class Builder;

// Check for circular dependency issues
class Edge;

class Vertex : public Observer {
    Building* residence;
    Edge* edges[3];
    public:
        Vertex() : residence{nullptr}, edges{nullptr, nullptr, nullptr} {}
        const Building* getBuilding() { return const_cast<const Building*>(residence); }
        void notify(Subject& whoNotified);
        bool canBuildOn(Builder& builder);
};

// istream& operator<<(istream& in, Vertex& vert);
#endif
