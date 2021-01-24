#include <fmt/format.h>
#include <argh.h>

#include "game/Game.h"


int main(int argc, char** argv) {

    std::string GLOBAL_MAP_FILE_PATH = "../data/map_test.txt";
    int GLOBAL_MAP_W = 100;
    int GLOBAL_MAP_H = 100;
    int COLLECTORS_N = 1;

    argh::parser cmdl(argc, argv, argh::parser::PREFER_PARAM_FOR_UNREG_OPTION);

    try {
        if (cmdl({"-m", "--map"})) {
            GLOBAL_MAP_FILE_PATH = cmdl({"-m", "--map"}).str();
        }
        if (cmdl({"-w", "--width"})) {
            GLOBAL_MAP_W = toInt(cmdl({"-w", "--width"}).str(), 5, 1000);
        }
        if (cmdl({"-h", "--height"})) {
            GLOBAL_MAP_H = toInt(cmdl({"-h", "--height"}).str(), 5, 1000);
        }
        if (cmdl({"-c", "--collector"})) {
            COLLECTORS_N = toInt(cmdl({"-c", "--collector"}).str(), 1, 5);
        }
        if (cmdl({"-a", "--algorithm"})) {
            SCAN_MODE_ALGORITHM = cmdl({"-a", "--algorithm"}).str();
        }
    }
    catch (error_exception& e) {
        fmt::print("Parse cmd line error ({}).\n", e.what());
        return 1;
    }

    Game* game;

    try {
        game = new Game(
            GLOBAL_MAP_FILE_PATH,
            GLOBAL_MAP_W,
            GLOBAL_MAP_H,
            COLLECTORS_N
        );
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