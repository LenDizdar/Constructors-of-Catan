#ifndef BUILDER_H
#define BUILDER_H

#include <vector>

#include "Observer.h"
#include "Building.h"
#include "ResourceList.h"

class Edge;
class Vertex;

class Builder : public Observer {
    std::string colour;
    std::vector<Vertex*> buildingLocations;
    ResourceList hand;
    int victoryPoints;
    //std::unique_ptr<Dice> die;
    public:
        Builder(std::string colour);

        void notify(Subject& whoNotified);

        int getVictoryPoints(); // does the calculation so returned IS up to date

        //void setLoaded();

        //void setFair();

        //void roll();

        std::string getColour();

        std::string getStatusDesc();

        std::string getResidencesDesc();

        bool improve(Vertex *v); // returns true if could improve, false otw

        bool buildRoad(Edge *e); // similar to above

        bool buildRes(Vertex* v, bool gameStart); // similar to above

        std::string halfResources();

        Resource loseRandomResource(); // returns park if hand is empty

        void addResources(ResourceList toAdd); //mainly for testing

        void addOneResource(Resource toAdd);

        bool trade(Resource losing, Resource receiving, Builder* partner); // returns true if trade successful
};

#endif