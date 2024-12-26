#ifndef CONSOLE_INPUT_H
#define CONSOLE_INPUT_H

#include "Structures.h"
#include "Exceptions.h"
#include "JsonHandler.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <limits>
#include <sstream>
#include <set>
#include <vector>
#include <map>


class ConsoleInput {
private:
    std::map<char, GameCommand> commandsChars;
    std::map<std::string, GameCommand> commandsStrings;
    std::map<std::string, char> stringsCmds;
public:
    ConsoleInput();
    int getOption();
    bool getBool();
    std::vector<int> getSizes();
    Coordinates getCoords();
    std::map<std::string, char> getGameCommands();
    std::map<std::string, char> getStartGameCommandsChars();
    void loadCommands(const std::string& filename);
    void useDefaultCommands();
    GameCommand getCommand();
};

#endif