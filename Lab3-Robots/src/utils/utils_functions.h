#ifndef LAB3_ROBOTS_UTILS_FUNCTIONS_H
#define LAB3_ROBOTS_UTILS_FUNCTIONS_H

#include <string>
#include <vector>
#include <algorithm>

#include "../utils/exceptions.h"


// VECTOR FIND FUNCTIONS

template <typename T>
bool isInArray(std::vector<T> v, T value) {
    return std::find(v.begin(), v.end(), value) != v.end();
}

// STD::PAIR OPERATORS OVERLOADING

template <typename T, typename U>
std::pair<T,U> operator+ (const std::pair<T, U>& l, const std::pair<T, U>& r) {
    return {l.first + r.first, l.second + r.second};
}

template <typename T, typename U>
std::pair<T,U> operator- (const std::pair<T, U>& l, const std::pair<T, U>& r) {
    return {l.first - r.first, l.second - r.second};
}

template <class T1, class T2>
bool empty(const std::pair<T1, T2> &p) {
    return p == std::pair<T1, T2>();
}

std::vector<std::string> splitStr(std::string&, char=' ');
std::vector<std::string> splitStrByLength(std::string, int);
std::string& toLower(std::string& s);
std::string& trimStr(std::string&);

int toInt(const std::string&, int = 0, int = 0);
int randInt(int, int);

int calculateCantorIndex(int, int);
std::pair<int, int> calculateCantorPair(int, bool);

int calculateSzudzikIndex(int, int);
std::pair<int, int> calculateSzudzikPair(int);

#endif //LAB3_ROBOTS_UTILS_FUNCTIONS_H
