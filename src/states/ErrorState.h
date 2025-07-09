#pragma once

#include <memory>
#include "states/ATMStateHandler.h"
#include "ATMControllerContext.h"
#include "presenter/OutputType.h"

class ErrorState : public ATMStateHandler {
public:
    std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) override;
};
