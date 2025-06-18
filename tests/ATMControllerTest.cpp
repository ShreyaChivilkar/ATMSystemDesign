#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ATMController.h"
#include "CardReader.h"
#include "PinService.h"
#include "Keypad.h"
#include "PinMessagePresenter.h"
#include "MessageServiceInterface.h"
#include "PinMessageType.h"

using ::testing::Return;

// --------- Mock Classes ---------
class MockCardReader : public CardReader {
public:
    MOCK_METHOD((std::pair<bool, std::string>), readCard, (), (override));
};

class MockPinService : public PinService {
public:
    MOCK_METHOD(bool, isPinSetup, (const std::string&), (override));
    MOCK_METHOD(bool, validatePin, (const std::string&, const std::string&), (override));
};

class MockKeypad : public Keypad {
public:
    MOCK_METHOD(std::string, getInput, (), (override));
    MOCK_METHOD(std::string, getConfirmation, (), (override));  
};


class MockPinMessagePresenter : public PinMessagePresenter {
public:
    MOCK_METHOD(std::string, getMessage, (PinMessageType, const std::string&), (const, override));
};



class MockMessageService : public MessageServiceInterface {
public:
    MOCK_METHOD(void, showMessage, (const std::string&), (override));
};

// --------- Test Case ---------


TEST(ATMControllerTest, SuccessfulLoginFlow) {
    auto reader = std::make_shared<MockCardReader>();
    auto pinService = std::make_shared<MockPinService>();
    auto keypad = std::make_shared<MockKeypad>();
    auto presenter = std::make_shared<MockPinMessagePresenter>();
    auto messageService = std::make_shared<MockMessageService>();

    ATMController controller(reader, pinService, keypad, presenter, messageService);
    // 1. Welcome message
    EXPECT_CALL(*presenter, getMessage(PinMessageType::WelcomeMessage, ""))
        .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));

    // 2. Card read
    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::CardReadSuccess, "ACC123"))
        .WillOnce(Return("Card read successful: ACC123"));
    EXPECT_CALL(*messageService, showMessage("Card read successful: ACC123"));

    // 3. PIN setup check
    EXPECT_CALL(*pinService, isPinSetup("ACC123")).WillOnce(Return(true));

    // 4. PIN entry
    EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptPinEntry, ""))
        .WillOnce(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageService, showMessage("Please enter your PIN:"));
    EXPECT_CALL(*keypad, getInput()).WillOnce(Return("1234"));

    // 5. PIN confirmation
    EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptUerConfirmation, ""))
        .WillOnce(Return("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*messageService, showMessage("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*keypad, getConfirmation()).WillOnce(Return("Y"));

    // 6. PIN validation success
    EXPECT_CALL(*pinService, validatePin("ACC123", "1234")).WillOnce(Return(true));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::PinSuccess, ""))
        .WillOnce(Return("PIN validation successful"));
    EXPECT_CALL(*messageService, showMessage("PIN validation successful"));

    // 7. Show operation selection
    EXPECT_CALL(*presenter, getMessage(PinMessageType::SelectOperation, ""))
        .WillOnce(Return("Access granted. Welcome!"));
    EXPECT_CALL(*messageService, showMessage("Access granted. Welcome!"));

    controller.run();
}

TEST(ATMControllerTest, CardReadFails_ShowsFailureMessage) {
    auto reader = std::make_shared<MockCardReader>();
    auto pinService = std::make_shared<MockPinService>();
    auto keypad = std::make_shared<MockKeypad>();
    auto presenter = std::make_shared<MockPinMessagePresenter>();
    auto messageService = std::make_shared<MockMessageService>();

    ATMController controller(reader, pinService, keypad, presenter, messageService);

    EXPECT_CALL(*presenter, getMessage(PinMessageType::WelcomeMessage, "")).
        WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));

    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(false, "")));

    EXPECT_CALL(*presenter, getMessage(PinMessageType::CardReadFailure, ""))
        .WillOnce(Return("Card read failed. Please try again."));
    EXPECT_CALL(*messageService, showMessage("Card read failed. Please try again."));

    controller.run();
}


TEST(ATMControllerTest, PinNotSet_ShowsPinNotSetMessage) {
    auto reader = std::make_shared<MockCardReader>();
    auto pinService = std::make_shared<MockPinService>();
    auto keypad = std::make_shared<MockKeypad>();
    auto presenter = std::make_shared<MockPinMessagePresenter>();
    auto messageService = std::make_shared<MockMessageService>();

    ATMController controller(reader, pinService, keypad, presenter, messageService);
    EXPECT_CALL(*presenter, getMessage(PinMessageType::WelcomeMessage, ""))
        .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::CardReadSuccess, "ACC123"))
        .WillOnce(Return("Card read successfully: ACC123"));
    EXPECT_CALL(*messageService, showMessage("Card read successfully: ACC123"));
    EXPECT_CALL(*pinService, isPinSetup("ACC123")).WillOnce(Return(false));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::PinNotSet, ""))
        .WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageService, showMessage("PIN not set yet."));

    controller.run();
}

// TEST(ATMControllerTest, WrongPin_ShowsFailure) {
//     auto reader = std::make_shared<MockCardReader>();
//     auto pinService = std::make_shared<MockPinService>();
//     auto keypad = std::make_shared<MockKeypad>();
//     auto presenter = std::make_shared<MockPinMessagePresenter>();
//     auto messageService = std::make_shared<MockMessageService>();

//     ATMController controller(reader, pinService, keypad, presenter, messageService);

