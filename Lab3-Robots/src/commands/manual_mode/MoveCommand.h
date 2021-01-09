#ifndef LAB3_ROBOTS_MOVECOMMAND_H
#define LAB3_ROBOTS_MOVECOMMAND_H

#include <iostream>

#include "../../variables/global.h"
#include "../../utils/convert_functions.h"
#include "../../utils/utils_functions.h"

#include "AbstractManualModeCommand.h"

class MoveCommand : public AbstractManualModeCommand {
private:
    const int argc = 2;
    direction_t direction;
public:
    void validate(std::vector<std::string>) override;
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>
        execute(
            std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>,
            int,
            Map*) override;
};

#endif //LAB3_ROBOTS_MOVECOMMAND_H
