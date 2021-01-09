#include "AutoMode.h"
#include "../game/Game.h"

void AutoMode::executeCommand(AbstractCommand *cmd) {
    for (int i=0; i < 10; ++i) {
        pGame->refresh(SLEEP_TIME);
    }
    pGame->setMode(MANUAL_MODE);
}