#pragma once

#include "Operation.h"
#include "ATMControllerContext.h"
#include "presenter/OutputType.h"

class ViewBalanceOperation : public Operation {
public:
    bool execute(ATMControllerContext& ctx) override;
};
