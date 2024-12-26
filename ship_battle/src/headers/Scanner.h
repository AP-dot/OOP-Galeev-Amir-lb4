#ifndef SCANNER_H
#define SCANNER_H

#include "Ability.h"

#include <iostream>


class Scanner : public Ability {
public:
    void use(GameBoard& gameBoard, ShipManager& shipManager) override;
    void get_coords(int x, int y);
private:
    int x;
    int y;
};

#endif