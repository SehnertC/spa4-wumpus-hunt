//
// Created by sehnertc on 11/12/2024.
//

#ifndef MAGICORB_H
#define MAGICORB_H

#include "Weapon.h"
#include "Map.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib> // For rand and srand
#include <ctime>   // For seeding rand


class MagicOrb : public Weapon {
public:
    MagicOrb(Player* p, Map* map) : Weapon(p, map) {
        // Seed random generator once
        static bool seeded = false;
        if (!seeded) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            seeded = true;
        }
    }
    void use(char direction) override;

    Point getRandomValidBounceDirection(const Point &originalVel, const Point &originalPos) const;

    std::vector<std::vector<char>> createInitialBuffer() const;

    void updateDisplayBuffer(std::vector<std::vector<char>> &buffer, const Point &pos, Room *room) const;

    void renderInitialBuffer(const std::vector<std::vector<char>> &buffer) const;

    void renderUpdatedMap(const std::vector<std::vector<char>> &buffer) const;

    void renderMapWithKey(const std::vector<std::vector<char>> &buffer) const;

    void printSeparator() const;

    void clearMessageArea() const;

    char getHazardMarker(Room *room) const;

    char getWeaponMarker(Room *room) const;

    std::string getDescription() const override;
};


#endif // MAGICORB_H
