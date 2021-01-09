#ifndef LAB3_ROBOTS_MAP_H
#define LAB3_ROBOTS_MAP_H

#include <iostream>
#include <fstream>
#include <vector>

#include <fmt/ranges.h>

#include "../variables/global.h"
#include "../utils/convert_functions.h"
#include "../utils/utils_functions.h"
#include "../utils/exceptions.h."

class Map {
private:
    std::vector<cell_t> data{};
    std::pair<int, int> size;
    int exp = 2;

    [[nodiscard]] int toVectorIdx(std::pair<int, int>) const;
    [[nodiscard]] int toVectorIdxSigned(std::pair<int, int>) const;
    void expand();

public:
    Map();

    const std::vector<cell_t>& getData();
    void setData(std::vector<cell_t>, int w, int h, int = 0);
    std::pair<int, int> getSize();
    cell_t getCell(std::pair<int, int>, bool = false);
    void setCell(std::pair<int, int>, cell_t, bool = false);

    void readFromFile(const std::string&);
};

#endif //LAB3_ROBOTS_MAP_H
