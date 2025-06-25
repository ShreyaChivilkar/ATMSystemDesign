#include "states/PinConfirmState.h"

std::unique_ptr<ATMStateHandler> PinConfirmState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(
        ctx.presenter->getMessage(MessageType::PromptUserConfirmation)
    );

    const std::string confirmation = ctx.keypad->getConfirmation();

    if (confirmation == CONFIRM_YES) {
        return std::make_unique<ValidatingState>();
    } 
    else if (confirmation == CONFIRM_NO) {
        ctx.messageService->showMessage(
            ctx.presenter->getMessage(MessageType::PinEntryCanceled)
        );
        return std::make_unique<PinPromptState>();  // Retry entry
    } 
    else {
        ctx.messageService->showMessage(
            ctx.presenter->getMessage(MessageType::InvalidConfirmation)
        );
        return std::make_unique<PinConfirmState>();  // Re-confirm
    }
}
