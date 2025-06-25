#pragma once
#include <string>
#include <unordered_map>

class PinDataRepository {
public:
    struct PinRecord {
        std::string pin;
        bool isPinSet;
    };

    void addAccount(const std::string& accountNum, const std::string& pin, bool isPinSet = true);
    bool hasPin(const std::string& accountNum) const;
    std::string getPin(const std::string& accountNum) const;
    bool updatePin(const std::string& accountNum, const std::string& pin);
    void populateDummyData();

private:
    std::unordered_map<std::string, PinRecord> pinDatabase_;
};
