#include "GrabCommand.h"


void GrabCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw error_exception("Invalid arguments number.");
    }
}

void GrabCommand::execute(
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& robots,
    int activeRobotId,
    Map* pGlobalMap,
    std::function<void(std::pair<int, int>, cell_t)> removeItemFromList)
{
    auto [pRobot, globalCoords] = robots[activeRobotId];

    cell_t cellT = pGlobalMap->getCell(globalCoords);

    if (cellT == EMPTY) {
        throw error_exception("The cell is empty - nothing to grab. ");
    }
    if (cellT != pRobot->getItemType()) {
        throw error_exception("You can't grab this item.");
    }

    pGlobalMap->setCell(globalCoords, EMPTY);
    pRobot->onGrab();

    removeItemFromList(globalCoords, pRobot->getItemType());
}
