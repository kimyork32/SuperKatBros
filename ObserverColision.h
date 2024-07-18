#pragma once
#ifndef OBSERVER_COLISION_H
#define OBSERVER_COLISION_H

#include <string>

class ObserverColision {
protected:
    std::string type;
public:
    virtual void onNotify(int, int) = 0;
    virtual ~ObserverColision() = default;
    std::string getType() {
        return type;
    }
};

#endif // OBSERVER_COLISION_H
