#pragma once
#include "IApplication.hpp"
#include "docker/IDockerManager.hpp"
#include "gateway/IHttpClient.hpp"
#include <fruit/fruit.h>

class Application : public IApplication {
  const IHttpClient *httpClient;
  const IDockerManager *dockerManager;

public:
  INJECT(Application(const IHttpClient *httpClient,
                     const IDockerManager *dockerManager));
  void start() const override;
};
