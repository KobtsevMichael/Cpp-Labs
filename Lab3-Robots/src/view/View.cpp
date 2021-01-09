#include "View.h"
#include "../game/Game.h" // Cyclic import avoid

View::View(Game *pGame) : pGame(pGame) {}

fmt::color View::getCellColor(cell_t cellT) {
    switch (cellT) {
        case ROCK: return rockColor;
        case BOMB: return bombColor;
        case APPLE: return appleColor;
        case ROBOT: return robotColor;
        default: return noneColor;
    }
}

std::pair<int, int> View::getViewMapSize() {
    return std::make_pair(viewMapW, viewMapH);
}

void View::updateConsoleInfo() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    viewW = csbi.srWindow.Right - csbi.srWindow.Left;
    viewH = 25;

    viewMapW = std::ceil((double)viewW / 2);
    viewMapH = viewH;

    stateLineColumns = viewW > 60 ? 4 : 2;
}

void View::clearView() {
    system("cls");
}

void View::drawMap() {
    clearView();
    updateConsoleInfo();

    auto [pRobot, globalCoords] = pGame->getRobots()[pGame->getActiveRobotId()];

    auto localMapCoords = globalCoords - (pRobot->getPositionCorner());
    auto localMapSize = pRobot->getLocalMap()->getSize();
    auto localMapData = pRobot->getLocalMap()->getData();

    int start_i = globalCoords.first - viewMapW/2;
    int start_j = globalCoords.second - viewMapH/2;

    for (int j = start_j, k = 0; j < viewMapH + start_j; ++j) {
        for (int i = start_i; i < viewMapW + start_i; ++i) {
            bool isXInLocalViewArea = \
                i >= localMapCoords.first &&
                i < localMapCoords.first + localMapSize.first;
            bool isYInLocalViewArea = \
                j >= localMapCoords.second &&
                j < localMapCoords.second + localMapSize.second;

            if (isXInLocalViewArea && isYInLocalViewArea) {
                if (i < 0 || j < 0) {
                    std::cout << toCellSymbol(NONE_CELL);
                }
                else {
                    fmt::print(fg(getCellColor(localMapData[k])), "{}",
                               toCellSymbol(localMapData[k]));
                }
                k++;
            }
            else if (i < 0 || j < 0) {
                std::cout << toCellSymbol(NONE_CELL);
            }
            else {
                std::cout << "-";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void View::showGameStatusLine(
    const std::pair<state_t, std::string>& state,
    int robotId,
    int applesCount,
    const std::string& modeName
) {
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

    // State message
    fmt::print(fg(messageColor),
               "{:<" + std::to_string(viewW/stateLineColumns) + "s}",
               state.second);
    // Robot id
    fmt::print(fg(classicColor),
               "{:^" + std::to_string(viewW/stateLineColumns) + "s}",
               "Robot id: " + std::to_string(robotId));
    // Collected apples
    fmt::print(fg(classicColor),
               "{:^" + std::to_string(viewW/stateLineColumns) + "s}",
               "Apples: " + std::to_string(applesCount));
    // Current mode
    fmt::print(fg(classicColor),
               "{:>" + std::to_string(viewW/stateLineColumns) + "s}",
               "Current mode: " + modeName);

    std::cout << "\n$ ";
}

void View::showGoodbyeMessage(std::string msg) {
//    clearView();
//    fmt::print(fg(accentColor),
//               std::string(viewW, '#') + "\n");
//    fmt::print(fg(accentColor),
//               "{:^" + std::to_string(viewW) + "s}\n",
//               " BYE BYE ! ");
//    fmt::print(fg(accentColor),
//               std::string(viewW, '#') + "\n\n");

    fmt::print(fg(classicColor), "\n" + msg + "\n");
}

