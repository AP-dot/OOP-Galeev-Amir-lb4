#include "GameController.h"

template <typename InputHandler, typename OutputHandler, typename Drawer>
GameControl<InputHandler, OutputHandler, Drawer>::GameControl(Game* game) noexcept : game(game) {
    inputter = new InputHandler();
}

template <typename InputHandler, typename OutputHandler, typename Drawer>
GameControl<InputHandler, OutputHandler, Drawer>::~GameControl() noexcept{
    delete inputter;
}

template <typename InputHandler, typename OutputHandler, typename Drawer>
void GameControl<InputHandler, OutputHandler, Drawer>::initNewGame(bool& processGameFlag){
    try{
        this->inputter->loadCommands("commands.json");
    } catch(const std::runtime_error& e) {
        displayer.printMessage("Commnads loading error, default settings will be applied");
        this->inputter->useDefaultCommands();
    }
    
    displayer.printMessage("\nSelect option:");
    displayer.printCommands(this->inputter->getStartGameCommandsChars());

    bool optionSelected = false;
    while (!optionSelected){
        GameCommand command;

        try {
            command = this->inputter->getCommand();
        }catch (const std::out_of_range& e) {
            displayer.printMessage("Incorrect command");
            continue;
        } catch (const std::exception& e){
            displayer.printMessage(e.what());
            continue;
        }

        switch (command) {
        case GameCommand::START_NEW_GAME:
            isNewGame = true;
            optionSelected = true;
            break;
        case GameCommand::LOAD: 
            if (this->game->getState().hasSave()) {
                displayer.printMessage("Loading");
                this->load();
                optionSelected = true;
            } else {
                displayer.printMessage("You have not saves");
            }
            break;
        case GameCommand::EXIT:
            processGameFlag = false;
            optionSelected = true;
            displayer.printMessage("Exit");
            break;
        
        default:
            displayer.printMessage("Incorrect command");
            break;
        }
    }
}

template <typename InputHandler, typename OutputHandler, typename Drawer>
void GameControl<InputHandler, OutputHandler, Drawer>::start() {
    bool processGameFlag = true;
    this->initNewGame(processGameFlag);

    while (processGameFlag) {
        if (isNewGame){
            this->game->newGame();
            isNewGame = false;
        }

        displayer.printMessage("\nSelect option:");
        displayer.printCommands(this->inputter->getGameCommands());
        
        while (!game->getPlayer(true)->allShipsSunk() && !game->getPlayer(false)->allShipsSunk()) {
            std::string roundMessage = "\nCurrent round: " + std::to_string(this->game->getCurrentRound());
            displayer.printMessage(roundMessage);

            displayer.printField(this->game->getPlayer(false), false);
            displayer.printField(this->game->getPlayer(true), true);

            displayer.printAvailableAbilities(this->game->getPlayer(false));

            bool optionSelected = false;
            GameCommand option;

            while(!optionSelected){
                try {
                    option = inputter->getCommand();
                    optionSelected = true;
                } catch (const std::out_of_range& e) {
                    displayer.printMessage("Incorrect command");
                } catch (const std::exception& e){
                    displayer.printMessage(e.what());
                }
            }
            switch (option) {
            case GameCommand::ATTACK: {
                displayer.printMessage("\nSelected attack, enter coordinates (x, y)");
                Coordinates coords(0,0);
                bool check = false;
                
                while(!check){
                    try {
                        coords = this->inputter->getCoords();
                        check = true;
                    } catch (const std::out_of_range& e) {
                        displayer.printMessage("Incorrect command");
                    }
                }

                this->game->getPlayer(true)->attack_player(coords.x, coords.y);
                Coordinates crd = this->game->enemyTurn();
                this->game->getPlayer(false)->attack_player(crd.x, crd.y);
                displayer.printMessage("\nEnemy attacked the point " + std::to_string(crd.x) + " " +  std::to_string(crd.y));
                this->game->nextRound();
                break;
            }
            case GameCommand::USE_ABILITY: {
                if (this->game->getPlayer(false)->get_ability_type() == 2) {
                    displayer.printMessage("\nScanner, enter coordinates (x, y)");
                    Coordinates coords(0,0);
                    bool check = false;
                    
                    while(!check){
                        try {
                            coords = this->inputter->getCoords();
                            check = true;
                        } catch (const std::out_of_range& e) {
                            displayer.printMessage("Incorrect command");
                        }
                    }
                    this->game->getPlayer(false)->get_coords(coords.x, coords.y);
                }
                if (this->game->getPlayer(false)->get_ability_type() == 3) {
                    displayer.printMessage("\nBombardment");
                }

                this->game->getPlayer(false)->use_ability_on_player(*this->game->getPlayer(true));
                
                if (this->game->getPlayer(true)->get_flag_dd()) {
                    displayer.printMessage("\nDouble attack, enter coordinates (x, y)");
                    Coordinates coords(0,0);
                    bool check = false;
                    
                    while(!check){
                        try {
                            coords = this->inputter->getCoords();
                            check = true;
                        } catch (const std::out_of_range& e) {
                            displayer.printMessage("Incorrect command");
                        }
                    }
                    this->game->getPlayer(true)->attack_player(coords.x, coords.y);
                }
                Coordinates crd = this->game->enemyTurn();
                this->game->getPlayer(false)->attack_player(crd.x, crd.y);
                displayer.printMessage("Enemy attacked the point " + std::to_string(crd.x) + " " +  std::to_string(crd.y));
                this->game->nextRound();
                continue;
            }
            case GameCommand::SAVE: {
                this->save();
                displayer.printMessage("Saved");
                continue;
            }
            case GameCommand::LOAD: {
                if (this->game->getState().hasSave()) {
                    this->load();
                } else {
                    displayer.printMessage("You have not saves");
                }

                break;
            }
            case GameCommand::START_NEW_GAME: {
                this->game->newGame();
                continue;
            }
            case GameCommand::EXIT: {
                displayer.printMessage("Exit");
                return;
            }

            default:{
                displayer.printMessage("Incorrect command");
                break;
            }

            }
        }
        if (game->getPlayer(false)->allShipsSunk()) {
            displayer.printMessage("Enemy won!");
            displayer.printMessage("Game Over");
            displayer.printMessage("Starting new game");
            isNewGame = true;
        } else if (game->getPlayer(true)->allShipsSunk()) {
            displayer.printMessage("Player won!");
            displayer.printMessage("Continue game");
            exit(0);
        }
    }
}

template <typename InputHandler, typename OutputHandler, typename Drawer>
void GameControl<InputHandler, OutputHandler, Drawer>::save() {
    game->saveGame();
}

template <typename InputHandler, typename OutputHandler, typename Drawer>
void GameControl<InputHandler, OutputHandler, Drawer>::load() {
    game->loadGame();
}

template class GameControl<ConsoleInput, ConsoleOutput, ConsoleDrawer>;