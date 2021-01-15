#include "Collector.h"

Collector::Collector(int id) : AbstractRobot(id) {
    pLocalMap->setData({ROBOT_SELF}, 1, 1);
    apples = 0;
}

std::pair<cell_t, cell_t> Collector::getOwnType() {
    return {ROBOT_SELF, ROBOT_OTHER};
}

cell_t Collector::getItemType() {
    return APPLE;
}

std::vector<cell_t> Collector::getGoodCells() {
    return {EMPTY, APPLE, UNKNOWN};
}

int Collector::getItemsCount() const {
    return apples;
}

void Collector::onGrab() {
    apples++;
}
