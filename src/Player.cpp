#include "Player.h"
#include <iostream>
#include <vector>
#include <cstdlib> // For rand
#include <ctime>   // For seeding rand

Player::Player(Map *map) {
    alive = true;
    this->map = map;
    currentRoom = map->getRoom(0, 0);
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Seed random generator
}

void Player::move(char direction) {
    Room* nextRoom = currentRoom->getAdjacentRoom(direction);
    if (nextRoom) {
        currentRoom = nextRoom;
        std::cout << "You move " << direction << "." << std::endl;
        currentRoom->describeRoom();
        currentRoom->promptWeaponPickup(this); // Trigger weapon pickup prompt if a weapon is present
        currentRoom->provideClues();

        // Check for hazards
        if (currentRoom->checkForHazards()) {
            currentRoom->triggerHazards(this);
        }
    } else {
        std::cout << "You cannot move in that direction." << std::endl;
    }
}

void Player::pickUpWeapon(Weapon* weapon) {
    inventory.push_back(weapon);
    std::cout << "Weapon added to your inventory." << std::endl;
}

void Player::useWeapon(char direction) {
    if (!inventory.empty()) {
        inventory.back()->use(direction);
        delete inventory.back(); // Free memory after use
        inventory.pop_back();    // Remove from inventory
    } else {
        std::cout << "You have no weapons to use!" << std::endl;
    }
}

void Player::moveToRandomRoom() {
    currentRoom = getRandomRoom();
    std::cout << "You are transported to a random room!" << std::endl;
    handleRoomActions(true); // Handle all room-related actions
}

void Player::moveToRandomTrapdoorRoom() {
    Room* randomTrapdoorRoom = getRandomTrapdoorRoom();
    if (randomTrapdoorRoom && randomTrapdoorRoom != currentRoom) {
        std::cout << "You are transported to another trapdoor room!" << std::endl;
        currentRoom = randomTrapdoorRoom;
    } else {
        // Fallback to a random room if no other trapdoor rooms are found
        std::cout << "No other trapdoor rooms found. Transporting to a random room instead." << std::endl;
        moveToRandomRoom();
        return; // Avoid re-triggering the trapdoor logic
    }

    handleRoomActions(/*skipTrapdoorCheck=*/true); // Skip trapdoor re-triggering
}

Room* Player::getRandomRoom() {
    std::vector<Room*> allRooms;

    // Collect all rooms in the grid
    for (int i = 0; i < map->getGridSize(); ++i) {
        for (int j = 0; j < map->getGridSize(); ++j) {
            allRooms.push_back(map->getRoom(i, j));
        }
    }

    // Choose a random room
    int randomIndex = std::rand() % allRooms.size();
    return allRooms[randomIndex];
}

Room* Player::getRandomTrapdoorRoom() {
    std::vector<Room*> trapdoorRooms;

    // Collect all rooms with a trapdoor, excluding the current room
    for (int i = 0; i < map->getGridSize(); ++i) {
        for (int j = 0; j < map->getGridSize(); ++j) {
            Room* room = map->getRoom(i, j);
            if (room == currentRoom) {
                continue; // Exclude the current room
            }
            for (Hazard* hazard : room->getHazards()) {
                if (hazard->getDescription() == "Trapdoor") {
                    trapdoorRooms.push_back(room);
                    break;
                }
            }
        }
    }

    // Return a random trapdoor room if available
    if (!trapdoorRooms.empty()) {
        int randomIndex = std::rand() % trapdoorRooms.size();
        return trapdoorRooms[randomIndex];
    }
    return nullptr; // No trapdoor rooms found
}

void Player::handleRoomActions(bool skipTrapdoorCheck) {
    currentRoom->describeRoom();
    currentRoom->promptWeaponPickup(this);
    currentRoom->provideClues();

    // Check for hazards unless specifically told to skip trapdoor re-triggering
    if (currentRoom->checkForHazards()) {
        for (Hazard* hazard : currentRoom->getHazards()) {
            if (skipTrapdoorCheck && hazard->getDescription() == "Trapdoor") {
                continue; // Skip triggering the trapdoor again
            }
            hazard->triggerEffect(this);
        }
    }
}
