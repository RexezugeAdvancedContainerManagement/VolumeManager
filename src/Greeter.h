#pragma once
#include "IGreeter.h"
#include <string>

class Greeter : public IGreeter {
    std::string message;
public:
    explicit Greeter(const std::string& message);
    std::string greet() const override;
};
