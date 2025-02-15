#include "Application.hpp"
#include "gateway/HttpClient.hpp"

Application::Application(std::string message, IHttpClient *httpClient)
    : message(std::move(message)), httpClient(httpClient) {}

std::string Application::greet() const {
  // Use the HttpClient to send a request
  std::string httpResponse = httpClient->sendRequest("https://example.com");
  return message + " " + httpResponse;
}
