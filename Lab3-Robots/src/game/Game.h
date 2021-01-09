#ifndef LAB3_ROBOTS_GAME_H
#define LAB3_ROBOTS_GAME_H

#include <windows.h>
#include <cstdlib>

#include "../variables/global.h"
#include "../utils/exceptions.h"
#include "../utils/utils_functions.h"
#include "../utils/convert_functions.h"

#include "../map/Map.h"
#include "../robots/Collector.h"
#include "../commands/SetModeCommand.h"
#include "../modes/AbstractMode.h"

class View;

class Game {
private:
    std::pair<state_t, std::string> state;

    View *pView;
    Map *pGlobalMap;

    AbstractMode *pMode{};
    rmode_t modeType;

    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>> robots;
    int activeRobotId;

    void mainCycle();
    void waitForCommand();
    static std::vector<std::string> parseCommandLine(std::string&);

public:
    Game();
    ~Game();

    Map* getGlobalMapPtr();

    std::vector<
        std::pair<AbstractRobot*, std::pair<int, int>>> getRobots();

    void setRobots(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>);

    [[nodiscard]] int getActiveRobotId() const;

    void setMode(rmode_t);

    void start();
    void refresh(int=0);
};

#endif //LAB3_ROBOTS_GAME_H