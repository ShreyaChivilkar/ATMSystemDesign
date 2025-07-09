#pragma once
#include "states/ATMStateHandler.h"
#include "ATMControllerContext.h"
#include "states/CardReadState.h"
#include "states/ErrorState.h"

class IdleState : public ATMStateHandler {
public:
    std::unique_ptr<ATMStateHandler> handle(ATMControllerContext& ctx) override {
        ctx.messageService->showMessage(ctx.presenter->getMessage(OutputType::WelcomeMessage));
        const auto [valid, acct] = ctx.reader->readCard();
        if (valid) {
            ctx.accountNum = acct;
            return std::make_unique<CardReadState>();
        }
        return std::make_unique<ErrorState>();
    }
};
