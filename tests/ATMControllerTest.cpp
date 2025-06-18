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
    MOCK_METHOD(std::string, getInput, (), (const, override));
    MOCK_METHOD(std::string, getConfirmation, (), (const, override));  
};


class MockPinMessagePresenter : public PinMessagePresenter {
public:
    MOCK_METHOD(std::string, getMessage, (PinMessageType, const std::string&), (const, override));
};



class MockMessageService : public MessageServiceInterface {
public:
    MOCK_METHOD(void, showMessage, (const std::string&), (const, override));
};

// --------- Test Case ---------


TEST(ATMControllerTest, SuccessfulLoginFlow) {
    auto reader = std::make_unique<MockCardReader>();
    auto* readerPtr = reader.get();

    auto pinService = std::make_unique<MockPinService>();
    auto* pinServicePtr = pinService.get();

    auto keypad = std::make_unique<MockKeypad>();
    auto* keypadPtr = keypad.get();

    auto presenter = std::make_unique<MockPinMessagePresenter>();
    auto* presenterPtr = presenter.get();

    auto messageService = std::make_unique<MockMessageService>();
    auto* messageServicePtr = messageService.get();

    ATMController controller(
        std::move(reader),
        std::move(pinService),
        std::move(keypad),
        std::move(presenter),
        std::move(messageService)
    );

    // 1. Welcome message
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::WelcomeMessage, ""))
        .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageServicePtr, showMessage("ATM System Started. Welcome! Please tap your card"));

    // 2. Card read
    EXPECT_CALL(*readerPtr, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::CardReadSuccess, "ACC123"))
        .WillOnce(Return("Card read successful: ACC123"));
    EXPECT_CALL(*messageServicePtr, showMessage("Card read successful: ACC123"));

    // 3. PIN setup check
    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123")).WillOnce(Return(true));

    // 4. PIN entry
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::PromptPinEntry, ""))
        .WillOnce(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please enter your PIN:"));
    EXPECT_CALL(*keypadPtr, getInput()).WillOnce(Return("1234"));

    // 5. PIN confirmation
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::PromptUerConfirmation, ""))
        .WillOnce(Return("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Press Y to accept or N to cancel:"));
    EXPECT_CALL(*keypadPtr, getConfirmation()).WillOnce(Return("Y"));

    // 6. PIN validation success
    EXPECT_CALL(*pinServicePtr, validatePin("ACC123", "1234")).WillOnce(Return(true));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::PinSuccess, ""))
        .WillOnce(Return("PIN validation successful"));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN validation successful"));

    // 7. Show operation selection
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::SelectOperation, ""))
        .WillOnce(Return("Access granted. Welcome!"));
    EXPECT_CALL(*messageServicePtr, showMessage("Access granted. Welcome!"));

    controller.run();
}


// TEST(ATMControllerTest, CardReadFails_ShowsFailureMessage) {
//     auto reader = std::make_shared<MockCardReader>();
//     auto pinService = std::make_shared<MockPinService>();
//     auto keypad = std::make_shared<MockKeypad>();
//     auto presenter = std::make_shared<MockPinMessagePresenter>();
//     auto messageService = std::make_shared<MockMessageService>();

//     ATMController controller(reader, pinService, keypad, presenter, messageService);

//     EXPECT_CALL(*presenter, getMessage(PinMessageType::WelcomeMessage, "")).
//         WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
//     EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));

//     EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(false, "")));

//     EXPECT_CALL(*presenter, getMessage(PinMessageType::CardReadFailure, ""))
//         .WillOnce(Return("Card read failed. Please try again."));
//     EXPECT_CALL(*messageService, showMessage("Card read failed. Please try again."));

//     controller.run();
// }

TEST(ATMControllerTest, CardReadFails_ShowsFailureMessage) {
    // Step 1: Create unique_ptrs and extract raw pointers
    auto reader = std::make_unique<MockCardReader>();
    auto* readerPtr = reader.get();

    auto pinService = std::make_unique<MockPinService>();
    auto* pinServicePtr = pinService.get();

    auto keypad = std::make_unique<MockKeypad>();
    auto* keypadPtr = keypad.get();

    auto presenter = std::make_unique<MockPinMessagePresenter>();
    auto* presenterPtr = presenter.get();

    auto messageService = std::make_unique<MockMessageService>();
    auto* messageServicePtr = messageService.get();

    // Step 2: Construct the controller by moving unique_ptrs
    ATMController controller(
        std::move(reader),
        std::move(pinService),
        std::move(keypad),
        std::move(presenter),
        std::move(messageService)
    );

    // Step 3: Set up mock expectations
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::WelcomeMessage, ""))
        .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageServicePtr, showMessage("ATM System Started. Welcome! Please tap your card"));

    EXPECT_CALL(*readerPtr, readCard()).WillOnce(Return(std::make_pair(false, "")));

    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::CardReadFailure, ""))
        .WillOnce(Return("Card read failed. Please try again."));
    EXPECT_CALL(*messageServicePtr, showMessage("Card read failed. Please try again."));

    // Step 4: Run the controller
    controller.run();
}


