#include <gtest/gtest.h>
#include "console.h"


int main(int argc, char **argv) {

    // reset            – Очистить поле и счетчик ходов
    // set XY           — Установить организм в клетку
    // clear XY         – Очистить клетку
    // step N           – Прокрутить игру вперед на N шагов
    // back             – Прокрутить игру назад на один шаг
    // save «filename»  – Сохранить поле в файл в текущей директории
    // load «filename»  – Загрузить поле из файла в текущей директории

    if (argc == 2 && !strcmp(argv[1], "-test")) {
        testing::InitGoogleTest();
        return RUN_ALL_TESTS();
    }

    Console console;
    Field field;
    consoleMessage msg;

    do {
        console.updateField(&field);
        msg = console.readCommand(&field);
        console.current_status = msg;
    } while (msg != QUIT);

    return 0;
}