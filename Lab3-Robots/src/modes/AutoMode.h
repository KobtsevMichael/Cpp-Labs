#ifndef LAB3_ROBOTS_AUTOMODE_H
#define LAB3_ROBOTS_AUTOMODE_H

#include <queue>

#include "../algorithms/a_star_search.h"

#include "../commands/manual_mode/MoveCommand.h"
#include "../commands/manual_mode/GrabCommand.h"

#include "AbstractMode.h"

class AutoMode : public AbstractMode {
private:
    std::queue<std::pair<int, int>> sortPoints(
        std::vector<std::pair<int, int>>, std::pair<int, int>);
    bool isCloserToTarget(
        std::pair<int, int>,
        std::pair<int, int>,
        std::pair<int, int>);
    std::vector<direction_t> generateWay(
        std::queue<std::pair<int, int>>&,
        std::pair<int, int>,
        bool*,
        bool*,
        bool*,
        int);
    void doMove(
        std::vector<direction_t>&,
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&,
        int,
        MoveCommand*);
    void doGrab(
        std::vector<direction_t>&,
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&,
        int,
        GrabCommand*);
public:
    void sendCommand(AbstractCommand*) override;

};


#endif //LAB3_ROBOTS_AUTOMODE_H
