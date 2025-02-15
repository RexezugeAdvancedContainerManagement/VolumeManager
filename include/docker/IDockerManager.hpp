#pragma once
#include <model/ContainerInfo.hpp>
#include <vector>

class IDockerManager {
public:
  virtual ~IDockerManager() = default;
  virtual std::vector<ContainerInfo> listContainers(bool all = false) const = 0;
};
