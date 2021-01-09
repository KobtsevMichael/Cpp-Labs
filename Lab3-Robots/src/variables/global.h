#ifndef LAB3_ROBOTS_GLOBAL
#define LAB3_ROBOTS_GLOBAL

#include <string>

enum state_t {
    START,
    RUNNING,
    SUCCESS,
    EXCEPTION,
    END
};

enum cell_t {
    EMPTY,
    ROCK,
    BOMB,
    APPLE,
    ROBOT,
    UNKNOWN,
    NONE_CELL
};

enum command_t {
    MOVE,
    GRAB,
    SCAN,
    SET_MODE,
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

extern int MAP_W;
extern int MAP_H;
extern int VIEW_W;
extern int VIEW_H;

extern int COLLECTORS_N;

extern std::string GLOBAL_MAP_FILE_PATH;

#endif //LAB3_ROBOTS_GLOBAL