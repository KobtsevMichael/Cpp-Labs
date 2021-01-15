#ifndef LAB3_ROBOTS_GRABCOMMAND_H
#define LAB3_ROBOTS_GRABCOMMAND_H

#include "../../robots/Collector.h"

#include "AbstractManualModeCommand.h"

class GrabCommand : public AbstractManualModeCommand {
private:
    const int argc = 1;

public:
    void validate(std::vector<std::string>) override;

    void execute(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&,
        int,
        Map*,
        std::function<void(std::pair<int, int>, cell_t)> = nullptr
    ) override;
};


#endif //LAB3_ROBOTS_GRABCOMMAND_H
