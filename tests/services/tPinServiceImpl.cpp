#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "services/PinServiceImpl.h"
#include "MockPinDataRepository.h"

using ::testing::Return;
using ::testing::_;

class PinServiceImplTest : public ::testing::Test {
protected:
    MockPinDataRepository mockRepo;
    PinServiceImpl service{&mockRepo};
};

TEST_F(PinServiceImplTest, IsPinSetup_ReturnsTrue_WhenPinIsSet) {
    EXPECT_CALL(mockRepo, hasPin("ACC123")).WillOnce(Return(true));
    EXPECT_TRUE(service.isPinSetup("ACC123"));
}

TEST_F(PinServiceImplTest, IsPinSetup_ReturnsFalse_WhenPinIsNotSet) {
    EXPECT_CALL(mockRepo, hasPin("ACC123")).WillOnce(Return(false));
    EXPECT_FALSE(service.isPinSetup("ACC123"));
}

TEST_F(PinServiceImplTest, ValidatePin_ReturnsTrue_WhenCorrectPin) {
    EXPECT_CALL(mockRepo, getPin("ACC123")).WillOnce(Return("1234"));
    EXPECT_TRUE(service.validatePin("ACC123", "1234"));
}

TEST_F(PinServiceImplTest, ValidatePin_ReturnsFalse_WhenIncorrectPin) {
    EXPECT_CALL(mockRepo, getPin("ACC123")).WillOnce(Return("1234"));
    EXPECT_FALSE(service.validatePin("ACC123", "0000"));
}

TEST_F(PinServiceImplTest, SetPin_ReturnsTrue_OnSuccessfulUpdate) {
    EXPECT_CALL(mockRepo, updatePin("ACC123", "5678")).WillOnce(Return(true));
    EXPECT_TRUE(service.setPin("ACC123", "5678"));
}

TEST_F(PinServiceImplTest, SetPin_ReturnsFalse_OnFailure) {
    EXPECT_CALL(mockRepo, updatePin("ACC123", "5678")).WillOnce(Return(false));
    EXPECT_FALSE(service.setPin("ACC123", "5678"));
}
