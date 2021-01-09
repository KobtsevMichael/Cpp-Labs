#include "SetModeCommand.h"
#include "../game/Game.h"

void SetModeCommand::validate(std::vector<std::string> argv) {
    if (argv.size() < 2) {
        throw descriptive_exception("Invalid arguments number.");
    }
    rmode_t modeType = toModeType(toLower(argv[1]));
    if (modeType == NONE_MODE) {
        throw descriptive_exception("Invalid mode name.");
    }
    else if (
        modeType == MANUAL_MODE and argv.size() != 2 or \
        modeType == AUTO_MODE and argv.size() != 2
    ) {
        throw descriptive_exception("Invalid arguments number.");
    }
    else if (modeType == SCAN_MODE) {
        try {
            std::stoi(argv.at(2));
        }
        catch (std::exception&) {
            throw descriptive_exception("Invalid steps number.");
        }
    }
    modeArgs = argv;
}

void SetModeCommand::execute(Game* pGame) {
    rmode_t newModeType = toModeType(modeArgs[1]);
    pGame->setMode(newModeType, modeArgs);
}
