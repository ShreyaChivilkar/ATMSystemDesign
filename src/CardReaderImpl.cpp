#include "CardReaderImpl.h"
#include <iostream>

std::pair<bool, std::string> CardReaderImpl::readCard() {
    std::string input;
    std::cout << "Please enter account number: ";
    std::getline(std::cin, input);

    if (!input.empty()) {
        return {true, input};
    }
    return {false, ""};
}
