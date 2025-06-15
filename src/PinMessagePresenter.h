#pragma once
#include <string>

class PinMessagePresenter {
public:
    virtual ~PinMessagePresenter() = default;

    virtual std::string cardReadSuccess(const std::string& accountNum) = 0;
    virtual std::string cardReadFailure() = 0;
    virtual std::string promptPinEntry() = 0;
    virtual std::string pinSuccess() = 0;
    virtual std::string pinFailure() = 0;
    virtual std::string pinNotSet() = 0;
};

