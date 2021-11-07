#ifndef BOOKINGSERVICEENGINE_H
#define BOOKINGSERVICEENGINE_H

#include <memory>
#include "RestApiController.hpp"
#include "RequestProcessor.hpp"

class BookingServiceEngine : public RestApiController
{
public:
    BookingServiceEngine(const std::string& address,const std::string& port);
    ~BookingServiceEngine();

    void handleGet(http_request message);
    void handlePut(http_request message);
    void initRestOpHandlers() override;

    void setRequestProcessorHandler(std::shared_ptr<IRequestProcessor> requestProcessor);

private:
    std::shared_ptr<IRequestProcessor> requestProcessor_;
};

#endif // BOOKINGSERVICEENGINE_H
