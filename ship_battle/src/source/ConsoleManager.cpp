#include "ConsoleManager.h"


template <typename Drawer, typename MessageHandler>
DisplayManager<Drawer, MessageHandler>::DisplayManager(){
    this->outputter = new MessageHandler();
    this->drawer = new Drawer();

}
template <typename Drawer, typename MessageHandler>
DisplayManager<Drawer, MessageHandler>::~DisplayManager(){
    delete outputter;
    delete drawer;
}

template <typename Drawer, typename MessageHandler>
void DisplayManager<Drawer, MessageHandler>::printMessage(std::string message){
    outputter->printMessage(message);
}

template <typename Drawer, typename MessageHandler>
void DisplayManager<Drawer, MessageHandler>::printAvailableAbilities(Player* player){
    outputter->printAvailableAbilities(player);
}

template <typename Drawer, typename MessageHandler>
void DisplayManager<Drawer, MessageHandler>::printField(Player* player, bool isHidden){
    drawer->print_board(player->getBoard(), isHidden);
}

template <typename Drawer, typename MessageHandler>
void DisplayManager<Drawer, MessageHandler>::printMenu(bool isStart){
    outputter->printMenu(isStart);
}

template <typename Drawer, typename OutputHandler>
void DisplayManager<Drawer, OutputHandler>::printCommands(std::map<std::string, char> enableCommands){
    outputter->printCommands(enableCommands);
}

template class DisplayManager<ConsoleDrawer, ConsoleOutput>;
