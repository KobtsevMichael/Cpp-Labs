#include "ManualMode.h"
#include "../game/Game.h"

void ManualMode::sendCommand(AbstractCommand* cmd) {
    auto manualCmd = dynamic_cast<AbstractManualModeCommand*>(cmd);
    if (manualCmd == nullptr) {
        return;
    }
    auto robots = pGame->getRobots();
    try {
        manualCmd->execute(
            // Robots list
            robots,
            // Active robot Id
            pGame->getActiveRobotId(),
            // Global map
            pGame->getGlobalMap(),
            // Callback for removing items (grab command necessary)
            [pGame = pGame](std::pair<int, int> c, cell_t t) {
                return pGame->removeItemFromItemList(c, t);
            }
        );
        pGame->setRobots(robots);
    }
    catch (collide_exeption& e) {
        pGame->setRobots(robots);
        throw e;
    }
}
