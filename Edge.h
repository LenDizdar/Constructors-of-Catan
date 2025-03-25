#ifndef EDGE_H
#define EDGE_H
#include <string>
class Vertex;

class Road;

class Builder;

class Edge {
    Vertex* vertices[2];
    std::unique_ptr<Road> road;
    int index;
    friend class Builder;
    public:
        Edge(int i) : vertices{nullptr, nullptr}, road{nullptr}, index{i} {}
        const Road* getRoad() { return &(*road); }
        const Vertex** getVertices() { return const_cast<const Vertex**>(vertices); }
        std::string getName() const;
};

#endif
