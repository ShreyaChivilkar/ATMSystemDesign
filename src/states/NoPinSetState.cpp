#include "states/NoPinSetState.h"
 

std::unique_ptr<ATMStateHandler> NoPinSetState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PinNotSet));
    ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PromptPinSetup));
    const std::string newPin = ctx.keypad->getInput();

    ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PromptPinConfirmation));
    const std::string confirmPin = ctx.keypad->getInput();

    if (newPin != confirmPin) {
        ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PinMismatch));
        return nullptr;  // Exit session
    }

    ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PromptUserConfirmation));
    const std::string confirmation = ctx.keypad->getConfirmation();

    if (confirmation == CONFIRM_YES) {
        if (ctx.pinService->setPin(ctx.accountNum, newPin)) {
            ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PinSetupSuccess));
            return std::make_unique<AccessGrantedState>();
        } else {
            ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PinSetupFailure));
            return nullptr;
        }
    } else if (confirmation == CONFIRM_NO) {
        ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PinEntryCanceled));
        return std::make_unique<NoPinSetState>();
    } else {
        ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::InvalidConfirmation));
        return nullptr;
    }
}