//     // 1. Welcome message
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::WelcomeMessage, "")).
//         WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
//     EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));

//     // 2. Card read
//     EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::CardReadSuccess, "ACC123"))
//         .WillOnce(Return("Card read successfully: ACC123"));
//     EXPECT_CALL(*messageService, showMessage("Card read successfully: ACC123"));

//     // 3. PIN is set
//     EXPECT_CALL(*pinService, isPinSetup("ACC123")).WillOnce(Return(true));
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptPinEntry, ""))
//         .WillOnce(Return("Please enter your PIN:"));
//     EXPECT_CALL(*messageService, showMessage("Please enter your PIN:"));

//     // 4. PIN entry and confirmation
//     EXPECT_CALL(*keypad, getInput()).WillOnce(Return("0000"));
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptUerConfirmation, ""))
//         .WillOnce(Return("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"));
//     EXPECT_CALL(*messageService, showMessage("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"));
//     EXPECT_CALL(*keypad, getConfirmation()).WillOnce(Return("Y"));
    
//     // 5. PIN validation fails
//     EXPECT_CALL(*pinService, validatePin("ACC123", "0000")).WillOnce(Return(false));
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::PinFailure, ""))
//         .WillOnce(Return("Incorrect PIN."));
//     EXPECT_CALL(*messageService, showMessage("Incorrect PIN."));

//     // 6. Access denied
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::AccessDenied, ""))
//     .WillOnce(Return("Access denied. Please try again."));
//     EXPECT_CALL(*messageService, showMessage("Access denied. Please try again."));

//      // 7. Show Prompt again (2nd attempt)
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptPinEntry, ""))
//         .WillOnce(Return("Please enter your PIN:"));
//     EXPECT_CALL(*messageService, showMessage("Please enter your PIN:"));
//     EXPECT_CALL(*keypad, getInput()).WillOnce(Return("0000"));
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptUerConfirmation, ""))
//         .WillOnce(Return("Press Y to accept or N to cancel:"));
//     EXPECT_CALL(*messageService, showMessage("Press Y to accept or N to cancel:"));
//     EXPECT_CALL(*keypad, getConfirmation()).WillOnce(Return("Y"));
//     EXPECT_CALL(*pinService, validatePin("ACC123", "0000")).WillOnce(Return(false));
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::PinFailure, ""))
//         .WillOnce(Return("Incorrect PIN. Try again."));
//     EXPECT_CALL(*messageService, showMessage("Incorrect PIN. Try again."));

//     // 8. MAX_RETRIES reached → show final message and exit
//     EXPECT_CALL(*presenter, getMessage(PinMessageType::MaximumRetriesExceeded, ""))
//         .WillOnce(Return("Maximum retries exceeded."));
//     EXPECT_CALL(*messageService, showMessage("Maximum retries exceeded."));

//     controller.run();
// }


TEST(ATMControllerTest, WrongPin_ShowsFailure) {
    auto reader = std::make_shared<MockCardReader>();
    auto pinService = std::make_shared<MockPinService>();
    auto keypad = std::make_shared<MockKeypad>();
    auto presenter = std::make_shared<MockPinMessagePresenter>();
    auto messageService = std::make_shared<MockMessageService>();

    ATMController controller(reader, pinService, keypad, presenter, messageService);

    // 1. Welcome message
    EXPECT_CALL(*presenter, getMessage(PinMessageType::WelcomeMessage, ""))
        .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));

    // 2. Card read
    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::CardReadSuccess, "ACC123"))
        .WillOnce(Return("Card read successfully: ACC123"));
    EXPECT_CALL(*messageService, showMessage("Card read successfully: ACC123"));

    // 3. PIN is set
    EXPECT_CALL(*pinService, isPinSetup("ACC123")).WillOnce(Return(true));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptPinEntry, ""))
        .Times(3) 
        .WillRepeatedly(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageService, showMessage("Please enter your PIN:")).Times(3);

    // 4. PIN entry & confirmation for first attempt
    EXPECT_CALL(*keypad, getInput()).Times(3).WillRepeatedly(Return("0000"));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::PromptUerConfirmation, ""))
        .Times(3)
        .WillRepeatedly(Return("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"));
    EXPECT_CALL(*messageService, showMessage("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"))
        .Times(3);
    EXPECT_CALL(*keypad, getConfirmation()).Times(3).WillRepeatedly(Return("Y"));

    // 5. Both attempts fail
    EXPECT_CALL(*pinService, validatePin("ACC123", "0000")).Times(3).WillRepeatedly(Return(false));
    EXPECT_CALL(*presenter, getMessage(PinMessageType::PinFailure, ""))
        .Times(3)
        .WillRepeatedly(Return("Incorrect PIN."));
    EXPECT_CALL(*messageService, showMessage("Incorrect PIN.")).Times(3);

    // 6. After each failure → AccessDenied shown
    EXPECT_CALL(*presenter, getMessage(PinMessageType::AccessDenied, ""))
        .Times(2)
        .WillRepeatedly(Return("Access denied. Please try again."));
    EXPECT_CALL(*messageService, showMessage("Access denied. Please try again.")).Times(2);

    // 7. Max retries exceeded on 2nd fail
    EXPECT_CALL(*presenter, getMessage(PinMessageType::MaximumRetriesExceeded, ""))
        .WillOnce(Return("Maximum retries exceeded. Please try again later."));
    EXPECT_CALL(*messageService, showMessage("Maximum retries exceeded. Please try again later."));

    controller.run();
}
