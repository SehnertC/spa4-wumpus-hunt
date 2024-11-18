#include "Map.h"

#include <algorithm>

#include "Wumpus.h"
#include "Pit.h"
#include "Bat.h"
#include "Trapdoor.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#include "Arrow.h"
#include "MagicOrb.h"

Map::Map(const int size) : gridSize(size) {
    rooms.resize(gridSize, std::vector<Room*>(gridSize, nullptr));
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            rooms[i][j] = new Room(Point(j, i));
        }
    }
}

int Map::getGridSize() {
    return gridSize;
}

Room* Map::getRoom(const int x, const int y) {
    if(x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        return rooms[y][x];
    }

    return nullptr;
}

Room* Map::getRoom(const Point pos) {
    if(pos.x >= 0 && pos.x < gridSize && pos.y >= 0 && pos.y < gridSize) {
        return rooms[pos.y][pos.x];
    }

    return nullptr;
}

void Map::generateMap() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Ensure only one Wumpus is placed on the map
    int wumpusX = rand() % gridSize;
    int wumpusY = rand() % gridSize;
    rooms[wumpusY][wumpusX]->addHazard(new Wumpus());

    // Place other hazards, ensuring only one hazard per tile
    std::vector<Point> availablePositions;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (i != wumpusY || j != wumpusX) {
                availablePositions.emplace_back(j, i); // Add Point(j, i) to available positions
            }
        }
    }

    // Shuffle available positions for random placement
    std::shuffle(availablePositions.begin(), availablePositions.end(), std::mt19937(std::random_device()()));

    // Place other hazards
    if (!availablePositions.empty()) {
        for (int i = 0; i < rand() % 2 + 1; i++) {
            Point pitPos = availablePositions.back();
            rooms[pitPos.y][pitPos.x]->addHazard(new Pit());
            availablePositions.pop_back();
        }
    }
    if (!availablePositions.empty()) {
        for (int i = 0; i < rand() % 2 + 1; i++) {
            Point batPos = availablePositions.back();
            rooms[batPos.y][batPos.x]->addHazard(new Bat());
            availablePositions.pop_back();
        }
    }
    if (!availablePositions.empty()) {
        for (int i = 0; i < rand() % 2 + 2; i++) {
            Point trapdoorPos = availablePositions.back();
            rooms[trapdoorPos.y][trapdoorPos.x]->addHazard(new Trapdoor());
            availablePositions.pop_back();
        }
    }

    // Place weapons on remaining tiles
    for (const auto& pos : availablePositions) {
        if (rand() % 3 == 0) {
            if (rand() % 3 >= 1) {
                rooms[pos.y][pos.x]->addWeapon(new Arrow(player, this));
            } else {
                rooms[pos.y][pos.x]->addWeapon(new MagicOrb(player, this));
            }
        }
    }

    // Establish room connections for all rooms in the grid
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (i > 0) rooms[i][j]->setAdjacentRoom(0, rooms[i - 1][j]); // North
            else rooms[i][j]->setAdjacentRoom(0, nullptr);
            if (i < gridSize - 1) rooms[i][j]->setAdjacentRoom(1, rooms[i + 1][j]); // South
            else rooms[i][j]->setAdjacentRoom(1, nullptr);
            if (j > 0) rooms[i][j]->setAdjacentRoom(2, rooms[i][j - 1]); // West
            else rooms[i][j]->setAdjacentRoom(2, nullptr);
            if (j < gridSize - 1) rooms[i][j]->setAdjacentRoom(3, rooms[i][j + 1]); // East
            else rooms[i][j]->setAdjacentRoom(3, nullptr);
        }
    }
}

void Map::displayMap() const {
    std::cout << std::endl;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            // Player's position is represented by '+'
            if (player && player->getCurrentRoom() == rooms[i][j]) {
                std::cout << " + ";
            }
            // Display hazard markers
            else if (rooms[i][j]->checkForHazards()) {
                // Assume each hazard has a unique identifier (e.g., 'W' for Wumpus, 'P' for Pit, etc.)
                bool hazardPrinted = false;
                for (Hazard* hazard : rooms[i][j]->getHazards()) {
                    if (hazard->isWumpus()) {
                        std::cout << " W "; // Wumpus
                        hazardPrinted = true;
                        break;
                    } else if (hazard->getDescription() == "Pit") {
                        std::cout << " P "; // Pit
                        hazardPrinted = true;
                        break;
                    } else if (hazard->getDescription() == "Bat") {
                        std::cout << " B "; // Bat
                        hazardPrinted = true;
                        break;
                    } else if (hazard->getDescription() == "Trapdoor") {
                        std::cout << " T "; // Trapdoor
                        hazardPrinted = true;
                        break;
                    }
                }
                if (!hazardPrinted) {
                    std::cout << " @ "; // Generic hazard marker
                }
            }
            // Display weapon markers
            else if (rooms[i][j]->checkWeapon()) {
                // Peek at the weapon to display the appropriate marker
                Weapon* weapon = rooms[i][j]->peekWeapon();
                if (weapon) {
                    if (weapon->getDescription() == "Arrow") {
                        std::cout << " A "; // Arrow
                    } else if (weapon->getDescription() == "Magic Orb") {
                        std::cout << " O "; // Magic Orb
                    } else {
                        std::cout << " > "; // Generic weapon marker
                    }
                }
            }
            // Empty room
            else {
                std::cout << " . ";
            }
        }
        std::cout << std::endl; // Newline for next row
    }

    std::cout << std::endl;
}

Map::~Map() {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            delete rooms[i][j];
        }
    }
}
