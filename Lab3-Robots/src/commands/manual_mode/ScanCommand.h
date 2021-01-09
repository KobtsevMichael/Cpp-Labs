#ifndef LAB3_ROBOTS_SCANCOMMAND_H
#define LAB3_ROBOTS_SCANCOMMAND_H

#include <iostream>

#include "AbstractManualModeCommand.h"

class ScanCommand : public AbstractManualModeCommand {
private:
    const int argc = 1;
public:
    void validate(std::vector<std::string>) override;
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>
    execute(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>,
        int,
        Map*) override;
};


#endif //LAB3_ROBOTS_SCANCOMMAND_H
