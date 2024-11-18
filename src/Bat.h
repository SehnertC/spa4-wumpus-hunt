//
// Created by sehnertc on 11/12/2024.
//

// Bat.h
#ifndef BAT_H
#define BAT_H

#include "Hazard.h"

class Bat : public Hazard {
public:
    void triggerEffect(Player *player) override;

    std::string getDescription() const override;

    std::string getClue() const override;
};

#endif // BAT_H