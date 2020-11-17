#include "console.h"
#include <fstream>

int main() {

    // reset            – Очистить поле и счетчик ходов
    // set XY           — Установить организм в клетку
    // clear XY         – Очистить клетку
    // step N           – Прокрутить игру вперед на N шагов
    // back             – Прокрутить игру назад на один шаг
    // save «filename»  – Сохранить поле в файл в текущей директории
    // load «filename»  – Загрузить поле из файла в текущей директории

    Console cmd;
    Field field;
    consoleMessage msg;
//
//    std::ofstream fout;
//    fout.open("files/out.txt");
//    fout << "BROOOOO";

    do {
        cmd.updateField(&field);
        msg = cmd.readCommand(&field);
        cmd.current_status = msg;
    } while (msg != QUIT);

    return 0;
}