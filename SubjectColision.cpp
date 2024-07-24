#include "SubjectColision.h"

SubjectColision::~SubjectColision() {
    /*for (int i = 0; i < observersColision.size(); i++) {
        delete observersColision[i];
    }*/
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
            //delete observersColision[i];
            for (size_t j = i; j < observersColision.size() - 1; j++) {
                observersColision[j] = observersColision[j + 1];
            }
            observersColision.resize(observersColision.size() - 1);
        }
    }



    //std::cout << "index: " << index << " count: " << countObservserDeletes << " tam: " << observersColision.size() << std::endl;
    
    //bool isBloqueRompible = false;
    //if (dynamic_cast<BloqueDestruible*>(observersColision[index])) {
        
    //if (observersColision[index]->getType() == "BD") {
        //isBloqueRompible = true;
    //}
    //for (size_t i = 0; i < observersColision.size(); i++) {
    //    if (observersColision[i] == bloque) {
    //        observersColision.erase(observersColision.begin() + i - countObservserDeletes);
    //    }
    //}
    //if (index > countObservserDeletes) {
    //    std::cout << "indice: " << index << "- " << countObservserDeletes << " tam " << observersColision.size() << std::endl;
    //    //std::cout << "indice: " << index - countObservserDeletes << " tam: " << observersColision.size() << std::endl;
    //    observersColision.erase(observersColision.begin() + index - countObservserDeletes);
    //}
    //    
    //else {
    //    //std::cout << "indice: " << index << " tam: " << observersColision.size() << std::endl;
    //    std::cout << "indice: " << index << " tam " << observersColision.size() << std::endl;

    //    observersColision.erase(observersColision.begin() + index );
    //}

    ////if (!isBloqueRompible) {
    //countObservserDeletes++;
    ////}
    ////std::cout << std::endl;
}

void SubjectColision::printObserverColision() {
    for (auto& observer : observersColision) {
        //std::cout << observer->getType() << " ";
    }
    std::cout  << std::endl;
}
