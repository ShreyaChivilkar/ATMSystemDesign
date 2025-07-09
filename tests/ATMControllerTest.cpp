#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ATMControllerTestFixture.h"

using ::testing::Return;


TEST_F(ATMControllerTest, SuccessfulLoginFlow) {
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(true));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinEntry, ""))
        .WillOnce(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please enter your PIN:"));
    
    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptUserConfirmation, ""))
        .WillOnce(Return("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*keypadPtr, getConfirmation()).WillOnce(Return("Y"));

    EXPECT_CALL(*pinServicePtr, validatePin("ACC123", "1234"))
        .WillOnce(Return(true));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinSuccess, ""))
        .WillOnce(Return("PIN correct. Access granted"));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN correct. Access granted"));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::OperationMenu, ""))
        .WillOnce(Return("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));
    EXPECT_CALL(*messageServicePtr, showMessage("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));

    EXPECT_CALL(*keypadPtr, getInput())
    .Times(2)                      // exactly two calls
    .WillOnce(Return("1234"))      // 1st call → PIN
    .WillOnce(Return("0"));        // 2nd call → Exit in menu

    controller->run();
}


TEST_F(ATMControllerTest, CardReadFails_ShowsFailureMessage) {
    expectWelcomeMessage();
    expectCardRead(false);
    controller->run();
}

TEST_F(ATMControllerTest, PinNotSet_Mismatch_ShowsErrorAndExits) {
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(false));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinNotSet, ""))
        .WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN not set yet."));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinSetup, ""))
        .WillOnce(Return("Please set your new 4-digit PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please set your new 4-digit PIN:"));


    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinConfirmation, ""))
        .WillOnce(Return("Please confirm your new PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please confirm your new PIN:"));

    EXPECT_CALL(*keypadPtr, getInput())
    .Times(2)                      // exactly two calls
    .WillOnce(Return("1234"))      // 1st call → PIN
    .WillOnce(Return("0000"));        // 2nd call → Exit in menu

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinMismatch, ""))
        .WillOnce(Return("PINs do not match. Please try again."));
    EXPECT_CALL(*messageServicePtr, showMessage("PINs do not match. Please try again."));

    controller->run();
}

TEST_F(ATMControllerTest, PinNotSet_SuccessfulSetup_ThenExit) {
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(false));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinNotSet, ""))
        .WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN not set yet."));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinSetup, ""))
        .WillOnce(Return("Please set a new PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please set a new PIN:"));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinConfirmation, ""))
        .WillOnce(Return("Please confirm your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please confirm your PIN:"));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptUserConfirmation, ""))
        .WillOnce(Return("Confirm PIN setup?"));
    EXPECT_CALL(*messageServicePtr, showMessage("Confirm PIN setup?"));

    EXPECT_CALL(*keypadPtr, getConfirmation())
        .WillOnce(Return("Y"));

    EXPECT_CALL(*pinServicePtr, setPin("ACC123", "1234"))
        .WillOnce(Return(true));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinSetupSuccess, ""))
        .WillOnce(Return("PIN setup successful."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN setup successful."));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinSuccess, ""))
        .WillOnce(Return("PIN correct. Access granted"));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN correct. Access granted"));

    // AccessGranted → OperationState
    EXPECT_CALL(*presenterPtr, getMessage(OutputType::OperationMenu, ""))
        .WillOnce(Return("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));
    EXPECT_CALL(*messageServicePtr, showMessage("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));

    EXPECT_CALL(*keypadPtr, getInput())
        .Times(3)
        .WillOnce(Return("1234"))
        .WillOnce(Return("1234"))
        .WillOnce(Return("0"));

    controller->run();
}

TEST_F(ATMControllerTest, PinNotSet_CancelThenMismatch) {
    {
    ::testing::InSequence seq;
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(false));

    // First PIN setup
    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinNotSet, ""))
        .WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN not set yet."));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinSetup, ""))
        .WillOnce(Return("Please set a new PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please set a new PIN:"));

    EXPECT_CALL(*keypadPtr, getInput()).WillOnce(Return("1234")); // 1st

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinConfirmation, ""))
        .WillOnce(Return("Please confirm your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please confirm your PIN:"));

    EXPECT_CALL(*keypadPtr, getInput()).WillOnce(Return("1234")); // 2nd

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptUserConfirmation, ""))
        .WillOnce(Return("Confirm PIN setup?"));
    EXPECT_CALL(*messageServicePtr, showMessage("Confirm PIN setup?"));

    EXPECT_CALL(*keypadPtr, getConfirmation()).WillOnce(Return("N"));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinEntryCanceled, ""))
        .WillOnce(Return("PIN entry canceled."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN entry canceled."));

    // Loop restarts (NoPinSetState again),simulate mismatch
    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinNotSet, ""))
        .WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN not set yet."));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinSetup, ""))
        .WillOnce(Return("Please set a new PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please set a new PIN:"));

    EXPECT_CALL(*keypadPtr, getInput()).WillOnce(Return("4323")); // 3rd

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinConfirmation, ""))
        .WillOnce(Return("Please confirm your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please confirm your PIN:"));
    EXPECT_CALL(*keypadPtr, getInput()).WillOnce(Return("4321")); // 4th

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinMismatch, ""))
        .WillOnce(Return("PINs do not match. Please try again."));
    EXPECT_CALL(*messageServicePtr, showMessage("PINs do not match. Please try again."));

    controller->run();
    }
}


