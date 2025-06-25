#include "states/ErrorState.h"

std::unique_ptr<ATMStateHandler> ErrorState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::CardReadFailure));
    return nullptr;  // Exit the session
}
