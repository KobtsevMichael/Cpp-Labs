#ifndef LAB3_ROBOTS_VIEW_H
#define LAB3_ROBOTS_VIEW_H

#include <iostream>
#include <fmt/chrono.h>
#include <fmt/color.h>

#include <windows.h>
#include <cmath>

#include "../variables/global.h"

class Game;

class View {
private:
    Game *pGame;
    int viewW{}, viewH{};
    int viewMapW{}, viewMapH{};
    int stateLineColumns{};

    fmt::color classicColor = fmt::color::white;
    fmt::color errorColor = fmt::color::crimson;
    fmt::color successColor = fmt::color::medium_sea_green;
    fmt::color accentColor = fmt::color::dark_salmon;
    fmt::color noneColor = fmt::color::dim_gray;

    fmt::color rockColor = fmt::color::yellow;
    fmt::color bombColor = fmt::color::red;
    fmt::color appleColor = fmt::color::light_green;
    fmt::color robotColor = fmt::color::cornflower_blue;

    fmt::color getCellColor(cell_t);

public:
    explicit View(Game*);

    std::pair<int, int> getViewMapSize();

    static void clearView();
    void updateConsoleInfo();
    void drawMap();

    void showGameStatusLine(const std::pair<state_t, std::string>& state,
                            int robotId,
                            int applesCount,
                            const std::string& modeName);

    void showGoodbyeMessage(std::string);
};

#endif //LAB3_ROBOTS_VIEW_H