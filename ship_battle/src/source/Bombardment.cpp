#include "Bombardment.h"

void Bombardment::use(GameBoard& gameBoard, ShipManager& shipManager) {
    const auto& ships = shipManager.getShips();
    if (ships.empty()) {
        std::cout << "Нет доступных кораблей для обстрела.\n";
        return;
    }

    int shipIndex = rand() % ships.size();
    Ship* ship = ships[shipIndex].ship;
    int shipLength = ship->getLength();

    int segmentIndex = rand() % shipLength;

    int x = ships[shipIndex].isVertical ? ships[shipIndex].startX : ships[shipIndex].startX + segmentIndex;
    int y = ships[shipIndex].isVertical ? ships[shipIndex].startY + segmentIndex : ships[shipIndex].startY;

    gameBoard.attackCell(x, y, false);

    std::cout << "Произведен обстрел координат (" << x << ", " << y << ").\n";
}