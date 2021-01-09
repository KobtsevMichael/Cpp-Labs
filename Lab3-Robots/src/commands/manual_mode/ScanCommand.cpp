#include "ScanCommand.h"

void ScanCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw descriptive_exception("Invalid arguments number.");
    }
}

std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>
    ScanCommand::execute(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>> robots,
        int activeRobotId,
        Map* pGlobalMap
    )
{
    auto [pRobot, globalCoords] = robots[activeRobotId];
    auto localCoords = pRobot->getPosition();
    auto pLocalMap = pRobot->getLocalMap();

    std::vector<std::pair<int, int>> diffCoordsArr = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    for (auto& diffCoords : diffCoordsArr) {
        pLocalMap->setCell(localCoords + diffCoords,
                           pGlobalMap->getCell(globalCoords + diffCoords),
                           true);
    }

    robots[activeRobotId] = {pRobot, globalCoords};

    return robots;
}