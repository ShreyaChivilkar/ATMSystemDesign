#pragma once
#include <string>
#include "PinMessageType.h"

class PinMessagePresenter {
public:
    virtual ~PinMessagePresenter() = default;
    virtual std::string getMessage(PinMessageType type, const std::string& context = "") = 0;
};
