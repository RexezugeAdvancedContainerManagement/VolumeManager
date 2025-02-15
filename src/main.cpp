#include "Application.hpp"
#include "IApplication.hpp"
#include "docker/DockerManager.hpp"
#include "docker/IDockerManager.hpp"
#include "gateway/HttpClient.hpp"
#include "gateway/IHttpClient.hpp"
#include <fruit/fruit.h>

fruit::Component<IApplication> getApplicationComponent() {
  return fruit::createComponent()
      .bind<IApplication, Application>() // Bind IApplication to Application
      .bind<IHttpClient, HttpClient>()   // Bind IHttpClient to HttpClient
      .bind<IDockerManager, DockerManager>()
      .registerConstructor<Application(
          IHttpClient *,
          IDockerManager *)>() // Register Application constructor
      .registerProvider([]() {
        return std::string("Hello from Safe DI!");
      }); // Provide the message
}

int main() {
  fruit::Injector<IApplication> injector(getApplicationComponent);

  const IApplication &application = injector.get<IApplication &>();

  application.start();

  return 0;
}
