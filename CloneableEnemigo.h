// Interfaz cloneable enemigo

#ifndef CLONEABLE_ENEMIGO_H
#define CLONEABLE_ENEMIGO_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>

class CloneableEnemigo {
public:
	virtual std::unique_ptr<CloneableEnemigo > clone(int newX, int newY) const = 0;
	virtual ~CloneableEnemigo() = default;
};


#endif // !CLONEABLE_ENEMIGO_H
