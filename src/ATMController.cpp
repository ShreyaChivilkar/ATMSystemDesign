#include "ATMController.h"

ATMController::ATMController(std::shared_ptr<CardReader> reader,
                             std::shared_ptr<PinService> pinService,
                             std::shared_ptr<Keypad> keypad,
                             std::shared_ptr<PinMessagePresenter> presenter,
                             std::shared_ptr<MessageServiceInterface> messageService)
    : reader_(reader),
      pinService_(pinService),
      keypad_(keypad),
      presenter_(presenter),
      messageService_(messageService) {}


void ATMController::run() {
    messageService_->showMessage("ATM System Started. Welcome! Please tap your card");

    auto [cardValid, accountNum] = reader_->readCard();

    if (cardValid) {
        messageService_->showMessage(presenter_->cardReadSuccess(accountNum));

        if (pinService_->isPinSetup(accountNum)) {
            messageService_->showMessage(presenter_->promptPinEntry());

            std::string enteredPin = keypad_->getInput();

            if (pinService_->validatePin(accountNum, enteredPin)) {
                messageService_->showMessage(presenter_->pinSuccess());
            } else {
                messageService_->showMessage(presenter_->pinFailure());
            }
        } else {
            messageService_->showMessage(presenter_->pinNotSet());
        }
    } else {
        messageService_->showMessage(presenter_->cardReadFailure());
    }
}

