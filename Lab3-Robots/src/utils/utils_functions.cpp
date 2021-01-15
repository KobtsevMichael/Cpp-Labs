#include "utils_functions.h"

#include <cctype>
#include <sstream>
#include <cmath>
#include <fmt/format.h>


// STRING FUNCTIONS

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

std::vector<std::string> splitStrByLength(std::string s, int len) {
    std::vector<std::string> stringWords = splitStr(s);
    std::vector<std::string> splittedStr;
    std::string r;
    for (auto& word : stringWords) {
        r += word + " ";
        if (r.length() + word.length() > len) {
            splittedStr.push_back(r);
            r = "";
        }
    }
    splittedStr.push_back(r);
    r.clear();
    return splittedStr;
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
            [] (unsigned char c) { return !std::isspace(c); }
        ).base(),
        s.end()
    );
    return s;
}

std::string& trimStr(std::string &s) {
    return ltrim(rtrim(s));
}

// STRING TO INT / RANDOM INTEGER

int toInt(const std::string& value, int min, int max) {
    try {
        int num = std::stoi(value);
        if (max && (num < min || num > max)) {
            throw error_exception(
                fmt::format("n is not above {} and {}", min, max)
            );
        }
        return num;
    }
    catch (std::exception& e) {
        throw error_exception(
            fmt::format("Incorrect argument - {}", e.what())
        );
    }
}

int randInt(int min, int max) {
    const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
    return static_cast<int>(rand() * fraction * (max - min) + min);
}

// CANTOR'S NUMERIC

int calculateCantorIndex(int r, int l) {
    return ((r + l)*(r + l) + r + l)/2 + r;
}

std::pair<int, int> calculateCantorPair(int n, bool sign) {

    double tmpSqrt = sqrt(8*n + 1);
    int tmp = static_cast<int>((tmpSqrt - 1.0)/2.0) *
              static_cast<int>((tmpSqrt + 1.0)/2.0) / 2;

    int l = n > tmp ? n - tmp : 0;
    int r = static_cast<int>((tmpSqrt - 1.0)/2.0) - l;

    return sign ? std::pair(l, r) : std::pair(-l, -r);
}

// SZUDZIK'S NUMERIC

int calculateSzudzikIndex(int x, int y) {
    int xx = x >= 0 ? x * 2 : x * -2 - 1;
    int yy = y >= 0 ? y * 2 : y * -2 - 1;
    return (xx >= yy) ? (xx * xx + xx + yy) : (yy * yy + xx);
}

std::pair<int, int> calculateSzudzikPair(int z) {
    int sqrtz = static_cast<int>(sqrt(z));
    int sqz = sqrtz * sqrtz;
    auto tmp = ((z - sqz) >= sqrtz)
        ? std::pair(sqrtz, z - sqz - sqrtz)
        : std::pair(z - sqz, sqrtz);
    int xx = tmp.first % 2 == 0 ? tmp.first / 2 : (tmp.first+1) / -2;
    int yy = tmp.second % 2 == 0 ? tmp.second / 2 : (tmp.second+1) / -2;
    return {xx, yy};
}