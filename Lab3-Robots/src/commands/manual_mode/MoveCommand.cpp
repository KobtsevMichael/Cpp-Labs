#include "MoveCommand.h"

void MoveCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw descriptive_exception("Invalid arguments number.");
    }
    direction = toDirectionType(argv[1]);
    if (direction == NONE_DIR) {
        throw descriptive_exception("Invalid argument(s).");
    }
}

std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>
    MoveCommand::execute(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>> robots,
        int activeRobotId,
        Map* pGlobalMap
    )
{
    auto [pRobot, globalCoords] = robots[activeRobotId];

    auto pLocalMap = pRobot->getLocalMap();
    auto localCoords = pRobot->getPosition();

    std::pair<int, int> diffCoords;

    switch (direction) {
        case U: diffCoords = {0, -1}; break;
        case D: diffCoords = {0, 1}; break;
        case R: diffCoords = {1, 0}; break;
        case L: diffCoords = {-1, 0}; break;
        case NONE_DIR:
            throw descriptive_exception("Wrong direction (programm bag).");
    }

    std::pair<int, int> newGlobalCoords = globalCoords + diffCoords;

    if (newGlobalCoords.first < 0 || newGlobalCoords.second < 0) {
        throw descriptive_exception("This is map end.");
    }

    cell_t oldCellT = pGlobalMap->getCell(globalCoords);
    cell_t newCellT = pGlobalMap->getCell(newGlobalCoords);

    if (newCellT == ROCK) {
        throw descriptive_exception("There is a rock on this cell!");
    }
    if (newCellT == BOMB) {
        throw end_exception("You exploded on the bomb...");
    }
    for (auto& robot : robots) {
        if (robot.second == newGlobalCoords) {
            throw descriptive_exception("There is a robot on this cell!");
        }
    }

    pRobot->setPosition(localCoords + diffCoords);
    pLocalMap->setCell(localCoords, oldCellT, true);

    robots[activeRobotId] = {pRobot, newGlobalCoords};

    return robots;
}