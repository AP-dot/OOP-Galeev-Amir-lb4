#include "GameState.h"

GameState::GameState() : fileHandler("save.json") {
    currentRound = 1;
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        save = data["Game_info"]["save"].get<bool>();


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

}

void GameState::set_save(bool sv) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        data["Game_info"]["save"] = sv;

        fileHandler.save();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    save = sv;
}