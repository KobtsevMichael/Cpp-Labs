#include "ScanMode.h"
#include "../game/Game.h"

void ScanMode::init(Game* _pGame, std::vector<std::string> _args) {
    AbstractMode::init(_pGame);
    stepsN = std::stoi(_args[2]);
}

void ScanMode::sendCommand(AbstractCommand *cmd) {

    auto robots = pGame->getRobots();
    auto robotId = pGame->getActiveRobotId();
    auto pGlobalMap = pGame->getGlobalMap();

    pGame->setState({RUNNING, "Running"});
    pGame->refresh();

    auto moveCmd = new MoveCommand;
    auto scanCmd = new ScanCommand;

    for (int i=0; i < stepsN; ++i) {

        auto [pRobot, globalCoords] = pGame->getActiveRobot();
        auto pLocalMap = pRobot->getLocalMap();

        std::vector<direction_t> way;

        if (SCAN_MODE_ALGORITHM == "dijkstra") {
            auto isTraversableCallback =
                [this, gM=pGlobalMap, lM=pLocalMap, r=pRobot, gRC=globalCoords]
                    (std::pair<int, int> lCC) -> bool {
                    auto gCC = gRC - r->getPosition() + lCC;
                    return isTraversable(gM, lM, gCC, lCC);
                }
            ;
            try {
                way = dijkstraSearch(
                    pLocalMap,
                    pRobot->getPosition(),
                    isTraversableCallback
                );
            }
            catch (way_not_found_exception&) {
                break;
            }
        }
        else {
            auto nearestPoint = findNearestUnknownCell();
            if (nearestPoint == pRobot->getPosition()) {
                break;
            }
            way = aStarSearch(
                pRobot->getLocalMap(),
                pRobot->getPosition(),
                nearestPoint
            );
        }

        for (auto it = way.rbegin(); it < way.rend() - 1; ++it) {
            moveCmd->setDirection(*it);
            moveCmd->execute(robots, robotId, pGlobalMap);
            pGame->setRobots(robots);
            pGame->refresh(SLEEP_TIME, false);
        }

        scanCmd->execute(robots, robotId, pGlobalMap);
        pGame->refresh(SLEEP_TIME, false);
    }

    delete moveCmd;
    delete scanCmd;

    pGame->setMode(MANUAL_MODE);
}

bool ScanMode::isTraversable(
    Map* pGlobalMap,
    Map* pLocalMap,
    std::pair<int, int> gCoords,
    std::pair<int, int> lCoords)
{
    auto cellT = pLocalMap->getCell(lCoords);
    return (isInArray(GOOD_CELLS, cellT) ||
            cellT == UNKNOWN ||
            cellT == NONE_CELL) &&
           pGlobalMap->isOnMap(gCoords);
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
