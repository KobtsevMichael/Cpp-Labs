#ifndef LAB3_ROBOTS_GLOBAL
#define LAB3_ROBOTS_GLOBAL

#include <string>
#include <vector>

enum state_t {
    START,
    RUNNING,
    INFO,
    SUCCESS,
    EXCEPTION,
    END
};

enum cell_t {
    EMPTY,
    ROCK,
    BOMB,
    APPLE,
    ROBOT_SELF,
    ROBOT_OTHER,
    SAPPER_SELF,
    SAPPER_OTHER,
    UNKNOWN,
    NONE_CELL
};

enum command_t {
    MOVE,
    GRAB,
    SCAN,
    SET_MODE,
    SET_ROBOT,
    TOGGLE_SAPPER,
    QUIT,
    NONE_CMD
};

enum rmode_t {
    MANUAL_MODE,
    SCAN_MODE,
    AUTO_MODE,
    NONE_MODE
};

enum direction_t {
    U,
    D,
    R,
    L,
    NONE_DIR
};


const int SLEEP_TIME = 0;
const int EXP_K = 2;

const std::vector<cell_t> GOOD_CELLS = {EMPTY, APPLE, ROBOT_SELF};

const std::vector<command_t> MODE_COMMANDS = {MOVE, SCAN, GRAB};

#endif //LAB3_ROBOTS_GLOBAL