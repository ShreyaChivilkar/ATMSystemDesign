#pragma once
#include "operations/Operation.h"
#include "ATMControllerContext.h"
#include "presenter/MessageType.h"

class DepositOperation : public Operation {
public:
    bool execute(ATMControllerContext& ctx) override;
};