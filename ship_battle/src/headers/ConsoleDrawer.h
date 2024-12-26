#ifndef CONSOLE_DRAWER_H
#define CONSOLE_DRAWER_H

#include "GameBoard.h"

#include <iostream>
#include <vector>


class ConsoleDrawer {
public:
    ConsoleDrawer() noexcept;
    void print_board(GameBoard& board, bool isHidden) const;
};

#endif