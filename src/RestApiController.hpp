#ifndef RESTAPICONTROLLER_H
#define RESTAPICONTROLLER_H

#include <cpprest/http_listener.h>
#include <pplx/pplxtasks.h>
#include <string>
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;
using namespace http::experimental::listener;

class RestApiController
{
public:
    RestApiController(const std::string& address, const std::string& port);
    virtual ~RestApiController();

    void setEndpoint(const std::string& mountPoint);
    std::string endpoint() const;
    pplx::task<void> accept();
    pplx::task<void> shutdown();

    virtual void initRestOpHandlers() = 0;

    std::vector<utility::string_t> requestPath(const http_request & message);

protected:
    http_listener listener_;
private:
    uri_builder endpointBuilder_;
};

#endif // RESTAPICONTROLLER_H