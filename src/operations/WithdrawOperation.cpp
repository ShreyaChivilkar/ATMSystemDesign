#include "operations/WithdrawOperation.h"


bool WithdrawOperation::execute(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(
        ctx.presenter->getMessage(MessageType::PromptWithdrawInput)
    );
    double amt = std::stod(ctx.keypad->getInput());

    double newBal{};
    bool withdrawSuccessFlag = ctx.accountService->withdraw(ctx.accountNum, amt, newBal);

    ctx.messageService->showMessage(
        ctx.presenter->getMessage(withdrawSuccessFlag ? MessageType::WithdrawSuccess
                                     : MessageType::WithdrawFailure,
                                  withdrawSuccessFlag ? std::to_string(newBal) : std::string{})
    );
    return true;          
}