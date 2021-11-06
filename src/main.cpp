#include <iostream>
#include "BookingServiceEngine.hpp"
#include "VolatileDatabase.hpp"
#include "ExampleData.hpp"

int main() {

    ExampleData data;

    auto Database = std::make_shared<VolatileDatabase>();
    Database->addSeances(data.getExampleSeancesList());

    BookingServiceEngine service("127.0.0.1","8080");
    service.setEndpoint("/api");
    service.accept().wait();

    service.setDatabaseHandler(Database);

    while(true)
    {
        sleep(1000);
    }

    return 0;
}
