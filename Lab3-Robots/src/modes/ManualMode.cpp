#include "ManualMode.h"
#include "../game/Game.h"

void ManualMode::executeCommand(AbstractCommand* cmd) {
    auto pGame = getGamePtr();
    auto robots = pGame->getRobots();
    int activeRobotId = pGame->getActiveRobotId();
    auto manualCmd = dynamic_cast<AbstractManualModeCommand*>(cmd);
    pGame->setRobots(
        manualCmd->execute(robots, activeRobotId, pGame->getGlobalMapPtr()));
}