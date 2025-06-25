#include "services/AccountServiceImpl.h"

AccountServiceImpl::AccountServiceImpl(AccountDataRepository* repo)
    : repo_(repo) {}

double AccountServiceImpl::getBalance(const std::string& acct) const {
    return repo_->fetchBalance(acct);
}

bool AccountServiceImpl::withdraw(const std::string& acct, double amt, double& newBal) {
    if (amt <= 0) return false;
    double cur = repo_->fetchBalance(acct);
    newBal = cur - amt;
    if (newBal < MINIMUM_BALANCE) return false;
    repo_->updateBalance(acct, newBal);
    return true;
}

bool AccountServiceImpl::deposit(const std::string& acct, double amt, double& newBal) {
    if (amt <= 0) return false;
    double cur = repo_->fetchBalance(acct);
    newBal = cur + amt;
    repo_->updateBalance(acct, newBal);
    return true;
}