#ifndef HOUSE_H
#define HOUSE_H

#include "Decorator.h"

class Basement : public Decorator {
    public:
        // The passed parameters are most of what makes a Building subclass
        Basement(std::unique_ptr<Building> foundation) : 
            Decorator{1, 1, "H", foundation} {}

        // The other part is the resourceList
        static ResourceList getCost() { 
            return ResourceList{0, 0, 2, 3, 0}; 
        }
};

#endif
