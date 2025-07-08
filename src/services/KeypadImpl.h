#pragma once
#include "services/Keypad.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

class KeypadImpl : public Keypad {
public:
    explicit KeypadImpl(std::istream& input = std::cin) : in(input) {}

    std::string getInput() const override;
    std::string getConfirmation() const override;

private:
    std::istream& in;
};
