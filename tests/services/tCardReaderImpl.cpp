#include <gtest/gtest.h>
#include "services/CardReaderImpl.h"
#include <sstream>

TEST(tCardReaderImpl, ReturnsTrueWhenInputIsProvided) {
    std::istringstream input("ACC123\n");
    CardReaderImpl reader(input);

    auto result = reader.readCard();
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second, "ACC123");
}

TEST(tCardReaderImpl, ReturnsFalseWhenInputIsEmpty) {
    std::istringstream input("\n");
    CardReaderImpl reader(input);

    auto result = reader.readCard();
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second, "");
}
