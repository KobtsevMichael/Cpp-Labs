#ifndef LAB2_LIFE_CONSOLE_H
#define LAB2_LIFE_CONSOLE_H

#include <iostream>
#include <sstream>
#include <vector>
#include <windows.h>
#include <fmt/format.h>
#include <fmt/color.h>

#include "variables.h"
#include "field.h"


enum consoleMessage {
    GREETING,
    SUCCESS,
    INVALID_COMMAND,
    INVALID_ARG_NUMBER,
    INVALID_ARGUMENT,
    INVALID_FILE,
    QUIT
};

class Console {

private:
    std::string alphabet;
public:
    consoleMessage current_status;

    Console();
    void clear();
    void updateField(Field*);
    consoleMessage readCommand(Field*);

    void readCoords(std::string, Field*, short_t*, short_t*);
    std::vector<std::string> split(const std::string&, char);
};

#endif //LAB2_LIFE_CONSOLE_H
