#include "states/ValidatingState.h"

std::unique_ptr<ATMStateHandler> ValidatingState::handle(ATMControllerContext& ctx) {
    if (ctx.pinService->validatePin(ctx.accountNum, ctx.enteredPin)) {
        return std::make_unique<AccessGrantedState>();
    } else {
        return std::make_unique<AccessDeniedState>();
    }
}
