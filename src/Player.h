#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Map.h"
#include "Weapon.h"
#include "Room.h"

class Room;
class Hazard;
class Map;

class Player {
private:
    Room* currentRoom;
    std::vector<Weapon*> inventory;
    bool alive;

public:
    Map* map;
    Player(Map *map);
    void move(char direction);
    void pickUpWeapon(Weapon* weapon);
    void useWeapon(char direction);
    void moveToRandomRoom();

    void moveToRandomTrapdoorRoom();

    Room *getRandomRoom();

    Room *getRandomTrapdoorRoom();

    void handleRoomActions(bool skipTrapdoorCheck);

    void describeCurrentRoom();

    bool isAlive() const { return alive; }
    void setAlive(bool state) { alive = state; }
    Room* getCurrentRoom() const { return currentRoom; }
};

#endif // PLAYER_H
