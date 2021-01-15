#include "MoveCommand.h"

#include <functional>

void MoveCommand::setDirection(direction_t _direction) {
    direction = _direction;
}

void MoveCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw error_exception("Invalid arguments number.");
    }
    direction = toDirectionFromString(argv[1]);
    if (direction == NONE_DIR) {
        throw error_exception("Invalid argument(s).");
    }
}

void MoveCommand::execute(
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& robots,
    int activeRobotId,
    Map* pGlobalMap,
    std::function<void(std::pair<int, int>, cell_t)>)
{
    auto [pRobot, globalCoords] =  robots[activeRobotId];
    auto newGlobalCoords = globalCoords + toDiffCoords(direction);

    cell_t newCellT = pGlobalMap->getCell(newGlobalCoords);

    if (!isInArray(pRobot->getGoodCells(), newCellT)) {
        switch (newCellT) {
            case ROCK:
                throw error_exception("There is a rock on this cell!");
            case NONE_CELL:
                throw error_exception("You can't move there - map end.");
            case BOMB:
                throw end_exception("You exploded on the bomb...");
            default:
                break;
        }
    }

    // Check on robots collide
    for (auto& robot : robots) {
        if (robot.second == newGlobalCoords) {
            auto [iRobot, iGlobalCoords] = robot;
            // If current is Sapper
            if (pRobot->getOwnType().first == SAPPER_SELF) {
                // Check if there is place to move Collector
                auto iNewGlobalCoords = getGoodNeighbourIfExists(
                    robots, pGlobalMap, iGlobalCoords
                );
                if (iNewGlobalCoords == std::pair(-1, -1)) {
                    throw collide_exeption(
                        "No place to move collector to..", NONE_DIR
                    );
                }
                // Moving poor Collector
                updatePositionOnAllLocalMaps(
                    robots,
                    iRobot,
                    pGlobalMap,
                    iGlobalCoords,
                    iNewGlobalCoords
                );
                // Updating poor Collector global coords
                robots[iRobot->getId()].second = iNewGlobalCoords;
                // Moving strong Sapper
                updatePositionOnAllLocalMaps(
                    robots,
                    pRobot,
                    pGlobalMap,
                    globalCoords,
                    newGlobalCoords
                );
                // Updating strong Sapper global coords
                robots[pRobot->getId()].second = newGlobalCoords;
                // Finnaly - throwing exception
                auto iDir = toDirection(iGlobalCoords - iNewGlobalCoords);
                throw collide_exeption("Sapper pushed collector :c", iDir);
            }
            // If other is Sapper
            else if (iRobot->getOwnType().first ==  SAPPER_SELF) {
                throw collide_exeption(
                    "Collector can't push Sapper c:", NONE_DIR
                );
            }
            // Two collectors collide
            throw collide_exeption(
                "There is other collector on this cell!", NONE_DIR
            );
        }
    }

    // Updating position on all local maps
    updatePositionOnAllLocalMaps(
        robots,
        pRobot,
        pGlobalMap,
        globalCoords,
        newGlobalCoords
    );

    // Updating global coords
    robots[activeRobotId].second = newGlobalCoords;
}

std::pair<int, int> MoveCommand::getGoodNeighbourIfExists(
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& robots,
    Map* pGlobalMap,
    std::pair<int, int> iGlobalCoords)
{
    auto goodNeighbours = pGlobalMap->getCellGoodNeighbours(iGlobalCoords);
    for (auto& goodNeighbour : goodNeighbours) {
        if (std::all_of(
                robots.begin(),
                robots.end(),
                [goodNeighbour] (auto& robot) {
                    return goodNeighbour != robot.second;
                }
            ))
        {
            return goodNeighbour;
        }
    }
    return {-1, -1};
}

void MoveCommand::updatePositionOnAllLocalMaps(
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& robots,
    AbstractRobot* pRobot,
    Map* pGlobalMap,
    std::pair<int, int> globalCoords,
    std::pair<int, int> newGlobalCoords)
{
    for (auto& robot : robots) {

        auto iRobot = robot.first;
        auto iLocalMap = iRobot->getLocalMap();
        auto iLocalMapCenter = robot.second - (iRobot->getPosition());

        auto oldPositionOnMap = globalCoords - iLocalMapCenter;
        auto newPositionOnMap = newGlobalCoords - iLocalMapCenter;

        cell_t robotCellType = iRobot == pRobot ?
            pRobot->getOwnType().first :
            pRobot->getOwnType().second;

        if (iRobot == pRobot) {
            iRobot->setPosition(newPositionOnMap);
        }

        // If was in visible zone - clear last position cell
        if (iLocalMap->getCell(oldPositionOnMap) == robotCellType) {
            iLocalMap->setCell(
                oldPositionOnMap, pGlobalMap->getCell(globalCoords)
            );
        }
        // If now in visible zone - update new position cell
        cell_t newCellType = iLocalMap->getCell(newPositionOnMap);
        if (newCellType != UNKNOWN && newCellType != NONE_CELL) {
            iLocalMap->setCell(newPositionOnMap, robotCellType);
        }
    }
}