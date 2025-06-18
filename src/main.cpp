#include "ATMController.h"
#include "MessageServiceImpl.h"
#include <iostream>
#include <memory>
#include "PinMessagePresenterImpl.h"
#include "CardReaderImpl.h"
#include "KeypadImpl.h"
#include "PinServiceImpl.h"
#include "PinDataRepository.h"


       
int main() {
    auto repository = std::make_unique<PinDataRepository>();
    repository->populateDummyData();  
    auto pinService = std::make_unique<PinServiceImpl>(repository.get());

    auto messageService = std::make_unique<MessageServiceImpl>();
    auto reader = std::make_unique<CardReaderImpl>();
    auto keypad = std::make_unique<KeypadImpl>();
    auto presenter = std::make_unique<PinMessagePresenterImpl>();

    ATMController controller(
        std::move(reader),
        std::move(pinService),
        std::move(keypad),
        std::move(presenter),
        std::move(messageService)
    );

    controller.run();

    return 0;
}
