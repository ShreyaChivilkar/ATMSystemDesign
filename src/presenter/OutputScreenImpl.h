#pragma once

#include "presenter/OutputScreen.h"
#include <string>

class OutputScreenImpl : public OutputScreen {  
public:
    std::string getMessage(OutputType type, const std::string& context = "") const override;
};
