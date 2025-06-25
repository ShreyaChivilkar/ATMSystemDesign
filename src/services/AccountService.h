#pragma once
#include <string>

class AccountService {
public:
    virtual ~AccountService() = default;

    virtual double getBalance(const std::string& acct) const = 0;
    virtual bool   withdraw  (const std::string& acct, double amt, double& newBal) = 0;
    virtual bool   deposit   (const std::string& acct, double amt, double& newBal) = 0;
};
