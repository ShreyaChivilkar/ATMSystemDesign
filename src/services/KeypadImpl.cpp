#include "services/KeypadImpl.h"

std::string KeypadImpl::getInput() const{
    std::string pin;
    std::cin >> pin;
    return pin;
}

std::string KeypadImpl::getConfirmation() const{
    std::string choice;
    std::cin >> choice;
    std::transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
    return choice;
}