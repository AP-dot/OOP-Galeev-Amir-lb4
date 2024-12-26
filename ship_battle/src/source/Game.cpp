#include "Game.h"

Game::Game() : currentRound(1), fileHandler("save.json") {}

void Game::newGame() {
    currentRound = 1;
    ConsoleOutput* printer = new ConsoleOutput();
    ConsoleInput* inputer = new ConsoleInput();
    printer->printMessage("\nEnter height and width:");
    bool check = false;
    Coordinates size(0, 0);
    while(!check){
        try {
            size = inputer->getCoords();
            check = true;
        } catch (const std::out_of_range& e) {
            printer->printMessage("Incorrect command");
        }
    }

    width = size.x;
    height = size.y;
    check = false;
    Enemy_ = new Enemy(size.x, size.y);
    printer->printMessage("\nEnter sizes of ships (1 to 4 ships, each size between 1 and 4):");
    sizes.clear();

    while(!check){
        try {
            sizes = inputer->getSizes();
            check = true;
        } catch (const InvalidInputType& e) {
            printer->printMessage("Incorrect input");
        }
    }

    check = false;
    game_state.set_sizes(sizes);

    auto ship_manager_one = std::make_shared<ShipManager>(sizes);
    auto ship_manager_two = std::make_shared<ShipManager>(sizes);
    
    for (size_t i = 0; i < sizes.size(); ++i) {
        Coordinates coords(0, 0);

        printer->printMessage("\nEnter coordinates (x y)");
        std::cout << "for ship of size " << sizes[i] << " (Ship №" << i + 1 << "):" << std::endl;

        while(!check){
            try {
                coords = inputer->getCoords();
                check = true;
            } catch (const std::out_of_range& e) {
                printer->printMessage("Incorrect command");
            }
        }
        check = false;

        printer->printMessage("\nEnter orientation (0 for horizontal, 1 for vertical) for ship of size ");
        std::cout << "for ship of size " << sizes[i] << " (Ship №" << i + 1 << "):" << std::endl;
        bool isVertical;

        while(!check){
            try {
                isVertical = inputer->getBool();
                check = true;
            } catch (const InvalidInputType& e) {
                printer->printMessage("Incorrect command");
            }
        }
        check = false;
        ship_manager_one->placeShip(i, coords.x, coords.y, isVertical);
    }
    Enemy_->placeShips(sizes, ship_manager_two);

    player = new Player(size.x, size.y, ship_manager_one);
    enemy = new Player(size.x, size.y, ship_manager_two);
}

Coordinates Game::enemyTurn() {
    Coordinates coords = Enemy_->getNextAttackCoordinates();
    return coords;
}

void Game::saveGame() {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();
        data.clear();

        data["Game_info"]["Current_round"] = currentRound;
        data["Game_info"]["width"] = width;
        data["Game_info"]["height"] = height;
        data["Game_info"]["sizes"] = sizes;

        fileHandler.save();

        player->saveGame(true);
        enemy->saveGame(false);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    game_state.set_save(true);
}

void Game::loadGame() {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        sizes = data["Game_info"]["sizes"].get<std::vector<int>>();
        currentRound = data["Game_info"]["Current_round"].get<int>();
        width = data["Game_info"]["width"].get<int>();
        height = data["Game_info"]["height"].get<int>();

        auto ship_manager_one = std::make_shared<ShipManager>(sizes);
        auto ship_manager_two = std::make_shared<ShipManager>(sizes);

        ship_manager_one->loadGame("Player");
        ship_manager_two->loadGame("Enemy");

        Enemy_ = new Enemy(width, height);
        player = new Player(width, height, ship_manager_one);
        enemy = new Player(width, height, ship_manager_two);

        player->loadGame(true);
        enemy->loadGame(false);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool Game::hasSave() {
    return game_state.hasSave();
}