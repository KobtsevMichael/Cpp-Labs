#ifndef LAB3_ROBOTS_A_STAR_SEARCH_H
#define LAB3_ROBOTS_A_STAR_SEARCH_H

#include <functional>
#include <vector>
#include <cmath>

#include "../variables/global.h"
#include "../utils/utils_functions.h"

#include "../map/Map.h"

std::vector<direction_t> aStarSearch(
    Map*,
    std::pair<int, int>,
    std::pair<int, int>,
    std::function<bool(std::pair<int, int>)> = nullptr
);

#endif //LAB3_ROBOTS_A_STAR_SEARCH_H
