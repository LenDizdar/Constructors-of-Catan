#include "Builder.h"

#include "Edge.h"
#include "Road.h"
#include "Basement.h"
#include "Vertex.h"

#include <random>
#include <algorithm>

using namespace std;

Builder::Builder(string colour, Dice* die) : 
    colour{colour}, buildingLocations{}, hand{0, 0, 0, 0, 0}, victoryPoints{0}, die{die} {}

void Builder::setDie(Dice* newDie) {
    die = newDie;
}

int Builder::roll() {
    return die->roll();
}

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

std::string Builder::getStatusDesc() {
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

std::string Builder::getColour() {
    return colour;
}

bool Builder::improve(Vertex *v) {
    if (v->getBuilding() && v->getBuilding()->getColour() == colour) {
        ResourceList improveResources;
        try {
            improveResources = v->getBuilding()->getImproveResources();
        } catch (...) {
            return false;
        }
        if (hand >= improveResources) {
            hand -= improveResources;
            v->improve();
            return true;
        }
    }
    return false;
}

bool Builder::buildRoad(Edge *e) {
    if (!e->getRoad()) {
        bool canBuild = false;
        for (int i = 0; i < 2; ++i) {
            if (e->getVertices()[i] && e->getVertices()[i]->getBuilding() &&
                e->getVertices()[i]->getBuilding()->getColour() == colour) {
                canBuild = true;
            }
            for (int j = 0; j < 3; ++j) {
                if (e->getVertices()[i] && e->getVertices()[i]->edges[j] &&
                    e->getVertices()[i]->edges[j]->getRoad() &&
                    e->getVertices()[i]->edges[j]->getRoad()->getColour() == colour) {
                        canBuild = true;
                        break;
                    }
            }
            if (canBuild) {
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

bool Builder::buildRes(Vertex* v, bool gameStart) {
    if (gameStart) {
        if (v->residence) {
            return false;
        } else {
            v->residence = make_unique<Basement>(colour);
            return true;
        }
    } else {
        if (v && v->canBuildOn(*this) && hand >= Basement::getCost()) {
            hand -= Basement::getCost();
            v->residence = make_unique<Basement>(colour);
            return true;
        } else {
            return false;
        }
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

void Builder::addResources(ResourceList toAdd) {
    hand += toAdd;
}

void Builder::addOneResource(Resource toAdd) {
    hand.change(toAdd, 1);
}

bool Builder::trade(Resource losing, Resource receiving, Builder* partner) {
    if (partner && hand.get(losing) && partner->hand.get(receiving)) {
        hand.change(losing, -1);
        partner->hand.change(losing, 1);
        hand.change(receiving, 1);
        partner->hand.change(receiving, -1);
        return true;
    }
    return false;
}

Resource Builder::loseRandomResource() {
    vector<Resource> possible;

    for (int i = 0; i < hand.get(Resource::BRICK); ++i) {
        possible.emplace_back(Resource::BRICK);
    }
    for (int i = 0; i < hand.get(Resource::ENERGY); ++i) {
        possible.emplace_back(Resource::ENERGY);
    }
    for (int i = 0; i < hand.get(Resource::GLASS); ++i) {
        possible.emplace_back(Resource::GLASS);
    }
    for (int i = 0; i < hand.get(Resource::HEAT); ++i) {
        possible.emplace_back(Resource::HEAT);
    }
    for (int i = 0; i < hand.get(Resource::WIFI); ++i) {
        possible.emplace_back(Resource::WIFI);
    }

    if (possible.size() == 0) {
        return Resource::PARK;
    }

    random_device rd;
    mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, possible.size());
    int idx = distrib(gen) - 1;

    hand.change(possible.at(idx), -1);
    return possible.at(idx);

}
