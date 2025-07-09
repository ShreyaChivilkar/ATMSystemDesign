#pragma once
#include <string>
#include "presenter/OutputType.h"

class OutputScreen {
public:
    virtual ~OutputScreen() = default;
    virtual std::string getMessage(OutputType type, const std::string& context = "") const = 0;
};
