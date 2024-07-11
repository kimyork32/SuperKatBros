#pragma once
#ifndef SUBJECT_COLISION_H
#define SUBJECT_COLISION_H

#include <vector>
#include <memory>
#include "ObserverColision.h"

class SubjectColision {
public:
    void addObserver(ObserverColision* observer);
    void deleteObserver(size_t);
    void notify(int, int);

private:
    std::vector<ObserverColision*> observersColision;
};

#endif // SUBJECT_COLISION_H
