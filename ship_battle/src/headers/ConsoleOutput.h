#ifndef CONSOLE_OUTPUT_H
#define CONSOLE_OUTPUT_H

#include "AbilityManager.h"
#include "Player.h"


class ConsoleOutput {
public:
    ConsoleOutput() noexcept;
    void printAvailableAbilities(Player* Player) noexcept;
    void printMessage(std::string message);
    void printMenu(bool isStart);
    void printCommands(std::map<std::string, char> enableCommands);
    ~ConsoleOutput() noexcept {};
};

#endif