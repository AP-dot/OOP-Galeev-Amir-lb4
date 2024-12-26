#ifndef ABILITY_H
#define ABILITY_H

#include "GameBoard.h"

class Ability {
public:
    virtual void use(GameBoard& gameBoard, ShipManager& shipManager) = 0;
    virtual ~Ability() = default;
};

#endif