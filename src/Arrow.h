// Arrow.h
#ifndef ARROW_H
#define ARROW_H

#include "Weapon.h"
#include <iostream>

class Arrow : public Weapon {
public:
    Arrow(Player* p, Map* map) : Weapon(p, map) {}
    void use(char direction) override;
    std::string getDescription() const override;
};

#endif // ARROW_H