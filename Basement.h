#ifndef BASEMENT_H
#define BASEMENT_H

#include "Building.h"

class Basement : public Building {
    public:
        // The passed parameters are most of what makes a Building subclass
        Basement(std::string colour) : Building{1, 1, "B", colour} {}

        // The other part is the resourceList
        static std::unique_ptr<ResourceList> getCost() { 
            return std::make_unique<ResourceList>(1, 1, 1, 0, 1); 
        }
};

#endif
