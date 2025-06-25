#include "states/AccessDeniedState.h"
#include "constants/Constants.h"  // for MAX_PIN_RETRIES

std::unique_ptr<ATMStateHandler> AccessDeniedState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinFailure));
    ctx.retryCount++;

    if (ctx.retryCount > MAX_PIN_RETRIES) {
        ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::MaximumRetriesExceeded));
        return nullptr;  // End session
    } else {
        ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::AccessDenied));
        return std::make_unique<PinPromptState>();  // Retry
    }
}
