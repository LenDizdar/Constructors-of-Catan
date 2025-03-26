#ifndef TOWER_H
#define TOWER_H

#include "Decorator.h"
#include <stdexcept>

class Tower : public Decorator {
    public:
        // The passed parameters are most of what makes a Building subclass
        Tower(std::unique_ptr<Building> foundation) : 
            Decorator{std::move(foundation)} {}

        // The other part is the resourceList
        static ResourceList getCost() { 
            return ResourceList{3, 2, 2, 2, 1}; 
        }

        std::unique_ptr<Building> improve(std::unique_ptr<Building> curr) { throw std::logic_error("can't improve Tower"); }

        ResourceList getImproveResources() { throw std::logic_error("can't improve Tower"); }

        virtual int getPointValue() override { return foundation->getPointValue() + 1; }

        virtual int getNumResources() override { return foundation->getPointValue() + 1; }

        virtual std::string getDesc() override { return "T"; }
};

#endif
