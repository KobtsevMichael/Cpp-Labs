#include "dijkstra.h"

struct NodeD {
    NodeD* parent;
    std::pair<int, int> coords;
    int dist;

    bool operator < (const NodeD& other) const {
        return coords < other.coords;
    }
};

NodeD* findNodeInList(std::set<NodeD*> list, std::pair<int, int> coords) {
    for (auto &node : list) {
        if (node->coords == coords) {
            return node;
        }
    }
    return nullptr;
}

std::vector<direction_t> dijkstraSearch(
    Map* map,
    std::pair<int, int> start,
    std::function<bool(std::pair<int, int>)> isTraversable)
{
    std::pair<int, int> mapSize = map->getSize();
    int maxIdx = calculateCantorIndex(mapSize.first+1, mapSize.second+1);

    std::set<NodeD*> openSet;
    openSet.insert(new NodeD {nullptr, start, 0});

    NodeD* current;

    for (int i = 0; i < maxIdx; ++i) {

        current = *openSet.begin();
        openSet.erase(openSet.begin());

        cell_t currentT = map->getCell(current->coords);
        if (currentT == UNKNOWN || currentT == NONE_CELL) {
            break;
        }

        auto neighbours = Map::getCellNeighbours(current->coords);
        for (auto& neighbourCoords : neighbours) {

            if (!isTraversable(neighbourCoords)) {
                continue;
            }

            NodeD* neighbour = findNodeInList(openSet, neighbourCoords);
            if (neighbour == nullptr) {
                neighbour = new NodeD {
                    current,
                    neighbourCoords,
                    current->dist + 1
                };
                openSet.insert(neighbour);
            }
            else if (current->dist + 1 < neighbour->dist) {
                neighbour->parent = current;
                neighbour->dist = current->dist + 1;
            }
        }
    }

    cell_t currentT = map->getCell(current->coords);
    if (currentT != UNKNOWN && currentT != NONE_CELL) {
        throw way_not_found_exception("All cells are scanned or surrounded.");
    }

    std::vector<direction_t> way;
    while (current->parent != nullptr) {
        auto dir = toDirection(
            (current->coords) - (current->parent->coords)
        );
        way.push_back(dir);
        current = current->parent;
    }

    return way;
}