#include "PinServiceImpl.h"

PinServiceImpl::PinServiceImpl(const PinDataRepository* repository)
    : repository_(repository) {}

bool PinServiceImpl::isPinSetup(const std::string& accountNum) {
    return repository_->hasPin(accountNum);
}

bool PinServiceImpl::validatePin(const std::string& accountNum, const std::string& pin) {
    return repository_->getPin(accountNum) == pin;
}
