#pragma once
#include "operations/Operation.h"
#include "ATMControllerContext.h"
#include "presenter/OutputType.h"

class WithdrawOperation : public Operation {
public:
    bool execute(ATMControllerContext& ctx) override;
};
