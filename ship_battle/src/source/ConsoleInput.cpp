#include "ConsoleInput.h"

ConsoleInput::ConsoleInput() {
    this->commandsStrings["ATTACK"] = GameCommand::ATTACK;
    this->commandsStrings["USE_ABILITY"] = GameCommand::USE_ABILITY;
    this->commandsStrings["SAVE"] = GameCommand::SAVE;
    this->commandsStrings["LOAD"] = GameCommand::LOAD;
    this->commandsStrings["START_NEW_GAME"] = GameCommand::START_NEW_GAME;
    this->commandsStrings["EXIT"] = GameCommand::EXIT;
}

int ConsoleInput::getOption() {
    int number;
    std::cin >> number;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputType();
    }

    if (number <= 0) {
        throw NegativeNumberEntering();
    }

    return number;
}

Coordinates ConsoleInput::getCoords() {
    int number1, number2;

    std::cin >> number1 >> number2;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidCoordinatesFormat();
    }

    if (number1 < 0 || number2 < 0) {
        throw NegativeNumberEntering();
    }

    return Coordinates{number1, number2};
}

std::vector<int> ConsoleInput::getSizes() {
    std::vector<int> sizes;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);

    std::istringstream stream(input);
    int value;

    while (stream >> value) {
        if (value < 1 || value > 4) {
            throw InvalidInputType();
        }
        sizes.push_back(value);
    }

    if (sizes.size() < 1 || sizes.size() > 4) {
        throw InvalidInputType();
    }

    return sizes;
}

bool ConsoleInput::getBool() {
    int input;
    std::cin >> input;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InvalidInputType();
    }

    if (input != 0 && input != 1) {
        throw InvalidInputType();
    }

    return static_cast<bool>(input);
}

void ConsoleInput::loadCommands(const std::string& filename) {
    JsonFileHandler fileHandler(filename);
    fileHandler.load();
    json& data = fileHandler.getData();

    std::set<char> keys;
    std::set<std::string> stringCommands;

    for (const auto& item : data.items()) {
        char key = item.key()[0];
        std::string value = item.value();

        if (keys.find(key) != keys.end()) {
            throw std::runtime_error("Duplicate key assignment: " + std::string(1, key));
        }

        if (stringCommands.find(value) != stringCommands.end()) {
            throw std::runtime_error("Duplicate command assignment: " + value);
        }

        if (commandsStrings.find(value) == commandsStrings.end()) {
            throw std::runtime_error("Unknown command: " + value);
        }

        this->commandsChars[key] = this->commandsStrings[value];
        keys.insert(key);
        stringCommands.insert(value);
    }

    if (commandsChars.size() < commandsStrings.size()) {
        throw std::runtime_error("Few commands!");
    }
}

void ConsoleInput::useDefaultCommands() {
    for (int i = 0; i < static_cast<int>(GameCommand::ENUM_END); i++) {
        this->commandsChars[static_cast<char>(static_cast<int>(i + 48))] = static_cast<GameCommand>(i);
    }
}

std::map<std::string, char> ConsoleInput::getGameCommands() {
    this->stringsCmds.clear();
    for (const auto& pair : this->commandsStrings) {
        for (const auto& otherPair : this->commandsChars) {
            if (pair.second == otherPair.second) {
                this->stringsCmds[pair.first] = otherPair.first;
                break;
            }
        }
    }

    return this->stringsCmds;
}

std::map<std::string, char> ConsoleInput::getStartGameCommandsChars() {
    this->stringsCmds.clear();
    std::set<std::string> startCommands;

    startCommands.insert("START_NEW_GAME");
    startCommands.insert("LOAD");
    startCommands.insert("EXIT");

    for (const auto& pair : this->commandsStrings) {
        for (const auto& otherPair : this->commandsChars) {
            if ((pair.second == otherPair.second) && startCommands.count(pair.first)) {
                this->stringsCmds[pair.first] = otherPair.first;
                break;
            }
        }
    }

    return this->stringsCmds;
}

GameCommand ConsoleInput::getCommand() {
    char key;
    std::cin >> key;

    if (std::cin.fail()) {
        std::cin.clear();
        throw InvalidInputType();
    }

    return this->commandsChars.at(key);
}