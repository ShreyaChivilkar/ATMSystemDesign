#pragma once

#include <memory>
#include "states/ATMStateHandler.h"
#include "ATMControllerContext.h"
#include "presenter/MessageType.h"
#include "states/ValidatingState.h"
#include "states/PinPromptState.h"
#include "constants/Constants.h"  // for CONFIRM_YES, CONFIRM_NO

class PinConfirmState : public ATMStateHandler {
public:
    std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) override;
};
