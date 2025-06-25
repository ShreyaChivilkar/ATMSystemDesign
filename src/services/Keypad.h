#pragma once
#include <string>

class Keypad {
public:
    virtual ~Keypad() = default;
    virtual std::string getInput() const = 0;
    virtual std::string getConfirmation() const = 0;
};
