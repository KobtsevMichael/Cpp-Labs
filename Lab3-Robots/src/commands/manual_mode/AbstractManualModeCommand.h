#ifndef LAB3_ROBOTS_ABSTRACTMANUALMODECOMMAND_H
#define LAB3_ROBOTS_ABSTRACTMANUALMODECOMMAND_H

#include "../../robots/AbstractRobot.h"

#include "../AbstractCommand.h"

class AbstractManualModeCommand : public AbstractCommand {
public:
    virtual std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>
        execute(
            std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>,
            int,
            Map*) = 0;
};


#endif //LAB3_ROBOTS_ABSTRACTMANUALMODECOMMAND_H
