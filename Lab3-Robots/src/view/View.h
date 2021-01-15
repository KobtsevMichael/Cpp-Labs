#ifndef LAB3_ROBOTS_VIEW_H
#define LAB3_ROBOTS_VIEW_H

#include <windows.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/ranges.h>

#include "../variables/global.h"

class Game;

class View {
private:
    Game *pGame;

    HANDLE consoleHandle;

    int viewW{}, viewH{};
    int viewMapW{}, viewMapH{};

    int robotLineH;
    int gameInfoLineH;

    fmt::color classicColor = fmt::color::white;
    fmt::color errorColor = fmt::color::crimson;
    fmt::color successColor = fmt::color::medium_sea_green;
    fmt::color accentColor = fmt::color::dark_salmon;
    fmt::color infoColor = fmt::color::pale_turquoise;
    fmt::color noneColor = fmt::color::dim_gray;

    fmt::color rockColor = fmt::color::yellow;
    fmt::color bombColor = fmt::color::red;
    fmt::color appleColor = fmt::color::light_green;
    fmt::color selfRobotColor = fmt::color::cornflower_blue;
    fmt::color otherRobotColor = fmt::color::light_pink;
    fmt::color sapperColor = fmt::color::sandy_brown;

    fmt::color getCellColor(cell_t);

public:
    explicit View(Game*);

    void updateConsoleInfo();
    static void cls();

    void setCursorPosition(int x, int y);
    void showCursor(bool);
    void clearData();

    void drawMap();

    void showRobotInfo(const std::pair<int, int>& robotGlobalCoords,
                       int robotId,
                       int applesCount,
                       float robotResearch);

    void showSapperInfo(const std::pair<int, int>& sapperGlobalCoords,
                        int bombsCount,
                        float sapperResearch);

    void showGameStatusLine(const std::pair<state_t, std::string>& state,
                            const std::string& modeName);

    void showGoodbyeMessage(std::string);
};

#endif //LAB3_ROBOTS_VIEW_H