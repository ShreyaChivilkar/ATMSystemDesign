#include "ATMController.h"
#include "MessageServiceImpl.h"
#include <iostream>
#include <memory>
#include "PinMessagePresenterImpl.h"
#include "CardReaderImpl.h"
#include "KeypadImpl.h"
#include "PinServiceImpl.h"
#include "PinDataRepository.h"



// // Minimal stubs for dependencies:

// class PinServiceStub : public PinService {
// public:
//     bool isPinSetup(const std::string&) override { return true; }
//     bool validatePin(const std::string&, const std::string&) override {
//         std::cout << "[Stub] validatePin called\n";
//         return true;
//     }
// };


/**
 * Main entry point for the ATM application.
 * 
 * Initializes core ATM components including message service, card reader, 
 * pin service, keypad, and message presenter. Creates an ATMController 
 * with these dependencies and runs the ATM system.
 * 
 * @returns Exit status of the application
 */
int main() {
    auto repository = std::make_unique<PinDataRepository>();
    repository->populateDummyData();  

    auto pinService = std::make_unique<PinServiceImpl>(repository.get());

    auto messageService = std::make_unique<MessageServiceImpl>();
    auto reader = std::make_unique<CardReaderImpl>();
    //auto pinService = std::make_unique<PinServiceStub>();
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
