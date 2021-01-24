#include <iostream>

#include "parser/Parser.h"


int main() {

    std::ifstream csvFile("../data/file3.csv");

    try {
        Parser<int, int, std::string, float> parser(csvFile);
        for (const auto& row : parser) {
            std::cout << row << std::endl;
        }
    }
    catch (simple_exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
