#pragma once

#include <string>
#include "services/CardReader.h"
#include "services/PinService.h"
#include "services/Keypad.h"
#include "presenter/MessagePresenter.h"
#include "services/MessageServiceInterface.h"

struct ATMControllerContext {
    std::string accountNum;
    std::string enteredPin;
    int retryCount = 0;

    CardReader* reader = nullptr;
    PinService* pinService = nullptr;
    Keypad* keypad = nullptr;
    MessagePresenter* presenter = nullptr;
    MessageServiceInterface* messageService = nullptr;
};
