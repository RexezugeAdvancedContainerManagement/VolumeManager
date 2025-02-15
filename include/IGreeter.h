#pragma once
#include <string>

class IGreeter {
public:
    virtual ~IGreeter() = default;
    virtual std::string greet() const = 0;
};
