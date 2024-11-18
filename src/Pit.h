//
// Created by sehnertc on 11/12/2024.
//

// Pit.h
#ifndef PIT_H
#define PIT_H

#include "Hazard.h"

class Pit : public Hazard {
public:
    void triggerEffect(Player *player) override;

    std::string getDescription() const override;

    std::string getClue() const override;
};

#endif // PIT_H
