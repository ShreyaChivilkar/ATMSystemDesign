#include "presenter/MessagePresenterImpl.h"

std::string MessagePresenterImpl::getMessage(MessageType type, const std::string& context) const {
    switch (type) {
        case  MessageType::WelcomeMessage:
        return "ATM System Started. Welcome! Please tap your card";
        case MessageType::CardReadSuccess:
            return "Card read successfully: " + context;
        case MessageType::CardReadFailure:
            return "Card read failed. Please try again.";
        case MessageType::PromptPinEntry:
            return "Please enter your PIN:";
        case MessageType::PromptUserConfirmation:
            return "Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N";
        case MessageType::PinEntryCanceled:
            return "PIN entry canceled.";
        case MessageType::InvalidConfirmation:
            return "Invalid option. Please select: Accept -> Y / Cancel -> N.";
        case MessageType::PinSuccess:
            return "PIN correct. Access granted.";
        case MessageType::SelectOperation:
            return "Please select an operation: 1. Check Balance, 2. Withdraw, 3. Deposit, 4. Exit";
        case MessageType::PinFailure:
            return "Incorrect PIN.";
        case MessageType::AccessDenied:
            return "Access denied. Please try again.";
        case MessageType::MaximumRetriesExceeded:
            return "Maximum retries exceeded. Please try again later.";
        case MessageType::PinNotSet:
            return "PIN not set yet.";
        case MessageType::PromptPinSetup:
            return "Please set your new 4-digit PIN:";
        case MessageType::PromptPinConfirmation:
            return "Please confirm your new PIN:";
        case MessageType::PinMismatch:
            return "PINs do not match. Please try again.";
        case MessageType::PinSetupSuccess:
            return "PIN setup successful. You may now proceed.";
        case MessageType::PinSetupFailure:
            return "PIN setup failed. Please contact support.";
            
        case MessageType::OperationMenu:
            return "Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit";
        case MessageType::PromptWithdrawInput:
            return "Enter amount to withdraw:";
        case MessageType::PromptDepositInput:
            return "Enter amount to deposit:";
        case MessageType::WithdrawSuccess:
            return "Withdraw successful. New Balance: $" + context;
        case MessageType::WithdrawFailure:
            return "Withdraw failed. Insufficient balance.";
        case MessageType::DepositSuccess:
            return "Deposit successful. New Balance: $" + context;
        case MessageType::DepositFailure:
            return "Deposit failed. Please try again.";
        case MessageType::DisplayBalance:
            return "Your current balance is: $" + context;
        case MessageType::InvalidSelection:
            return "Invalid operation choice. Please try again.";
        default:
            return "Unknown message.";
    }
}
