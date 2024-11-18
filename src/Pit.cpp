//
// Created by sehnertc on 11/12/2024.
//

#include "Pit.h"
#include <iostream>
#include "Player.h"

void Pit::triggerEffect(Player* player) {
    std::cout << "You fall into a bottomless pit and are lost forever.\n";
    player->setAlive(false);
}

std::string Pit::getDescription() const {
    return "Pit";
}

std::string Pit::getClue() const {
    return "You feel a chilling breeze.";
}
