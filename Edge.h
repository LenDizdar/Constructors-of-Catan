#ifndef EDGE_H
#define EDGE_H
#include <string>
class Vertex;

class Road;

class Edge {
    Vertex* vertices[2];
    Road* road;
    int index;
    public:
        Edge(int i) : vertices{nullptr, nullptr}, road{nullptr}, index{i} {}
        const Road* getRoad() { return const_cast<const Road*>(road); }
        const Vertex** getVertices() { return const_cast<const Vertex**>(vertices); }
        std::string getName() const;
};

#endif
