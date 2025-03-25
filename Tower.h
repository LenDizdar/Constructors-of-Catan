#ifndef TOWER_H
#define TOWER_H

#include "Decorator.h"

class Basement : public Decorator {
    public:
        // The passed parameters are most of what makes a Building subclass
        Basement(std::unique_ptr<Building> foundation) : 
            Decorator{1, 1, "T", foundation} {}

        // The other part is the resourceList
        static ResourceList getCost() { 
            return ResourceList{3, 2, 2, 2, 1}; 
        }
};

#endif
