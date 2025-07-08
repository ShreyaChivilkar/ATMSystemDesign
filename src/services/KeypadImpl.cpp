#include "services/KeypadImpl.h"

std::string KeypadImpl::getInput() const {
    std::string pin;
    in >> pin;
    return pin;
}

std::string KeypadImpl::getConfirmation() const {
    std::string choice;
    in >> choice;
    std::transform(choice.begin(), choice.end(), choice.begin(), ::toupper);
    return choice;
}
