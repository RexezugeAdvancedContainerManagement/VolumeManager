#include "DockerManager.hpp"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

std::vector<ContainerInfo> DockerManager::listContainers(bool all) const {
  std::vector<ContainerInfo> containers;
  std::string command = "docker ps " + std::string(all ? "-a" : "") +
                        " --format \"{{.ID}}:{{.Image}}:{{.Names}}\"";
  FILE *pipe = popen(command.c_str(), "r");
  if (!pipe) {
    std::cerr << "Failed to execute command." << std::endl;
    return containers;
  }
  char buffer[256];
  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    std::istringstream ss(buffer);
    ContainerInfo container;
    std::getline(ss, container.id, ':');
    std::getline(ss, container.image, ':');
    std::getline(ss, container.name, ':');
    containers.push_back(container);
  }
  pclose(pipe);
  return containers;
}
