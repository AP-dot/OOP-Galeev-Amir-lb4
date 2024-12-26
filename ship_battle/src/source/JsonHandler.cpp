#include "JsonHandler.h"

JsonFileHandler::JsonFileHandler(const std::string& file) : filename(file) {}

nlohmann::json& JsonFileHandler::load() {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    inFile >> data;
    return data;
}

void JsonFileHandler::save() const {
    std::ofstream outFile(filename, std::ios::out | std::ios::trunc);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for saving JSON: " + filename);
    }

    outFile << data.dump(4);
}

json& JsonFileHandler::getData() {
    return data;
}

void JsonFileHandler::setData(const json& newData) {
    data = newData;
}