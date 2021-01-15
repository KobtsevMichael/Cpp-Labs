#ifndef LAB3_ROBOTS_GAME_H
#define LAB3_ROBOTS_GAME_H

#include "../variables/global.h"
#include "../utils/exceptions.h"
#include "../utils/utils_functions.h"
#include "../utils/convert_functions.h"

#include "../map/Map.h"
#include "../robots/Collector.h"
#include "../robots/Sapper.h"
#include "../modes/ManualMode.h"
#include "../commands/SetModeCommand.h"

class View;

class Game {
private:
    // PRIVATE FIELDS
    std::pair<state_t, std::string> state;

    View *pView;

    AbstractMode *pMode{};
    rmode_t modeType;

    Map *pGlobalMap;
    std::vector<std::pair<int, int>> globalApplesList;
    std::vector<std::pair<int, int>> globalBombsList;

    std::vector<std::pair<AbstractRobot*, std::pair<int, int>>> robots;
    int robotsN, activeRobotId;
    bool isSapperOn;

    // PRIVATE METHODS
    void mainCycle();
    void waitForCommand();
    static void onKeyboardInterrupt(sig_atomic_t);
    static std::vector<std::string> parseCommandLine(std::string&);
    void generateRobotsList(int, int, int);
    float calculateRobotResearch(int);

public:
    Game(std::string, int, int, int);
    ~Game();

    // GETTERS & SETTERS
    void setState(std::pair<state_t, std::string>);
    void setMode(rmode_t, std::vector<std::string> = {});

    Map* getGlobalMap();
    const std::vector<std::pair<int, int>>& getItemList(cell_t);
    void removeItemFromItemList(std::pair<int, int>, cell_t);

    std::vector<
        std::pair<AbstractRobot*, std::pair<int, int>>> getRobots();
    void setRobots(
        std::vector<std::pair<AbstractRobot*, std::pair<int, int>>>&);
    int getRobotsN() const;

    int getActiveRobotId() const;
    void setActiveRobotId(int);
    std::pair<AbstractRobot*, std::pair<int, int>> getActiveRobot();

    std::pair<AbstractRobot*, std::pair<int, int>> getSapper();
    bool getSapperState() const;
    void setSapperState(bool);

    // PUBLIC METHODS
    void start();
    void refresh(int=0, bool = true);
    bool isOtherRobotOnCell(std::pair<int, int>, int=-1);
};

#endif //LAB3_ROBOTS_GAME_H