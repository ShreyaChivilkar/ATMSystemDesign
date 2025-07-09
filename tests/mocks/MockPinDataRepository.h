#pragma once
#include "data/PinDataRepository.h"
#include <gmock/gmock.h>

class MockPinDataRepository : public PinDataRepository {
public:
    MOCK_METHOD(bool, hasPin, (const std::string& accountNum), (const, override));
    MOCK_METHOD(std::string, getPin, (const std::string& accountNum), (const, override));
    MOCK_METHOD(bool, updatePin, (const std::string& accountNum, const std::string& pin), (override));
};
