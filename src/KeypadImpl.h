#pragma once
#include "Keypad.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

class KeypadImpl : public Keypad {
public:
    std::string getInput() const override;
    std::string getConfirmation() const override;
};

