#include "Tile.h"
#include <sstream>
#include "Vertex.h"
// Whoever  creates a Tile must attach its observers (will be Board)
// Goes for both contructors
Tile::Tile(int brick, int energy, int glass, int heat, int wifi, int rollNum, int index) : 
    Subject{brick, energy, glass, heat, wifi}, rollNum{rollNum}, isBlocked{false}, index{index} {}


Tile::Tile(Resource r, int rollNum, int index) : 
    Subject{r}, rollNum{rollNum}, isBlocked{false}, index{index} {}

void Tile::roll(int dieRoll) {
    if (dieRoll == rollNum && !isBlocked) {
        notifyObservers();
    }
}

std::string Tile::getRollNumStr() const {

    if (getResourceName() == " PARK ") {

        return "";

    } else {

        std::ostringstream oss;
        oss << rollNum;
        return oss.str();

    }

}

std::string Tile::getResourceName() const {
    if (resList->get(Resource::BRICK)) {
        return " BRICK";
    }
    if (resList->get(Resource::ENERGY)) {
        return "ENERGY";
    }
    if (resList->get(Resource::GLASS)) {
        return " GLASS";
    }
    if (resList->get(Resource::HEAT)) {
        return " HEAT ";
    }
    if (resList->get(Resource::WIFI)) {
        return " WIFI ";
    }
    return " PARK ";
}

int Tile::getResourceInt() const {
    if (resList->get(Resource::BRICK)) {
        return 0;
    }
    if (resList->get(Resource::ENERGY)) {
        return 1;
    }
    if (resList->get(Resource::GLASS)) {
        return 2;
    }
    if (resList->get(Resource::HEAT)) {
        return 3;
    }
    if (resList->get(Resource::WIFI)) {
        return 4;
    }
    return 5;
}

// Exists so when a goose is moved we can find who can be stolen from.
std::vector<Builder*> Tile::getBuildersOnTile() {
    std::vector<Builder*> toRet;
    for (auto& obs : getObservers()) {
        Vertex* curr = dynamic_cast<Vertex*>(obs);
        if (curr && curr->getBuilding()) {
            Builder* toPlace = dynamic_cast<Builder*>(curr->getBuilding()->getObservers()[0]);
            if (toPlace) {
                toRet.emplace_back(toPlace);
            }
        }
    }
    return toRet;
}
