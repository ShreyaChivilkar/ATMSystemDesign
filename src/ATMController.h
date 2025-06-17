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
    ATMController(std::shared_ptr<CardReader> reader,
                  std::shared_ptr<PinService> pinService,
                  std::shared_ptr<Keypad> keypad,
                  std::shared_ptr<PinMessagePresenter> presenter,
                  std::shared_ptr<MessageServiceInterface> messageService);

    void run();

private:
    std::shared_ptr<CardReader> reader_;
    std::shared_ptr<PinService> pinService_;
    std::shared_ptr<Keypad> keypad_;
    std::shared_ptr<PinMessagePresenter> presenter_;
    std::shared_ptr<MessageServiceInterface> messageService_;
};
