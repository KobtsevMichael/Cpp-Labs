#include "ScanMode.h"
#include "../game/Game.h"

void ScanMode::init(Game* _pGame, std::vector<std::string> _args) {
    AbstractMode::init(_pGame, _args);
    stepsN = std::stoi(_args[2]);
}

void ScanMode::executeCommand(AbstractCommand *cmd) {

}