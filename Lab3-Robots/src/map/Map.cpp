#include "Map.h"

#include <fstream>

// CONSTRUCTOR / COPY CONTRUCTOR / DESTRUCTOR

Map::Map(bool _sign) {
    size = {0, 0};
    sign = _sign;
    researched = 0;
    szudzikMaxIdx = 0;
}

Map::Map(Map* other) {
    for (auto cell : other->data) {
        this->data.push_back(cell);
    }
    this->size = other->size;
    this->sign = other->sign;
    this->researched = other->researched;
    this->szudzikMaxIdx = other->szudzikMaxIdx;
}

Map::~Map() {
    data.clear();
}

// GETTERS & SETTERS

void Map::setData(
    std::vector<cell_t> _data, int w, int h, int _researched)
{
    if (_data.size() != w*h) {
        return;
    }
    data.clear();
    data = _data;
    size = {w, h};
    researched = _researched;
    szudzikMaxIdx = size.first * size.second * 4;
}

std::pair<int, int> Map::getSize() {
    return size;
}

int Map::getResearch() const {
    return researched;
}

int Map::getSzudzikMaxIdx() const {
    return szudzikMaxIdx;
}

cell_t Map::getCell(std::pair<int, int> coords) {
    if (!isOnMap(coords)) {
        return NONE_CELL;
    }
    return data[toVectorIdx(coords)];
}

void Map::setCell(std::pair<int, int> coords, cell_t value) {
    if (!isOnMap(coords)) {
        expand();
    }
    int idx = toVectorIdx(coords);
    if (data[idx] == UNKNOWN && value != UNKNOWN && value != NONE_CELL) {
        researched++;
    }
    data[idx] = value;
}

bool Map::isOnMap(std::pair<int, int> coords) const {
    if (sign) {
        return abs(coords.first) <= size.first/2 &&
               abs(coords.second) <= size.second/2;
    }
    return coords.first >= 0 && coords.first < size.first &&
           coords.second >= 0 && coords.second < size.second;
}

std::vector<std::pair<int, int>> Map::getCellNeighbours(
    std::pair<int, int> coords)
{
    return {
        {coords.first, coords.second - 1},
        {coords.first, coords.second + 1},
        {coords.first + 1, coords.second},
        {coords.first - 1, coords.second}
    };
}

std::vector<std::pair<int, int>> Map::getCellGoodNeighbours(
    std::pair<int, int> coords, std::pair<int, int> ignore)
{
    std::vector<std::pair<int, int>> goodNeighbours;
    for (auto& neighbour : getCellNeighbours(coords)) {
        if (
            isInArray(GOOD_CELLS, getCell(neighbour)) ||
            neighbour == ignore
        ) {
            goodNeighbours.push_back(neighbour);
        }
    }
    return goodNeighbours;
}

bool Map::hasGoodNeighbours(std::pair<int, int> coords) {
    auto neighbours = getCellNeighbours(coords);
    return std::any_of(
        neighbours.begin(),
        neighbours.end(),
        [this] (std::pair<int, int> iCoords) {
            return isInArray(GOOD_CELLS, getCell(iCoords));
        }
    );
}

// GENERATING IDX / EXPANSION / READ FROM FILE

int Map::toVectorIdx(std::pair<int, int> coords) const {
    if (sign) {
        return (coords.second + size.second/2)*size.first + \
            (coords.first + size.first/2);
    }
    return coords.second*size.first + coords.first;
}

void Map::expand() {

    std::vector<cell_t> tmpData;
    int oldSize = size.first * size.second;

    size = {size.first + EXP_K*2, size.second + EXP_K*2};
    data.resize(size.first * size.second);
    szudzikMaxIdx = size.first * size.second * 4;

    for (int i = 0, j = 0; i < data.size(); ++i) {
        if (i < oldSize) {
            tmpData.push_back(data[i]);
        }
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

void Map::readFromFile(
    const std::string& file_path, int w, int h,
    std::vector<std::pair<int, int>>& applesList,
    std::vector<std::pair<int, int>>& bombsList
)  {
    std::ifstream map_file(file_path);
    if (!map_file) {
        throw error_exception("Can't find map file.");
    }
    char cellCh;
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            map_file >> cellCh;
            cell_t cellT = toCellType(cellCh);
            if (cellT == NONE_CELL) {
                throw error_exception("Unknown symbol.");
            }
            else if (cellT == ROBOT_SELF || cellT == SAPPER_SELF) {
                throw error_exception("You can't set robots position.");
            }
            else if (cellT == APPLE) {
                applesList.emplace_back(i, j);
            }
            else if (cellT == BOMB) {
                bombsList.emplace_back(i, j);
            }
            data.push_back(cellT);
        }
    }
    size = {w, h};
}

