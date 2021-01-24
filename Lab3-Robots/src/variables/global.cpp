#include "global.h"

const int SLEEP_TIME = 0;
const int EXP_K = 2;

const std::vector<cell_t> GOOD_CELLS = {EMPTY, APPLE, ROBOT_SELF};
const std::vector<command_t> MODE_COMMANDS = {MOVE, SCAN, GRAB};

std::string SCAN_MODE_ALGORITHM = "a_star";