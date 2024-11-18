//
// Created by sehnertc on 11/12/2024.
//

#include "Trapdoor.h"
#include <iostream>
#include "Player.h"

void Trapdoor::triggerEffect(Player* player) {
    player->moveToRandomTrapdoorRoom();
}

std::string Trapdoor::getDescription() const {
    return "Trapdoor";
}

std::string Trapdoor::getClue() const {
    return "You hear a faint clicking sound beneath your feet.";
}