#include "ATMController.h"
#include "services/MessageServiceImpl.h"
#include <iostream>
#include <memory>
#include "presenter/MessagePresenterImpl.h"
#include "services/CardReaderImpl.h"
#include "services/KeypadImpl.h"
#include "services/PinServiceImpl.h"
#include "data/PinDataRepository.h"


       
int main() {
    auto repository = std::make_unique<PinDataRepository>();
    repository->populateDummyData();  
    auto pinService = std::make_unique<PinServiceImpl>(repository.get());

    auto messageService = std::make_unique<MessageServiceImpl>();
    auto reader = std::make_unique<CardReaderImpl>();
    auto keypad = std::make_unique<KeypadImpl>();
    auto presenter = std::make_unique<MessagePresenterImpl>();

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
