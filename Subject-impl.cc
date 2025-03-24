module subject;

//import observer;
import <vector>;

void Subject::notifyObservers() {
    for (auto& obs : observers) {
        obs->notify(resList);
    }
}

void Subject::attach(Observer *obs) {
    observers.emplace_back(obs);
}
