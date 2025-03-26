#ifndef HOUSE_H
#define HOUSE_H

#include "Decorator.h"
#include "Tower.h"

class House : public Decorator {
    public:
        // The passed parameters are most of what makes a Building subclass
        House(std::unique_ptr<Building> foundation) : 
            Decorator{std::move(foundation)} {}

        // The other part is the resourceList
        static ResourceList getCost() { 
            return ResourceList{0, 0, 2, 3, 0}; 
        }

        //std::unique_ptr<Building> improve(std::unique_ptr<Building> curr) { 
        //    return std::make_unique<Tower>(move(curr)); 
        //}

        virtual int getPointValue() override { return foundation->getPointValue() + 1; }

        virtual int getNumResources() override { return foundation->getNumResources() + 1; }

        virtual std::string getDesc() override { return "H"; }

        ResourceList getImproveResources() { return Tower::getCost(); }

};

#endif
