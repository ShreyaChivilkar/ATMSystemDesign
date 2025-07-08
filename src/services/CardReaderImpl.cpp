#include "services/CardReaderImpl.h"

std::pair<bool, std::string> CardReaderImpl::readCard() {
    std::string input;
    std::cout << "Please enter account number: ";
    std::getline(in, input);

    if (!input.empty()) {
        return {true, input};
    }
    return {false, ""};
}
