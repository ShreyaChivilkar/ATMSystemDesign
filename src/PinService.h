#pragma once
#include <string>

class PinService {
public:
    virtual ~PinService() = default;
    virtual bool isPinSetup(const std::string& accountNum) = 0;
    virtual bool validatePin(const std::string& accountNum, const std::string& pin) = 0;
};
