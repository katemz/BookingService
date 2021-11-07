#include <iostream>
#include "BookingServiceEngine.hpp"
#include "VolatileDatabase.hpp"
#include "ExampleData.hpp"
#include "RequestProcessor.hpp"

int main() {

    ExampleData data;

    auto Database = std::make_shared<VolatileDatabase>();
    Database->addSeances(data.getExampleSeancesList());

    auto requestProcessor = std::make_shared<RequestProcessor>();
    requestProcessor->setDatabaseHandler(Database);

    BookingServiceEngine service("127.0.0.1","8080");
    service.setEndpoint("/api");
    service.accept().wait();

    service.setRequestProcessorHandler(requestProcessor);

    while(true)
    {
        sleep(1000);
    }

    return 0;
}
