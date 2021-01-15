#ifndef LAB3_ROBOTS_ABSTRACTROBOT_H
#define LAB3_ROBOTS_ABSTRACTROBOT_H

#include <cmath>

#include "../map/Map.h"

class AbstractRobot {
protected:
    Map *pLocalMap;
    int id;
    std::pair<int, int> position;

public:
    explicit AbstractRobot(int id);
    virtual ~AbstractRobot();

    // COMMON GETTERS & SETTERS
    Map* getLocalMap();

    int getId() const;

    std::pair<int, int> getPosition();
    void setPosition(std::pair<int, int> pos);

    // NECESSARY ROBOTS METHODS
    virtual std::pair<cell_t, cell_t> getOwnType() = 0;
    virtual cell_t getItemType() = 0;
    virtual std::vector<cell_t> getGoodCells() = 0;
    virtual int getItemsCount() const = 0;
    virtual void onGrab() = 0;
};


#endif //LAB3_ROBOTS_ABSTRACTROBOT_H
