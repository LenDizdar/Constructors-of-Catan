#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

#include "ResourceList.h"
#include "Observer.h"

class Subject {
    std::vector<Observer*> observers;
    protected:
        std::unique_ptr<ResourceList> resList;
    public:
        Subject(int brick, int energy, int glass, int heat, int wifi);
        void notifyObservers();
        void attach(Observer *obs);
        ResourceList* getResList() { return &(*resList); }
};
#endif
