#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/variables.h"
#include "../src/console.h"

using testing::Eq;
class CommandsTest: public testing::Test {};


TEST_F(CommandsTest, reset) {
    Field field;
    Console console;

    consoleMessage m = console.readCommand(&field, "reset");

    ASSERT_EQ(m, SUCCESS) << "reset -- MSG ERROR";

    bool** cells = field.getCurrentField();
    for (short_t i=0; i < FIELD_W; ++i) {
        for (short_t j=0; j < FIELD_H; ++j) {
            EXPECT_FALSE(cells[i][j]) << "reset -- DATA ERROR";
        }
    }
}

TEST_F(CommandsTest, set) {
    Field field;
    Console console;

    consoleMessage m1 = console.readCommand(&field, "set 2i2");
    consoleMessage m2 = console.readCommand(&field, "set i22");
    consoleMessage m3 = console.readCommand(&field, "set ");
    consoleMessage m4 = console.readCommand(&field, "set 2 2");

    ASSERT_EQ(m1, INVALID_ARGUMENT) << "set 2i2 -- ERROR";
    ASSERT_EQ(m2, INVALID_ARGUMENT) << "set i22 -- ERROR";
    ASSERT_EQ(m3, INVALID_ARGS_NUMBER) << "set _ -- ERROR";
    ASSERT_EQ(m4, INVALID_ARGS_NUMBER) << "set 2 2 -- ERROR";

    console.readCommand(&field, "set a8");
    bool** cells = field.getCurrentField();
    EXPECT_TRUE(cells[0][8]) << "set a8 -- ERROR";
}

TEST_F(CommandsTest, clear) {
    Field field;
    Console console;

    consoleMessage m1 = console.readCommand(&field, "clear 44");
    consoleMessage m2 = console.readCommand(&field, "clear j44");
    consoleMessage m3 = console.readCommand(&field, "clear ");
    consoleMessage m4 = console.readCommand(&field, "clear 4 4");

    ASSERT_EQ(m1, INVALID_ARGUMENT) << "clear 44 -- ERROR";
    ASSERT_EQ(m2, INVALID_ARGUMENT) << "clear j44 -- ERROR";
    ASSERT_EQ(m3, INVALID_ARGS_NUMBER) << "clear _ -- ERROR";
    ASSERT_EQ(m4, INVALID_ARGS_NUMBER) << "clear 4 4 -- ERROR";
}

TEST_F(CommandsTest, step) {
    Field field;
    Console console;

    consoleMessage m1 = console.readCommand(&field, "step");
    consoleMessage m2 = console.readCommand(&field, "step 3");

    ASSERT_EQ(m1, SUCCESS) << "step -- ERROR";
    ASSERT_EQ(m2, SUCCESS) << "step 3 -- ERROR";
}

TEST_F(CommandsTest, save_load) {
    Field field;
    Console console;

    console.readCommand(&field, "set b4");
    consoleMessage m1 = console.readCommand(&field, "save new.txt");
    console.readCommand(&field, "reset");
    consoleMessage m2 = console.readCommand(&field, "load new.txt");

    ASSERT_EQ(m1, SUCCESS) << "save new.txt -- MSG ERROR";
    ASSERT_EQ(m2, SUCCESS) << "load new.txt -- MSG ERROR";
    
    bool** cells = field.getCurrentField();
    EXPECT_TRUE(cells[1][4]) << "save/load -- DATA ERROR";
}