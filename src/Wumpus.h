//
// Created by sehnertc on 11/12/2024.
//

// Wumpus.h
#ifndef WUMPUS_H
#define WUMPUS_H

#include "Hazard.h"

class Wumpus : public Hazard {
public:
    void triggerEffect(Player *player) override;

    std::string getClue() const override;
    std::string getDescription() const override;
    bool isWumpus() const override { return true; }

};

#endif