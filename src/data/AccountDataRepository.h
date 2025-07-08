#pragma once
#include <string>
#include <unordered_map>

class AccountDataRepository {
public:
    virtual ~AccountDataRepository() = default; 
    virtual double fetchBalance(const std::string& acct) const;
    virtual void updateBalance(const std::string& acct, double newBal);

    void populateDummyData();

private:
    std::unordered_map<std::string, double> balance_;
};
