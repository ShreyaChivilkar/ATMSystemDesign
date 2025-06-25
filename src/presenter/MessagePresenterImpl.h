#pragma once

#include "presenter/MessagePresenter.h"
#include <string>

class MessagePresenterImpl : public MessagePresenter {  
public:
    std::string getMessage(MessageType type, const std::string& context = "") const override;
};
