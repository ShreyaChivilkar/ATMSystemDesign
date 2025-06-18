#pragma once
#include "PinService.h"
#include "PinDataRepository.h"

class PinServiceImpl : public PinService {
public:
    explicit PinServiceImpl(const PinDataRepository* repository);
    
    bool isPinSetup(const std::string& accountNum) override;
    bool validatePin(const std::string& accountNum, const std::string& pin) override;

private:
    const PinDataRepository* repository_; 
};
