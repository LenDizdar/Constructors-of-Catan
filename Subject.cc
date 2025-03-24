export module subject;

import <vector>;

import resourcelist;
import observer;

export class Subject {
    std::vector<Observer*> observers;
    ResourceList *resList;
    public:
        void notifyObservers();
        void attach(Observer *obs);
};
