#ifndef BOOKINGSERVICEENGINE_H
#define BOOKINGSERVICEENGINE_H

#include <memory>
#include "RestApiController.hpp"
#include <IDatabase.hpp>



class BookingServiceEngine : public RestApiController
{
public:
    BookingServiceEngine(const std::string& address,const std::string& port);
    ~BookingServiceEngine();

    void handleGet(http_request message);
    void handlePut(http_request message);
    void initRestOpHandlers() override;

    void setDatabaseHandler(std::shared_ptr<IDatabase> dbPtr);

private:
    std::shared_ptr<IDatabase> database_;
};

#endif // BOOKINGSERVICEENGINE_H
