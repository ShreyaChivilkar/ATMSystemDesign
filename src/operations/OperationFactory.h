#pragma once

#include <memory>
#include <string>
#include "Operation.h"
#include "operations/ViewBalanceOperation.h"
#include "operations/ExitOperation.h"
#include "operations/DepositOperation.h"
#include "operations/WithdrawOperation.h"

class OperationFactory {
public:
    static std::unique_ptr<Operation> create(const std::string& choice);
};
