#pragma once
#include "services/CardReader.h"
#include <istream>
#include <iostream>  

class CardReaderImpl : public CardReader {
public:
    explicit CardReaderImpl(std::istream& inputStream = std::cin)
        : in(inputStream) {}

    std::pair<bool, std::string> readCard() override;

private:
    std::istream& in;
};
