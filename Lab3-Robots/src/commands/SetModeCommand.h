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
private:
    std::vector<std::string> modeArgs;
public:
    void validate(std::vector<std::string>) override;
    void execute(Game*);
};

#endif //LAB3_ROBOTS_SETMODECOMMAND_H
