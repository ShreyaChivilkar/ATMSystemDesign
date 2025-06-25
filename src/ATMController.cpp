#include "ATMController.h"

ATMController::ATMController(std::unique_ptr<CardReader> reader,
                             std::unique_ptr<PinService> pinService,
                             std::unique_ptr<Keypad> keypad,
                             std::unique_ptr<MessagePresenter> presenter,
                             std::unique_ptr<MessageServiceInterface> messageService)
    : reader_(std::move(reader)),
      pinService_(std::move(pinService)),
      keypad_(std::move(keypad)),
      presenter_(std::move(presenter)),
      messageService_(std::move(messageService)) {}

void ATMController::run() {
    // Shared context for all states
    ATMControllerContext ctx{
        .reader = reader_.get(),
        .pinService = pinService_.get(),
        .keypad = keypad_.get(),
        .presenter = presenter_.get(),
        .messageService = messageService_.get()
    };

    // Start with Idle state
    std::unique_ptr<ATMStateHandler> state = std::make_unique<IdleState>();

    while (state) {
        state = state->handle(ctx);  // Each state's handle returns the next state or nullptr to exit
    }
}
