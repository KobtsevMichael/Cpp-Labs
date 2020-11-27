#include "console.h"


using namespace std;

Console::Console() {
    status = GREETING;
}

void Console::startApp() {
    Field field;
    do {
        field.print();
        status = readCommand(&field);
    } while (status != QUIT);
}

consoleMessage Console::readCommand(Field *field, string command_str) {

    cout << " ";

    switch (status) {
        case GREETING:
            fmt::print(fg(fmt::color::cadet_blue) | fmt::emphasis::bold,
                       "Waiting for your command");
            break;
        case SUCCESS:
            fmt::print(fg(fmt::color::sea_green) | fmt::emphasis::bold,
                       "Success!");
            break;
        case INVALID_COMMAND:
            fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                       "Invalid command. Please, try again");
            break;
        case INVALID_ARGS_NUMBER:
            fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                       "Invalid args number. Please, try again");
            break;
        case INVALID_ARGUMENT:
            fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                       "Invalid argument. Please, try again");
            break;
        case INVALID_FILE:
            fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold,
                       "Invalid file. Please, try again");
            break;
        case QUIT:
            break;
    }
    cout << "\n";

    while (command_str.empty()) {
        cout << " $ ";
        getline(cin, command_str);
    }
    
    vector<string> command = split(command_str, ' ');

    if (command[0] == "reset") {
        if (command.size() != 1) {
            return INVALID_ARGS_NUMBER;
        }
        field->reset();
    }
    else if (command[0] == "back") {
        if (command.size() != 1) {
            return INVALID_ARGS_NUMBER;
        }
        field->back();
    }
    else if (command[0] == "set") {
        if (command.size() != 2) {
            return INVALID_ARGS_NUMBER;
        }
        short_t row_int, col_int;
        try {
            readCoords(command[1], field, &row_int, &col_int);
            field->set(row_int, col_int);
        }
        catch (exception&) {
            return INVALID_ARGUMENT;
        }
    }
    else if (command[0] == "clear") {
        if (command.size() != 2) {
            return INVALID_ARGS_NUMBER;
        }
        short_t row_int, col_int;
        try {
            readCoords(command[1], field, &row_int, &col_int);
            field->clear(row_int, col_int);
        }
        catch (exception&) {
            return INVALID_ARGUMENT;
        }
    }
    else if (command[0] == "step") {
        if (command.size() > 2) {
            return INVALID_ARGS_NUMBER;
        }
        short_t n;
        try {
            n = command.size() == 1 ? 1 : stoi(command[1]);
            if (n < 0) {
                exception e;
                throw e;
            }
            for (short_t i=0; i < n-1; ++i) {
                field->step();
                Sleep(SLEEP_TIME);
                field->print();
            }
            field->step();
            Sleep(SLEEP_TIME);
        }
        catch (exception&) {
            return INVALID_ARGUMENT;
        }
    }
    else if (command[0] == "save") {
        if (command.size() != 2) {
            return INVALID_ARGS_NUMBER;
        }
        field->save(command[1]);
    }
    else if (command[0] == "load") {
        if (command.size() != 2) {
            return INVALID_ARGS_NUMBER;
        }
        try {
            field->load(command[1]);
        }
        catch (exception&) {
            return INVALID_FILE;
        }
    }
    else if (command[0] == "quit") {
        if (command.size() != 1) {
            return INVALID_ARGS_NUMBER;
        }
        cout << endl;
        return QUIT;
    }
    else {
        return INVALID_COMMAND;
    }

    return SUCCESS;
}

void Console::readCoords(
        string cmd_str,
        Field *field,
        short_t *row_int,
        short_t *col_int
) {
    string row = "", col = "";
    int_t i = 0;

    for (; i < cmd_str.length(); ++i) {
        if (ALPHABET.find(cmd_str[i]) == string::npos) {
            break;
        }
        row += cmd_str[i];
    }
    for (; i < cmd_str.length(); ++i) {
        col += cmd_str[i];
    }

    try {
        *row_int = ALPHABET.find(row);
        *col_int = stoi(col);
    }
    catch (exception& e) {
        throw e;
    }
    if (!(*field).isCell(*row_int, *col_int) ||
        row.empty() || col.empty())
    {
        exception e;
        throw e;
    }
}

vector<string> Console::split(const string& str, char delim) {
    vector<string> str_arr;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        str_arr.push_back(token);
    }
    return str_arr;
}