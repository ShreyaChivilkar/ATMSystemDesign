#include "PinMessagePresenterImpl.h"

std::string PinMessagePresenterImpl::getMessage(PinMessageType type, const std::string& context) {
    switch (type) {
        case PinMessageType::CardReadSuccess:
            return "Card read successfully: " + context;
        case PinMessageType::CardReadFailure:
            return "Card read failed. Please try again.";
        case PinMessageType::PromptPinEntry:
            return "Please enter your PIN:";
        case PinMessageType::PinSuccess:
            return "PIN correct. Access granted.";
        case PinMessageType::PinFailure:
            return "Incorrect PIN. Try again.";
        case PinMessageType::PinNotSet:
            return "PIN not set yet.";
        default:
            return "Unknown message.";
    }
}
