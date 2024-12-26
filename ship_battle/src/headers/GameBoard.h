#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "ShipManager.h"
#include "JsonHandler.h"
#include "Structures.h"
#include "Exceptions.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>


class GameBoard {
public:
    GameBoard(int width, int height, ShipManager& manager);
    GameBoard(const GameBoard& other);
    GameBoard(GameBoard&& other) noexcept;
    GameBoard& operator=(const GameBoard& other);
    GameBoard& operator=(GameBoard&& other) noexcept;
    ~GameBoard() = default;

    bool placeShipsFromManager();
    bool attackCell(int x, int y, bool double_damage);

    int getWidth();
    int getHeight();

    std::vector<std::vector<CellState>> getBoard(bool isHidden);
    ShipManager& getShips();

    void print_board() const;
    void print_hidden_board() const;

    bool canPlaceShip(Ship* ship, int startX, int startY, bool isVertical) const;

    void saveGame(std::string str);
    void loadGame(std::string str);

private:
    int width;
    int height;
    std::vector<std::vector<CellState>> board1;
    std::vector<std::vector<CellState>> board2;
    std::string cellStateToString(CellState state) const;
    JsonFileHandler fileHandler;
    CellState stringToCellState(const std::string& str) const;
    ShipManager& shipManager;
};

#endif