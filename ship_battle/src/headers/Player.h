#ifndef PLAYER_H
#define PLAYER_H

#include "ShipManager.h"
#include "GameBoard.h"
#include "Ability.h"
#include "AbilityManager.h"
#include "JsonHandler.h"
#include "Exceptions.h"
#include "nlohmann/json.hpp"

#include <vector>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <iostream>


class Player {
public:
    Player(int width, int height, std::shared_ptr<ShipManager> shipManager);
    ~Player() = default;

    bool attack_player(int x, int y);

    bool get_flag_dd() const;
    void set_flag_dd(bool new_flag_value);

    void add_ability();
    void use_ability_on_player(Player& enemyPlayer);

    void get_coords(int x, int y);

    GameBoard& getBoard() {return game_board; };

    void print_board() const;
    void print_hidden_board() const;
    void print_abilities() const;

    int get_ability_type();
    std::vector<int> get_ability_list();

    bool allShipsSunk() const;
    
    bool hasAbility();

    bool canPlaceShip(int i, int X, int Y, bool isHorizontal);

    void saveGame(bool isPlayer);
    void loadGame(bool isPlayer);

private:
    int x;
    int y;
    int width;
    int height;
    bool DD_FLAG = false;
    std::shared_ptr<ShipManager> ship_manager;
    GameBoard game_board;
    AbilityManager ability_manager;
    JsonFileHandler fileHandler;
};

#endif