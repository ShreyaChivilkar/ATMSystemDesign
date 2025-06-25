#include "data/AccountDataRepository.h"

double AccountDataRepository::fetchBalance(const std::string& acct) const {
    auto it = balance_.find(acct);
    return it == balance_.end() ? 0.0 : it->second;
}
void AccountDataRepository::updateBalance(const std::string& acct, double b) {
    balance_[acct] = b;
}

//we would have the code to connect with actual db here
void AccountDataRepository::populateDummyData() {
    balance_["ACC456"] = 1500.00;
    balance_["ACC123"] = 1250.75;
    balance_["ACC789"] = 2250.75;
    balance_["ACC101"] = 2520.75;
    balance_["ACC202"] = 2570.75;
}
