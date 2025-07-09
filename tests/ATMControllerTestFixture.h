#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ATMController.h"
#include "services/CardReader.h"
#include "services/PinService.h"
#include "services/Keypad.h"
#include "presenter/OutputScreen.h"
#include "services/MessageServiceInterface.h"
#include "presenter/OutputType.h"
#include "services/AccountService.h"


using ::testing::Return;

// -------------------- Mock Classes --------------------
class MockCardReader : public CardReader {
public:
    MOCK_METHOD((std::pair<bool, std::string>), readCard, (), (override));
};

class MockPinService : public PinService {
public:
    MOCK_METHOD(bool, isPinSetup, (const std::string&), (const, override));
    MOCK_METHOD(bool, validatePin, (const std::string&, const std::string&), (const, override));
    MOCK_METHOD(bool, setPin, (const std::string&, const std::string&), (override));

};

class MockAccountService : public AccountService {
public:
    MOCK_METHOD(double, getBalance, (const std::string&), (const, override));
    MOCK_METHOD(bool, withdraw,
                (const std::string&, double, double&),      (override));

    MOCK_METHOD(bool, deposit,
                (const std::string&, double, double&),      (override));
};

class MockKeypad : public Keypad {
public:
    MOCK_METHOD(std::string, getInput, (), (const, override));
    MOCK_METHOD(std::string, getConfirmation, (), (const, override));
};

class MockOutputScreen : public OutputScreen {
public:
    MOCK_METHOD(std::string, getMessage, (OutputType, const std::string&), (const, override));
};

class MockMessageService : public MessageServiceInterface {
public:
    MOCK_METHOD(void, showMessage, (const std::string&), (const, override));
};

// -------------------- Test Fixture --------------------
class ATMControllerTest : public ::testing::Test {
protected:
    std::unique_ptr<MockCardReader> reader;
    std::unique_ptr<MockPinService> pinService;
    std::unique_ptr<MockKeypad> keypad;
    std::unique_ptr<MockOutputScreen> presenter;
    std::unique_ptr<MockMessageService> messageService;
    std::unique_ptr<MockAccountService> accountService;

    MockCardReader* readerPtr;
    MockPinService* pinServicePtr;
    MockKeypad* keypadPtr;
    MockOutputScreen* presenterPtr;
    MockMessageService* messageServicePtr;
    MockAccountService* accountServicePtr;

    std::unique_ptr<ATMController> controller;

    void SetUp() override {
        reader = std::make_unique<MockCardReader>();
        readerPtr = reader.get();

        pinService = std::make_unique<MockPinService>();
        pinServicePtr = pinService.get();

        keypad = std::make_unique<MockKeypad>();
        keypadPtr = keypad.get();

        presenter = std::make_unique<MockOutputScreen>();
        presenterPtr = presenter.get();

        messageService = std::make_unique<MockMessageService>();
        messageServicePtr = messageService.get();

        accountService = std::make_unique<MockAccountService>();
        accountServicePtr = accountService.get();

        controller = std::make_unique<ATMController>(
            std::move(reader),
            std::move(pinService),
            std::move(keypad),
            std::move(presenter),
            std::move(messageService),
            std::move(accountService)
        );
    }

    void expectWelcomeMessage() {
        EXPECT_CALL(*presenterPtr, getMessage(OutputType::WelcomeMessage, ""))
            .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
        EXPECT_CALL(*messageServicePtr, showMessage("ATM System Started. Welcome! Please tap your card"));
    }

    void expectCardRead(bool success, const std::string& accountNum = "") {
        EXPECT_CALL(*readerPtr, readCard()).WillOnce(Return(std::make_pair(success, accountNum)));

        if (success) {
            EXPECT_CALL(*presenterPtr, getMessage(OutputType::CardReadSuccess, accountNum))
                .WillOnce(Return("Card read successful: " + accountNum));
            EXPECT_CALL(*messageServicePtr, showMessage("Card read successful: " + accountNum));
        } else {
            EXPECT_CALL(*presenterPtr, getMessage(OutputType::CardReadFailure, ""))
                .WillOnce(Return("Card read failed. Please try again."));
            EXPECT_CALL(*messageServicePtr, showMessage("Card read failed. Please try again."));
        }
    }

    void expectSuccessfulLogin(const std::string& acct = "ACC456",
                           const std::string& pin  = "5678") {
        expectWelcomeMessage();
        expectCardRead(true, acct);

        EXPECT_CALL(*pinServicePtr, isPinSetup(acct))
            .WillOnce(Return(true));

        EXPECT_CALL(*presenterPtr,
                    getMessage(OutputType::PromptPinEntry, ""))
            .WillOnce(Return("Please enter your PIN:"));
        EXPECT_CALL(*messageServicePtr,
                    showMessage("Please enter your PIN:"));
        EXPECT_CALL(*keypadPtr, getInput())          // PIN entry
            .WillOnce(Return(pin));

        EXPECT_CALL(*presenterPtr,
                    getMessage(OutputType::PromptUserConfirmation, ""))
            .WillOnce(Return("Press Y to accept or N to cancel:"));
        EXPECT_CALL(*messageServicePtr,
                    showMessage("Press Y to accept or N to cancel:"));
        EXPECT_CALL(*keypadPtr, getConfirmation())
            .WillOnce(Return("Y"));

        EXPECT_CALL(*pinServicePtr, validatePin(acct, pin))
            .WillOnce(Return(true));

        EXPECT_CALL(*presenterPtr,
                    getMessage(OutputType::PinSuccess, ""))
            .WillOnce(Return("PIN correct. Access granted"));
        EXPECT_CALL(*messageServicePtr,
                    showMessage("PIN correct. Access granted"));
}

};
