#include <gtest/gtest.h>
#include "services/KeypadImpl.h"
#include <sstream>

TEST(tKeypadImpl, GetInput_ReturnsCorrectString) {
    std::istringstream simulatedInput("1234");
    KeypadImpl keypad(simulatedInput);
    EXPECT_EQ(keypad.getInput(), "1234");
}

TEST(tKeypadImpl, GetConfirmation_UppercasesInput) {
    std::istringstream simulatedInput("y");
    KeypadImpl keypad(simulatedInput);
    EXPECT_EQ(keypad.getConfirmation(), "Y");
}

TEST(tKeypadImpl, GetConfirmation_MultipleCallsSequentially) {
    std::istringstream simulatedInput("n Y n");
    KeypadImpl keypad(simulatedInput);

    EXPECT_EQ(keypad.getConfirmation(), "N");
    EXPECT_EQ(keypad.getConfirmation(), "Y");
    EXPECT_EQ(keypad.getConfirmation(), "N");
}
