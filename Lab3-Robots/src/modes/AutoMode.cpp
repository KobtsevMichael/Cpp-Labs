#include "AutoMode.h"
#include "../game/Game.h"

#include <fmt/ranges.h>


void AutoMode::sendCommand(AbstractCommand *cmd) {

    auto robots = pGame->getRobots();
    bool isSapper = pGame->getSapperState();

    int collectorId = pGame->getActiveRobotId();
    int sapperId = pGame->getRobotsN() - 1;

    std::queue<std::pair<int, int>> sortedApples;
    std::queue<std::pair<int, int>> sortedBombs;

    std::pair<int, int> globalActiveRobotCoords;

    // Sorting array of APPLES' coords one by one
    pGame->setState({RUNNING, "Sorting apples array..."});
    pGame->refresh();

    auto applesList = pGame->getItemList(APPLE);
    globalActiveRobotCoords = pGame->getActiveRobot().second;

    sortedApples = sortPoints(applesList, globalActiveRobotCoords);

    // Sorting array of BOMBS' coords one by one
    if (isSapper) {

        pGame->setState({RUNNING, "Sorting bombs array..."});
        pGame->refresh();

        auto bombsList = pGame->getItemList(BOMB);
        globalActiveRobotCoords = pGame->getSapper().second;

        sortedBombs = sortPoints(bombsList, globalActiveRobotCoords);
    }

    // Starting collection
    pGame->setState({RUNNING, "Running"});
    pGame->refresh();

    auto moveCmd = new MoveCommand;
    auto grabCmd = new GrabCommand;

    bool isCollectorFinished = false;
    bool isSapperFinished = !isSapper;

    bool isAnyItemSurrounded = false;
    bool isOtherRobotOnItemCell = false;

    std::vector<direction_t> collectorWay;
    std::vector<direction_t> sapperWay;

    while (true) {

        if (collectorWay.empty()) {
            globalActiveRobotCoords = robots[collectorId].second;
            collectorWay = generateWay(
                sortedApples,
                globalActiveRobotCoords,
                &isOtherRobotOnItemCell,
                &isAnyItemSurrounded,
                &isCollectorFinished,
                sapperId
            );
        }

        if (isSapper && sapperWay.empty()) {
            globalActiveRobotCoords = robots[sapperId].second;
            sapperWay = generateWay(
                sortedBombs,
                globalActiveRobotCoords,
                &isOtherRobotOnItemCell,
                &isAnyItemSurrounded,
                &isSapperFinished,
                collectorId
            );
        }

        if (isCollectorFinished && isSapperFinished) {
            break;
        }

        if (!isCollectorFinished) {
            try {
                doMove(collectorWay, robots, collectorId, moveCmd);
            }
            catch (collide_exeption& e) {
                // Do nothing
            }
            if (collectorWay.empty()) {
                doGrab(collectorWay, robots, collectorId, grabCmd);
            }
        }

        if (isSapper && !isSapperFinished) {
            try {
                doMove(sapperWay, robots, sapperId, moveCmd);
            }
            catch (collide_exeption& e) {
                if (e.where() == NONE_DIR) {
                    throw error_exception("Can't find way to cross.");
                }
                collectorWay.push_back(e.where());
                sapperWay.pop_back();
                pGame->setRobots(robots);
                pGame->refresh(SLEEP_TIME, false);
            }
            if (sapperWay.empty()) {
                doGrab(sapperWay, robots, sapperId, grabCmd);
            }
        }
    }

    delete moveCmd;
    delete grabCmd;

    pGame->setMode(MANUAL_MODE);

    if (isAnyItemSurrounded && isOtherRobotOnItemCell) {
        throw info_exception(
            "There were some surrounded items & items with other "
            "robots on their cells, "
            "so they were ignored, BUT all other have been collected!"
        );
    }
    if (isAnyItemSurrounded) {
        throw info_exception(
            "There were some surrounded items, "
            "so they were ignored, BUT all other have been collected!"
        );
    }
    if (isOtherRobotOnItemCell) {
        throw info_exception(
            "There were items with other robots on their cells, "
            "so they were ignored, BUT all other have been collected!"
        );
    }
}

// SORTING ITEMS ARRAYS
std::queue<std::pair<int, int>> AutoMode::sortPoints(
    std::vector<std::pair<int, int>> arr, std::pair<int, int> startTarget)
{
    std::queue<std::pair<int, int>> sortedArr;
    auto target = startTarget;

    for (auto it = arr.begin(); it < arr.end();) {
        auto nearest = std::pair(1E9, 1E9);
        auto nearestIt = arr.begin();
        for (auto jt = arr.begin(); jt < arr.end(); ++jt) {
            if (isCloserToTarget(*jt, nearest, target)) {
                nearest = *jt;
                nearestIt = jt;
            }
        }
        target = nearest;
        arr.erase(nearestIt);
        sortedArr.push(target);
    }
    arr.clear();

    return sortedArr;
}

bool AutoMode::isCloserToTarget(
    std::pair<int, int> p1,
    std::pair<int, int> p2,
    std::pair<int, int> target)
{
    return abs(p1.first - target.first) + abs(p1.second - target.second) <
           abs(p2.first - target.first) + abs(p2.second - target.second);
}

// GENEREATING WAY & PASS UNREACHABLE POINTS
std::vector<direction_t> AutoMode::generateWay(
    std::queue<std::pair<int, int>>& sortedItems,
    std::pair<int, int> globalActiveRobotCoords,
    bool *isAnyRobotOnAppleCell,
    bool *isAnyAppleSurrounded,
    bool *isFinished,
    int otherRobotId)
{
    std::vector<direction_t> way;

    while (true) {

        if (sortedItems.empty()) {
            *isFinished = true;
            break;
        }

        auto item = sortedItems.front();
        sortedItems.pop();

        if (pGame->isOtherRobotOnCell(item)) {
            *isAnyRobotOnAppleCell = true;
            continue;
        }

        try {
            way = aStarSearch(
                // Global map instance
                pGame->getGlobalMap(),
                // Collector's coords
                globalActiveRobotCoords,
                // Current item coords
                item,
                // Callback for check if cell neighbour is robot
                [pGame = pGame, otherId = otherRobotId]
                (std::pair<int, int> gPointCoords) -> bool {
                    return pGame->isOtherRobotOnCell(gPointCoords, otherId);
                }
            );
        }
        catch (way_not_found_exception&) {
            *isAnyAppleSurrounded = true;
            continue;
        }

        break;
    }

    return way;
}

// MOVING COLLECTOR/SAPPER
void AutoMode::doMove(
    std::vector<direction_t>& way,
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& robots,
    int robotId,
    MoveCommand* moveCmd)
{
    moveCmd->setDirection(way.back());
    moveCmd->execute(
        robots,
        robotId,
        pGame->getGlobalMap()
    );
    way.pop_back();
    pGame->setRobots(robots);
    pGame->refresh(SLEEP_TIME, false);
}

// TO GRAB CURRENT ROBOT'S ITEM
void AutoMode::doGrab(
    std::vector<direction_t>& way,
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& robots,
    int robotId,
    GrabCommand* grabCmd)
{
    grabCmd->execute(
        // Robots list
        robots,
        // Active robot Id
        robotId,
        // Global map
        pGame->getGlobalMap(),
        // Callback for removing items from global search list
        [pGame = pGame] (std::pair<int, int> c, cell_t t) {
            return pGame->removeItemFromItemList(c, t);
        }
    );
}
