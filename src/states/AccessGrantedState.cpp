#include "states/AccessGrantedState.h"


std::unique_ptr<ATMStateHandler> AccessGrantedState::handle(ATMControllerContext& ctx) {

    ctx.messageService->showMessage(
        ctx.presenter->getMessage(MessageType::PinSuccess)
    );

    return std::make_unique<OperationState>();
}
