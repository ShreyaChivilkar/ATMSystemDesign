#pragma once
#include "Keypad.h"
#include <iostream>
#include <string>

class KeypadImpl : public Keypad {
public:
    std::string getInput() override;
};
