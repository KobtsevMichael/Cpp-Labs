#include "console.h"

int main() {

    // reset           – очистить поле и счетчик ходов
    // set XY          — установить организм в клетку
    // clear XY        – очистить клетку
    // step N          – прокрутить игру вперед на N шагов
    // back            – прокрутить игру назад на один шаг
    // save “filename” – сохранить поле в файл в текущей директории
    // load “filename” – загрузить поле из файла в текущей директории

    Console cmd;
    Field field;
    consoleMessage msg;

    do {
        cmd.updateField(&field);
        msg = cmd.readCommand(&field);
        cmd.current_status = msg;
    } while (msg != QUIT);

    return 0;
}