#include "states/AccessDeniedState.h"
 
std::unique_ptr<ATMStateHandler> AccessDeniedState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinFailure));
    ctx.retryCount++;

    if (ctx.retryCount > MAX_PIN_RETRIES) {
        ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::MaximumRetriesExceeded));
        return nullptr; // exit the application
    } else {
        ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::AccessDenied));
        return std::make_unique<PinPromptState>();
    }
}
