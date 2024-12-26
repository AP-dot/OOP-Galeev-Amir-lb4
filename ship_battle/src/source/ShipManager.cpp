#include "ShipManager.h"

ShipManager::ShipManager(const std::vector<int>& sizes) : fileHandler("save.json"), sizes(sizes) {
    for (int size : sizes) {
        Ship* newShip = new Ship(size, true);
        ships.push_back({newShip, -1, -1, true});
    }
}

ShipManager::~ShipManager() {
    for (const ShipInfo& info : ships) {
        delete info.ship;
    }
}

bool ShipManager::placeShip(int index, int startX, int startY, bool isVertical) {
    if (index < 0 || index >= ships.size() || isVertical != true & isVertical != false) {
        throw OverlappingShipsException();
    }

    ships[index].startX = startX;
    ships[index].startY = startY;
    ships[index].isVertical = isVertical;
    return true;
}

std::pair<Ship*, int> ShipManager::getShipAt(int x, int y) const {
    for (const auto& shipInfo : ships) {
        int shipLength = shipInfo.ship->getLength();
        
        for (int i = 0; i < shipLength; ++i) {
            int currentX = shipInfo.isVertical ? shipInfo.startX : shipInfo.startX + i;
            int currentY = shipInfo.isVertical ? shipInfo.startY + i : shipInfo.startY;
            
            if (currentX == x && currentY == y) {
                return {shipInfo.ship, i};
            }
        }
    }
    return {nullptr, -1};
}

bool ShipManager::allShipsSunk() const {
    for (const auto& shipInfo : ships) {
        if (!shipInfo.ship->isSunk()) {
            return false;
        }
    }
    return true;
}

const std::vector<ShipInfo>& ShipManager::getShips() const {
    return ships;
}

void ShipManager::printShips() const {
    std::cout << "List of Ships:" << std::endl;
    for (const auto& shipInfo : ships) {
        std::cout << "Ship of length " << shipInfo.ship->getLength() 
                  << " at position (" << shipInfo.startX 
                  << ", " << shipInfo.startY 
                  << "), Vertical: " << (shipInfo.isVertical ? "Yes" : "No") 
                  << std::endl;
    }
}

void ShipManager::saveGame(std::string str) {
    try {
        int cnt = 0;

        for (const auto& shipInfo : ships) {
            fileHandler.load();
            json& data = fileHandler.getData();
            data[str]["Ship_manager"][std::to_string(cnt)]["startX"] = shipInfo.startX;
            data[str]["Ship_manager"][std::to_string(cnt)]["startY"] = shipInfo.startY;
            data[str]["Ship_manager"][std::to_string(cnt)]["isVertical"] = shipInfo.isVertical;

            fileHandler.save();
            shipInfo.ship->saveGame(str, cnt);
            ++cnt;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void ShipManager::loadGame(std::string str) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        ships.clear();

        for (size_t cnt = 0; cnt < sizes.size(); ++cnt) {

            const auto& shipJson = data[str]["Ship_manager"][std::to_string(cnt)];
            int startX = shipJson["startX"].get<int>();
            int startY = shipJson["startY"].get<int>();
            bool isVertical = shipJson["isVertical"].get<bool>();

            Ship* newShip = new Ship(sizes[cnt], isVertical);
            newShip->loadGame(str, cnt);

            ships.push_back({newShip, startX, startY, isVertical});
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}