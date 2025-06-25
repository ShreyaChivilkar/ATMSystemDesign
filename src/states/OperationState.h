#pragma once

#include "ATMStateHandler.h"
#include "ATMControllerContext.h"
#include "operations/OperationFactory.h"
#include "operations/Operation.h"
#include "presenter/MessageType.h"

class OperationState : public ATMStateHandler {
public:
    std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) override;
};
