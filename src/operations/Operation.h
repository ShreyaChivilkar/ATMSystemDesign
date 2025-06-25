#pragma once
#include <memory>
struct ATMControllerContext;


class Operation {
public:
    virtual ~Operation() = default;
    virtual bool execute(ATMControllerContext& ctx) = 0;
};
