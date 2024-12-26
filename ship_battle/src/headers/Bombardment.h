#ifndef BOMBARDMENT_H
#define BOMBARDMENT_H

#include "Ability.h"

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>


class Bombardment : public Ability {
public:
    void use(GameBoard& gameBoard,ShipManager& shipManager) override;
};

#endif