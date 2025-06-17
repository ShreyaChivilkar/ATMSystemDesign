#pragma once
#include <string>

class Keypad {
public:
    virtual ~Keypad() = default;
    virtual std::string getInput() = 0;
    virtual std::string getConfirmation() = 0;
};
