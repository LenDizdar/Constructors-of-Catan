#include "Subject.h"
//import observer;
#include <vector>

Subject::Subject(int brick, int energy, int glass, int heat, int wifi) :
    observers{},
    resList{std::make_unique<ResourceList>(brick, energy, glass, heat, wifi)} {}
    

Subject::Subject(Resource r) : observers{}, resList{std::make_unique<ResourceList>()} {
        
    resList->set(r, 1);

}

void Subject::notifyObservers() {
    for (auto& obs : observers) {
        obs->notify(*this);
    }
}

void Subject::attach(Observer *obs) {
    observers.emplace_back(obs);
}

void Subject::detach(Observer *obs) {
    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) {
        if (*it == obs) {
            observers.erase(it);
            break;
        }
    }
}
