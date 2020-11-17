#ifndef LAB2_LIFE_FIELD_H
#define LAB2_LIFE_FIELD_H

#include <iostream>
#include <algorithm>
#include <fstream>

#include "variables.h"


class Field {

private:
    bool **old_field;
public:
    bool **new_field;

    Field();
    ~Field();

    void reset();
    void set(short_t, short_t);
    void clear(short_t, short_t);
    void step();
    void back();
    void save(std::string);
    void load(std::string);

    short_t getAliveNighbours(short_t, short_t);
    bool isCell(short_t, short_t);

    void copyField();
};

#endif //LAB2_LIFE_FIELD_H
