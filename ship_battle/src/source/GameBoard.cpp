#include "GameBoard.h"

using json = nlohmann::json;

GameBoard::GameBoard(int width, int height, ShipManager& manager)
    : width(width), height(height), shipManager(manager), fileHandler("save.json") {
    board1.resize(height, std::vector<CellState>(width, CellState::Empty));
    board2.resize(height, std::vector<CellState>(width, CellState::Unknown));
}

GameBoard::GameBoard(const GameBoard& other)
    : width(other.width), height(other.height), board1(other.board1), board2(other.board2), shipManager(other.shipManager), fileHandler("save.json") {}

GameBoard::GameBoard(GameBoard&& other) noexcept
    : width(other.width), height(other.height), board1(std::move(other.board1)), board2(std::move(other.board2)), shipManager(other.shipManager), fileHandler("save.json") {
    other.width = 0;
    other.height = 0;
}

GameBoard& GameBoard::operator=(const GameBoard& other) {
    if (this != &other) {
        width = other.width;
        height = other.height;
        board1 = other.board1;
        board2 = other.board2;
        shipManager = other.shipManager;
    }
    return *this;
}

GameBoard& GameBoard::operator=(GameBoard&& other) noexcept {
    if (this != &other) {
        width = other.width;
        height = other.height;
        board1 = std::move(other.board1);
        board2 = std::move(other.board2);
        other.width = 0;
        other.height = 0;
    }
    return *this;
}

bool GameBoard::placeShipsFromManager() {
    const auto& ships = shipManager.getShips();

    for (const auto& shipInfo : ships) {
        Ship* ship = shipInfo.ship;
        int startX = shipInfo.startX;
        int startY = shipInfo.startY;
        bool isVertical = shipInfo.isVertical;

        if (canPlaceShip(ship, startX, startY, isVertical)) {
            for (int i = 0; i < ship->getLength(); ++i) {
                if (isVertical) {
                    board1[startY + i][startX]  = CellState::Ship;
                } else {
                    board1[startY][startX + i] = CellState::Ship;
                }
            }
        } else {
            throw OverlappingShipsException();
        }
    }
    return true;
}

bool GameBoard::canPlaceShip(Ship* ship, int startX, int startY, bool isVertical) const {
    for (int i = 0; i < ship->getLength(); ++i) {
        int x = isVertical ? startX : startX + i;
        int y = isVertical ? startY + i : startY;
        
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return false;
        }

        if (board1[y][x] == CellState::Ship) {
            return false;
        }

        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                if (dx == 0 && dy == 0) continue;
                int neighborX = x + dx;
                int neighborY = y + dy;
                if (neighborX >= 0 && neighborX < width - 1 && neighborY >= 0 && neighborY < height - 1) {
                    if (board1[neighborY][neighborX] == CellState::Ship) {
                        return false; 
                    }
                }
            }
        }
    }
    return true;
}

bool GameBoard::attackCell(int x, int y, bool double_damage) {
    auto [ship, segmentIndex] = shipManager.getShipAt(x, y);

    if (ship != nullptr) {
        ship->hit(segmentIndex, double_damage);
        board2[y][x] = CellState::Ship;
        return true;
    } else {
        board2[y][x] = CellState::Empty;
        return false;
    }
}

int GameBoard::getWidth() {
    return width;
}

int GameBoard::getHeight() {
    return height;
}


void GameBoard::print_board() const{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (board1[y][x]) {
                case CellState::Unknown:
                    std::cout << "~ ";
                    break;
                case CellState::Empty:
                    std::cout << ". ";
                    break;
                case CellState::Ship:
                    auto [ship, segmentIndex] = shipManager.getShipAt(x, y);
                    switch (ship->getSegmentState(segmentIndex)) {
                        case SegmentState::Intact:
                            std::cout << "▢ ";
                            break;
                        case SegmentState::Damaged:
                            std::cout << "◫ ";
                            break;
                        case SegmentState::Destroyed:
                            std::cout << "■ ";
                            break;
                    }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GameBoard::print_hidden_board() const{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            switch (board2[y][x]) {
                case CellState::Unknown:
                    std::cout << "~ ";
                    break;
                case CellState::Empty:
                    std::cout << ". ";
                    break;
                case CellState::Ship:
                    auto [ship, segmentIndex] = shipManager.getShipAt(x, y);
                    switch (ship->getSegmentState(segmentIndex)) {
                        case SegmentState::Intact:
                            std::cout << "▢ ";
                            break;
                        case SegmentState::Damaged:
                            std::cout << "◫ ";
                            break;
                        case SegmentState::Destroyed:
                            std::cout << "■ ";
                            break;
                    }
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::string GameBoard::cellStateToString(CellState state) const {
    switch (state) {
        case CellState::Unknown: return "Unknown";
        case CellState::Empty: return "Empty";
        case CellState::Ship: return "Ship";
        default: throw std::invalid_argument("Invalid CellState");
    }
}

CellState GameBoard::stringToCellState(const std::string& str) const {
    if (str == "Unknown") return CellState::Unknown;
    if (str == "Empty") return CellState::Empty;
    if (str == "Ship") return CellState::Ship;
    throw std::invalid_argument("Invalid CellState string");
}



void GameBoard::saveGame(std::string str) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        for (const auto& row : board1) {
            nlohmann::json rowJson;
            for (const auto& cell : row) {
                rowJson.push_back(cellStateToString(cell));
            }
            data[str]["Game_board"]["board"].push_back(rowJson);
        }

        for (const auto& row : board2) {
            nlohmann::json rowJson;
            for (const auto& cell : row) {
                rowJson.push_back(cellStateToString(cell));
            }
            data[str]["Game_board"]["hidden_board"].push_back(rowJson);
        }

        fileHandler.save();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void GameBoard::loadGame(std::string str) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        board1.clear();
        for (const auto& rowJson : data[str]["Game_board"]["board"]) {
            std::vector<CellState> row;
            for (const auto& cellStr : rowJson) {
                row.push_back(stringToCellState(cellStr));
            }
            board1.push_back(row);
        }

        board2.clear();
        for (const auto& rowJson : data[str]["Game_board"]["hidden_board"]) {
            std::vector<CellState> row;
            for (const auto& cellStr : rowJson) {
                row.push_back(stringToCellState(cellStr));
            }
            board2.push_back(row);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

std::vector<std::vector<CellState>> GameBoard::getBoard(bool isHidden) {
    if (isHidden) return board2;
    else return board1;
}

ShipManager& GameBoard::getShips() {
    return shipManager;
}
