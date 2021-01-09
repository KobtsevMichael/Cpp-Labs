#ifndef LAB3_ROBOTS_ABSTRACTROBOT_H
#define LAB3_ROBOTS_ABSTRACTROBOT_H

#include <cmath>

#include "../map/Map.h"

class AbstractRobot {
protected:
    Map *pLocalMap;
    int id;
    int localX, localY;
public:
    explicit AbstractRobot(int id);
    virtual ~AbstractRobot();

    Map* getLocalMap();

    [[nodiscard]] int getId() const;
    std::pair<int, int> getPosition();

    std::pair<int, int> getPositionCorner();
    void setPosition(std::pair<int, int> pos);
};


#endif //LAB3_ROBOTS_ABSTRACTROBOT_H
