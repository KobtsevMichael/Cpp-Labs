#ifndef LAB3_ROBOTS_SCANMODE_H
#define LAB3_ROBOTS_SCANMODE_H

#include "../utils/utils_functions.h"
#include "../algorithms/a_star_search.h"
#include "../algorithms/dijkstra.h"

#include "../robots/AbstractRobot.h"
#include "../commands/manual_mode/MoveCommand.h"
#include "../commands/manual_mode/ScanCommand.h"

#include "AbstractMode.h"

class ScanMode : public AbstractMode {
private:
    int stepsN;
public:
    void init(Game *, std::vector<std::string> = {}) override;
    void sendCommand(AbstractCommand *) override;
    bool isTraversable(Map*, Map*, std::pair<int, int>, std::pair<int, int>);
    std::pair<int, int> findNearestUnknownCell();
};

#endif //LAB3_ROBOTS_SCANMODE_H
