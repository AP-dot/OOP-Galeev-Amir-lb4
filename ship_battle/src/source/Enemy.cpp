#include "Enemy.h"


Enemy::Enemy(int width, int height)
    : width(width), height(height), field(height, std::vector<int>(width, 0)) {}

void Enemy::placeShips(const std::vector<int>& ships, std::shared_ptr<ShipManager> ship_manager) {
    for (size_t i = 0; i < ships.size(); ++i) {
        switch (i) {
        case 0:
            ship_manager->placeShip(0, 0, 0, false);
            break;
        case 1:
            ship_manager->placeShip(1, 0, height - ships[1], true);
            break;
        case 2:
            ship_manager->placeShip(2, width - ships[2], height - 1, false);
            break;
        case 3:
            ship_manager->placeShip(3, width - 1, 0, true);
            break;
        default:
            std::cout << "Error: Неверная длина";
            break;
        }
    }
}

Coordinates Enemy::getNextAttackCoordinates() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> xDist(0, width - 1);
    static std::uniform_int_distribution<> yDist(0, height - 1);
    int x = xDist(gen);
    int y = yDist(gen);
    Coordinates coords(x, y);

    return coords;
}