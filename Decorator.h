#ifndef DECORATOR_H
#define DECORATOR_H

#include "Building.h"

class Decorator : public Building {
    // The building on which this decorator is built
    protected:
        std::unique_ptr<Building> foundation;
    public:
        Decorator(std::unique_ptr<Building> foundation) : 
            Building{foundation->getColour()}, 
            foundation{std::move(foundation)} {}

        virtual ~Decorator() = 0;
};

#endif
