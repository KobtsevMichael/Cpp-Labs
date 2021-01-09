#include "GrabCommand.h"

void GrabCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw descriptive_exception("Invalid arguments number.");
    }
}

std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>
    GrabCommand::execute(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>> robots,
        int activeRobotId,
        Map* pGlobalMap
    )
{
    auto [pRobot, globalCoords] = robots[activeRobotId];
    auto pCollector = dynamic_cast<Collector*>(pRobot);

    cell_t cellT = pGlobalMap->getCell(globalCoords);

    if (cellT != APPLE) {
        throw descriptive_exception("No apples on this cell.");
    }

    pCollector->addApple();
    pGlobalMap->setCell(globalCoords, EMPTY);

    robots[activeRobotId] = {pRobot, globalCoords};

    return robots;
}
