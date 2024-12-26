#include "Scanner.h"

void Scanner::use(GameBoard& gameBoard, ShipManager& shipManager) {
    for (int dy = 0; dy < 2; ++dy) {
        for (int dx = 0; dx < 2; ++dx) {
            int checkX = x + dx;
            int checkY = y + dy;

            if (checkX < 0 || checkX >= gameBoard.getWidth() || checkY < 0 || checkY >= gameBoard.getHeight()) {
                throw; //ИСПРАВИТЬ
                continue;
            }

            auto [ship, segmentIndex] = shipManager.getShipAt(checkX, checkY);
            if (ship != nullptr) {
                std::cout << "Обнаружен сегмент корабля\n";
            }
        }
    }
    std::cout << "Произведено сканирование (" << x << ", " << y << ").\n";
}

void Scanner::get_coords(int x, int y) {
    this->x = x;
    this->y = y;
}