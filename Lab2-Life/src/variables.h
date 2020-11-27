#ifndef LAB2_LIFE_VARIABLES_H
#define LAB2_LIFE_VARIABLES_H

#include <iostream>
#include <stdint.h>

typedef int8_t short_t;
typedef int32_t int_t;

const std::string ALPHABET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

const short_t FIELD_W = 40;
const short_t FIELD_H = 40;

const std::string ALIVE_CELL = "@";
const std::string DEAD_CELL = ".";

const short_t MAX_NUM_LEN = 2;
const short_t X_SEP = 1;

const int_t SLEEP_TIME = 100;

#endif //LAB2_LIFE_VARIABLES_H