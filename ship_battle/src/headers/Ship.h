#ifndef SHIP_H
#define SHIP_H

#include "Structures.h"
#include "Exceptions.h"
#include "JsonHandler.h"
#include "nlohmann/json.hpp"

#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>


class Ship {
public:
    Ship(int length, bool isVertical);
    
    int getLength() const;
    bool isVertical() const;
    SegmentState getSegmentState(int index) const;

    void hit(int index, bool double_damage);
    bool isSunk() const;

    void printStatus() const;

    void saveGame(std::string str, int cnt);
    void loadGame(std::string str, int cnt);

private:
    int length;
    bool vertical;
    std::vector<SegmentState> segments;
    JsonFileHandler fileHandler;
};

#endif