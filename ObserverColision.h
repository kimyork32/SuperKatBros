#pragma once
#ifndef OBSERVER_COLISION_H
#define OBSERVER_COLISION_H

class ObserverColision {
public:
    virtual void onNotify(int, int) = 0;
    virtual ~ObserverColision() = default;
};

#endif // OBSERVER_COLISION_H
