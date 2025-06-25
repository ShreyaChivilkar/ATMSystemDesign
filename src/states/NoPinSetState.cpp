#include "states/NoPinSetState.h"
 

std::unique_ptr<ATMStateHandler> NoPinSetState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinNotSet));
    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PromptPinSetup));
    const std::string newPin = ctx.keypad->getInput();

    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PromptPinConfirmation));
    const std::string confirmPin = ctx.keypad->getInput();

    if (newPin != confirmPin) {
        ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinMismatch));
        return nullptr;  // Exit session
    }

    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PromptUserConfirmation));
    const std::string confirmation = ctx.keypad->getConfirmation();

    if (confirmation == CONFIRM_YES) {
        if (ctx.pinService->setPin(ctx.accountNum, newPin)) {
            ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinSetupSuccess));
            return std::make_unique<AccessGrantedState>();
        } else {
            ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinSetupFailure));
            return nullptr;
        }
    } else if (confirmation == CONFIRM_NO) {
        ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinEntryCanceled));
        return std::make_unique<NoPinSetState>();
    } else {
        ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::InvalidConfirmation));
        return nullptr;
    }
}
