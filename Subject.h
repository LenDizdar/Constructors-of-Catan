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
        Subject(int brick, int energy, int glass, int heat, int wifi); //Constructor
                                            // initializes the resource list with
                                            // the corresponding ints

        std::vector<Observer*>getObservers() { return observers; }

        Subject(Resource r); // Constructor
                             // initializes resource list with a single resource
                             // of the specified type

        void notifyObservers(); // Notify all attached observers

        void attach(Observer *obs); // Attach a new observer
        void detach(Observer *obs); // Detach an observer (or do nothing)

        ResourceList* getResList() { return &(*resList); } // Getter
};
#endif
