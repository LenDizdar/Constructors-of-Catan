#include "Tile.h"
#include <sstream>
// Whoever  creates a Tile must attach its observers (will be Board)
// Goes for both contructors
Tile::Tile(int brick, int energy, int glass, int heat, int wifi, int rollNum) : 
    Subject{brick, energy, glass, heat, wifi}, rollNum{rollNum} {
        // only a park will be initialized without resources
        if (!brick && !energy && !glass && !heat && !wifi) {
            isBlocked = true;
        } else {
            isBlocked = false;
        }
}


Tile::Tile(Resource r, int rollNum) : Subject{r}, rollNum{rollNum}, isBlocked{false} {
    if (r == Resource::PARK) {
        isBlocked = true;
    }
};


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

// Exists so when a goose is moved we can find who can be stolen from.
std::vector<Builder*> Tile::getBuildersOnTile() {
    std::vector<Builder*> toRet;
    for (auto& obs : getObservers()) {
        Builder* curr = dynamic_cast<Builder*>(obs);
        if (curr) {
            toRet.emplace_back(curr);
        }
    }
    return toRet;
}
