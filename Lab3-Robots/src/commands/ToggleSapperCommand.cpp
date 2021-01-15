#include "ToggleSapperCommand.h"
#include "../game/Game.h"

void ToggleSapperCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw error_exception("Invalid arguments number.");
    }
    if (toLower(argv[1]) == "on") {
        action = true;
    }
    else if (toLower(argv[1]) == "off") {
        action = false;
    }
    else {
        throw error_exception("Incorrent argument. Try ON/OFF.");
    }
}

void ToggleSapperCommand::execute(Game* pGame) {
    if (pGame->getSapperState() == action) {
        return;
    }
    if (action) {
        auto robots = pGame->getRobots();
        auto [pCollector, globalCollectorCoords] = pGame->getActiveRobot();
        auto pLocalMapCollector = pCollector->getLocalMap();

        // Getting possiable cells near Collector to add Sapper
        auto collectorGoodNeighbours = pLocalMapCollector
            ->getCellGoodNeighbours(pCollector->getPosition());

        if (collectorGoodNeighbours.empty()) {
            throw error_exception("No place on local map for Sapper.");
        }

        // Calculating Sapper global coords
        auto globalSapperCoords =
            globalCollectorCoords -
            pCollector->getPosition() +
            collectorGoodNeighbours.back();

        // Setting Sapper global coords
        robots.back().second = globalSapperCoords;

        // Adding Sapper on all local maps
        for (auto& robot : robots) {

            if (robot == robots.back()) {
                continue;
            }

            auto rLocalMap = robot.first->getLocalMap();
            auto localSapperCoords =
                robots.back().second -
                robot.second +
                robot.first->getPosition();

            if (isInArray(GOOD_CELLS, rLocalMap->getCell(localSapperCoords))) {
                rLocalMap->setCell(localSapperCoords, SAPPER_OTHER);
            }
        }

        pGame->setRobots(robots);
    }
    else {
        auto robots = pGame->getRobots();

        // Deleting Sapper on all maps and setting its coords to (-1, -1)
        for (auto& robot : robots) {

            if (robot == robots.back()) {
                robot.first->getLocalMap()->setData({SAPPER_SELF}, 1, 1);
                continue;
            }

            auto rLocalMap = robot.first->getLocalMap();
            auto localSapperCoords =
                robots.back().second -
                robot.second +
                robot.first->getPosition();

            // If sapper exists on local map
            if (rLocalMap->getCell(localSapperCoords) == SAPPER_OTHER) {
                rLocalMap->setCell(
                    localSapperCoords,
                    pGame->getGlobalMap()->getCell(robots.back().second)
                );
            }
        }
        robots.back().second = {-1, -1};

        pGame->setRobots(robots);
    }
    pGame->setSapperState(action);
}
