#include "states/AccessGrantedState.h"

std::unique_ptr<ATMStateHandler> AccessGrantedState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::PinSuccess));
    ctx.messageService->showMessage(ctx.presenter->getMessage(MessageType::SelectOperation));

    // Future: perform transaction or route to operation state

    return nullptr;  // End session
}
