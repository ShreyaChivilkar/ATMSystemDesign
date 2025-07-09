#include "operations/DepositOperation.h"


bool DepositOperation::execute(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(
        ctx.presenter->getMessage(OutputType::PromptDepositInput)
    );
    double amt = std::stod(ctx.keypad->getInput());

    double newBal{};
    bool depositSuccessFlag = ctx.accountService->deposit(ctx.accountNum, amt, newBal);

    ctx.messageService->showMessage(
        ctx.presenter->getMessage (depositSuccessFlag ? OutputType::DepositSuccess
                                     : OutputType::DepositFailure,
                                 depositSuccessFlag ? std::to_string(newBal) : std::string{})
    );
    return true;
}