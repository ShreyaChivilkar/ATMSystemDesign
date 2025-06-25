#pragma once

#include "Operation.h"
#include "ATMControllerContext.h"
#include "presenter/MessageType.h"

class ViewBalanceOperation : public Operation {
public:
    bool execute(ATMControllerContext& ctx) override;
};
