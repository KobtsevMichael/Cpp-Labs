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

extern const int SLEEP_TIME;
extern const int EXP_K;

extern const std::vector<cell_t> GOOD_CELLS;
extern const std::vector<command_t> MODE_COMMANDS;

extern std::string SCAN_MODE_ALGORITHM;

#endif //LAB3_ROBOTS_GLOBAL