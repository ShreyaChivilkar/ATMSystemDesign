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
    ATMState state = ATMState::Idle;
    std::string accountNum;
    std::string enteredPin;
    int retryCount = 0;
    const int MAX_RETRIES = 3;

    while (state != ATMState::Exit) {
        switch (state) {
            case ATMState::Idle: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::WelcomeMessage));

                auto [cardValid, acct] = reader_->readCard();
                if (cardValid) {
                    accountNum = acct;
                    state = ATMState::CardRead;
                } else {
                    state = ATMState::Error;
                }
                break;
            }

            case ATMState::CardRead: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::CardReadSuccess, accountNum));
                if (pinService_->isPinSetup(accountNum)) {
                    state = ATMState::PinPrompt;
                } else {
                    state = ATMState::NoPinSet;
                }
                break;
            }

            case ATMState::PinPrompt: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::PromptPinEntry));
                enteredPin = keypad_->getInput();
                state = ATMState::PinConfirm;
                break;
            }

            case ATMState::PinConfirm: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::PromptUerConfirmation));
                std::string confirmation = keypad_->getConfirmation();
                if (confirmation == "Y") {
                    state = ATMState::Validating;
                } else if (confirmation == "N") {
                    messageService_->showMessage(presenter_->getMessage(PinMessageType::PinEntryCanceled));
                    state = ATMState::PinPrompt;
                } else {
                    messageService_->showMessage(presenter_->getMessage(PinMessageType::InvalidConfirmation));
                    state = ATMState::PinConfirm;
                }
                break;
            }

            case ATMState::Validating: {
                if (pinService_->validatePin(accountNum, enteredPin)) {
                    state = ATMState::AccessGranted;
                } else {
                    state = ATMState::AccessDenied;
                }
                break;
            }

            case ATMState::AccessGranted: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::PinSuccess));
                messageService_->showMessage(presenter_->getMessage(PinMessageType::SelectOperation));
                // code for operation factory and operation selection

                state = ATMState::Exit;
                break;
            }

            case ATMState::AccessDenied: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::PinFailure));
                retryCount++;
                if (retryCount >= MAX_RETRIES) {
                    messageService_->showMessage(presenter_->getMessage(PinMessageType::MaximumRetriesExceeded));
                    state = ATMState::Exit;
                } else {
                    messageService_->showMessage(presenter_->getMessage(PinMessageType::AccessDenied));
                    state = ATMState::PinPrompt;
                }
                break;
            }

            case ATMState::NoPinSet: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::PinNotSet));
                state = ATMState::Exit;
                break;
            }

            case ATMState::Error: {
                messageService_->showMessage(presenter_->getMessage(PinMessageType::CardReadFailure));
                state = ATMState::Exit;
                break;
            }

            default: {
                state = ATMState::Exit;
                break;
            }
        }
    }
}

