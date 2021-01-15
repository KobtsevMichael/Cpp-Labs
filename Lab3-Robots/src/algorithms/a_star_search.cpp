#include "a_star_search.h"

#include <fmt/ranges.h>

struct Node {
    Node* parent;
    std::pair<int, int> coords;
    int g;
    int h;
};

int heuristic(std::pair<int, int> p1, std::pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

Node* findNodeInList(std::vector<Node*> list, std::pair<int, int> coords) {
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
    std::vector<Node*> open, closed;

    Node* startNode = new Node {nullptr, start, 0, 0};
    open.push_back(startNode);

    Node* current;

    while (!open.empty()) {

        auto currentIt = open.begin();
        current = *currentIt;

        for (auto it = open.begin(); it != open.end(); ++it) {
            auto node = *it;
            if (node->g + node->h < current->g + current->h || (
                node->g + node->h == current->g + current->h &&
                node->h < current->h)
            ) {
                current = node;
                currentIt = it;
            }
        }

        open.erase(currentIt);
        closed.push_back(current);

        if (current->coords == dest) {
            break;
        }

        auto neighbours = map->getCellGoodNeighbours(current->coords, dest);
        for (auto& neighbourCoords : neighbours) {

            if (findNodeInList(closed, neighbourCoords) != nullptr || (
                isRobot != nullptr && isRobot(neighbourCoords))
            ) {
                continue;
            }

            Node* successor = findNodeInList(open, neighbourCoords);
            if (successor == nullptr) {
                successor = new Node {
                    current,
                    neighbourCoords,
                    current->g + 1,
                    heuristic(neighbourCoords, dest)
                };
                open.push_back(successor);
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