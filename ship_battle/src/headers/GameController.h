#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Game.h"
#include "ConsoleInput.h"
#include "ConsoleManager.h"
#include "ConsoleDrawer.h"
#include "ConsoleOutput.h"
#include "Enemy.h"

#include <iostream>


template <typename InputHandler, typename OutputHandler, typename Drawer>
class GameControl{
private:
    Game* game;
    InputHandler* inputter;
    DisplayManager<Drawer, OutputHandler> displayer;
    bool isNewGame = false;
    
public:
    GameControl(Game* game) noexcept;
    void start();
    void initNewGame(bool& processGameFlag);
    void save();
    void load();
    ~GameControl() noexcept;
};

#endif