#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include "Ship.h"
#include "JsonHandler.h"
#include "Exceptions.h"
#include "nlohmann/json.hpp"

#include <vector>
#include <string>
#include <iostream>


struct ShipInfo {
    Ship* ship;
    int startX;
    int startY;
    bool isVertical;
};

class ShipManager {
public:
    ShipManager(const std::vector<int>& sizes);
    ~ShipManager();

    bool placeShip(int index, int startX, int startY, bool isVertical);
    
    std::pair<Ship*, int> getShipAt(int x, int y) const;
    
    const std::vector<ShipInfo>& getShips() const;

    bool allShipsSunk() const;

    void printShips() const;

    void saveGame(std::string str);
    void loadGame(std::string str);

private:
    std::vector<int> sizes; 
    std::vector<ShipInfo> ships;
    JsonFileHandler fileHandler;
};

#endif