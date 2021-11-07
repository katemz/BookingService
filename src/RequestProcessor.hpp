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

/**
 * Class for processing HTTP requests
 */
class RequestProcessor : public IRequestProcessor
{
public:
    RequestProcessor();

    /**
     * Process the GET request
     * @param path - request URL path
     * @param jsonReply - json object that will be filled with response data
     * @return status_code - status_codes::OK if request was valid, status_codes::BadRequest otherwise
     */
    status_code handleGet(const std::vector<std::string>& path, json::value& jsonReply);

    /**
     * Process the PUT request
     * @param path - request URL path
     * @param jsonVal - json object with request data
     * @param jsonReply - json object that will be filled with response data
     * @return status_code - status_codes::OK if request was valid and succeeded, status_codes::BadRequest otherwise
     */
    status_code handlePut(const std::vector<std::string>& path, json::value jsonVal, json::value& jsonReply);

    /**
     * Sets the database handler
     * @param dbPtr - database to be used for requests processing
     */
    void setDatabaseHandler(std::shared_ptr<IDatabase> dbPtr);

private:
    status_code handleGetAllMovies(json::value& jsonReply);
    status_code handleGetTheaterPlayingMovie(const std::vector<std::string>& path, json::value& jsonReply);
    status_code handleGetSeatsForSeance(const std::vector<std::string>& path, json::value& jsonReply);
    status_code handlePutReserve(json::value jsonVal, json::value& jsonReply);

   std::shared_ptr<IDatabase> database_;
};

#endif // REQUESTPROCESSOR_HPP
