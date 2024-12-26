#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Player.h"
#include "ShipManager.h"
#include "JsonHandler.h"
#include "nlohmann/json.hpp"

#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>


class GameState {
public:
    GameState();
    void set_width(int wid) { width = wid; } 
    void set_height(int hei) { height = hei; } 
    void next_round() { currentRound++; }
    void set_sizes(std::vector<int>& size) {sizes = size;}
    void set_save(bool sv);
    void set_game(bool game) {newGame = game;}

    bool hasSave() {return save;}
    bool getGame() {return newGame;}

    int getCurrentRound() const { return currentRound; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    const std::vector<int>& getSizes() const { return sizes; }

private:
    bool newGame;
    int currentRound;
    int width, height;
    std::vector<int> sizes;
    JsonFileHandler fileHandler;
    bool save = false;
};

#endif