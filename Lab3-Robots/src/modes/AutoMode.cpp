#include "AutoMode.h"
#include "../game/Game.h"

void AutoMode::executeCommand(AbstractCommand *cmd) {
    Game* pGame = getGamePtr();
    for (int i=0; i < 10; ++i) {
        pGame->refresh(300);
    }
    pGame->setMode(MANUAL_MODE);
}