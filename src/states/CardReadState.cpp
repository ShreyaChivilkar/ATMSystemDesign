#include "states/CardReadState.h"

std::unique_ptr<ATMStateHandler> CardReadState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(
        ctx.presenter->getMessage(MessageType::CardReadSuccess, ctx.accountNum)
    );

    if (ctx.pinService->isPinSetup(ctx.accountNum)) {
        return std::make_unique<PinPromptState>();
    } else {
        return std::make_unique<NoPinSetState>();
    }
}
