#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "Ability.h"

#include <iostream>


class DoubleDamage : public Ability {
public:
    void use(GameBoard& gameBoard, ShipManager& shipManager) override;
};

#endif