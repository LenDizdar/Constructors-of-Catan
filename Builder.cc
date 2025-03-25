#include "Builder.h"

#include "Edge.h"
#include "Road.h"
#include "Basement.h"

#include <random>

using namespace std;

Builder::Builder(string colour) : 
    colour{colour}, buildingLocations{}, hand{0, 0, 0, 0, 0}, victoryPoints{0} {}

int Builder::getVictoryPoints() { 
    victoryPoints = 0;
    for (auto& loc : buildingLocations) {
        victoryPoints += loc->getBuilding()->getPointValue();
    }
    return victoryPoints; 
}

void Builder::notify(Subject& whoNotified) {
    hand += *(whoNotified.getResList());
}

//void setLoaded();

//void setFair();

//void roll();

std::string Builder::getStatusDesc() {
    // <colour> has <numPoints> building points, <numBrick> brick, <numEnergy> energy,
    // <numGlass> glass, <numHeat> heat, and <numWiFi> WiFi.
    return colour + " has " + to_string(victoryPoints) + 
          to_string(hand.get(Resource::BRICK)) + " brick, " +
          to_string(hand.get(Resource::ENERGY)) + " energy, " +
          to_string(hand.get(Resource::GLASS)) + " glass, " +
          to_string(hand.get(Resource::HEAT)) + " heat, and " +
          to_string(hand.get(Resource::WIFI)) + " WiFi.";
}

std::string Builder::getResidencesDesc() {
    string toRet = colour + "has built:\n";
    for (auto& loc : buildingLocations) {
        toRet += loc->getName() + " " + loc->getBuilding()->getDesc() + "\n";
    }
    return toRet;
}

bool Builder::improve(Vertex *v) {
    if (v->getBuilding() && v->getBuilding()->getColour() == colour) {
        try {
            ResourceList improveResources = v->residence->getImproveResources();
            if (hand >= improveResources) {
                v->residence = v->residence->improve(move(v->residence));
                hand -= improveResources;
                return true;
            } else {
                return false;
            }
        } catch (...) {
            // This means there is a Tower on v.
            return false;
        }
    } else {
        return false;
    }
}

bool Builder::buildRoad(Edge *e) {
    if (!e->getRoad()) {
        for (int i = 0; i < 2; ++i) {
            if (e->getVertices()[i] && e->getVertices()[i]->getBuilding()->getColour() == colour) {
                if (hand >= Road::getCost()) {
                    hand -= Road::getCost();
                    e->road = make_unique<Road>(colour);
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
    return false;
}

bool Builder::buildRes(Vertex* v) {
    if (v->canBuildOn(*this) && hand >= Basement::getCost()) {
        hand -= Basement::getCost();
        v->residence = make_unique<Basement>(colour);
        return true;
    } else {
        return false;
    }
}

string Builder::halfResources() {
    string lost = "";
    if (hand.getTotal() >= 10) {
        int brickLost = 0;
        int energyLost = 0;
        int glassLost = 0;
        int heatLost = 0;
        int wifiLost = 0;
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> distrib(0, 4);
        // above from cppreference for uniform_int_distribution example
        for (int i = 0; i < hand.getTotal() / 2; ++i) {
            switch (distrib(gen)) {
                case 0 :
                    hand.change(Resource::BRICK, -1);
                    ++brickLost;
                    break;
                case 1 :
                    hand.change(Resource::ENERGY, -1);
                    ++energyLost;
                    break;
                case 2 :
                    hand.change(Resource::GLASS, -1);
                    ++glassLost;
                    break;
                case 3 :
                    hand.change(Resource::HEAT, -1);
                    ++heatLost;
                    break;
                case 4 :
                    hand.change(Resource::WIFI, -1);
                    ++wifiLost;
                    break;
            }
        }
        if (brickLost) {
            lost += to_string(brickLost) + " brick\n";
        }
        if (energyLost) {
            lost += to_string(energyLost) + " energy\n";
        }
        if (glassLost) {
            lost += to_string(glassLost) + " glass\n";
        }
        if (heatLost) {
            lost += to_string(heatLost) + " heat\n";
        }
        if (wifiLost) {
            lost += to_string(wifiLost) + " wifi\n";
        }
    }
    return lost;
}
