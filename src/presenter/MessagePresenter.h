#pragma once
#include <string>
#include "presenter/MessageType.h"

class MessagePresenter {
public:
    virtual ~MessagePresenter() = default;
    virtual std::string getMessage(MessageType type, const std::string& context = "") const = 0;
};
