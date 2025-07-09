#include "presenter/OutputScreenImpl.h"

std::string OutputScreenImpl::getMessage(OutputType type, const std::string& context) const {
    switch (type) {
        case  OutputType::WelcomeMessage:
        return "ATM System Started. Welcome! Please tap your card";
        case OutputType::CardReadSuccess:
            return "Card read successfully: " + context;
        case OutputType::CardReadFailure:
            return "Card read failed. Please try again.";
        case OutputType::PromptPinEntry:
            return "Please enter your PIN:";
        case OutputType::PromptUserConfirmation:
            return "Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N";
        case OutputType::PinEntryCanceled:
            return "PIN entry canceled.";
        case OutputType::InvalidConfirmation:
            return "Invalid option. Please select: Accept -> Y / Cancel -> N.";
        case OutputType::PinSuccess:
            return "PIN correct. Access granted.";
        case OutputType::SelectOperation:
            return "Please select an operation: 1. Check Balance, 2. Withdraw, 3. Deposit, 4. Exit";
        case OutputType::PinFailure:
            return "Incorrect PIN.";
        case OutputType::AccessDenied:
            return "Access denied. Please try again.";
        case OutputType::MaximumRetriesExceeded:
            return "Maximum retries exceeded. Please try again later.";
        case OutputType::PinNotSet:
            return "PIN not set yet.";
        case OutputType::PromptPinSetup:
            return "Please set your new 4-digit PIN:";
        case OutputType::PromptPinConfirmation:
            return "Please confirm your new PIN:";
        case OutputType::PinMismatch:
            return "PINs do not match. Please try again.";
        case OutputType::PinSetupSuccess:
            return "PIN setup successful. You may now proceed.";
        case OutputType::PinSetupFailure:
            return "PIN setup failed. Please contact support.";
            
        case OutputType::OperationMenu:
            return "Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit";
        case OutputType::PromptWithdrawInput:
            return "Enter amount to withdraw:";
        case OutputType::PromptDepositInput:
            return "Enter amount to deposit:";
        case OutputType::WithdrawSuccess:
            return "Withdraw successful. New Balance: $" + context;
        case OutputType::WithdrawFailure:
            return "Withdraw failed. Insufficient balance.";
        case OutputType::DepositSuccess:
            return "Deposit successful. New Balance: $" + context;
        case OutputType::DepositFailure:
            return "Deposit failed. Please try again.";
        case OutputType::DisplayBalance:
            return "Your current balance is: $" + context;
        case OutputType::InvalidSelection:
            return "Invalid operation choice. Please try again.";
        default:
            return "Unknown message.";
    }
}
