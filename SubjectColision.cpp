#include "SubjectColision.h"

SubjectColision::~SubjectColision() {
    observersColision.clear();
}
void SubjectColision::addObserver(std::shared_ptr<ObserverColision> observerColision) {
    observersColision.push_back(observerColision);
}

void SubjectColision::notify(int i, int j) {
    for (auto& observer : observersColision) {
        observer->onNotify(i, j);
    }
}

void SubjectColision::deleteObserver(std::shared_ptr<Bloque> bloque) {

    for (size_t i = 0; i < observersColision.size(); i++) {
        if (observersColision[i] == bloque) {
            for (size_t j = i; j < observersColision.size() - 1; j++) {
                observersColision[j] = observersColision[j + 1];
            }
            observersColision.resize(observersColision.size() - 1);
        }
    }

}

void SubjectColision::printObserverColision() {
    for (auto& observer : observersColision) {
    }
    std::cout  << std::endl;
}
