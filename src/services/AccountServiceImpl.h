#pragma once
#include "AccountService.h"
#include "data/AccountDataRepository.h"
#include "constants/Constants.h"

class AccountServiceImpl : public AccountService {
public:
    explicit AccountServiceImpl(AccountDataRepository* repo);
    double getBalance(const std::string& acct) const override;
    bool   withdraw  (const std::string& acct, double amt, double& newBal) override;
    bool   deposit   (const std::string& acct, double amt, double& newBal) override;

private:
    AccountDataRepository* repo_;
};
