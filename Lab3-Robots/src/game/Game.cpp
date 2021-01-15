#include "Game.h"
#include "../view/View.h" // Cyclic import avoid

#include <thread>

// CONSTRUCTOR & DESTRUCTOR

Game::Game(
    std::string GLOBAL_MAP_FILE_PATH,
    int GLOBAL_MAP_W,
    int GLOBAL_MAP_H,
    int COLLECTORS_N)
{
    try {
        pGlobalMap = new Map;
        pGlobalMap->readFromFile(
            GLOBAL_MAP_FILE_PATH, GLOBAL_MAP_W, GLOBAL_MAP_H,
            globalApplesList, globalBombsList
        );
    }
    catch (std::exception& e) {
        throw error_exception(
            fmt::format("Map reading error - {}", e.what())
        );
    }

    pView = new View(this);

    setMode(MANUAL_MODE);

    generateRobotsList(COLLECTORS_N, GLOBAL_MAP_W, GLOBAL_MAP_H);
    activeRobotId = 0;
    isSapperOn = false;
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

void Game::setState(std::pair<state_t, std::string> _state) {
    state = _state;
}

void Game::setMode(rmode_t _modeType, std::vector<std::string> _modeArgs) {
    delete pMode;
    pMode = toModeClass(_modeType);
    pMode->init(this, _modeArgs);
    modeType = _modeType;
}

Map* Game::getGlobalMap() {
    return pGlobalMap;
}

const std::vector<std::pair<int, int>>& Game::getItemList(cell_t itemT) {
    if (itemT == APPLE) {
        return globalApplesList;
    }
    else if (itemT == BOMB) {
        return globalBombsList;
    }
    // Default
    return globalApplesList;
}

void Game::removeItemFromItemList(std::pair<int, int> coords, cell_t itemT) {
    if (itemT == APPLE) {
        globalApplesList.erase(
            std::remove(
                globalApplesList.begin(),
                globalApplesList.end(),
                coords
            ), globalApplesList.end()
        );
    }
    else if (itemT == BOMB) {
        globalBombsList.erase(
            std::remove(
                globalBombsList.begin(),
                globalBombsList.end(),
                coords
            ), globalBombsList.end()
        );
    }
}

std::vector<
    std::pair<AbstractRobot*, std::pair<int, int>>> Game::getRobots() {
    return robots;
}

void Game::setRobots(
    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>& _robots)
{
    robots = _robots;
}

int Game::getRobotsN() const {
    return robotsN;
}

int Game::getActiveRobotId() const {
    return activeRobotId;
}

void Game::setActiveRobotId(int _id) {
    activeRobotId = _id;
}

std::pair<AbstractRobot*, std::pair<int, int>> Game::getActiveRobot() {
    return robots[activeRobotId];
}

std::pair<AbstractRobot*, std::pair<int, int>> Game::getSapper() {
    return robots.back();
}

bool Game::getSapperState() const {
    return isSapperOn;
}

void Game::setSapperState(bool _isSapperOn) {
    isSapperOn = _isSapperOn;
}

// METHODS

void Game::start() {
    signal (SIGINT, onKeyboardInterrupt);
    state = {START, "Hello, my dear friend!"};
    mainCycle();
}

void Game::onKeyboardInterrupt(sig_atomic_t) {
    View::cls();
    exit(0);
}

void Game::mainCycle() {
    View::cls();
    while (state.first != END) {
        refresh();
        waitForCommand();
    }
}

void Game::refresh(int delay, bool isClearingData) {

    if (state.first != START) {
        pView->setCursorPosition(0, 0);
    }

    pView->showRobotInfo(
        robots[activeRobotId].second,
        activeRobotId,
        robots[activeRobotId].first->getItemsCount(),
        calculateRobotResearch(activeRobotId)
    );
    if (isSapperOn) {
        pView->showSapperInfo(
            robots.back().second,
            robots.back().first->getItemsCount(),
            calculateRobotResearch(robotsN - 1)
        );
    }

    pView->drawMap();
    pView->showGameStatusLine(state, toModeName(modeType));

    if (delay) {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
    if (isClearingData) {
        pView->clearData();
    }
}

void Game::waitForCommand() {

    std::string cmdLine;
    std::getline(std::cin, cmdLine);

    try {
        // Split command line on args
        std::vector<std::string> args = parseCommandLine(cmdLine);
        // Command check
        command_t cmdType = toCommandType(args[0]);
        if (cmdType == QUIT) {
            throw end_exception("Bye bye !");
        }
        if (cmdType == NONE_CMD) {
            throw error_exception("Invalid command name.");
        }
        // Getting command class and checking args
        auto cmd = toCommandClass(cmdType);
        cmd->validate(args);
        // Passing command to necessary mode & executing
        if (cmdType == SET_MODE) {
            cmd->execute(this);
            pMode->sendCommand(cmd);
        }
        else if (isInArray(MODE_COMMANDS, cmdType)) {
            pMode->sendCommand(cmd);
        }
        else {
            cmd->execute(this);
        }
        delete cmd;
        // If everything is ok
        state = {SUCCESS, "Success!"};
    }
    catch (info_exception& e) {
        state = {INFO, e.what()};
        return;
    }
    catch (error_exception& e) {
        state = {EXCEPTION, e.what()};
        return;
    }
    catch (end_exception& e) {
        state.first = END;
        pView->showGoodbyeMessage(e.what());
        return;
    }
}

std::vector<std::string> Game::parseCommandLine(std::string& cmdLine) {
    std::vector<std::string> args = splitStr(toLower(trimStr(cmdLine)));
    if (args.empty()) {
        throw error_exception("Command line is empty.");
    }
    return args;
}

void Game::generateRobotsList(int collectorsN, int mapW, int mapH) {

    srand(time(nullptr));
    std::pair<int, int> randCoords;

    for (int i=0; i < collectorsN; ++i) {
        do {
            randCoords = {randInt(0, mapW), randInt(0, mapH)};
        } while (
            // To spawn collector on an empty cell
            pGlobalMap->getCell(randCoords) != EMPTY ||
            // To not spawn on the same cell as other collector
            isOtherRobotOnCell(randCoords)
        );
        robots.emplace_back(new Collector(i), randCoords);
    }
    robots.emplace_back(new Sapper(collectorsN), std::pair(-1, -1));
    robotsN = collectorsN + 1;
}

float Game::calculateRobotResearch(int id) {
    auto globalMapSize = pGlobalMap->getSize();
    int globalMapCellsCount = globalMapSize.first * globalMapSize.second;
    return (
        static_cast<float>(
            (robots[id].first)->getLocalMap()->getResearch()) /
        static_cast<float>(globalMapCellsCount) *
        static_cast<float>(100.0)
    );
}

bool Game::isOtherRobotOnCell(std::pair<int, int> cellCoords, int ignore) {
    if (ignore == -1) {
        ignore = activeRobotId;
    }
    return std::any_of(
        robots.begin(),
        robots.end(),
        [this, cellCoords, ignore] (const auto& robot) {
            return robot.second == cellCoords &&
                   robot.first->getId() != activeRobotId &&
                   robot.first->getId() != ignore;
        }
    );
}