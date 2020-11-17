#include "console.h"


using namespace std;

Console::Console() {
    current_status = GREETING;
    alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
}

void Console::clear() {
    system("cls");
}

void Console::updateField(Field *field) {

    this->clear();

    string num_col_format = " {:<" + to_string(MAX_NUM_LEN) + "}";

    cout << fmt::format(num_col_format, "");
    for (short_t j=0; j < FIELD_W; ++j) {
        cout << string(" ", X_SEP) << alphabet[j];
    }
    cout << string("\n", Y_SEP+1);

    for (short_t i=0; i < FIELD_H; ++i) {
        for (short_t j=-1; j < FIELD_W; ++j) {

            if (j == -1) {
                cout << fmt::format(num_col_format, (short)i);
                continue;
            }

            cout << string(" ", X_SEP);

            if ((*field).new_field[j][i]) {
                fmt::print(fg(fmt::color::cornflower_blue), ALIVE_CELL);
            } else {
                fmt::print(fg(fmt::color::white), DEAD_CELL);
            }
        }
        cout << string("\n", Y_SEP+1);
    }
    cout << "\n";
}

consoleMessage Console::readCommand(Field *field, string command_str) {

    cout << " ";

    switch (current_status) {
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
            for (short_t i=0; i < n-1; ++i) {
                field->step();
                Sleep(SLEEP_TIME);
                updateField(field);
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
        if (alphabet.find(cmd_str[i]) == string::npos) {
            break;
        }
        row += cmd_str[i];
    }
    for (; i < cmd_str.length(); ++i) {
        col += cmd_str[i];
    }

    try {
        *row_int = alphabet.find(row);
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