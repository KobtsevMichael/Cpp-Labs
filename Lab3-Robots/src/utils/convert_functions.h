#ifndef LAB3_ROBOTS_CONVERT_FUNCTIONS_H
#define LAB3_ROBOTS_CONVERT_FUNCTIONS_H

#include <iostream>

#include "../variables/global.h"

class AbstractMode;
class AbstractCommand;

cell_t toCellType(char);
char toCellSymbol(cell_t);

std::string toModeName(rmode_t);
rmode_t toModeType(const std::string&);
AbstractMode* toModeClass(rmode_t);

command_t toCommandType(const std::string&);
AbstractCommand* toCommandClass(command_t);

direction_t toDirection(std::pair<int, int>);
direction_t toDirectionFromString(const std::string&);
std::pair<int, int> toDiffCoords(direction_t);
std::pair<int, int> toDiffCoordsOpposite(direction_t);

#endif //LAB3_ROBOTS_CONVERT_FUNCTIONS_H
