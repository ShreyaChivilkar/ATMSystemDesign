#include "ATMController.h"
#include "services/MessageServiceImpl.h"
#include <iostream>
#include <memory>
#include "presenter/OutputScreenImpl.h"
#include "services/CardReaderImpl.h"
#include "services/KeypadImpl.h"
#include "services/PinServiceImpl.h"
#include "data/PinDataRepository.h"
#include "services/AccountServiceImpl.h"
#include "data/AccountDataRepository.h"


       
int main() {
    auto repository = std::make_unique<PinDataRepository>();
    repository->populateDummyData();  
    auto pinService = std::make_unique<PinServiceImpl>(repository.get());

    auto accountRepo   = std::make_unique<AccountDataRepository>();
    accountRepo->populateDummyData();
    auto accountService = std::make_unique<AccountServiceImpl>(accountRepo.get());

    auto messageService = std::make_unique<MessageServiceImpl>();
    auto reader = std::make_unique<CardReaderImpl>();
    auto keypad = std::make_unique<KeypadImpl>();
    auto presenter = std::make_unique<OutputScreenImpl>();

    ATMController controller(
        std::move(reader),
        std::move(pinService),
        std::move(keypad),
        std::move(presenter),
        std::move(messageService),
        std::move(accountService)
    );

    controller.run();

    return 0;
}
