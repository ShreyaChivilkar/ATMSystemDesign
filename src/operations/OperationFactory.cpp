#include "operations/OperationFactory.h"


std::unique_ptr<Operation> OperationFactory::create(const std::string& c) {
    if (c == "1") return std::make_unique<ViewBalanceOperation>();
    if (c == "2") return std::make_unique<DepositOperation>();
    if (c == "3") return std::make_unique<WithdrawOperation>();
    if (c == "0") return std::make_unique<ExitOperation>();
    return nullptr;
}