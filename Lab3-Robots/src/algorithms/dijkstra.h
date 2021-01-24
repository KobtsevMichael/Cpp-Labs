#ifndef LAB3_ROBOTS_DIJKSTRA_H
#define LAB3_ROBOTS_DIJKSTRA_H

#include <functional>
#include <vector>
#include <set>

#include "../utils/utils_functions.h"
#include "../map/Map.h"

std::vector<direction_t> dijkstraSearch(
    Map*,
    std::pair<int, int>,
    std::function<bool(std::pair<int, int>)>);

#endif //LAB3_ROBOTS_DIJKSTRA_H
