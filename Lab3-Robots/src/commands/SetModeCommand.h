#ifndef LAB3_ROBOTS_SETMODECOMMAND_H
#define LAB3_ROBOTS_SETMODECOMMAND_H

#include <vector>

#include "../variables/global.h"
#include "../utils/utils_functions.h"
#include "../utils/convert_functions.h"

#include "../modes/AbstractMode.h"

#include "AbstractCommand.h"

class Game;

class SetModeCommand : public AbstractCommand {
public:
    void validate(std::vector<std::string>) override;
    static void execute(Game*, std::vector<std::string>);
};

#endif //LAB3_ROBOTS_SETMODECOMMAND_H
