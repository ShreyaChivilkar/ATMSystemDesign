#include "states/PinPromptState.h"

std::unique_ptr<ATMStateHandler> PinPromptState::handle(ATMControllerContext& ctx) {
    ctx.messageService->showMessage(
        ctx.presenter->getMessage(OutputType::PromptPinEntry)
    );

    ctx.enteredPin = ctx.keypad->getInput();

    return std::make_unique<PinConfirmState>();
}
