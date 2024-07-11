#include "SubjectColision.h"

void SubjectColision::addObserver(ObserverColision* observerColision) {
    observersColision.push_back(observerColision);
}

void SubjectColision::notify(int i, int j) {
    for (auto& observer : observersColision) {
        observer->onNotify(i, j);
    }
}

void SubjectColision::deleteObserver(size_t index) {
    observersColision.erase(observersColision.begin() + index);
}