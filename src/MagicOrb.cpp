//
// Created by sehnertc on 11/12/2024.
//
#include "MagicOrb.h"
#include <iostream>
#include <map>
#include <thread>
#include <chrono>
#include <vector>
#include <cstdlib> // For rand and srand
#include <ctime>   // For seeding rand
#include "Room.h"
#include "Hazard.h"

void MagicOrb::use(char direction) {
    Point pos = player->getCurrentRoom()->getPos();
    std::map<char, Point> directions = Point().directions;

    if (directions.find(direction) != directions.end()) {
        Point vel = directions.at(direction);
        pos = vel + pos;
        Room* nextRoom = this->map->getRoom(pos);

        std::vector<Point> orbPath;
        std::vector<std::vector<char>> displayBuffer = createInitialBuffer();
        std::system("cls");
        renderInitialBuffer(displayBuffer);
        std::cout << std::endl; // Add padding

        int bounces = 0;
        while (bounces < 3) {
            if (nextRoom != nullptr) {
                orbPath.push_back(pos);
                updateDisplayBuffer(displayBuffer, pos, nextRoom);
                renderUpdatedMap(displayBuffer); // Render the entire map to simplify logic
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            } else {
                vel = getRandomValidBounceDirection(vel, pos); // Get a new random valid bounce direction
                bounces++;
                std::cout << "The orb bounces." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            pos = vel + pos;
            nextRoom = this->map->getRoom(pos);
        }
    }
}

Point MagicOrb::getRandomValidBounceDirection(const Point& originalVel, const Point& originalPos) const {
    // Possible vectors with components {-1, 0, 1}
    std::vector<Point> candidates = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1},
        {1, 1}, {-1, 1}, {1, -1}, {-1, -1}
    };

    // Filter candidates based on the dot product condition
    std::vector<Point> validDirections;
    for (const Point& candidate : candidates) {
        if (map->getRoom(Point(candidate.x, candidate.y) + originalPos) != nullptr
            && Point(candidate.x, candidate.y) != -originalVel) {
            validDirections.push_back(candidate);
        }
    }

    // Randomly choose one from the valid directions
    if (!validDirections.empty()) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        int randomIndex = std::rand() % validDirections.size();
        return validDirections[randomIndex];
    }

    // Fallback to a default direction if no valid directions are found (should not happen)
    return {-originalVel.x, -originalVel.y}; // Simple reverse
}

std::vector<std::vector<char>> MagicOrb::createInitialBuffer() const {
    int size = map->getGridSize();
    return std::vector(size, std::vector(size, '*'));
}

void MagicOrb::updateDisplayBuffer(std::vector<std::vector<char>>& buffer, const Point& pos, Room* room) const {
    if (player && player->getCurrentRoom() == room) {
        buffer[pos.y][pos.x] = '+';
    } else if (room->checkForHazards()) {
        buffer[pos.y][pos.x] = getHazardMarker(room);
    } else if (room->checkWeapon()) {
        buffer[pos.y][pos.x] = getWeaponMarker(room);
    } else {
        buffer[pos.y][pos.x] = '.';
    }
}

void MagicOrb::renderInitialBuffer(const std::vector<std::vector<char>>& buffer) const {
    for (int i = 0; i < buffer.size(); ++i) {
        // Render the map row
        for (const char cell : buffer[i]) {
            std::cout << " " << cell << " ";
        }

        // Display key for the first few rows
        if (i == 0) {
            std::cout << "  Key:";
        } else if (i == 1) {
            std::cout << "  + : Player";
        } else if (i == 2) {
            std::cout << "  W : Wumpus";
        } else if (i == 3) {
            std::cout << "  P : Pit";
        } else if (i == 4) {
            std::cout << "  B : Bat";
        } else if (i == 5) {
            std::cout << "  T : Trapdoor";
        } else if (i == 6) {
            std::cout << "  A : Arrow";
        } else if (i == 7) {
            std::cout << "  O : Magic Orb";
        }

        std::cout << std::endl;
    }
    std::cout.flush();
}

void MagicOrb::renderUpdatedMap(const std::vector<std::vector<char>>& buffer) const {
    std::cout << "\033[H"; // Move to top-left corner of the terminal
    for (int i = 0; i < buffer.size(); ++i) {
        // Render the map row
        for (const char cell : buffer[i]) {
            std::cout << " " << cell << " ";
        }

        // Display key for the first few rows
        if (i == 0) {
            std::cout << "  Key:";
        } else if (i == 1) {
            std::cout << "  + : Player | T : Trapdoor";
        } else if (i == 2) {
            std::cout << "  W : Wumpus | A : Arrow";
        } else if (i == 3) {
            std::cout << "  P : Pit    | O : Magic Orb";
        }
        std::cout << std::endl;
    }
    std::cout.flush();
}

void MagicOrb::printSeparator() const {
    // Prints enough new lines to separate map from any messages or inputs
    int gridSize = map->getGridSize();
    for (int i = 0; i < gridSize + 5; ++i) {
        // Print enough lines to clear map area
        std::cout << std::endl;
    }
}

void MagicOrb::clearMessageArea() const {
    // Clear a few lines of the message area to prevent overlapping messages
    std::cout << "\033[J"; // Clear everything from the cursor to the end of the screen
}

char MagicOrb::getHazardMarker(Room* room) const {
    for (Hazard* hazard : room->getHazards()) {
        if (hazard->isWumpus()) {
            return 'W';
        } else if (hazard->getDescription() == "Pit") {
            return 'P';
        } else if (hazard->getDescription() == "Bat") {
            return 'B';
        } else if (hazard->getDescription() == "Trapdoor") {
            return 'T';
        }
    }
    return '@';
}

char MagicOrb::getWeaponMarker(Room* room) const {
    Weapon* weapon = room->peekWeapon();
    if (weapon) {
        if (weapon->getDescription() == "Arrow") {
            return 'A';
        } else if (weapon->getDescription() == "Magic Orb") {
            return 'O';
        } else {
            return '>';
        }
    }
    return '.';
}

std::string MagicOrb::getDescription() const {
    return "Magic Orb";
}
