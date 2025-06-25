#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ATMControllerTestFixture.h"

using ::testing::Return;

TEST_F(ATMControllerTest, SuccessfulLoginFlow) {
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");
    
    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(true));

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::PromptPinEntry, ""))
        .WillOnce(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please enter your PIN:"));
    EXPECT_CALL(*keypadPtr, getInput()).WillOnce(Return("1234"));

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::PromptUserConfirmation, ""))
        .WillOnce(Return("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*keypadPtr, getConfirmation()).WillOnce(Return("Y"));

    EXPECT_CALL(*pinServicePtr, validatePin("ACC123", "1234"))
        .WillOnce(Return(true));

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::PinSuccess, ""))
        .WillOnce(Return("PIN validation successful"));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN validation successful"));

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::SelectOperation, ""))
        .WillOnce(Return("Access granted. Welcome!"));
    EXPECT_CALL(*messageServicePtr, showMessage("Access granted. Welcome!"));

    controller->run();
}

TEST_F(ATMControllerTest, CardReadFails_ShowsFailureMessage) {
    expectWelcomeMessage();
    expectCardRead(false);
    controller->run();
}

TEST_F(ATMControllerTest, PinNotSet_ShowsPinNotSetMessage) {
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(false));

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::PinNotSet, ""))
        .WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN not set yet."));

    controller->run();
}

TEST_F(ATMControllerTest, WrongPin_ShowsFailureAndRetry) {
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(true));

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::PromptPinEntry, ""))
        .Times(3).WillRepeatedly(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please enter your PIN:")).Times(3);

    EXPECT_CALL(*keypadPtr, getInput()).Times(3).WillRepeatedly(Return("0000"));
    EXPECT_CALL(*presenterPtr, getMessage(MessageType::PromptUserConfirmation, ""))
        .Times(3).WillRepeatedly(Return("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"))
        .Times(3);
    EXPECT_CALL(*keypadPtr, getConfirmation()).Times(3).WillRepeatedly(Return("Y"));

    EXPECT_CALL(*pinServicePtr, validatePin("ACC123", "0000"))
        .Times(3).WillRepeatedly(Return(false));

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::PinFailure, ""))
        .Times(3).WillRepeatedly(Return("Incorrect PIN."));
    EXPECT_CALL(*messageServicePtr, showMessage("Incorrect PIN.")).Times(3);

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::AccessDenied, ""))
        .Times(2).WillRepeatedly(Return("Access denied. Please try again."));
    EXPECT_CALL(*messageServicePtr, showMessage("Access denied. Please try again.")).Times(2);

    EXPECT_CALL(*presenterPtr, getMessage(MessageType::MaximumRetriesExceeded, ""))
        .WillOnce(Return("Maximum retries exceeded. Please try again later."));
    EXPECT_CALL(*messageServicePtr, showMessage("Maximum retries exceeded. Please try again later."));

    controller->run();
}
