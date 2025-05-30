#ifndef EDGE_H
#define EDGE_H
#include <memory>
#include <string>
class Vertex;

#include "Road.h"

class Builder;

class Edge {
    Vertex* vertices[2];
    std::unique_ptr<Road> road;
    int index;
    friend class Builder;
    public:
        ~Edge();
        Edge(int i) : vertices{nullptr, nullptr}, road{nullptr}, index{i} {}
        Edge(Edge&& other);
        const Road* getRoad() { return road ? &(*road) : nullptr; }
        const Vertex** getVertices() { return const_cast<const Vertex**>(vertices); }
        std::string getName() const;
        int getIndex() const { return index; }
        void setVertex(Vertex* v1); // Adds a neighbouring vertex to the list
};

#endif
