#pragma once

#include <memory>
#include "ATMControllerContext.h"
#include "states/ATMStateHandler.h"
#include "states/IdleState.h" 

class CardReader;
class PinService;
class Keypad;
class OutputScreen;
class MessageServiceInterface;
class AccountService;

class ATMController {
public:
    ATMController(std::unique_ptr<CardReader> reader,
                  std::unique_ptr<PinService> pinService,
                  std::unique_ptr<Keypad> keypad,
                  std::unique_ptr<OutputScreen> presenter,
                  std::unique_ptr<MessageServiceInterface> messageService,
                  std::unique_ptr<AccountService> accountService);

    void run();

private:
    std::unique_ptr<CardReader> reader_;
    std::unique_ptr<PinService> pinService_;
    std::unique_ptr<Keypad> keypad_;
    std::unique_ptr<OutputScreen> presenter_;
    std::unique_ptr<MessageServiceInterface> messageService_;
    std::unique_ptr<AccountService> accountService_;
};