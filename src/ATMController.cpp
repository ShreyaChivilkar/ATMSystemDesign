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
        messageService_->showMessage(presenter_->getMessage(PinMessageType::CardReadSuccess, accountNum));

        if (pinService_->isPinSetup(accountNum)) {
            messageService_->showMessage(presenter_->getMessage(PinMessageType::PromptPinEntry));

            std::string enteredPin = keypad_->getInput();

            if (pinService_->validatePin(accountNum, enteredPin)) {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::PinSuccess));
            } else {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::PinFailure));
            }
        } else {
            messageService_->showMessage(presenter_->getMessage(PinMessageType::PinNotSet));
        }
    } else {
        messageService_->showMessage(presenter_->getMessage(PinMessageType::CardReadFailure));
    }
}


