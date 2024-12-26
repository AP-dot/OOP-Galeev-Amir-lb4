#include "AbilityManager.h"

AbilityManager::AbilityManager() : currentAbilityIndex(0), fileHandler("save.json") {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    initializeAbilities();
}

void AbilityManager::initializeAbilities() {
    abilities.emplace_back(std::make_unique<DoubleDamage>());
    abilities.emplace_back(std::make_unique<Scanner>());
    abilities.emplace_back(std::make_unique<Bombardment>());

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(abilities.begin(), abilities.end(), g);
}

void AbilityManager::applyAbility(GameBoard& enemyGameBoard, ShipManager& enemyShipManager, int x, int y) {
    if (abilities.empty()) {
        throw NoAbilitiesException();
    }

    Scanner* scannerAbility = dynamic_cast<Scanner*>(abilities[currentAbilityIndex].get());
    if (scannerAbility != nullptr) {
        scannerAbility->get_coords(x, y);
    }

    abilities[currentAbilityIndex]->use(enemyGameBoard, enemyShipManager);

    abilities.erase(abilities.begin() + currentAbilityIndex);

    if (abilities.empty()) {
        currentAbilityIndex = 0;
    } else {
        currentAbilityIndex %= abilities.size();
    }
}

void AbilityManager::get_coords(int x, int y) {
    this->x = x;
    this->y = y;
}

void AbilityManager::addRandomAbility() {
    int randomIndex = std::rand() % 3;
    switch (randomIndex) {
        case 0:
            abilities.push_back(std::make_unique<DoubleDamage>());
            break;
        case 1:
            abilities.push_back(std::make_unique<Scanner>());
            break;
        case 2:
            abilities.push_back(std::make_unique<Bombardment>());
            break;
    }
}

int AbilityManager::getAbilityType() const {
    const Ability& currentAbility = *abilities[currentAbilityIndex];
    if (dynamic_cast<const DoubleDamage*>(&currentAbility) != nullptr) {
        return 1;
    } 
    else if (dynamic_cast<const Scanner*>(&currentAbility) != nullptr) {
        return 2;
    } 
    else if (dynamic_cast<const Bombardment*>(&currentAbility) != nullptr) {
        return 3;
    }
    return 0;
}

bool AbilityManager::hasAbility() const {
    return !abilities.empty();
}

std::vector<int> AbilityManager::getAbilitiesAsNumbers() const {
    std::vector<int> abilitiesNumbers;
    for (const auto& ability : abilities) {
        if (dynamic_cast<const DoubleDamage*>(ability.get())) {
            abilitiesNumbers.push_back(1); 
        } else if (dynamic_cast<const Scanner*>(ability.get())) {
            abilitiesNumbers.push_back(2);
        } else if (dynamic_cast<const Bombardment*>(ability.get())) {
            abilitiesNumbers.push_back(3);
        } else {
            abilitiesNumbers.push_back(0);
        }
    }
    return abilitiesNumbers;
}

void AbilityManager::listAbilities() const {
    std::cout << "Список доступных способностей:\n";
    for (const auto& ability : abilities) {
        if (dynamic_cast<const DoubleDamage*>(ability.get())) {
            std::cout << "- Двойной урон\n";
        } else if (dynamic_cast<const Scanner*>(ability.get())) {
            std::cout << "- Сканер\n";
        } else if (dynamic_cast<const Bombardment*>(ability.get())) {
            std::cout << "- Обстрел\n";
        } else {
            std::cout << "- Неизвестная способность\n";
        }
    }
}

void AbilityManager::saveGame(std::string str) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        data[str]["Ability_manager"]["currentAbilityIndex"] = currentAbilityIndex;

        for (const auto& ability : abilities) {
            if (dynamic_cast<const DoubleDamage*>(ability.get())) {
                data[str]["Ability_manager"]["abilities"].push_back("DoubleDamage");
            } else if (dynamic_cast<const Scanner*>(ability.get())) {
                data[str]["Ability_manager"]["abilities"].push_back("Scanner");
            } else if (dynamic_cast<const Bombardment*>(ability.get())) {
                data[str]["Ability_manager"]["abilities"].push_back("Bombardment");
            } else {
                data[str]["Ability_manager"]["abilities"].push_back("Unknown");
            }
        }

        fileHandler.save();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void AbilityManager::loadGame(std::string str) {
    try {
        fileHandler.load();
        json& data = fileHandler.getData();

        abilities.clear();

        currentAbilityIndex = data.at(str).at("Ability_manager").at("currentAbilityIndex").get<size_t>();

        for (const auto& abilityName : data.at(str).at("Ability_manager").at("abilities")) {
            if (abilityName == "DoubleDamage") {
                abilities.push_back(std::make_unique<DoubleDamage>());
            } else if (abilityName == "Scanner") {
                abilities.push_back(std::make_unique<Scanner>());
            } else if (abilityName == "Bombardment") {
                abilities.push_back(std::make_unique<Bombardment>());
            } else {
                throw std::runtime_error("Unknown ability type in file: " + abilityName.get<std::string>());
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}