//
// Created by sehnertc on 11/12/2024.
//

#ifndef HAZARD_H
#define HAZARD_H

#include <string>

#include "Player.h"

class Player;

class Hazard {
public:
    virtual void triggerEffect(Player* player) = 0;
    virtual std::string getClue() const = 0;
    virtual std::string getDescription() const = 0;
    virtual bool isWumpus() const {return false;}
    virtual ~Hazard() {}
};

#endif // HAZARD_H
