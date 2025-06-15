#pragma once
#include <string>

class MessageServiceInterface {
public:
    virtual void showMessage(const std::string& msg) = 0;
    virtual ~MessageServiceInterface() = default;
};
