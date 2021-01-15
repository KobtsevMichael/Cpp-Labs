#include "ScanCommand.h"

void ScanCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw error_exception("Invalid arguments number.");
    }
}

void ScanCommand::execute(
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& robots,
    int activeRobotId,
    Map* pGlobalMap,
    std::function<void(std::pair<int, int>, cell_t)>)
{
    auto [pRobot, globalCoords] =  robots[activeRobotId];

    auto localCoords = pRobot->getPosition();
    auto pLocalMap = pRobot->getLocalMap();

    for (int i = 0; i < NONE_DIR; ++i) {
        auto diffCoords = toDiffCoords(static_cast<direction_t>(i));
        auto cellGlobalCoords = globalCoords + diffCoords;
        cell_t cellT = pGlobalMap->getCell(cellGlobalCoords);
        for (auto& robot : robots) {
            // If there is other robot on the scanning cell
            if (robot.second == cellGlobalCoords) {
                cellT = robot.first->getOwnType().second;
            }
        }
        pLocalMap->setCell(localCoords + diffCoords, cellT);
    }
}