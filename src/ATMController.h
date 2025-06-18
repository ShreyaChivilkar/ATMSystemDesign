#pragma once

#include <memory>
#include <string>

#include "MessageServiceInterface.h"
#include "CardReader.h"
#include "PinService.h"
#include "Keypad.h"
#include "PinMessagePresenter.h"
#include "ATMState.h"


class ATMController {

public:
    ATMController(std::unique_ptr<CardReader> reader,
                  std::unique_ptr<PinService> pinService,
                  std::unique_ptr<Keypad> keypad,
                  std::unique_ptr<PinMessagePresenter> presenter,
                  std::unique_ptr<MessageServiceInterface> messageService);

    void run();

private:
    std::unique_ptr<CardReader> reader_;
    std::unique_ptr<PinService> pinService_;
    std::unique_ptr<Keypad> keypad_;
    std::unique_ptr<PinMessagePresenter> presenter_;
    std::unique_ptr<MessageServiceInterface> messageService_;
};
