#ifndef ENEMY_H
#define ENEMY_H

#include "ShipManager.h"
#include "Player.h"
#include "Structures.h"

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>


class Enemy {
public:
    Enemy(int width, int height);

    void placeShips(const std::vector<int>& ships, std::shared_ptr<ShipManager> ship_manager);
    Coordinates getNextAttackCoordinates();

private:
    int width;
    int height;
    std::vector<std::vector<int>> field;
};

#endif