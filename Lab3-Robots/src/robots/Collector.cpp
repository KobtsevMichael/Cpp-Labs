#include "Collector.h"

Collector::Collector(int id) : AbstractRobot(id) {
    apples = 0;
    pLocalMap->setData({ROBOT}, 1, 1);
}

int Collector::getApples() const {
    return apples;
}

void Collector::addApple() {
    apples++;
}

