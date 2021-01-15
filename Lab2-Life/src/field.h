#ifndef LAB2_LIFE_FIELD_H
#define LAB2_LIFE_FIELD_H

#include <algorithm>
#include <fstream>
#include <windows.h>
#include <fmt/format.h>
#include <fmt/color.h>

#include "variables.h"
#include "console.h"


class Field {
private:
    bool **old_field;
    bool **new_field;
    Console console;
    short_t getAliveNeighbours(short_t, short_t);

public:
    Field();
    ~Field();

    bool** getCells();
    bool isCell(short_t, short_t);

    void reset();
    void set(short_t, short_t);
    void clear(short_t, short_t);
    void step();
    void back();
    void save(std::string);
    void load(const std::string&);
    void print();
};

#endif //LAB2_LIFE_FIELD_H
