#ifndef BUILDING_H
#define BUILDING_H

#include "Constructable.h"
#include "Subject.h"
#include <string>

class Vertex;

class Building : public Constructable, public Subject {
    // When notified by vertex this is called to update what is sent to the Builder
    void setLastResource(ResourceList oResList) { resList->set(oResList); }
    friend class Vertex;
    public:
        // By default a building's resList is that of a PARK, all 0s
        Building(std::string colour) : 
            Constructable{colour}, Subject{Resource::PARK} {}


        virtual int getPointValue() = 0;

        virtual int getNumResources() = 0;

        virtual std::string getDesc() = 0;

        //virtual std::unique_ptr<Building> improve(std::unique_ptr<Building> curr) = 0;

        virtual ResourceList getImproveResources() = 0;
};

#endif