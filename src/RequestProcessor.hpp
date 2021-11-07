#ifndef REQUESTPROCESSOR_HPP
#define REQUESTPROCESSOR_HPP

#include <cpprest/http_msg.h>
#include <vector>
#include <string>
#include <pplx/pplxtasks.h>
#include <memory>
#include "IDatabase.hpp"
#include "IRequestProcessor.hpp"

using namespace web;
using namespace http;

class RequestProcessor : public IRequestProcessor
{
public:
    RequestProcessor();

    status_code handleGet(const std::vector<std::string>& path, json::value& jsonReply);
    status_code handlePut(const std::vector<std::string>& path, json::value jsonVal, json::value& jsonReply);
    void setDatabaseHandler(std::shared_ptr<IDatabase> dbPtr);

private:
    status_code handleGetAllMovies(json::value& jsonReply);
    status_code handleGetTheaterPlayingMovie(const std::vector<std::string>& path, json::value& jsonReply);
    status_code handleGetSeatsForSeance(const std::vector<std::string>& path, json::value& jsonReply);
    status_code handlePutReserve(json::value jsonVal, json::value& jsonReply);

   std::shared_ptr<IDatabase> database_;
};

#endif // REQUESTPROCESSOR_HPP
