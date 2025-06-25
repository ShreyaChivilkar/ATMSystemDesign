#pragma once
#include "services/MessageServiceInterface.h"
#include <iostream>

class MessageServiceImpl : public MessageServiceInterface {
public:
    void showMessage(const std::string& msg) const override;
};
