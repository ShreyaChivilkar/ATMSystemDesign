#pragma once

#include <memory>
#include "states/ATMStateHandler.h"
#include "ATMControllerContext.h"
#include "presenter/MessageType.h"
#include "states/AccessGrantedState.h"
#include "states/PinPromptState.h"
#include "constants/Constants.h"

class NoPinSetState : public ATMStateHandler {
public:
    std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) override;
};
