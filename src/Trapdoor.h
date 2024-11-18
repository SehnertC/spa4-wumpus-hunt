//
// Created by sehnertc on 11/12/2024.
//


// Trapdoor.h (Unique Hazard)
#ifndef TRAPDOOR_H
#define TRAPDOOR_H

#include "Hazard.h"
#include <iostream>

class Trapdoor : public Hazard {
public:
    void triggerEffect(Player *player) override;

    std::string getDescription() const override;

    std::string getClue() const override;
};

#endif // TRAPDOOR_H