#pragma once
#include <string>
#include <utility>

class CardReader {
public:
    virtual ~CardReader() = default;
    virtual std::pair<bool, std::string> readCard() = 0;
};
