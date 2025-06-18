#include "PinServiceImpl.h"

PinServiceImpl::PinServiceImpl(PinDataRepository* repository)
    : repository_(repository) {}

bool PinServiceImpl::isPinSetup(const std::string& accountNum) const {
    return repository_->hasPin(accountNum);
}

bool PinServiceImpl::validatePin(const std::string& accountNum, const std::string& pin) const {
    return repository_->getPin(accountNum) == pin;
}

bool PinServiceImpl::setPin(const std::string& accountNum, const std::string& newPin) {
    return repository_->updatePin(accountNum, newPin);
}
