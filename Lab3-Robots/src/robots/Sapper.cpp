#include "Sapper.h"

Sapper::Sapper(int id) : AbstractRobot(id) {
    pLocalMap->setData({SAPPER_SELF}, 1, 1);
    bombs = 0;
}

std::pair<cell_t, cell_t> Sapper::getOwnType() {
    return {SAPPER_SELF, SAPPER_OTHER};
}

cell_t Sapper::getItemType() {
    return BOMB;
}

std::vector<cell_t> Sapper::getGoodCells() {
    return {EMPTY, APPLE, BOMB, UNKNOWN};
}

int Sapper::getItemsCount() const {
    return bombs;
}

void Sapper::onGrab() {
    bombs++;
}