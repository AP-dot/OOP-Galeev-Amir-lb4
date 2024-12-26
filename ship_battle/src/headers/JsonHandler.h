#ifndef JSON_HANDLER_H
#define JSON_HANDLER_H

#include "nlohmann/json.hpp"

#include <string>
#include <stdexcept>
#include <fstream>
#include <iostream>


using json = nlohmann::json;

class JsonFileHandler {
private:
    std::string filename;
    json data;

public:
    JsonFileHandler(const std::string& file);

    nlohmann::json& load();

    void save() const;

    json& getData();

    void setData(const json& newData);
};

#endif