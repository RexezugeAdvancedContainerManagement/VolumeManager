#pragma once
#include <iostream>
#include <string>

struct ContainerInfo {
  std::string id;
  std::string image;
  std::string name;

  inline friend std::ostream &operator<<(std::ostream &os,
                                         const ContainerInfo &container) {
    os << "Container ID: " << container.id << ", Image: " << container.image
       << ", Name: " << container.name;
    return os;
  }
};
