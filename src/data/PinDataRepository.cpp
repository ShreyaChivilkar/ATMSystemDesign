#include "data/PinDataRepository.h"

void PinDataRepository::addAccount(const std::string& accountNum, const std::string& pin, bool isPinSet) {
    pinDatabase_[accountNum] = PinRecord{pin, isPinSet};
}

bool PinDataRepository::hasPin(const std::string& accountNum) const {
    auto it = pinDatabase_.find(accountNum);
    return it != pinDatabase_.end() && it->second.isPinSet;
}

std::string PinDataRepository::getPin(const std::string& accountNum) const {
    auto it = pinDatabase_.find(accountNum);
    if (it != pinDatabase_.end()) {
        return it->second.pin;
    }
    return "";
}

bool PinDataRepository::updatePin(const std::string& accountNum, const std::string& pin) {
    auto it = pinDatabase_.find(accountNum);
    if (it != pinDatabase_.end()) {
        it->second.pin = pin;
        it->second.isPinSet = true;
        return true;
    }
    return false;
}

//we would have the code to connect with actual db here 
void PinDataRepository::populateDummyData() {
    addAccount("ACC123", "", false);    
    addAccount("ACC456", "5678", true);
    addAccount("ACC789", "9012", true);
    addAccount("ACC101", "1111", true);
    addAccount("ACC202", "2222", true);
}
