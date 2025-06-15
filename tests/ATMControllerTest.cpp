#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ATMController.h"
#include "CardReader.h"
#include "PinService.h"
#include "Keypad.h"
#include "PinMessagePresenter.h"
#include "MessageServiceInterface.h"

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
};


class MockPinMessagePresenter : public PinMessagePresenter {
public:
    MOCK_METHOD(std::string, cardReadSuccess, (const std::string&), (override));
    MOCK_METHOD(std::string, cardReadFailure, (), (override));
    MOCK_METHOD(std::string, promptPinEntry, (), (override));
    MOCK_METHOD(std::string, pinSuccess, (), (override));
    MOCK_METHOD(std::string, pinFailure, (), (override));
    MOCK_METHOD(std::string, pinNotSet, (), (override));
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

    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenter, cardReadSuccess("ACC123")).WillOnce(Return("Card read successful: ACC123"));
    EXPECT_CALL(*messageService, showMessage("Card read successful: ACC123"));
    EXPECT_CALL(*pinService, isPinSetup("ACC123")).WillOnce(Return(true));
    EXPECT_CALL(*presenter, promptPinEntry()).WillOnce(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageService, showMessage("Please enter your PIN:"));
    EXPECT_CALL(*keypad, getInput()).WillOnce(Return("1234"));
    EXPECT_CALL(*pinService, validatePin("ACC123", "1234")).WillOnce(Return(true));
    EXPECT_CALL(*presenter, pinSuccess()).WillOnce(Return("PIN validation successful"));
    EXPECT_CALL(*messageService, showMessage("PIN validation successful"));

    controller.run();
}

TEST(ATMControllerTest, CardReadFails_ShowsFailureMessage) {
    auto reader = std::make_shared<MockCardReader>();
    auto pinService = std::make_shared<MockPinService>();
    auto keypad = std::make_shared<MockKeypad>();
    auto presenter = std::make_shared<MockPinMessagePresenter>();
    auto messageService = std::make_shared<MockMessageService>();

    ATMController controller(reader, pinService, keypad, presenter, messageService);

    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(false, "")));
    EXPECT_CALL(*presenter, cardReadFailure()).WillOnce(Return("Card read failed. Please try again."));
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

    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenter, cardReadSuccess("ACC123")).WillOnce(Return("Card read successfully: ACC123"));
    EXPECT_CALL(*messageService, showMessage("Card read successfully: ACC123"));
    EXPECT_CALL(*pinService, isPinSetup("ACC123")).WillOnce(Return(false));
    EXPECT_CALL(*presenter, pinNotSet()).WillOnce(Return("PIN not set yet."));
    EXPECT_CALL(*messageService, showMessage("PIN not set yet."));

    controller.run();
}

TEST(ATMControllerTest, WrongPin_ShowsFailure) {
    auto reader = std::make_shared<MockCardReader>();
    auto pinService = std::make_shared<MockPinService>();
    auto keypad = std::make_shared<MockKeypad>();
    auto presenter = std::make_shared<MockPinMessagePresenter>();
    auto messageService = std::make_shared<MockMessageService>();

    ATMController controller(reader, pinService, keypad, presenter, messageService);

    EXPECT_CALL(*messageService, showMessage("ATM System Started. Welcome! Please tap your card"));
    EXPECT_CALL(*reader, readCard()).WillOnce(Return(std::make_pair(true, "ACC123")));
    EXPECT_CALL(*presenter, cardReadSuccess("ACC123")).WillOnce(Return("Card read successfully: ACC123"));
    EXPECT_CALL(*messageService, showMessage("Card read successfully: ACC123"));
    EXPECT_CALL(*pinService, isPinSetup("ACC123")).WillOnce(Return(true));
    EXPECT_CALL(*presenter, promptPinEntry()).WillOnce(Return("Please enter your PIN:"));
    EXPECT_CALL(*messageService, showMessage("Please enter your PIN:"));
    EXPECT_CALL(*keypad, getInput()).WillOnce(Return("0000"));
    EXPECT_CALL(*pinService, validatePin("ACC123", "0000")).WillOnce(Return(false));
    EXPECT_CALL(*presenter, pinFailure()).WillOnce(Return("Incorrect PIN. Try again."));
    EXPECT_CALL(*messageService, showMessage("Incorrect PIN. Try again."));

    controller.run();
}
