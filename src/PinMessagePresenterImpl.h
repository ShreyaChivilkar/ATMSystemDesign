#pragma once

#include "PinMessagePresenter.h"
#include <string>

class PinMessagePresenterImpl : public PinMessagePresenter {  
public:
    std::string getMessage(PinMessageType type, const std::string& context = "") override;
};
