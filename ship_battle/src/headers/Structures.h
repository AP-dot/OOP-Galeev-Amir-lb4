#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <map>


enum class PointStates {
    Empty,
    Ship,
    DamagedShip,
    DestroyedShip,
    Unknown,
    Attacked
};

enum class Orientation{
    Vertical,
    Horizontal
};

enum class SegmentState {
    Intact,
    Damaged,
    Destroyed
};

enum class CellState {
    Unknown,
    Empty,
    Ship
};

enum ShipLengths{
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4
};

enum class GameCommand{
    ATTACK,
    USE_ABILITY,
    SAVE,
    LOAD,
    EXIT,
    START_NEW_GAME,
    ENUM_END
};


struct Coordinates{
    int x;
    int y;

    Coordinates(int x, int y) : x(x), y(y) {}

    bool operator==(const Coordinates &other) const {
        return x == other.x && y == other.y;
    }

    Coordinates& operator=(const Coordinates& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;  
    }
};


struct AbilityRes {
    std::string res;
};

#endif