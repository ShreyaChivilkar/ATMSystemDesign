#include "ATMController.h"

ATMController::ATMController(std::unique_ptr<CardReader> reader,
                             std::unique_ptr<PinService> pinService,
                             std::unique_ptr<Keypad> keypad,
                             std::unique_ptr<OutputScreen> presenter,
                             std::unique_ptr<MessageServiceInterface> messageService,
                             std::unique_ptr<AccountService> accountService)
    : reader_(std::move(reader)),
      pinService_(std::move(pinService)),
      keypad_(std::move(keypad)),
      presenter_(std::move(presenter)),
      messageService_(std::move(messageService)),
      accountService_(std::move(accountService)) {}

void ATMController::run() {
    
    ATMControllerContext ctx{
        .reader = reader_.get(),
        .pinService = pinService_.get(),
        .keypad = keypad_.get(),
        .presenter = presenter_.get(),
        .messageService = messageService_.get(),
        .accountService = accountService_.get()
    };

    // shared pointer - if ctx gets passed out of atmcontroller it will be dangling
    std::unique_ptr<ATMStateHandler> state = std::make_unique<IdleState>();

    while (state) {
        state = state->handle(ctx);  
    }
}
