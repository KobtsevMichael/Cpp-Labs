#include "utils_functions.h"

#include <functional>
#include <cstdlib>

template<typename out>
void split(std::string &s, char delim, out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> splitStr(std::string &s, char delim) {
    std::vector<std::string> elements;
    split(s, delim, std::back_inserter(elements));
    return elements;
}

std::string& toLower(std::string& s) {
    std::transform(
        s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return tolower(c); }
    );
    return s;
}

std::string& ltrim(std::string &s) {
    s.erase(
        s.begin(),
        std::find_if(
            s.begin(),
            s.end(),
            [](unsigned char c) { return !std::isspace(c); }
        )
    );
    return s;
}

std::string& rtrim(std::string &s) {
    s.erase(
        std::find_if(
            s.rbegin(),
            s.rend(),
            [](unsigned char c) { return !std::isspace(c); }
        ).base(),
        s.end()
    );
    return s;
}

std::string& trimStr(std::string &s) {
    return ltrim(rtrim(s));
}

int randInt(int min, int max) {
    return (rand() % (max-min)) + min;
}
