#ifndef LAB3_ROBOTS_MOVECOMMAND_H
#define LAB3_ROBOTS_MOVECOMMAND_H

#include "../../variables/global.h"
#include "../../utils/convert_functions.h"
#include "../../utils/utils_functions.h"

#include "AbstractManualModeCommand.h"

class MoveCommand : public AbstractManualModeCommand {
private:
    const int argc = 2;
    direction_t direction;

public:
    void setDirection(direction_t);

    void validate(std::vector<std::string>) override;

    void execute(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&,
        int,
        Map*,
        std::function<void(std::pair<int, int>, cell_t)> = nullptr
    ) override;

    std::pair<int, int> getGoodNeighbourIfExists(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&,
        Map*,
        std::pair<int, int>
    );

    void updatePositionOnAllLocalMaps(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&,
        AbstractRobot*,
        Map*,
        std::pair<int, int>,
        std::pair<int, int>
    );
};

#endif //LAB3_ROBOTS_MOVECOMMAND_H
