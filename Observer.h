#ifndef OBSERVER_H
#define OBSERVER_H
#include "ResourceList.h"

class Subject;

class Observer {
    public:
        // The parameter lets us pass the necessary information
        // while avoiding the circular dependency from passing a Subject
        virtual void notify(Subject& whoNotified) = 0;
        virtual ~Observer() = default;
};

#endif
