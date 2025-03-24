#ifndef EDGE_H
#define EDGE_H
class Vertex;

class Road;

class Edge {
    Vertex* vertices[2];
    Road* road;
    public:
        Edge() : vertices{nullptr, nullptr}, road{nullptr} {}
        const Road* getRoad() { return const_cast<const Road*>(road); }
        const Vertex** getVertices() { return const_cast<const Vertex**>(vertices); }
};

#endif
