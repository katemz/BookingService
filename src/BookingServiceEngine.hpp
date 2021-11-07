#ifndef BOOKINGSERVICEENGINE_H
#define BOOKINGSERVICEENGINE_H

#include <memory>
#include "RestApiController.hpp"
#include "RequestProcessor.hpp"

/**
 * This class creates REST service, receives HTTP requests and sends the responses.
 * Processing of specific request is delegated to RequestProcessor.
 */
class BookingServiceEngine : public RestApiController
{
public:
    /**
     * Constructor setting up the server address
     * @param address - IP address of server
     * @param port - port number of server
     */
    BookingServiceEngine(const std::string& address,const std::string& port);

    /**
     * Destructor
     */
    ~BookingServiceEngine();

    /**
     * This method processes the GET request and sends the response message
     * @param message - httpRequest
     */
    void handleGet(http_request message);

   /**
    * This method processes the PUT request and sends the response message
    * @param message - httpRequest
    */
    void handlePut(http_request message);

    /**
     * Sets up the processor handler responsible for processing HTTP requests
     * @param requestProcessor - request processor handler
     */
    void setRequestProcessorHandler(std::shared_ptr<IRequestProcessor> requestProcessor);

protected:
    /**
     * Binds methods handlers for GET and PUT requests
     */
    void initRestOpHandlers() override;

private:
    std::shared_ptr<IRequestProcessor> requestProcessor_;
};

#endif // BOOKINGSERVICEENGINE_H
