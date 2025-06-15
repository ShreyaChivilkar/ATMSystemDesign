#include "KeypadImpl.h"

std::string KeypadImpl::getInput() {
    std::string pin;
    std::cin >> pin;
    return pin;
}
