#include "states/AccessDeniedState.h"
 
std::unique_ptr<ATMStateHandler> AccessDeniedState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::PinFailure));
    ctx.retryCount++;

    if (ctx.retryCount > MAX_PIN_RETRIES) {
        ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::MaximumRetriesExceeded));
        return nullptr; // exit the application
    } else {
        ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::AccessDenied));
        return std::make_unique<PinPromptState>();
    }
}
