#include "PinMessagePresenterImpl.h"

std::string PinMessagePresenterImpl::getMessage(PinMessageType type, const std::string& context) const {
    switch (type) {
        case  PinMessageType::WelcomeMessage:
        return "ATM System Started. Welcome! Please tap your card";
        case PinMessageType::CardReadSuccess:
            return "Card read successfully: " + context;
        case PinMessageType::CardReadFailure:
            return "Card read failed. Please try again.";
        case PinMessageType::PromptPinEntry:
            return "Please enter your PIN:";
        case PinMessageType::PromptUerConfirmation:
            return "Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N";
        case PinMessageType::PinEntryCanceled:
            return "PIN entry canceled.";
        case PinMessageType::InvalidConfirmation:
            return "Invalid option. Please select: Accept -> Y / Cancel -> N.";
        case PinMessageType::PinSuccess:
            return "PIN correct. Access granted.";
        case PinMessageType::SelectOperation:
            return "Please select an operation: 1. Check Balance, 2. Withdraw, 3. Deposit, 4. Exit";
        case PinMessageType::PinFailure:
            return "Incorrect PIN.";
        case PinMessageType::AccessDenied:
            return "Access denied. Please try again.";
        case PinMessageType::MaximumRetriesExceeded:
            return "Maximum retries exceeded. Please try again later.";
        case PinMessageType::PinNotSet:
            return "PIN not set yet.";
        case PinMessageType::PromptPinSetup:
            return "Please set your new 4-digit PIN:";
        case PinMessageType::PromptPinConfirmation:
            return "Please confirm your new PIN:";
        case PinMessageType::PinMismatch:
            return "PINs do not match. Please try again.";
        case PinMessageType::PinSetupSuccess:
            return "PIN setup successful. You may now proceed.";
        case PinMessageType::PinSetupFailure:
            return "PIN setup failed. Please contact support.";
        default:
            return "Unknown message.";
    }
}
