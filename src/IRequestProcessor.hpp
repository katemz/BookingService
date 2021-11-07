#ifndef IREQUESTPROCESSOR_HPP
#define IREQUESTPROCESSOR_HPP

#include <string>
//#include <pplx/pplxtasks.h>
//#include <memory>
#include <cpprest/http_msg.h>
#include <vector>
#include "IDatabase.hpp"

using namespace web;
using namespace http;

class IRequestProcessor
{
public:
    virtual ~IRequestProcessor(){}
    virtual status_code handleGet(const std::vector<std::string>& path, json::value& jsonReply) = 0;
    virtual status_code handlePut(const std::vector<std::string>& path, json::value jsonVal, json::value& jsonReply) = 0;
};


#endif // IREQUESTPROCESSOR_HPP
