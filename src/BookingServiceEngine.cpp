#include "BookingServiceEngine.hpp"
#include "utils.hpp"

BookingServiceEngine::BookingServiceEngine(const std::string &address, const std::string &port)
    :  RestApiController(address,port)
{
}

BookingServiceEngine::~BookingServiceEngine()
{
}

void BookingServiceEngine::initRestOpHandlers()
{
    listener_.support(methods::GET,std::bind(&BookingServiceEngine::handleGet,this,std::placeholders::_1));
    listener_.support(methods::PUT,std::bind(&BookingServiceEngine::handlePut,this,std::placeholders::_1));
}

void BookingServiceEngine::handleGet(http_request message)
{
    std::vector<std::string> path = requestPath(message);

    json::value jsonReply;
    status_code status = requestProcessor_->handleGet(path, jsonReply);
    message.reply(status, jsonReply);
}

void BookingServiceEngine::handlePut(http_request message)
{
    std::vector<std::string> path = requestPath(message);

    message.extract_json().then([=](pplx::task<json::value> task)
    {
        json::value jsonReply; // todo: write reply
        status_code status = requestProcessor_->handlePut(path, task.get(), jsonReply);
        message.reply(status, jsonReply);
    });
}

void BookingServiceEngine::setRequestProcessorHandler(std::shared_ptr<IRequestProcessor> rpPtr)
{
    requestProcessor_ = rpPtr;
}

