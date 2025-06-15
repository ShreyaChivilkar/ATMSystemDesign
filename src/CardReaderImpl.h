#pragma once
#include "CardReader.h"

class CardReaderImpl : public CardReader {
public:
    std::pair<bool, std::string> readCard() override;
};
