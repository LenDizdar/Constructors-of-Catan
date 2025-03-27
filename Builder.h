#ifndef BUILDER_H
#define BUILDER_H

#include <vector>

#include "Observer.h"
#include "Building.h"
#include "ResourceList.h"
#include "Dice.h"

class Edge;
class Vertex;

class Builder : public Observer {
    std::string colour;
    std::vector<Vertex*> buildingLocations;
    ResourceList hand;
    int victoryPoints;
    Dice* die;
    public:
        Builder(std::string colour, Dice* die); // Default constructor

        void notify(Subject& whoNotified);

        int getVictoryPoints(); // does the calculation so returned IS up to date

        void setDie(Dice* newDie);

        int roll();

        std::string getColour();

        std::string getStatusDesc();

        std::string getResidencesDesc();

        bool improve(Vertex *v, bool gameStart); // returns true if could improve, false otw

        bool buildRoad(Edge *e, bool gameStart); // similar to above

        bool buildRes(Vertex* v, bool gameStart); // similar to above

        std::string halfResources();

        Resource loseRandomResource(); // returns park if hand is empty

        void addResources(ResourceList toAdd); //mainly for testing

        void addOneResource(Resource toAdd);

        bool trade(Resource losing, Resource receiving, Builder* partner); // returns true if trade successful
};

#endif