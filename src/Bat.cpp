//
// Created by sehnertc on 11/12/2024.
//

#include "Bat.h"
#include <iostream>
#include <cstdlib>

#include "Bat.h"
#include <iostream>
#include "Player.h"
#include <cstdlib>

void Bat::triggerEffect(Player* player) {
    std::cout << "A giant bat carries you to a random chamber!\n";
    player->moveToRandomRoom();
}

std::string Bat::getDescription() const {
    return "Bat";
}

std::string Bat::getClue() const {
    return "You hear the flapping of wings.";
}