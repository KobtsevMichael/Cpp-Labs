#include <iostream>
#include <fmt/core.h>

#include "utils/option_parser.h"
#include "utils/exceptions.h"
#include "variables/global.h"

#include "game/Game.h"


enum optionIndex {HELP, MAP_FILE, MAP_WIDTH, MAP_HEIGHT, COLLECTORS};

const option::Descriptor usage[] = {
    {HELP, 0, "", "help", option::Arg::None,
        "--help \tOptions list"},
    {MAP_FILE, 0, "m", "map", option::Arg::None,
        "--map, -m \tFor own map file"},
    {MAP_WIDTH, 0, "w", "width", option::Arg::None,
        "--width, -w \tMap width (10 <= n <= 1000)"},
    {MAP_HEIGHT, 0, "h", "height", option::Arg::None,
        "--height, -h \tMap height (10 <= n <= 1000)"},
    {COLLECTORS, 0, "r", "robots", option::Arg::None,
        "--collectors, -c \tSet collectors number (1 <= n <= 5)"},
    {0, 0, nullptr, nullptr, nullptr}
};

int toInt(const std::string& value, const int min, const int max) {
    try {
        int num = std::stoi(value);
        if (num < min || num > max) {
            throw descriptive_exception(
                fmt::format("n is not above {} and {}", min, max)
            );
        }
        return num;
    }
    catch (std::exception& e) {
        throw descriptive_exception(
            fmt::format("Incorrect argument - {}.", e.what())
        );
    }
}

void setVariables(option::Parser parse, option::Option *buffer) {
    for (int i = 0; i < parse.nonOptionsCount(); ++i) {
        std::string value = parse.nonOption(i);
        switch (buffer[i].index()) {
            case MAP_FILE: GLOBAL_MAP_FILE_PATH = value; break;
            case MAP_WIDTH: MAP_W = toInt(value, 10, 1000); break;
            case MAP_HEIGHT: MAP_H = toInt(value, 10, 1000); break;
            case COLLECTORS: COLLECTORS_N = toInt(value, 1, 5); break;
        }
    }
}

int main(int argc, char** argv) {

    argc -= (argc > 0);
    argv += (argc > 0);
    option::Stats  stats(usage, argc, argv);
    option::Option options[stats.options_max], buffer[stats.buffer_max];
    option::Parser parse(usage, argc, argv, options, buffer);

    if (parse.error()) {
        std::cout << "Parse command line error." << std::endl;
        return 1;
    }

    if (options[HELP]) {
        option::printUsage(std::cout, usage);
        return 0;
    }

    Game *game;

    try {
        setVariables(parse, buffer);
        game = new Game;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        delete game;
        return 1;
    }

    game->start();
    delete game;

    return 0;
}