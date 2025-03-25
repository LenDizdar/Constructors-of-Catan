#ifndef DECORATOR_H
#define DECORATOR_H

#include "Building.h"

class Decorator : public Building {
    // The building on which this decorator is built
    std::unique_ptr<Building> foundation;
    public:
        Decorator(int pVal, int numRes, std::string buildingType, 
                  std::unique_ptr<Building> foundation) : 
            Building{pVal, numRes, buildingType, foundation->getColour()}, 
            foundation{foundation} {}

        // Take note! This means that decorator point values are EXTRA points
        int getPointValue() { return pointValue + foundation->getPointValue(); }

        // Take note! This means that decorator resource values are EXTRA resources
        int getNumResources() { return numResources + foundation->getNumResources(); }

        virtual ~Decorator() = 0;
};

#endif
