#pragma once
#ifndef SUBJECT_COLISION_H
#define SUBJECT_COLISION_H

#include <vector>
#include <memory>
#include <iostream>
#include "ObserverColision.h"
#include "BloqueDestruible.h"


class SubjectColision {
public:
    ~SubjectColision();
    void addObserver(std::shared_ptr<ObserverColision>);
    void deleteObserver(std::shared_ptr<Bloque>);
    void notify(int, int);
    void printObserverColision();
    unsigned short int countObservserDeletes = 0;

private:
    std::vector<std::shared_ptr<ObserverColision>> observersColision;
};

#endif // SUBJECT_COLISION_H
