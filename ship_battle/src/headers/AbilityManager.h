#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include "Ability.h"
#include "Exceptions.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "Bombardment.h"
#include "JsonHandler.h"
#include "nlohmann/json.hpp"

#include <vector>
#include <random>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <stdexcept>


class AbilityManager {
public:
    AbilityManager();

    // Запрещаем копирование
    AbilityManager(const AbilityManager&) = delete;
    AbilityManager& operator=(const AbilityManager&) = delete;

    // Разрешаем перемещение
    AbilityManager(AbilityManager&&) noexcept = default;
    AbilityManager& operator=(AbilityManager&&) noexcept = default;

    void initializeAbilities();
    void applyAbility(GameBoard& gameBoard, ShipManager& shipManager, int x, int y);
    void get_coords(int x, int y);
    void addRandomAbility();
    std::vector<int> getAbilitiesAsNumbers() const;

    const Ability& getCurrentAbility() const;
    int getAbilityType() const;
    bool hasAbility() const;
    void listAbilities() const;

    void saveGame(std::string str);
    void loadGame(std::string str);

private:
    std::vector<std::unique_ptr<Ability>> abilities;
    size_t currentAbilityIndex;
    JsonFileHandler fileHandler;
    int x = -1;
    int y = -1;
};

#endif