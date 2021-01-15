#ifndef LAB3_ROBOTS_ABSTRACTMANUALMODECOMMAND_H
#define LAB3_ROBOTS_ABSTRACTMANUALMODECOMMAND_H

#include <functional>

#include "../../robots/AbstractRobot.h"

#include "../AbstractCommand.h"

class AbstractManualModeCommand : public AbstractCommand {
public:
    virtual void execute(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&,
        int,
        Map*,
        std::function<void(std::pair<int, int>, cell_t)> = nullptr
    ) = 0;
};


#endif //LAB3_ROBOTS_ABSTRACTMANUALMODECOMMAND_H
