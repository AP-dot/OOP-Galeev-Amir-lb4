#include "GameController.h"

#include <iostream>


int main() {
    Game* game = new Game();
    auto game_control = GameControl<ConsoleInput, ConsoleOutput, ConsoleDrawer>(game);
    game_control.start();
}

