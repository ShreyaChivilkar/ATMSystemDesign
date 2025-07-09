#include "states/OperationState.h"


#include <memory>

std::unique_ptr<ATMStateHandler> OperationState::handle(ATMControllerContext& ctx) {
    bool performOperation = true;
    while (performOperation) {

        ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::OperationMenu));
        
        std::string choice = ctx.keypad->getInput();

        std::unique_ptr<Operation> op = OperationFactory::create(choice);
        if (!op) {
            ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::InvalidSelection));
            continue;
        }

        performOperation = op->execute(ctx);
    }

    return nullptr; 
}
