#include "AbstractMode.h"
#include "../game/Game.h"

void AbstractMode::init(Game* _pGame, std::vector<std::string>) {
    pGame = _pGame;
}
