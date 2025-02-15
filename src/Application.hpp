#pragma once
#include "IApplication.hpp"
#include "gateway/HttpClient.hpp"
#include <fruit/fruit.h>
#include <string>

class Application : public IApplication {
  const std::string message;
  const IHttpClient *httpClient;

public:
  INJECT(Application(std::string message, IHttpClient *httpClient));
  std::string greet() const override;
};
