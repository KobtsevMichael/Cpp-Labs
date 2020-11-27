#ifndef LAB2_LIFE_FIELD_H
#define LAB2_LIFE_FIELD_H

#include <algorithm>
#include <fstream>
#include <fmt/format.h>
#include <fmt/color.h>

#include "variables.h"


class Field {

private:
    bool **old_field;
    bool **new_field;
    short_t getAliveNeighbours(short_t, short_t);

public:
    Field();
    ~Field();
    bool** getCells();
    void reset();
    void set(short_t, short_t);
    void clear(short_t, short_t);
    void step();
    void back();
    void save(std::string);
    void load(std::string);
    void print();
    bool isCell(short_t, short_t);
};

#endif //LAB2_LIFE_FIELD_H
