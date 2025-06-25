#pragma once

#include <memory>

struct ATMControllerContext;

class ATMStateHandler {
public:
    virtual ~ATMStateHandler() = default;

    // Returns the next state (nullptr to exit loop)
    virtual std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) = 0;
};
