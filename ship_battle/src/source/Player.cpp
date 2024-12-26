#include "Player.h"

Player::Player(int width, int height, std::shared_ptr<ShipManager> shipManager)
    : width(width), height(height), ship_manager(shipManager),
      game_board(width, height, *ship_manager), ability_manager(), fileHandler("save.json") {
    game_board.placeShipsFromManager();
}

bool Player::attack_player(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBoundsAttackException();
    }

    bool res = game_board.attackCell(x, y, get_flag_dd());

    if (get_flag_dd() == true) {
        set_flag_dd(false);
    }

    if (ship_manager->getShipAt(x, y).first != nullptr) {
        if (ship_manager->getShipAt(x, y).first->isSunk() == true) {
            ability_manager.addRandomAbility();
        }
    }
    return res;
}

bool Player::get_flag_dd() const {
    return DD_FLAG;
}

void Player::print_abilities() const {
    ability_manager.listAbilities();
}

int Player::get_ability_type() {
    return ability_manager.getAbilityType();
}

std::vector<int> Player::get_ability_list() {
    return ability_manager.getAbilitiesAsNumbers();
}

void Player::set_flag_dd(bool new_flag_value) {
    DD_FLAG = new_flag_value;
}

void Player::add_ability() {
    ability_manager.addRandomAbility();
}

void Player::use_ability_on_player(Player& enemyPlayer) {
    if (ability_manager.hasAbility()) {
        if ((ability_manager.getAbilityType() == 2) && (x == -1 || y == -1)) {
            throw OutOfBoundsAttackException();
        }
        if ((ability_manager.getAbilityType() == 1)) {
            enemyPlayer.set_flag_dd(true);
        }
        ability_manager.applyAbility(enemyPlayer.game_board, *enemyPlayer.ship_manager, x, y);
    } else {
        throw NoAbilitiesException();
    }
}

void Player::print_board() const {
    game_board.print_board();
}

void Player::print_hidden_board() const {
    game_board.print_hidden_board();
}

void Player::get_coords(int x, int y) {
    this->x = x;
    this->y = y;
}

bool Player::allShipsSunk() const {
    return ship_manager->allShipsSunk();
}

bool Player::hasAbility() {
    return ability_manager.hasAbility();
}

bool Player::canPlaceShip(int i, int X, int Y, bool isHorizontal) {
    std::vector<ShipInfo> ships = ship_manager->getShips();
    return game_board.canPlaceShip(ships[i].ship, X, Y, isHorizontal);
}

void Player::saveGame(bool isPlayer) {
    std::string str;

    if (isPlayer){
        str = "Player";
    } else {
        str = "Enemy";
    }

    try {
        game_board.saveGame(str);
        ability_manager.saveGame(str);
        ship_manager->saveGame(str);

        fileHandler.load();
        json& data = fileHandler.getData();

        data[str]["x"] = x;
        data[str]["y"] = y;
        data[str]["DD_Flag"] = DD_FLAG;

        fileHandler.save();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Player::loadGame(bool isPlayer) {
    std::string str;

    if (isPlayer){
        str = "Player";
    } else {
        str = "Enemy";
    }
    game_board.loadGame(str);
    ability_manager.loadGame(str);

    fileHandler.load();
    json& data = fileHandler.getData();
    

    x = data[str]["x"].get<int>();
    y = data[str]["y"].get<int>();
    DD_FLAG = data[str]["DD_Flag"].get<bool>();

//     try {
//         game_board.loadGame(str);
//         ability_manager.loadGame(str);

//         fileHandler.load();
//         json& data = fileHandler.getData();
        

//         x = data[str]["x"].get<int>();
//         y = data[str]["y"].get<int>();
//         DD_FLAG = data[str]["DD_Flag"].get<bool>();

//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
}