TEST(ATMControllerTest, PinNotSet_ShowsPinNotSetMessage) {
    auto reader = std::make_unique<MockCardReader>();
    auto* readerPtr = reader.get();

    auto pinService = std::make_unique<MockPinService>();
    auto* pinServicePtr = pinService.get();

    auto keypad = std::make_unique<MockKeypad>();
    auto* keypadPtr = keypad.get();

    auto presenter = std::make_unique<MockPinMessagePresenter>();
    auto* presenterPtr = presenter.get();

    auto messageService = std::make_unique<MockMessageService>();
    auto* messageServicePtr = messageService.get();

    ATMController controller(
        std::move(reader),
        std::move(pinService),
        std::move(keypad),
        std::move(presenter),
        std::move(messageService)
    );

    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::WelcomeMessage, ""))
        .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageServicePtr, showMessage("ATM System Started. Welcome! Please tap your card"));

    EXPECT_CALL(*readerPtr, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::CardReadSuccess, "ACC123"))
        .WillOnce(Return("Card read successfully: ACC123"));
    EXPECT_CALL(*messageServicePtr, showMessage("Card read successfully: ACC123"));

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123")).WillOnce(Return(false));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::PinNotSet, ""))
        .WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageServicePtr, showMessage("PIN not set yet."));

    controller.run();
}


TEST(ATMControllerTest, WrongPin_ShowsFailure) {
    auto reader = std::make_unique<MockCardReader>();
    auto* readerPtr = reader.get();

    auto pinService = std::make_unique<MockPinService>();
    auto* pinServicePtr = pinService.get();

    auto keypad = std::make_unique<MockKeypad>();
    auto* keypadPtr = keypad.get();

    auto presenter = std::make_unique<MockPinMessagePresenter>();
    auto* presenterPtr = presenter.get();

    auto messageService = std::make_unique<MockMessageService>();
    auto* messageServicePtr = messageService.get();

    ATMController controller(
        std::move(reader),
        std::move(pinService),
        std::move(keypad),
        std::move(presenter),
        std::move(messageService)
    );

    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::WelcomeMessage, ""))
        .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*messageServicePtr, showMessage("ATM System Started. Welcome! Please tap your card"));

    EXPECT_CALL(*readerPtr, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::CardReadSuccess, "ACC123"))
        .WillOnce(Return("Card read successfully: ACC123"));
    EXPECT_CALL(*messageServicePtr, showMessage("Card read successfully: ACC123"));

    EXPECT_CALL(*pinServicePtr, isPinSetup("ACC123")).WillOnce(Return(true));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::PromptPinEntry, ""))
        .Times(3)
        .WillRepeatedly(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please enter your PIN:")).Times(3);

    EXPECT_CALL(*keypadPtr, getInput()).Times(3).WillRepeatedly(Return("0000"));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::PromptUerConfirmation, ""))
        .Times(3)
        .WillRepeatedly(Return("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"));
    EXPECT_CALL(*messageServicePtr, showMessage("Please confirm to proceed with the transaction: Accept -> Y / Cancel -> N"))
        .Times(3);
    EXPECT_CALL(*keypadPtr, getConfirmation()).Times(3).WillRepeatedly(Return("Y"));

    EXPECT_CALL(*pinServicePtr, validatePin("ACC123", "0000")).Times(3).WillRepeatedly(Return(false));
    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::PinFailure, ""))
        .Times(3)
        .WillRepeatedly(Return("Incorrect PIN."));
    EXPECT_CALL(*messageServicePtr, showMessage("Incorrect PIN.")).Times(3);

    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::AccessDenied, ""))
        .Times(2)
        .WillRepeatedly(Return("Access denied. Please try again."));
    EXPECT_CALL(*messageServicePtr, showMessage("Access denied. Please try again.")).Times(2);

    EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::MaximumRetriesExceeded, ""))
        .WillOnce(Return("Maximum retries exceeded. Please try again later."));
    EXPECT_CALL(*messageServicePtr, showMessage("Maximum retries exceeded. Please try again later."));

    controller.run();
}