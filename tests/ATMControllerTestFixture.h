#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "ATMController.h"
#include "services/CardReader.h"
#include "services/PinService.h"
#include "services/Keypad.h"
#include "presenter/MessagePresenter.h"
#include "services/MessageServiceInterface.h"
#include "presenter/MessageType.h"
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

class MockMessagePresenter : public MessagePresenter {
public:
    MOCK_METHOD(std::string, getMessage, (MessageType, const std::string&), (const, override));
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
    std::unique_ptr<MockMessagePresenter> presenter;
    std::unique_ptr<MockMessageService> messageService;
    std::unique_ptr<MockAccountService> accountService;

    MockCardReader* readerPtr;
    MockPinService* pinServicePtr;
    MockKeypad* keypadPtr;
    MockMessagePresenter* presenterPtr;
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

        presenter = std::make_unique<MockMessagePresenter>();
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
        EXPECT_CALL(*presenterPtr, getMessage(MessageType::WelcomeMessage, ""))
            .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
        EXPECT_CALL(*messageServicePtr, showMessage("ATM System Started. Welcome! Please tap your card"));
    }

    void expectCardRead(bool success, const std::string& accountNum = "") {
        EXPECT_CALL(*readerPtr, readCard()).WillOnce(Return(std::make_pair(success, accountNum)));

        if (success) {
            EXPECT_CALL(*presenterPtr, getMessage(MessageType::CardReadSuccess, accountNum))
                .WillOnce(Return("Card read successful: " + accountNum));
            EXPECT_CALL(*messageServicePtr, showMessage("Card read successful: " + accountNum));
        } else {
            EXPECT_CALL(*presenterPtr, getMessage(MessageType::CardReadFailure, ""))
                .WillOnce(Return("Card read failed. Please try again."));
            EXPECT_CALL(*messageServicePtr, showMessage("Card read failed. Please try again."));
        }
    }
};