TEST_F(ATMControllerTest, WrongPin_ShowsFailureAndRetry) {
    expectWelcomeMessage();
    expectCardRead(true, "ACC123");

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123"))
        .WillOnce(Return(true));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptPinEntry, ""))
        .Times(3).WillRepeatedly(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please enter your PIN:")).Times(3);

    EXPECT_CALL(*keypadPtr, getInput()).Times(3).WillRepeatedly(Return("0000"));
    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PromptUserConfirmation, ""))
        .Times(3).WillRepeatedly(Return("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"))
        .Times(3);
    EXPECT_CALL(*keypadPtr, getConfirmation()).Times(3).WillRepeatedly(Return("Y"));

    EXPECT_CALL(*pinServicePtr, validatePin("ACC123", "0000"))
        .Times(3).WillRepeatedly(Return(false));

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::PinFailure, ""))
        .Times(3).WillRepeatedly(Return("Incorrect PIN."));
    EXPECT_CALL(*messageServicePtr, showMessage("Incorrect PIN.")).Times(3);

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::AccessDenied, ""))
        .Times(2).WillRepeatedly(Return("Access denied. Please try again."));
    EXPECT_CALL(*messageServicePtr, showMessage("Access denied. Please try again.")).Times(2);

    EXPECT_CALL(*presenterPtr, getMessage(OutputType::MaximumRetriesExceeded, ""))
        .WillOnce(Return("Maximum retries exceeded. Please try again later."));
    EXPECT_CALL(*messageServicePtr, showMessage("Maximum retries exceeded. Please try again later."));

    controller->run();
}


// TEST_F(ATMControllerTest, ViewBalance_ShowsCorrectBalanceAndExits) {
//     {
//         ::testing::InSequence seq;
//         // --- 1) successful login ---
//         expectSuccessfulLogin("ACC456", "5678");

//         // --- 2) first menu display ---
//         EXPECT_CALL(*presenterPtr,
//                     getMessage(OutputType::OperationMenu, ""))
//             .WillOnce(Return("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));
//         EXPECT_CALL(*messageServicePtr,
//                     showMessage("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));

//         // choose "1"  → View Balance
//         EXPECT_CALL(*keypadPtr, getInput())
//             .WillOnce(Return("1"));

//         // --- 3) AccountService interaction & balance message ---
//         EXPECT_CALL(*accountServicePtr, getBalance("ACC456"))
//             .WillOnce(Return(1500));

//         EXPECT_CALL(*presenterPtr,
//                     getMessage(OutputType::DisplayBalance, "2500.5"))
//             .WillOnce(Return("Your current balance is: $2500.5"));
//         EXPECT_CALL(*messageServicePtr,
//                     showMessage("Your current balance is: $2500.5"));

//         // --- 4) Menu shown again, user exits with "0" ---
//         EXPECT_CALL(*presenterPtr,
//                     getMessage(OutputType::OperationMenu, ""))
//             .WillOnce(Return("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));
//         EXPECT_CALL(*messageServicePtr,
//                     showMessage("Choose Operation: 1-View Balance, 2-Deposit, 3-Withdraw, 0-Exit"));

//         EXPECT_CALL(*keypadPtr, getInput())
//             .WillOnce(Return("0"));  // ExitOperation

//         controller->run();           // Full session runs
//     }
// }


