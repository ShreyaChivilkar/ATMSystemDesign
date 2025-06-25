#pragma once

#include "Operation.h"

class ExitOperation : public Operation {
public:
    bool execute(ATMControllerContext& ctx) override;
};
