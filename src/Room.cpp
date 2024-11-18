#include "Room.h"
#include "Player.h"
#include <iostream>

Point Room::getPos() {
    return position;
}

void Room::setAdjacentRoom(int index, Room* room) {
    if (index >= 0 && index < adjacentRooms.size()) {
        adjacentRooms[index] = room;
    }
}

void Room::addHazard(Hazard* hazard) {
    if (hazards.empty()) { // Only allow one hazard per room
        hazards.push_back(hazard);
    }
}

void Room::setWeapon() {
    hasWeapon = true;
}

void Room::addWeapon(Weapon* weapon) {
    if (!hasWeapon) {
        weapons.push_back(weapon);
        hasWeapon = true;
    }
}

Weapon* Room::peekWeapon() const {
    if (!weapons.empty()) {
        return weapons.front(); // Return the first weapon without removing it
    }
    return nullptr; // Return nullptr if there are no weapons
}

bool Room::checkForHazards() const {
    return !hazards.empty();
}

void Room::triggerHazards(Player* player) {
    for (Hazard* hazard : hazards) {
        hazard->triggerEffect(player);
    }
}

void Room::removeHazard(Hazard *hazard) {
    hazards.erase(hazards.begin(), hazards.end());
}


void Room::describeRoom() const {
    std::cout << roomDescription << std::endl;
    if (hasWeapon) {
        std::cout << "You notice a weapon lying here." << std::endl;
    }
}

void Room::promptWeaponPickup(Player* player) {
    if (hasWeapon) {
        std::cout << "You see a weapon. Would you like to pick it up? (y/n): ";
        char choice;
        std::cin >> choice;
        if (std::tolower(choice) == 'y') {
            Weapon* weapon = takeWeapon();
            if (weapon) {
                player->pickUpWeapon(weapon);
                std::cout << "You picked up the weapon: " << weapon->getDescription() << std::endl;
            }
        }
    }
}

void Room::provideClues() const {
    for (const Room* adj : adjacentRooms) {
        if (adj) {
            for (Hazard* hazard : adj->hazards) {
                std::cout << "Clue: " << hazard->getClue() << std::endl;
            }
        }
    }
}

Room* Room::getAdjacentRoom(char direction) const {
    switch (direction) {
        case 'n': return adjacentRooms[0]; // North
        case 's': return adjacentRooms[1]; // South
        case 'w': return adjacentRooms[2]; // West
        case 'e': return adjacentRooms[3]; // East
        default: return nullptr;
    }
}

Weapon* Room::takeWeapon() {
    if (!weapons.empty()) {
        Weapon* weapon = weapons.back();
        weapons.pop_back();
        hasWeapon = !weapons.empty(); // Update weapon status
        return weapon;
    }
    return nullptr;
}
