#pragma once
#include "PinService.h"
#include "PinDataRepository.h"

class PinServiceImpl : public PinService {
public:
    explicit PinServiceImpl(PinDataRepository* repository);
    
    bool isPinSetup(const std::string& accountNum) const override;
    bool validatePin(const std::string& accountNum, const std::string& pin) const override;
    bool setPin(const std::string& accountNum, const std::string& newPin) override;

private:
    PinDataRepository* repository_; 
};
