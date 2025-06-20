#pragma once

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

// -------------------- Test Fixture --------------------
class ATMControllerTest : public ::testing::Test {
protected:
    std::unique_ptr<MockCardReader> reader;
    std::unique_ptr<MockPinService> pinService;
    std::unique_ptr<MockKeypad> keypad;
    std::unique_ptr<MockPinMessagePresenter> presenter;
    std::unique_ptr<MockMessageService> messageService;

    MockCardReader* readerPtr;
    MockPinService* pinServicePtr;
    MockKeypad* keypadPtr;
    MockPinMessagePresenter* presenterPtr;
    MockMessageService* messageServicePtr;

    std::unique_ptr<ATMController> controller;

    void SetUp() override {
        reader = std::make_unique<MockCardReader>();
        readerPtr = reader.get();

        pinService = std::make_unique<MockPinService>();
        pinServicePtr = pinService.get();

        keypad = std::make_unique<MockKeypad>();
        keypadPtr = keypad.get();

        presenter = std::make_unique<MockPinMessagePresenter>();
        presenterPtr = presenter.get();

        messageService = std::make_unique<MockMessageService>();
        messageServicePtr = messageService.get();

        controller = std::make_unique<ATMController>(
            std::move(reader),
            std::move(pinService),
            std::move(keypad),
            std::move(presenter),
            std::move(messageService)
        );
    }

    void expectWelcomeMessage() {
        EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::WelcomeMessage, ""))
            .WillOnce(Return("ATM System Started. Welcome! Please tap your card"));
        EXPECT_CALL(*messageServicePtr, showMessage("ATM System Started. Welcome! Please tap your card"));
    }

    void expectCardRead(bool success, const std::string& accountNum = "") {
        EXPECT_CALL(*readerPtr, readCard()).WillOnce(Return(std::make_pair(success, accountNum)));

        if (success) {
            EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::CardReadSuccess, accountNum))
                .WillOnce(Return("Card read successful: " + accountNum));
            EXPECT_CALL(*messageServicePtr, showMessage("Card read successful: " + accountNum));
        } else {
            EXPECT_CALL(*presenterPtr, getMessage(PinMessageType::CardReadFailure, ""))
                .WillOnce(Return("Card read failed. Please try again."));
            EXPECT_CALL(*messageServicePtr, showMessage("Card read failed. Please try again."));
        }
    }
};
