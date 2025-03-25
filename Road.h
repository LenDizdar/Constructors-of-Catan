#ifndef ROAD_H
#define ROAD_H

#include "Constructable.h"
#include "ResourceList.h"

class Road : public Constructable {
    public:
        Road(std::string colour) : Constructable{colour} {}
        static ResourceList getCost() {
            return ResourceList{0, 0, 0, 1, 1};
        }
};

#endif
