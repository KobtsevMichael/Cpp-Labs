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

bool** Field::getCells() {
    return new_field;
}

bool Field::isCell(short_t row, short_t col) {
    return row >= 0 && row < FIELD_W && col >= 0 && col < FIELD_H;
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
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            short_t alive_neighbours = getAliveNeighbours(i, j);
            if (alive_neighbours == 3) {
                old_field[i][j] = true;
            }
            else if (alive_neighbours != 2) {
                old_field[i][j] = false;
            }
            else {
                old_field[i][j] = new_field[i][j];
            }
        }
    }
    bool** tmp = old_field;
    old_field = new_field;
    new_field = tmp;
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

void Field::load(const string& filename) {
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

void Field::print() {

    console.setCursor(0, 0);

    string num_col_format = " {:<" + to_string(MAX_NUM_LEN) + "}";

    cout << fmt::format(num_col_format, "");
    for (short_t j=0; j < FIELD_W; ++j) {
        cout << string(" ", X_SEP) << ALPHABET[j];
    }
    cout << "\n";

    for (short_t i=0; i < FIELD_H; ++i) {
        for (short_t j=-1; j < FIELD_W; ++j) {

            if (j == -1) {
                cout << fmt::format(num_col_format, (short)i);
                continue;
            }

            cout << string(" ", X_SEP);

            if (new_field[j][i]) {
                fmt::print(fg(fmt::color::dark_khaki), ALIVE_CELL);
            } else {
                fmt::print(fg(fmt::color::white), DEAD_CELL);
            }
        }
        cout << "\n";
    }

    cout << std::string(MAX_NUM_LEN + 1 + FIELD_W*(X_SEP+1), ' ');
    cout << "\n";
}

short_t Field::getAliveNeighbours(short_t x, short_t y) {

    short_t count = 0;

    for (short_t i = x - 1; i <= x + 1; ++i) {
        for (short_t j = y - 1; j <= y + 1; ++j) {
            if (i == x && j == y) {
                continue;
            }
            if (i < 0 || j < 0 || i >= FIELD_W || j >= FIELD_H) {
                continue;
            }
            count += (new_field[i][j] ? 1 : 0);
        }
    }

    return count;
}
