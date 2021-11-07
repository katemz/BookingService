#ifndef IREQUESTPROCESSOR_HPP
#define IREQUESTPROCESSOR_HPP

#include <string>
#include <cpprest/http_msg.h>
#include <vector>
#include "IDatabase.hpp"

using namespace web;
using namespace http;

/**
 * Interface class for request processing object
 */
class IRequestProcessor
{
public:
    virtual ~IRequestProcessor(){}

    /**
     * Process the GET request
     * @param path - request URL path
     * @param jsonReply - json object that will be filled with response data
     * @return status_code - status_codes::OK if request was valid, status_codes::BadRequest otherwise
     */
    virtual status_code handleGet(const std::vector<std::string>& path, json::value& jsonReply) = 0;

    /**
     * Process the PUT request
     * @param path - request URL path
     * @param jsonVal - json object with request data
     * @param jsonReply - json object that will be filled with response data
     * @return status_code - status_codes::OK if request was valid and succeeded, status_codes::BadRequest otherwise
     */
    virtual status_code handlePut(const std::vector<std::string>& path, json::value jsonVal, json::value& jsonReply) = 0;
};


#endif // IREQUESTPROCESSOR_HPP
