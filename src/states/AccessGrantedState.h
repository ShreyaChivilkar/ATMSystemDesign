#pragma once

#include <memory>
#include "states/ATMStateHandler.h"
#include "ATMControllerContext.h"
#include "presenter/OutputType.h"
#include "states/OperationState.h"         

class AccessGrantedState : public ATMStateHandler {
public:
    std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) override;
};
