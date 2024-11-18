//
// Created by sehnertc on 11/12/2024.
//

#include "Wumpus.h"
#include <iostream>
#include "Player.h"

void Wumpus::triggerEffect(Player* player) {
    std::cout << "The Wumpus devours you in an instant! Game over.\n";
    player->setAlive(false);
}

std::string Wumpus::getDescription() const {
    return "Wumpus";
}

std::string Wumpus::getClue() const {
    return "You smell something foul nearby.";
}
