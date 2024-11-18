//
// Created by sehnertc on 11/12/2024.
//

// Arrow.cpp
#include "Arrow.h"
#include <iostream>
#include <thread>

#include "Room.h"

void Arrow::use(char direction) {
    std::cout << "You shoot an arrow to the " << direction << " direction.\n";

    Room* currentRoom = player->getCurrentRoom();
    Room* nextRoom = currentRoom->getAdjacentRoom(direction);

    // Arrow travels up to two spaces
    for (int i = 0; i < 2; ++i) {
        if (nextRoom) {
            if (nextRoom->checkForHazards()) {
                // Check if the hazard is a Wumpus
                for (Hazard* hazard : nextRoom->getHazards()) {
                    if (hazard->isWumpus()) {
                        std::cout << "The arrow strikes the Wumpus! You hear a monstrous roar as it collapses.\n";
                        std::cout << "You have felled the mighty Wumpus!" << std::endl;
                        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                        std::cout << "Nice.";
                        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                        exit(0);
                    }
                }
                std::cout << "The arrow hits something, but it's not the Wumpus.\n";
                return;
            }
            nextRoom = nextRoom->getAdjacentRoom(direction);
        } else {
            std::cout << "The arrow flies off into the darkness.\n";
            break;
        }
    }
}

std::string Arrow::getDescription() const {
    return "Arrow";
}