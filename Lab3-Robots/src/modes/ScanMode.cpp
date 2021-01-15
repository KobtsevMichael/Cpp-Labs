#include "ScanMode.h"
#include "../game/Game.h"

#include <fmt/ranges.h>
#include <memory>


void ScanMode::init(Game* _pGame, std::vector<std::string> _args) {
    AbstractMode::init(_pGame);
    stepsN = std::stoi(_args[2]);
}

void ScanMode::sendCommand(AbstractCommand *cmd) {

    auto robots = pGame->getRobots();

    pGame->setState({RUNNING, "Running"});
    pGame->refresh();

    auto moveCmd = new MoveCommand;
    auto scanCmd = new ScanCommand;

    for (int i=0; i < stepsN; ++i) {

        auto [pRobot, globalCoords] = pGame->getActiveRobot();

        auto localCoords = pRobot->getPosition();
        auto nearestPoint = findNearestUnknownCell();

        if (nearestPoint == localCoords) {
            break;
        }

        auto way = aStarSearch(
            pRobot->getLocalMap(),
            localCoords,
            nearestPoint
        );

        for (auto it = way.rbegin(); it < way.rend() - 1; ++it) {
            moveCmd->setDirection(*it);
            moveCmd->execute(
                robots,
                pGame->getActiveRobotId(),
                pGame->getGlobalMap()
            );
            pGame->setRobots(robots);
            pGame->refresh(SLEEP_TIME, false);
        }

        scanCmd->execute(
            robots,
            pGame->getActiveRobotId(),
            pGame->getGlobalMap()
        );
        pGame->refresh(SLEEP_TIME, false);
    }

    delete moveCmd;
    delete scanCmd;

    pGame->setMode(MANUAL_MODE);
}

std::pair<int, int> ScanMode::findNearestUnknownCell() {

    auto [pRobot, gCoords] = pGame->getActiveRobot();
    auto lCoords = pRobot->getPosition();

    auto pGlobalMap = pGame->getGlobalMap();
    auto pLocalMap = pRobot->getLocalMap();

    int searchingAreaSize = pLocalMap->getSzudzikMaxIdx();

    std::pair<int, int> iPoint;
    cell_t iCellType;

    for (int i = 1; i < searchingAreaSize; ++i) {

        iPoint = calculateSzudzikPair(i);
        iCellType = pLocalMap->getCell(lCoords + iPoint);

        bool isUnknown = iCellType == UNKNOWN || iCellType == NONE_CELL;
        bool isOnMap = pGlobalMap->isOnMap(gCoords + iPoint);

        if (!isUnknown || !isOnMap) {
            continue;
        }

        if (pLocalMap->hasGoodNeighbours(lCoords + iPoint)) {
            return lCoords + iPoint;
        }
    }

    return lCoords;
}
