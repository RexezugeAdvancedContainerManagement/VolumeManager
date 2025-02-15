#pragma once
#include "gateway/IHttpClient.hpp"
#include <fruit/fruit.h>
#include <string>

class HttpClient : public IHttpClient {
public:
  INJECT(HttpClient()) = default;
  ~HttpClient() override = default;
  std::string sendRequest(const std::string &url,
                          const std::string &method = "GET") const override;
};
