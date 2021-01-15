#include "SetRobotCommand.h"
#include "../game/Game.h"

void SetRobotCommand::validate(std::vector<std::string> argv) {
    if (argv.size() != argc) {
        throw error_exception("Invalid arguments number.");
    }
    // Parsing argument & setting id
    newId = toInt(argv[1]);
}

void SetRobotCommand::execute(Game* pGame) {
    if (newId < 0 || newId >= pGame->getRobots().size()) {
        throw error_exception("There is no collector with this id.");
    }
    pGame->setActiveRobotId(newId);
}
