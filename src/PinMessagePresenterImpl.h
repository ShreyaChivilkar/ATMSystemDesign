#pragma once
#include "PinMessagePresenter.h"

class PinMessagePresenterImpl : public PinMessagePresenter {
public:
    std::string cardReadSuccess(const std::string& accountNum) override;
    std::string cardReadFailure() override;
    std::string promptPinEntry() override;
    std::string pinSuccess() override;
    std::string pinFailure() override;
    std::string pinNotSet() override;
};
