#include "operations/ViewBalanceOperation.h"


bool ViewBalanceOperation::execute(ATMControllerContext& ctx) {
    double balance = ctx.accountService->getBalance(ctx.accountNum);

    ctx.messageService->showMessage(
        ctx.presenter->getMessage(OutputType::DisplayBalance, std::to_string(balance))
    );

    return true; 
}
