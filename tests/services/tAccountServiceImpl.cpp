// tests/services/tAccountServiceImpl.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "services/AccountServiceImpl.h"
#include "MockAccountDataRepository.h"

using ::testing::Return;
using ::testing::_;

class tAccountServiceImpl : public ::testing::Test {
protected:
    MockAccountDataRepository mockRepo;
    AccountServiceImpl service{&mockRepo};
};

TEST_F(tAccountServiceImpl, GetBalance_ReturnsExpectedValue) {
    EXPECT_CALL(mockRepo, fetchBalance("ACC123"))
        .WillOnce(Return(5000.0));

    double balance = service.getBalance("ACC123");
    EXPECT_DOUBLE_EQ(balance, 5000.0);
}

TEST_F(tAccountServiceImpl, Withdraw_Succeeds_WhenSufficientBalance) {
    EXPECT_CALL(mockRepo, fetchBalance("ACC123"))
        .WillOnce(Return(1500.0));
    EXPECT_CALL(mockRepo, updateBalance("ACC123", 1400.0));

    double newBal = 0;
    bool result = service.withdraw("ACC123", 100.0, newBal);

    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(newBal, 1400.0);
}

TEST_F(tAccountServiceImpl, Withdraw_Fails_WhenInsufficientBalance) {
    EXPECT_CALL(mockRepo, fetchBalance("ACC123"))
        .WillOnce(Return(1000.0));
    // No updateBalance call expected

    double newBal = 0;
    bool result = service.withdraw("ACC123", 980.0, newBal);

    EXPECT_FALSE(result);
}

TEST_F(tAccountServiceImpl, Deposit_Succeeds_WithPositiveAmount) {
    EXPECT_CALL(mockRepo, fetchBalance("ACC123"))
        .WillOnce(Return(1000.0));
    EXPECT_CALL(mockRepo, updateBalance("ACC123", 1300.0));

    double newBal = 0;
    bool result = service.deposit("ACC123", 300.0, newBal);

    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(newBal, 1300.0);
}

TEST_F(tAccountServiceImpl, Deposit_Fails_WithNonPositiveAmount) {
    // fetchBalance should not be called
    double newBal = 0;
    bool result = service.deposit("ACC123", -50.0, newBal);
    EXPECT_FALSE(result);
}
