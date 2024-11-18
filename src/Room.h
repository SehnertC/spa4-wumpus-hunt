#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <string>
#include "Hazard.h"
#include "Point.h"
#include "Weapon.h"


class Hazard;
class Player;

class Room {
private:
    Point position;
    std::vector<Room*> adjacentRooms; // Index 0 = North, 1 = South, 2 = West, 3 = East
    bool hasWeapon;
    std::vector<Weapon*> weapons; // Support multiple weapons
    std::vector<Hazard*> hazards;
    std::string roomDescription;

public:
    Room(Point pos) : hasWeapon(false), roomDescription("An empty chamber."), position(pos) {
        adjacentRooms.resize(4, nullptr); // Initialize with nullptr for all directions
    }

    Point getPos();
    void setAdjacentRoom(int index, Room* room);
    void addHazard(Hazard* hazard);
    std::vector<Hazard*> getHazards() const { return hazards; }
    void removeHazard(Hazard* hazard);
    void setWeapon();
    void addWeapon(Weapon* weapon);

    Weapon *peekWeapon() const;

    bool checkWeapon() const { return !weapons.empty(); }
    bool checkForHazards() const;
    void triggerHazards(Player* player);
    void describeRoom() const;

    void promptWeaponPickup(Player *player);

    void provideClues() const;
    Room* getAdjacentRoom(char direction) const;
    void setDescription(const std::string& description) { roomDescription = description; }
    Weapon* takeWeapon(); // Allow player to pick up weapon
};

#endif // ROOM_H
