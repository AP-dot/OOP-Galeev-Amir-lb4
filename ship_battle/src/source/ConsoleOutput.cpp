#include "ConsoleOutput.h"

ConsoleOutput::ConsoleOutput() noexcept {}

void ConsoleOutput::printAvailableAbilities(Player* player) noexcept{
    std::vector<int> abilities = player->get_ability_list();
    std::unordered_map<int, std::string> abilityNames = {
        {1, "Double_damage"},
        {2, "Scanner"},
        {3, "Bombardment"}
    };

    std::cout << "Player Abilities" << std::endl;
    int index = 1;
    for (int ability : abilities) {
        if (abilityNames.find(ability) != abilityNames.end()) {
            std::cout << index << ". " << abilityNames[ability] << std::endl;
            ++index;
        } else {
            std::cout << index << ". Unknown Ability" << std::endl;
            ++index;
        }
    }
}

void ConsoleOutput::printMessage(std::string message) {
    std::cout << message << "\n";
}

void ConsoleOutput::printCommands(std::map<std::string, char> enableCommands) {
    for (auto pair : enableCommands){
        std::cout << pair.second << " - " << pair.first << "\n";
    }
}
