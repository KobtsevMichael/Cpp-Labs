#include "convert_functions.h"

#include "../modes/AutoMode.h"
#include "../modes/ManualMode.h"
#include "../modes/ScanMode.h"

#include "../commands/SetModeCommand.h"
#include "../commands/SetRobotCommand.h"
#include "../commands/ToggleSapperCommand.h"

// CELL_T
cell_t toCellType(char cellSymb) {
    switch(cellSymb) {
        case '.': return EMPTY;
        case '#': return ROCK;
        case 'B': return BOMB;
        case 'A': return APPLE;
        case 'R': return ROBOT_SELF;
        case 'S': return SAPPER_SELF;
        case '?': return UNKNOWN;
        default: return NONE_CELL;
    }
}

char toCellSymbol(cell_t cellType) {
    switch(cellType) {
        case EMPTY: return '.';
        case ROCK: return '#';
        case BOMB: return 'B';
        case APPLE: return 'A';
        case ROBOT_SELF:
        case ROBOT_OTHER: return 'R';
        case SAPPER_SELF:
        case SAPPER_OTHER: return 'S';
        case UNKNOWN: return '?';
        default: return ' ';
    }
}

// COMMAND_T
command_t toCommandType(const std::string& cmdName) {
    if (cmdName == "move") {
        return MOVE;
    }
    else if (cmdName == "grab") {
        return GRAB;
    }
    else if (cmdName == "scan") {
        return SCAN;
    }
    else if (cmdName == "set_mode") {
        return SET_MODE;
    }
    else if (cmdName == "robot") {
        return SET_ROBOT;
    }
    else if (cmdName == "sapper") {
        return TOGGLE_SAPPER;
    }
    else if (cmdName == "quit") {
        return QUIT;
    }
    else {
        return NONE_CMD;
    }
}

AbstractCommand* toCommandClass(command_t cmdType) {
    switch (cmdType) {
        case MOVE: return new MoveCommand;
        case GRAB: return new GrabCommand;
        case SCAN: return new ScanCommand;
        case SET_MODE: return new SetModeCommand;
        case SET_ROBOT: return new SetRobotCommand;
        case TOGGLE_SAPPER: return new ToggleSapperCommand;
        default: return nullptr;
    }
}


// MODE_T
std::string toModeName(rmode_t modeType) {
    switch (modeType) {
        case MANUAL_MODE: return "manual";
        case SCAN_MODE: return "scan";
        case AUTO_MODE: return "auto";
        default: return "unknown";
    }
}

rmode_t toModeType(const std::string& modeName) {
    if (modeName == "manual") {
        return MANUAL_MODE;
    }
    else if (modeName == "scan") {
        return SCAN_MODE;
    }
    else if (modeName == "auto") {
        return AUTO_MODE;
    }
    else {
        return NONE_MODE;
    }
}

AbstractMode* toModeClass(rmode_t modeType) {
    switch (modeType) {
        case MANUAL_MODE: return new ManualMode;
        case SCAN_MODE: return new ScanMode;
        case AUTO_MODE: return new AutoMode;
        default: return nullptr;
    }
}

// DIRECTION_T
direction_t toDirection(std::pair<int, int> diff) {
    switch (diff.second) {
        case -1: return U;
        case 1: return D;
        default: break;
    }
    switch (diff.first) {
        case 1: return R;
        case -1: return L;
        default: break;
    }
    return NONE_DIR;
}

direction_t toDirectionFromString(const std::string& dirStr) {
    if (dirStr == "u") {
        return U;
    }
    else if (dirStr == "d") {
        return D;
    }
    else if (dirStr == "r") {
        return R;
    }
    else if (dirStr == "l") {
        return L;
    }
    else {
        return NONE_DIR;
    }
}

std::pair<int, int> toDiffCoords(direction_t dir) {
    switch (dir) {
        case U: return {0, -1};
        case D: return {0, 1};
        case R: return {1, 0};
        case L: return {-1, 0};
        default: return {0, 0};
    }
}

std::pair<int, int> toDiffCoordsOpposite(direction_t dir) {
    switch (dir) {
        case U: return {0, 1};
        case D: return {0, -1};
        case R: return {-1, 0};
        case L: return {1, 0};
        default: return {0, 0};
    }
}
