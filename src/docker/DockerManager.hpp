#pragma once
#include "docker/IDockerManager.hpp"
#include <fruit/fruit.h>

class DockerManager : public IDockerManager {
public:
  INJECT(DockerManager()) = default;
  ~DockerManager() override = default;
  std::vector<ContainerInfo> listContainers(bool all = false) const override;
};
