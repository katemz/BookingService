#include "RequestProcessor.hpp"

RequestProcessor::RequestProcessor()
{
}

status_code RequestProcessor::handleGet(const std::vector<std::string>& path, json::value& jsonReply)
{
    jsonReply = json::value::null();

    if(path.empty())
    {
        return status_codes::BadRequest;
    }
    else if(path[0]=="getallmovies")
    {
        status_code status = handleGetAllMovies(jsonReply);
        return status;
    }
    else if(path[0]=="gettheatersplayingmovie")
    {
        status_code status = handleGetTheaterPlayingMovie(path, jsonReply);
        return status;
    }
    else if(path[0]=="getseatsforseance")
    {
        status_code status = handleGetSeatsForSeance(path, jsonReply);
        return status;
    }

    return status_codes::BadRequest;
}

status_code RequestProcessor::handlePut(const std::vector<std::string>& path, json::value jsonVal, json::value &jsonReply)
{
    if(path.empty())
    {
        return status_codes::BadRequest;
    }
    else if(path[0]=="reserve")
    {
        status_code status = handlePutReserve(jsonVal, jsonReply);
        return status;
    }

    return status_codes::BadRequest;
}


void RequestProcessor::setDatabaseHandler(std::shared_ptr<IDatabase> dbPtr)
{
    database_ = dbPtr;
}

status_code RequestProcessor::handleGetAllMovies(json::value& jsonReply)
{
    std::vector <json::value> jsonMovies;

    auto allPlayingMovies = database_->getAllPlayingMovies();

    for (const std::string& movie : allPlayingMovies)
    {
        jsonMovies.push_back(json::value(movie));
    }

    jsonReply["movies"] = json::value::array(jsonMovies);
    return status_codes::OK;
}

status_code RequestProcessor::handleGetTheaterPlayingMovie(const std::vector<std::string>& path, json::value& jsonReply)
{
    if (path.size() < 2)
    {
        return status_codes::BadRequest;
    }

    auto& movie = path[1];
    auto theaters = database_->getAllTheatersPlayingMovie(movie);

    std::vector <json::value> jsonTheaters;
    for (auto& theater: theaters)
        jsonTheaters.push_back(json::value(theater));

    jsonReply["movie"] = json::value(movie);
    jsonReply["theaters"] = json::value::array(jsonTheaters);
    return status_codes::OK;
}

status_code RequestProcessor::handleGetSeatsForSeance(const std::vector<std::string>& path, json::value& jsonReply)
{
    if (path.size() < 3)
    {
        return status_codes::BadRequest;
    }

    auto& movie = path[1];
    auto& theater = path[2];

    auto seatsVector = database_->getSeatsForSeance(movie, theater);

    std::vector <json::value> seatsJsonVector;
    for (auto& seat: seatsVector)
        seatsJsonVector.push_back(json::value(seat));

    jsonReply["movie"] = json::value(movie);
    jsonReply["theater"] = json::value(theater);
    jsonReply["available_seats"] = json::value::array(seatsJsonVector);
    return status_codes::OK;
}

status_code RequestProcessor::handlePutReserve(json::value jsonVal, json::value& jsonReply)
{
    try
    {
        std::string movie = jsonVal[U("movie")].as_string();
        std::string theater = jsonVal[U("theater")].as_string();
        json::array seatsJsonVector = jsonVal[U("seats")].as_array();

        std::list <uint16_t> seatsUintVector;
        for (auto& seat: seatsJsonVector)
        {
            seatsUintVector.push_back(seat.as_integer());
            std::cout << "," << seat.as_integer() << std::endl;
        }

        bool success = database_->makeReservation(movie, theater, seatsUintVector);

        if (success)
        {
            return status_codes::OK;
        }
        else
        {
            //todo add error des
            return status_codes::InternalError;
        }

    }
    catch(std::exception& e)
    {
        return status_codes::BadRequest;
    }
}

