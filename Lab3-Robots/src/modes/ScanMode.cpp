#include "ScanMode.h"
#include "../game/Game.h"

void ScanMode::init(Game* _pGame, std::vector<std::string> _args) {
    AbstractMode::init(_pGame);
    stepsN = std::stoi(_args[2]);
}

void ScanMode::executeCommand(AbstractCommand *cmd) {
    for (int i=0; i < stepsN; ++i) {
        pGame->refresh(SLEEP_TIME);
    }
    pGame->setMode(MANUAL_MODE);
}