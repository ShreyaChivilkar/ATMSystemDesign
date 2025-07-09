#pragma once

#include <memory>
#include "states/ATMStateHandler.h"
#include "ATMControllerContext.h"
#include "presenter/OutputType.h"
#include "states/PinPromptState.h"
#include "states/NoPinSetState.h"

class CardReadState : public ATMStateHandler {
public:
    std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) override;
};
