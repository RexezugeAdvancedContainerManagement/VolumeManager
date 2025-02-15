#include "Greeter.h"

Greeter::Greeter(const std::string& message) : message(message) {}

std::string Greeter::greet() const {
    return message;
}
