#ifndef LAB3_ROBOTS_ABSTRACTCOMMAND_H
#define LAB3_ROBOTS_ABSTRACTCOMMAND_H

#include <string>
#include <vector>

#include "../utils/utils_functions.h"
#include "../utils/exceptions.h"

class Game;

class AbstractCommand {
public:
    virtual ~AbstractCommand() = default;
    virtual void validate(std::vector<std::string>) = 0;
    virtual void execute(Game*) {};
};


#endif //LAB3_ROBOTS_ABSTRACTCOMMAND_H
