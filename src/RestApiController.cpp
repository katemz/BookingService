#include "RestApiController.hpp"

RestApiController::RestApiController(const std::string& naddress,const std::string& nport)
{
   endpointBuilder_.set_host(naddress);
   endpointBuilder_.set_port(nport);
   endpointBuilder_.set_scheme("http");
}

RestApiController::~RestApiController()
{
}

void RestApiController::setEndpoint(const std::string& mount_point)
{
    endpointBuilder_.set_path(mount_point);
    listener_ = http_listener(endpointBuilder_.to_uri());
}

pplx::task<void> RestApiController::accept()
{
    initRestOpHandlers();
    return listener_.open();
}
pplx::task<void> RestApiController::shutdown()
{
    return listener_.close();
}

std::vector<utility::string_t> RestApiController::requestPath(const http_request& message)
{
    auto relativePath = uri::decode(message.relative_uri().path());
    return uri::split_path(relativePath);
}
