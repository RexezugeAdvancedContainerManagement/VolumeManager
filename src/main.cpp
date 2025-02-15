#include "Application.hpp"
#include "IApplication.hpp"
#include "gateway/HttpClient.hpp"
#include "gateway/IHttpClient.hpp"
#include <fruit/fruit.h>
#include <iostream>

fruit::Component<IApplication> getApplicationComponent() {
  return fruit::createComponent()
      .bind<IApplication, Application>() // Bind IApplication to Application
      .bind<IHttpClient, HttpClient>()   // Bind IHttpClient to HttpClient
      .registerConstructor<Application(
          std::string, IHttpClient *)>() // Register Application constructor
      .registerProvider([]() {
        return std::string("Hello from Safe DI!");
      }); // Provide the message
}

int main() {
  fruit::Injector<IApplication> injector(getApplicationComponent);

  // Get reference without ownership transfer
  IApplication &app = injector.get<IApplication &>();

  std::cout << app.greet() << std::endl;
  return 0;
}
