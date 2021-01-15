#include "AbstractRobot.h"

AbstractRobot::AbstractRobot(int _id) {
    pLocalMap = new Map(true);
    id = _id;
    position = {0, 0};
}

AbstractRobot::~AbstractRobot() {
    delete pLocalMap;
}

void AbstractRobot::setPosition(std::pair<int, int> newPos) {
    if ((abs(position.first - newPos.first) == 1 &&
        abs(position.second - newPos.second) == 0) ||
        (abs(position.first - newPos.first) == 0 &&
        abs(position.second - newPos.second) == 1)
    ) {
        position = newPos;
        pLocalMap->setCell(newPos, getOwnType().first);
    }
}

Map* AbstractRobot::getLocalMap() {
    return pLocalMap;
}

int AbstractRobot::getId() const {
    return id;
}

std::pair<int, int> AbstractRobot::getPosition() {
    return position;
}
