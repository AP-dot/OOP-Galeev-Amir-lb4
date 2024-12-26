#ifndef CONSOLE_MANAGER_H
#define CONSOLE_MANAGER_H

#include "ConsoleDrawer.h"
#include "ConsoleOutput.h"
#include "ConsoleInput.h"
#include "Player.h"

#include <string>

template <typename Drawer, typename MessageHandler>
class DisplayManager
{
private:
    MessageHandler *outputter;
    Drawer *drawer;

public:
    DisplayManager();
    void printMessage(std::string message);
    void printAvailableAbilities(Player *player);
    void printField(Player *player, bool isHidden);
    void printCommands(std::map<std::string, char> enableCommands);
    void printMenu(bool isStart);
    ~DisplayManager();
};

#endif