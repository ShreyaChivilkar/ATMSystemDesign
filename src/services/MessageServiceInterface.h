#pragma once
#include <string>

class MessageServiceInterface {
public:
    virtual void showMessage(const std::string& msg) const = 0;
    virtual ~MessageServiceInterface() = default;
};
