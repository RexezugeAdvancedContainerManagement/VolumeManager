#pragma once
#include <string>

class IHttpClient {
public:
  virtual ~IHttpClient() = default;
  virtual std::string sendRequest(const std::string &url,
                                  const std::string &method = "GET") const = 0;
};
