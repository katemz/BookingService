#include "BookingServiceEngine.hpp"

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

    if(path.empty())
    {
        message.reply(status_codes::BadRequest);
    }
    else if(path[0]=="getallmovies")
    {
        std::vector <json::value> jsonMovies;

        auto allPlayingMovies = database_->getAllPlayingMovies();

        for (const std::string& movie : allPlayingMovies)
        {
            jsonMovies.push_back(json::value(movie));
        }

        json::value jsonReply;
        jsonReply["movies"] = json::value::array(jsonMovies);
        message.reply(status_codes::OK, jsonReply);
    }
    else if(path[0]=="gettheatersplayingmovie")
    {
        auto& movie = path[1];
        auto theaters = database_->getAllTheatersPlayingMovie(movie);
        std::vector <json::value> jsonTheaters;
        //jsonTheaters.push_back(json::value("uberkino"));
        for (auto& t: theaters)
            jsonTheaters.push_back(json::value(t));
        json::value jsonReply;
        jsonReply["movie"] = json::value(movie);
        jsonReply["theaters"] = json::value::array(jsonTheaters);
        message.reply(status_codes::OK, jsonReply);
    }
    else if(path[0]=="getSeatForSeanse")
    {
        auto& movie = path[1];
        auto& theather = path[2];
        json::value jsonReply;
        jsonReply["movie"] = json::value(movie);
        jsonReply["theater"] = json::value(theather);
        message.reply(status_codes::OK, jsonReply);
    }
    else
    {
        message.reply(status_codes::BadRequest);
    }
}

void BookingServiceEngine::handlePut(http_request message)
{
    message.extract_json().then([=](pplx::task<json::value> task)
    {
        std::cout << "handlePut" << std::endl;
        try
        {
            message.reply(status_codes::OK);
        }
        catch(std::exception& e)
        {
            message.reply(status_codes::BadRequest);
        }
    });
}

void BookingServiceEngine::setDatabaseHandler(std::shared_ptr<IDatabase> dbPtr)
{
    database_ = dbPtr;
}

