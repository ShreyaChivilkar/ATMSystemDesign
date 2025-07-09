#include "operations/WithdrawOperation.h"


bool WithdrawOperation::execute(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(
        ctx.presenter->getMessage(OutputType::PromptWithdrawInput)
    );
    double amt = std::stod(ctx.keypad->getInput());

    double newBal{};
    bool withdrawSuccessFlag = ctx.accountService->withdraw(ctx.accountNum, amt, newBal);

    ctx.messageService->showMessage(
        ctx.presenter->getMessage(withdrawSuccessFlag ? OutputType::WithdrawSuccess
                                     : OutputType::WithdrawFailure,
                                  withdrawSuccessFlag ? std::to_string(newBal) : std::string{})
    );
    return true;          
}