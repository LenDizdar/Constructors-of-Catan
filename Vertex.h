#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "ResourceList.h"
#include "Observer.h"

// Change forward declaration to #include when Building is implemented
#include "Building.h"
class Builder;

// Check for circular dependency issues
class Edge;

class Vertex : public Observer {
    std::unique_ptr<Building> residence;
    friend class Builder;
    Edge* edges[3];
    int index;
    public:
        ~Vertex();
        Vertex(int i) : residence{nullptr}, edges{nullptr, nullptr, nullptr}, index{i} {}
        Building* getBuilding() const { return &(*residence); }
        void notify(Subject& whoNotified);
        bool canBuildOn(Builder& builder);
        std::string getName() const;
        void improve();
};

// istream& operator<<(istream& in, Vertex& vert);
#endif
