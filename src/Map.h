#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Room.h"
#include "Player.h"
#include "Point.h"

class Room;
class Player;

class Map {
private:
    std::vector<std::vector<Room*>> rooms;
    int gridSize;
    Player* player; // Add a reference to the player

public:
    Map(int size);

    Room *getRoom(int x, int y);

    Room *getRoom(Point pos);

    void generateMap();
    void setPlayer(Player* p) { player = p; } // Method to set the player
    Room* getStartingRoom() const { return rooms[0][0]; }
    void displayMap() const;
    ~Map();

    int getGridSize();
};

#endif // MAP_H
