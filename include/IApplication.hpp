#pragma once
#include <string>

class IApplication {
public:
  virtual ~IApplication() = default;
  virtual std::string greet() const = 0;
};
