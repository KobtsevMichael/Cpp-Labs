#ifndef LAB3_ROBOTS_SAPPER_H
#define LAB3_ROBOTS_SAPPER_H

#include "AbstractRobot.h"

class Sapper : public AbstractRobot {
private:
    int bombs = 0;
public:
    explicit Sapper(int id);

    std::pair<cell_t, cell_t> getOwnType() override;
    cell_t getItemType() override;
    std::vector<cell_t> getGoodCells() override;
    int getItemsCount() const override;
    void onGrab() override;
};


#endif //LAB3_ROBOTS_SAPPER_H
