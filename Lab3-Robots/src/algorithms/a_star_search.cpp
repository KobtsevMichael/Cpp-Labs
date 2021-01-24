#include "a_star_search.h"

struct NodeA {
    NodeA* parent;
    std::pair<int, int> coords;
    int g;
    int h;
};

int heuristic(std::pair<int, int> p1, std::pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

NodeA* findNodeInList(std::set<NodeA*> list, std::pair<int, int> coords) {
    for (auto &node : list) {
        if (node->coords == coords) {
            return node;
        }
    }
    return nullptr;
}

std::vector<direction_t> aStarSearch(
    Map* map,
    std::pair<int, int> start,
    std::pair<int, int> dest,
    std::function<bool(std::pair<int, int>)> isRobot)
{
    std::set<NodeA*> openSet, closedSet;
    openSet.insert(new NodeA {nullptr, start, 0, 0});

    NodeA* current;

    while (!openSet.empty()) {

        current = *openSet.begin();

        openSet.erase(openSet.begin());
        closedSet.insert(current);

        if (current->coords == dest) {
            break;
        }

        auto neighbours = map->getCellGoodNeighbours(current->coords, dest);
        for (auto& neighbourCoords : neighbours) {

            if (findNodeInList(closedSet, neighbourCoords) != nullptr || (
                isRobot != nullptr && isRobot(neighbourCoords)))
            {
                continue;
            }

            NodeA* successor = findNodeInList(openSet, neighbourCoords);
            if (successor == nullptr) {
                successor = new NodeA {
                    current,
                    neighbourCoords,
                    current->g + 1,
                    heuristic(neighbourCoords, dest)
                };
                openSet.insert(successor);
            }
            else if (current->g + 1 < successor->g) {
                successor->parent = current;
                successor->g = current->g + 1;
            }
        }
    }

    if (current->coords != dest) {
        throw way_not_found_exception("Last is not equal to destination");
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