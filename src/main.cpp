#include <fruit/fruit.h>
#include <iostream>
#include "IGreeter.h"
#include "Greeter.h"

fruit::Component<IGreeter> getGreeterComponent() {
    return fruit::createComponent()
        .bind<IGreeter, Greeter>()
        .registerConstructor<Greeter(std::string)>()
        .registerProvider([]() { return std::string("Hello from Safe DI!"); });
}

int main() {
    fruit::Injector<IGreeter> injector(getGreeterComponent);
    
    // Get reference without ownership transfer
    IGreeter& greeter = injector.get<IGreeter&>();
    
    std::cout << greeter.greet() << std::endl;
    return 0;
}
