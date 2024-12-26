#include "ConsoleDrawer.h"

ConsoleDrawer::ConsoleDrawer() noexcept{}

void ConsoleDrawer::print_board(GameBoard& board, bool isHidden) const {
    const auto& game_board = board.getBoard(isHidden);
    const auto& ship_manager = board.getShips();

    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            switch (game_board[y][x]) {
                case CellState::Unknown:
                    std::cout << "~ ";
                    break;
                case CellState::Empty:
                    std::cout << ". ";
                    break;
                case CellState::Ship:
                    auto [ship, segmentIndex] = ship_manager.getShipAt(x, y);
                    if (ship) {
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
                    break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}