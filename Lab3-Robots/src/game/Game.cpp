#include "Game.h"
#include "../view/View.h" // Cyclic import avoid

// CONSTRUCTOR & DESTRUCTOR

Game::Game() {

    try {
        pGlobalMap = new Map;
        pGlobalMap->readFromFile(GLOBAL_MAP_FILE_PATH);
    }
    catch (std::exception& e) {
        throw descriptive_exception(
            std::string("Map reading error - ") + e.what()
        );
    }

    pView = new View(this);

    setMode(MANUAL_MODE);

    srand(time(nullptr));

    for (int i=0; i < COLLECTORS_N; ++i) {
        // To spawn collector on random empty cell
        std::pair<int, int> randCoords;
        do {
            randCoords = {randInt(0, MAP_W), randInt(0, MAP_H)};
        } while (pGlobalMap->getCell(randCoords) != EMPTY);

        robots.push_back({new Collector(i), randCoords});
    }
    activeRobotId = 0;
}

Game::~Game() {

    delete pView;
    delete pGlobalMap;
    delete pMode;

    for (auto& pRobot : robots) {
        delete pRobot.first;
    }
    robots.clear();
}

// GETTERS & SETTERS

Map* Game::getGlobalMapPtr() {
    return pGlobalMap;
}

std::vector<
    std::pair<AbstractRobot*, std::pair<int, int>>> Game::getRobots() {
    return robots;
}

int Game::getActiveRobotId() const {
    return activeRobotId;
}

void Game::setRobots(
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>> _robots
) {
    robots = _robots;
}

void Game::setMode(rmode_t _modeType, std::vector<std::string> _modeArgs) {
    delete pMode;
    pMode = toModeClass(_modeType);
    pMode->init(this, _modeArgs);
    modeType = _modeType;
}

// METHODS

void Game::start() {
    state = {START, "Hello, my dear friend!"};
    mainCycle();
}

void Game::mainCycle() {
    while (state.first != END) {
        refresh();
        waitForCommand();
    }
}

void Game::refresh(int delay) {
    pView->drawMap();
    pView->showGameStatusLine(
        state,
        activeRobotId,
        dynamic_cast<Collector*>(robots[activeRobotId].first)->getApples(),
        toModeName(modeType)
    );
    if (delay) {
        Sleep(delay);
    }
}

void Game::waitForCommand() {

    state = {RUNNING, "Running..."};

    std::string cmdLine;
    std::getline(std::cin, cmdLine);

    try {
        // Split command line on args
        std::vector<std::string> args = parseCommandLine(cmdLine);
        // Command check
        command_t cmdType = toCommandType(args[0]);
        if (cmdType == QUIT) {
            throw end_exception("BYE BYE !");
        }
        if (cmdType == NONE_CMD) {
            throw descriptive_exception("Invalid command name.");
        }
        // Getting command class and checking args
        auto cmd = toCommandClass(cmdType);
        cmd->validate(args);
        // Passing command to necessary mode & executind
        if (cmdType == SET_MODE) {
            dynamic_cast<SetModeCommand*>(cmd)->execute(this);
        }
        if (cmdType != SET_MODE or modeType != MANUAL_MODE) {
            pMode->executeCommand(cmd);
        }
        delete cmd;
        // If everything is ok
        state = {SUCCESS, "Success!"};
    }
    catch (end_exception& e) {
        state.first = END;
        pView->showGoodbyeMessage(e.what());
        return;
    }
    catch (descriptive_exception& e) {
        state = {EXCEPTION, e.what()};
        return;
    }
}

std::vector<std::string> Game::parseCommandLine(std::string& cmdLine) {
    std::vector<std::string> args = splitStr(toLower(trimStr(cmdLine)));
    if (args.empty()) {
        throw descriptive_exception("Command line is empty.");
    }
    return args;
}
