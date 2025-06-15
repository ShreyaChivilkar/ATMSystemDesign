#include "PinMessagePresenterImpl.h"

std::string PinMessagePresenterImpl::cardReadSuccess(const std::string& accountNum) {
    return "Card read successfully: " + accountNum;
}

std::string PinMessagePresenterImpl::cardReadFailure() {
    return "Card read failed. Please try again.";
}

std::string PinMessagePresenterImpl::promptPinEntry() {
    return "Please enter your PIN:";
}

std::string PinMessagePresenterImpl::pinSuccess() {
    return "PIN correct. Access granted.";
}

std::string PinMessagePresenterImpl::pinFailure() {
    return "Incorrect PIN. Try again.";
}

std::string PinMessagePresenterImpl::pinNotSet() {
    return "PIN not set yet.";
}
