#include "convert_functions.h"

#include "../modes/AutoMode.h"
#include "../modes/ManualMode.h"
#include "../modes/ScanMode.h"

#include "../commands/manual_mode/MoveCommand.h"
#include "../commands/manual_mode/GrabCommand.h"
#include "../commands/manual_mode/ScanCommand.h"
#include "../commands/SetModeCommand.h"

// CELL_T
cell_t toCellType(char cellSymb) {
    switch(cellSymb) {
        case '.': return EMPTY;
        case '#': return ROCK;
        case 'B': return BOMB;
        case 'A': return APPLE;
        case 'R': return ROBOT;
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
        case ROBOT: return 'R';
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
    else if (cmdName == "quit") {
        return QUIT;
    }
    else {
        return command_t::NONE_CMD;
    }
}

AbstractCommand* toCommandClass(command_t cmdType) {
    switch (cmdType) {
        case MOVE: return new MoveCommand;
        case GRAB: return new GrabCommand;
        case SCAN: return new ScanCommand;
        case SET_MODE: return new SetModeCommand;
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
direction_t toDirectionType(const std::string& dir) {
    if (dir == "u") {
        return U;
    }
    else if (dir == "d") {
        return D;
    }
    else if (dir == "r") {
        return R;
    }
    else if (dir == "l") {
        return L;
    }
    else {
        return NONE_DIR;
    }
}

