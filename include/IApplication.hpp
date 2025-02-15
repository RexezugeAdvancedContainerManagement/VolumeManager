#pragma once

class IApplication {
public:
  virtual ~IApplication() = default;
  virtual void start() const = 0;
};
