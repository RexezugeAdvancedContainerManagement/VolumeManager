#include "Application.hpp"
#include <iostream>
#include <json/json.h>
#include <string>

Application::Application(const IHttpClient *httpClient,
                         const IDockerManager *dockerManager)
    : httpClient(httpClient), dockerManager(dockerManager) {}

Json::Value parseJson(const std::string &jsonString) {
  Json::Value root;
  Json::CharReaderBuilder reader;
  std::string errs;

  std::istringstream s(jsonString);
  std::string doc;
  s >> doc;

  if (!Json::parseFromStream(reader, s, &root, &errs)) {
    std::cerr << "Failed to parse JSON: " << errs << std::endl;
  }

  return root;
}

void Application::start() const {
  // std::string url = "http://localhost/containers/json";
  // std::string httpResponse = httpClient->sendRequest(url);

  // Json::Value jsonResponse = parseJson(httpResponse);
  // std::cout << "Containers: " << jsonResponse << std::endl;
  std::vector<ContainerInfo> containerInfos = dockerManager->listContainers();

  for (const auto &container : containerInfos) {
    std::cout << container << std::endl;
  }
}
