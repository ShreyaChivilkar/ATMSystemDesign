#pragma once

#include <string>
#include "services/CardReader.h"
#include "services/PinService.h"
#include "services/Keypad.h"
#include "presenter/OutputScreen.h"
#include "services/MessageServiceInterface.h"
#include "services/AccountService.h"

struct ATMControllerContext {
    std::string accountNum;
    std::string enteredPin;
    int retryCount = 0;

    CardReader* reader = nullptr;
    PinService* pinService = nullptr;
    Keypad* keypad = nullptr;
    OutputScreen* presenter = nullptr;
    MessageServiceInterface* messageService = nullptr;
    AccountService* accountService = nullptr;

};
