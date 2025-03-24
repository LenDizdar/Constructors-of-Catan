#include "Subject.h"
//import observer;

Subject::Subject(int brick, int energy, int glass, int heat, int wifi) :
    observers{},
    resList{std::make_unique<ResourceList>(brick, energy, glass, heat, wifi)} {}

void Subject::notifyObservers() {
    for (auto& obs : observers) {
        obs->notify(*this);
    }
}

void Subject::attach(Observer *obs) {
    observers.emplace_back(obs);
}
