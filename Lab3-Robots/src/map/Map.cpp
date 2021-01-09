#include "Map.h"


Map::Map() : size({0, 0}) {}

void Map::expand() {
    std::vector<cell_t> tmpData(data);
    size = {size.first + EXP_K*2, size.second + EXP_K*2};
    data.resize(size.first*size.second);
    for (int i = 0, j = 0; i < data.size(); ++i) {
        if (i > size.first*EXP_K &&
            i < data.size() - size.first*EXP_K &&
            i % size.first >= EXP_K &&
            i % size.first < size.first - EXP_K
        ) {
            data[i] = tmpData[j++];
        }
        else {
            data[i] = UNKNOWN;
        }
    }
    tmpData.clear();
}

int Map::toVectorIdx(std::pair<int, int> coords) const {
    return coords.second*size.first + coords.first;
}

int Map::toVectorIdxSigned(std::pair<int, int> coords) const {
    return (coords.second + size.second/2)*size.first + \
        (coords.first + size.first/2);
}

const std::vector<cell_t>& Map::getData() {
    return data;
}

void Map::setData(std::vector<cell_t> newData, int w, int h, int emptyCells) {
    if (emptyCells > 0 && emptyCells != w*h) {
        newData.resize(emptyCells);
        std::fill(newData.begin(), newData.end(), UNKNOWN);
    }
    if (newData.empty() || newData.size() != w*h) {
        return;
    }
    data.clear();
    data = newData;
    size = {w, h};
}

std::pair<int, int> Map::getSize() {
    return size;
}

cell_t Map::getCell(std::pair<int, int> coords, bool sign) {
    return data[sign ? toVectorIdxSigned(coords) : toVectorIdx(coords)];
}

void Map::setCell(std::pair<int, int> coords, cell_t value, bool sign) {
    if (abs(coords.first) > size.first/2 || abs(coords.second) > size.second/2) {
        expand();
    }
    data[sign ? toVectorIdxSigned(coords) : toVectorIdx(coords)] = value;
}

void Map::readFromFile(const std::string& file_path)  {
    std::ifstream map_file(file_path);
    if (!map_file) {
        throw descriptive_exception("Can't find map file.");
    }
    char cellCh;
    for (int j = 0; j < MAP_H; ++j) {
        for (int i = 0; i < MAP_W; ++i) {
            map_file >> cellCh;
            cell_t cellT = toCellType(cellCh);
            if (cellT == NONE_CELL) {
                throw descriptive_exception("Unknown symbol.");
            }
            if (cellT == ROBOT) {
                throw descriptive_exception("You can't set robot position.");
            }
            data.push_back(cellT);
        }
    }
    size = {MAP_W, MAP_H};
}
