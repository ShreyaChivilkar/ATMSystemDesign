#pragma once
#include <string>
#include <unordered_map>

class AccountDataRepository {
public:
    double fetchBalance(const std::string& acct) const;
    void   updateBalance(const std::string& acct, double newBal);

    void populateDummyData();

private:
    std::unordered_map<std::string,double> balance_;
};
