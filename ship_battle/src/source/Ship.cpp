#include "Ship.h"

Ship::Ship(int length, bool isVertical)
    : length(length), vertical(isVertical), segments(length, SegmentState::Intact), fileHandler("save.json") {}

int Ship::getLength() const {
    return length;
}

bool Ship::isVertical() const {
    return vertical;
}

SegmentState Ship::getSegmentState(int index) const {
    if (index < 0 || index >= length) {
        throw OutOfShipLen();
    }
    return segments[index];
}

void Ship::hit(int index, bool double_damage) {
    if (index < 0 || index >= length) {
        throw OutOfShipLen();
    }

    if (double_damage == false) {
        if (segments[index] == SegmentState::Intact) {
            segments[index] = SegmentState::Damaged;
        } else if (segments[index] == SegmentState::Damaged) {
            segments[index] = SegmentState::Destroyed;
        } else if (segments[index] == SegmentState::Destroyed) {
            throw AlreadyDestroyed();
        }
    } else {
        if (segments[index] == SegmentState::Destroyed) {
            throw AlreadyDestroyed();
        } else {
            segments[index] = SegmentState::Destroyed;
        }
    }
}

bool Ship::isSunk() const {
    for (const auto& state : segments) {
        if (state != SegmentState::Destroyed) {
            return false;
        }
    }
    return true;
}

void Ship::printStatus() const {
    for (int i = 0; i < length; ++i) {
        std::cout << "Segment " << i << ": ";
        switch (segments[i]) {
            case SegmentState::Intact:
                std::cout << "Intact";
                break;
            case SegmentState::Damaged:
                std::cout << "Damaged";
                break;
            case SegmentState::Destroyed:
                std::cout << "Destroyed";
                break;
        }
        std::cout << std::endl;
    }
}

void Ship::saveGame(std::string str, int cnt) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        data[str]["Ship_manager"][std::to_string(cnt)]["length"] = length;
        data[str]["Ship_manager"][std::to_string(cnt)]["vertical"] = vertical;
        data[str]["Ship_manager"][std::to_string(cnt)]["segments"] = json::array();

        for (int i = 0; i < length; ++i) {
            switch (segments[i]) {
                case SegmentState::Intact:
                    data[str]["Ship_manager"][std::to_string(cnt)]["segments"].push_back("Intact");
                    break;
                case SegmentState::Damaged:
                    data[str]["Ship_manager"][std::to_string(cnt)]["segments"].push_back("Damaged");
                    break;
                case SegmentState::Destroyed:
                    data[str]["Ship_manager"][std::to_string(cnt)]["segments"].push_back("Destroyed");
                    break;
            }
        }

        fileHandler.save();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Ship::loadGame(std::string str, int cnt) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        length = data[str]["Ship_manager"][std::to_string(cnt)]["length"].get<int>();
        vertical = data[str]["Ship_manager"][std::to_string(cnt)]["vertical"].get<bool>();

        segments.clear();

        for (const auto& state : data[str]["Ship_manager"][std::to_string(cnt)]["segments"]) {
            if (state == "Intact") {
                segments.push_back(SegmentState::Intact);
            } else if (state == "Damaged") {
                segments.push_back(SegmentState::Damaged);
            } else if (state == "Destroyed") {
                segments.push_back(SegmentState::Destroyed);
            }
        }

        fileHandler.save();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}