#include "AbstractRobot.h"

AbstractRobot::AbstractRobot(int id)
: pLocalMap(new Map), id(id), localX(0), localY(0) {}

AbstractRobot::~AbstractRobot() {
    delete pLocalMap;
}

void AbstractRobot::setPosition(std::pair<int, int> pos) {
    if (
        (abs(localX - pos.first) == 1 && abs(localY - pos.second) == 0) ||
        (abs(localX - pos.first) == 0 && abs(localY - pos.second) == 1)
    ) {
        pLocalMap->setCell({localX, localY}, UNKNOWN, true);
        localX = pos.first;
        localY = pos.second;
        pLocalMap->setCell(pos, ROBOT, true);
    }
}

Map* AbstractRobot::getLocalMap() {
    return pLocalMap;
}

int AbstractRobot::getId() const {
    return id;
}

std::pair<int, int> AbstractRobot::getPosition() {
    return std::make_pair(localX, localY);
}

std::pair<int, int> AbstractRobot::getPositionCorner() {
    auto localMapSize = pLocalMap->getSize();
    return {localX + localMapSize.first/2, localY + localMapSize.second/2};
}
