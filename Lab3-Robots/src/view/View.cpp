#include "View.h"
#include "../game/Game.h" // Cyclic import avoid


View::View(Game* _pGame) {
    pGame = _pGame;
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    showCursor(false);
    updateConsoleInfo();
}

void View::updateConsoleInfo() {

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(consoleHandle, &csbi);

    viewW = csbi.srWindow.Right - csbi.srWindow.Left;
    viewH = csbi.srWindow.Bottom - csbi.srWindow.Top;

    viewMapW = std::ceil((double)viewW / 2);
    viewMapH = pGame->getSapperState() ? 23 : 25;
}

void View::cls() {
    system("cls");
}

void View::setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(consoleHandle, coord);
}

void View::showCursor(bool flag) {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = flag;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void View::clearData() {
    // Printing spaces
    fmt::print(std::string(viewW*6, ' '));
    // Returning cursor
    setCursorPosition(2, robotLineH + viewMapH + gameInfoLineH + 1);
}

fmt::color View::getCellColor(cell_t cellT) {
    switch (cellT) {
        case ROCK: return rockColor;
        case BOMB: return bombColor;
        case APPLE: return appleColor;
        case ROBOT_SELF: return selfRobotColor;
        case ROBOT_OTHER: return otherRobotColor;
        case SAPPER_SELF:
        case SAPPER_OTHER: return sapperColor;
        default: return noneColor;
    }
}

void View::drawMap() {

    updateConsoleInfo();

    auto [pRobot, gCoords] = pGame->getActiveRobot();

    auto pLocalMap = pRobot->getLocalMap();
    auto localMapCenter = gCoords - (pRobot->getPosition());

    auto localMapSize = pLocalMap->getSize();
    auto globalMapSize = pGame->getGlobalMap()->getSize();

    int start_i = gCoords.first - viewMapW/2;
    int start_j = gCoords.second - viewMapH/2;

    fmt::print("{}\n", std::string(viewW, ' '));

    for (int j = start_j; j < viewMapH + start_j; ++j) {
        for (int i = start_i; i < viewMapW + start_i; ++i) {

            bool isOutsideMap = i < 0 || j < 0 ||
                i >= globalMapSize.first ||
                j >= globalMapSize.second;

            bool isInLocalViewArea =
                i >= localMapCenter.first - localMapSize.first/2 &&
                i <= localMapCenter.first + localMapSize.first/2 &&
                j >= localMapCenter.second - localMapSize.second/2 &&
                j <= localMapCenter.second + localMapSize.second/2;

            if (isOutsideMap) {
                std::cout << toCellSymbol(NONE_CELL);
            }
            else if (isInLocalViewArea) {
                cell_t cellT = pLocalMap->getCell(
                    std::pair(i, j) - localMapCenter
                );
                fmt::print(
                    fg(getCellColor(cellT)),
                    "{}", toCellSymbol(cellT)
                );
            }
            else {
                fmt::print("-");
            }
            fmt::print(" ");
        }
        fmt::print("\n");
    }
    fmt::print("{}\n", std::string(viewW, ' '));
}

void View::showRobotInfo(
    const std::pair<int, int>& robotGlobalCoords,
    int robotId,
    int applesCount,
    float robotResearch)
{
    fmt::print("{}\n", std::string(viewW, '-'));

    // Global coords
    fmt::print(fg(classicColor), "{:^{}}",
               fmt::format("Robot {}: {}", robotId, robotGlobalCoords),
               viewW/3);

    // Collected apples
    fmt::print(fg(classicColor), "{:^{}}",
               "Apples: " + std::to_string(applesCount), viewW/3);

    // Map research
    fmt::print(fg(classicColor), "{:^{}}",
               fmt::format("Researched: {:.1f}%", robotResearch), viewW/3);

    fmt::print("\n{}\n", std::string(viewW, '-'));

    robotLineH = pGame->getSapperState() ? 5 : 3;
}

void View::showSapperInfo(
    const std::pair<int, int>& sapperGlobalCoords,
    int bombsCount,
    float sapperResearch)
{
    // Global coords
    fmt::print(fg(classicColor), "{:^{}}",
               fmt::format("Sapper: {}", sapperGlobalCoords), viewW/3);

    // Collected bombs
    fmt::print(fg(classicColor), "{:^{}}",
               "Bombs: " + std::to_string(bombsCount), viewW/3);

    // Map research
    fmt::print(fg(classicColor), "{:^{}}",
               fmt::format("Researched: {:.1f}%", sapperResearch), viewW/3);

    fmt::print("\n{}\n", std::string(viewW, '-'));
}

void View::showGameStatusLine(
    const std::pair<state_t, std::string>& state,
    const std::string& modeName)
{
    fmt::color messageColor = classicColor;

    if (state.first == RUNNING) {
        messageColor = accentColor;
    }
    if (state.first == EXCEPTION) {
        messageColor = errorColor;
    }
    else if (state.first == SUCCESS) {
        messageColor = successColor;
    }
    else if (state.first == INFO) {
        messageColor = infoColor;
    }

    auto splittedStateMsg = splitStrByLength(state.second, viewW/2);

    for (auto& stateString : splittedStateMsg) {
        // State message
        fmt::print(fg(messageColor), "{:<{}}", stateString, viewW/2);

        // Current mode
        if (stateString == splittedStateMsg.front()) {
            fmt::print(fg(classicColor), "{:>{}}",
                       "Current mode: " + modeName, viewW/2);
        }
        fmt::print("\n");
    }

    fmt::print("$ ");

    gameInfoLineH = static_cast<int>(splittedStateMsg.size()) + 1;
}

void View::showGoodbyeMessage(std::string msg) {
//    cls();
//    fmt::print(fg(accentColor),
//               std::string(viewW, '#') + "\n");
//    fmt::print(fg(accentColor),
//               "{:^" + std::to_string(viewW) + "s}\n",
//               " BYE BYE ! ");
//    fmt::print(fg(accentColor),
//               std::string(viewW, '#') + "\n\n");

    fmt::print(fg(classicColor), "\n" + msg + "\n\n");
}

