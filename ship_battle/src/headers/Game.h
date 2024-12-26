#ifndef GAME_H
#define GAME_H

#include "GameBoard.h"
#include "ShipManager.h"
#include "Ship.h"
#include "AbilityManager.h"
#include "Player.h"
#include "Enemy.h"
#include "JsonHandler.h"
#include "GameState.h"
#include "ConsoleManager.h"
#include "ConsoleDrawer.h"
#include "ConsoleInput.h"
#include "ConsoleOutput.h"
#include "nlohmann/json.hpp"
#include "Structures.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>


class Game {
public:
    Game();
    void newGame();
    Coordinates enemyTurn();
    bool hasSave();
    int getCurrentRound() const { return currentRound; }
    GameState getState() { return game_state; }
    Player* getPlayer(bool isEnemy) {
        return isEnemy ? enemy : player;
    }
    void nextRound() {currentRound++;}
    void saveGame();
    void loadGame();

private:
    int currentRound;
    int number;
    int height;
    int width;
    Player* player;
    Player* enemy;
    Enemy* Enemy_;
    std::vector<int> sizes;
    GameState game_state;

    JsonFileHandler fileHandler;

};

#endif