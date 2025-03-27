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
    void improve();
    public:
        ~Vertex();
        Vertex(int i) : residence{nullptr}, edges{nullptr, nullptr, nullptr}, index{i} {}
        Vertex(Vertex&& other);
        Building* getBuilding() const { return residence ? &(*residence) : nullptr; }
        void notify(Subject& whoNotified);
        bool canBuildOn(Builder& builder);
        std::string getName() const;
        void setEdges(Edge* e1 = nullptr, Edge* e2 = nullptr, Edge* e3 = nullptr); // Setter
                                                            // Also connects the vertex to
                                                            // each edge passed
};

// istream& operator<<(istream& in, Vertex& vert);
#endif
