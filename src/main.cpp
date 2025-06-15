#include "ATMController.h"
#include "MessageServiceImpl.h"
#include <iostream>
#include <memory>
#include "PinMessagePresenterImpl.h"
#include "CardReaderImpl.h"
#include "KeypadImpl.h"



// Minimal stubs for dependencies:

class PinServiceStub : public PinService {
public:
    bool isPinSetup(const std::string&) override { return true; }
    bool validatePin(const std::string&, const std::string&) override {
        std::cout << "[Stub] validatePin called\n";
        return true;
    }
};


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
    auto messageService = std::make_shared<MessageServiceImpl>();
    auto reader = std::make_shared<CardReaderImpl>();
    auto pinService = std::make_shared<PinServiceStub>();
    auto keypad = std::make_shared<KeypadImpl>();
    auto presenter = std::make_shared<PinMessagePresenterImpl>();

    ATMController controller(reader, pinService, keypad, presenter, messageService);

    controller.run();

    return 0;
}
