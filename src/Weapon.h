//
// Created by sehnertc on 11/12/2024.
//

// Weapon.h
#ifndef WEAPON_H
#define WEAPON_H

#include <string>

class Map;
class Player;

class Weapon {
protected:
    Player* player; // Reference to the player
    Map* map;

public:
    Weapon(Player* p, Map* map) : player(p), map(map) {}
    virtual void use(char direction) = 0;
    virtual std::string getDescription() const = 0;
    virtual ~Weapon() {}
};

#endif // WEAPON_H