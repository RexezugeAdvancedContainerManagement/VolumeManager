#include "Application.hpp"
#include "gateway/HttpClient.hpp"
#include <iostream>
#include <json/json.h>
#include <string>

Application::Application(std::string message, IHttpClient *httpClient)
    : message(std::move(message)), httpClient(httpClient) {}

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

std::string Application::greet() const {
  std::string url = "http://localhost/containers/json";
  std::string httpResponse = httpClient->sendRequest(url);

  Json::Value jsonResponse = parseJson(httpResponse);
  std::cout << "Containers: " << jsonResponse << std::endl;
  return message + " " + httpResponse;
}
