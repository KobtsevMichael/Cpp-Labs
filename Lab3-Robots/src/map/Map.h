#ifndef LAB3_ROBOTS_MAP_H
#define LAB3_ROBOTS_MAP_H

#include <vector>

#include "../variables/global.h"
#include "../utils/convert_functions.h"
#include "../utils/utils_functions.h"
#include "../utils/exceptions.h."

class Map {
private:
    std::vector<cell_t> data;
    std::pair<int, int> size;
    bool sign;
    int researched;
    int szudzikMaxIdx;

    int toVectorIdx(std::pair<int, int>) const;
    void expand();

public:
    explicit Map(bool = false);
    Map(Map* other);
    ~Map();

    void setData(std::vector<cell_t>, int w, int h, int = 1);
    std::pair<int, int> getSize();

    int getResearch() const;
    int getSzudzikMaxIdx() const;

    cell_t getCell(std::pair<int, int>);
    void setCell(std::pair<int, int>, cell_t);

    bool isOnMap(std::pair<int, int>) const;

    static std::vector<std::pair<int, int>>
        getCellNeighbours(std::pair<int, int>);

    std::vector<std::pair<int, int>>
        getCellGoodNeighbours(std::pair<int, int>, std::pair<int, int> = {});

    bool hasGoodNeighbours(std::pair<int, int>);

    void readFromFile(const std::string&, int, int,
        std::vector<std::pair<int, int>>&,
        std::vector<std::pair<int, int>>&);
};

#endif //LAB3_ROBOTS_MAP_Hszud
