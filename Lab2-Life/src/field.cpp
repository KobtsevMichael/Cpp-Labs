#include "field.h"


using namespace std;

Field::Field() {
    old_field = new bool* [FIELD_W];
    for (short_t i=0; i < FIELD_W; ++i) {
        old_field[i] = new bool [FIELD_H];
        fill(old_field[i], old_field[i] + FIELD_H, false);
    }
    new_field = new bool* [FIELD_W];
    for (short_t i=0; i < FIELD_W; ++i) {
        new_field[i] = new bool [FIELD_H];
        fill(new_field[i], new_field[i] + FIELD_H, false);
    }
}

Field::~Field() {
    for (short_t i=0; i < FIELD_W; ++i) {
        delete[] old_field[i];
    }
    delete[] old_field;

    for (short_t i=0; i < FIELD_W; ++i) {
        delete[] new_field[i];
    }
    delete[] new_field;
}

bool** Field::getCurrentField() {
    return new_field;
}

void Field::reset() {
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            old_field[i][j] = new_field[i][j];
            new_field[i][j] = false;
        }
    }
}

void Field::set(short_t row, short_t col) {
    new_field[row][col] = true;
}

void Field::clear(short_t row, short_t col) {
    new_field[row][col] = false;
}

void Field::step() {
    copyField();
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            short_t alive_neighbours = getAliveNighbours(i, j);
            if (alive_neighbours == 3) {
                new_field[i][j] = true;
            }
            else if (alive_neighbours != 2) {
                new_field[i][j] = false;
            }
        }
    }
}

void Field::back() {
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            bool tmp = old_field[i][j];
            old_field[i][j] = new_field[i][j];
            new_field[i][j] = tmp;
        }
    }
}

void Field::save(string filename) {
    ofstream fout;
    fout.open(filename, fstream::trunc);
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            fout << (int)new_field[i][j];
        }
    }
    fout.close();
}

void Field::load(string filename) {
    ifstream fin;
    fin.open(filename);
    char symb;
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            fin >> symb;
            if (symb != '0' and symb != '1') {
                exception e;
                fin.close();
                throw e;
            }
            new_field[i][j] = (symb == '1');
        }
    }
    fin.close();
}

short_t Field::getAliveNighbours(short_t x, short_t y) {

    short_t count = 0;

    for (short_t i = x - 1; i <= x + 1; ++i) {
        for (short_t j = y - 1; j <= y + 1; ++j) {
            if (i == x && j == y) {
                continue;
            }
            if (i < 0 || j < 0 || i >= FIELD_W || j >= FIELD_H) {
                continue;
            }
            count += (old_field[i][j] ? 1 : 0);
        }
    }

    return count;
}

bool Field::isCell(short_t row, short_t col) {
    return row >= 0 && row < FIELD_W && col >= 0 && col < FIELD_H;
}

void Field::copyField() {
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            old_field[i][j] = new_field[i][j];
        }
    }
}