#ifndef LAB3_ROBOTS_UTILS_FUNCTIONS_H
#define LAB3_ROBOTS_UTILS_FUNCTIONS_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

template <typename T>
bool isInArray(std::vector<T> v, T value) {
    return std::find(v.begin(), v.end(), value) != v.end();
}

template <typename T>
int getElementIndex(std::vector<T> v, T value) {
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == value) {
            return i;
        }
    }
    return -1;
}

template <typename T, typename U>
std::pair<T,U> operator+ (const std::pair<T, U>& l, const std::pair<T, U>& r) {
    return {l.first + r.first, l.second + r.second};
}

template <typename T, typename U>
std::pair<T,U> operator- (const std::pair<T, U>& l, const std::pair<T, U>& r) {
    return {l.first - r.first, l.second - r.second};
}

std::vector<std::string> splitStr(std::string&, char=' ');
std::string& toLower(std::string& s);
std::string& trimStr(std::string&);

int randInt(int, int);

#endif //LAB3_ROBOTS_UTILS_FUNCTIONS_H
