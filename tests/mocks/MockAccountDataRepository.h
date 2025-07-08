#pragma once

#include "data/AccountDataRepository.h"
#include <gmock/gmock.h>

class MockAccountDataRepository : public AccountDataRepository {
public:
    MOCK_METHOD(double, fetchBalance, (const std::string& acct), (const,override));
    MOCK_METHOD(void, updateBalance, (const std::string& acct, double newBal), (override));
};
