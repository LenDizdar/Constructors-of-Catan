#ifndef BUILDING_H
#define BUILDING_H

#include "Constructable.h"
#include "Subject.h"
#include <string>

class Building : public Constructable, public Subject {
    protected:
        int pointValue;
        int numResources;
        std::string buildingType;
    public:
        // By default a building's resList is that of a PARK, all 0s
        Building(int pVal, int numRes, std::string buildingType, std::string colour) : 
            Constructable{colour}, Subject{Resource::PARK}, pointValue{pVal},
            numResources{numRes}, buildingType{buildingType} {}

        int getPointValue() { return pointValue; }

        int getNumResources() { return numResources; }

        std::string getDesc() { return buildingType; }

        virtual ~Building() = 0;
};

#endif