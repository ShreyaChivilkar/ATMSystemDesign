#pragma once
#include <string>
#include <unordered_map>

class PinDataRepository {
public:
    struct PinRecord {
        std::string pin;
        bool isPinSet;
    };

    virtual ~PinDataRepository() = default;

    virtual void addAccount(const std::string& accountNum, const std::string& pin, bool isPinSet = true);
    virtual bool hasPin(const std::string& accountNum) const;
    virtual std::string getPin(const std::string& accountNum) const;
    virtual bool updatePin(const std::string& accountNum, const std::string& pin);
    virtual void populateDummyData();

protected:
    std::unordered_map<std::string, PinRecord> pinDatabase_;
};
