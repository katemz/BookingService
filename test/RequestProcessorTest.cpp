#include "gtest/gtest.h"
#include "VolatileDatabase.hpp"
#include "RequestProcessor.hpp"
#include "ExampleData.hpp"
#include "DatabaseMock.hpp"

#include <iostream>
#include <numeric>

using ::testing::Return;

class RequestProcessorTests : public ::testing::Test {
public:
    RequestProcessorTests( )
    {
        dbMock_ = std::make_shared<DatabaseMock>();
        MOVIES_ = data_.getExampleMoviesList();
        THEATERS_ = data_.getExampleTheatersList();
        SEANCES_ = data_.getExampleSeancesList();
        rp_.setDatabaseHandler(dbMock_);
    }

    void SetUp( )
    {
    }

    void TearDown( )
    {
    }

    ~RequestProcessorTests( )
    {
    }

    std::shared_ptr<DatabaseMock> dbMock_;
    ExampleData data_;
    RequestProcessor rp_;

    std::vector<MovieName> MOVIES_;
    std::vector<TheaterName> THEATERS_;
    std::vector<Seance> SEANCES_;
};

TEST_F(RequestProcessorTests, GET_emptyPath)
{
    std::vector<std::string> path = {};
    json::value jsonReply;
    status_code status = rp_.handleGet(path, jsonReply);
    EXPECT_EQ(status, status_codes::BadRequest);
    EXPECT_EQ(jsonReply, json::value::null());
}

TEST_F(RequestProcessorTests, GET_getAllMovies)
{
    std::vector<std::string> path = {"getallmovies"};
    json::value jsonReply;

    EXPECT_CALL(*dbMock_, getAllPlayingMovies()).WillOnce(Return(MOVIES_));

    status_code status = rp_.handleGet(path, jsonReply);
    EXPECT_EQ(status, status_codes::OK);

    json::array jsonReplyAsArray = jsonReply["movies"].as_array();
    std::vector<MovieName> result;
    result.resize(jsonReplyAsArray.size());

    std::transform(jsonReplyAsArray.begin(), jsonReplyAsArray.end(), result.begin(),
                   [](json::value val) -> std::string { return val.as_string(); });
    EXPECT_EQ(result, MOVIES_);
}

TEST_F(RequestProcessorTests, GET_getTheatersPlayingMovie_noMoviePath)
{
    std::vector<std::string> path = {"gettheatersplayingmovie"};
    json::value jsonReply;

    status_code status = rp_.handleGet(path, jsonReply);
    EXPECT_EQ(status, status_codes::BadRequest);
    EXPECT_EQ(jsonReply, json::value::null());
}

TEST_F(RequestProcessorTests, GET_getTheatersPlayingMovie_dune)
{
    std::string movie = "dune";
    std::vector<std::string> path = {"gettheatersplayingmovie", movie};
    json::value jsonReply;

    EXPECT_CALL(*dbMock_, getAllTheatersPlayingMovie(movie)).WillOnce(Return(THEATERS_));

    status_code status = rp_.handleGet(path, jsonReply);
    EXPECT_EQ(status, status_codes::OK);

    json::array jsonReplyTheatersArray = jsonReply["theaters"].as_array();
    std::vector<TheaterName> result;
    result.resize(jsonReplyTheatersArray.size());

    std::transform(jsonReplyTheatersArray.begin(), jsonReplyTheatersArray.end(), result.begin(),
                   [](json::value val) -> std::string { return val.as_string(); });
    EXPECT_EQ(result, THEATERS_);
}

TEST_F(RequestProcessorTests, GET_getSeatsForSeance_invalidPath)
{
    std::vector<std::string> path = {"getseatsforseance"};
    json::value jsonReply;

    status_code status = rp_.handleGet(path, jsonReply);
    EXPECT_EQ(status, status_codes::BadRequest);
    EXPECT_EQ(jsonReply, json::value::null());

    path = {"getseatsforseance", "dune"};
    status = rp_.handleGet(path, jsonReply);
    EXPECT_EQ(status, status_codes::BadRequest);
    EXPECT_EQ(jsonReply, json::value::null());
}

TEST_F(RequestProcessorTests, GET_getSeatsForSeance_OK)
{
    std::vector<std::string> path = {"getseatsforseance", "dune", "cinemacity"};
    json::value jsonReply;

//    status_code status = rp_.handleGet(path, jsonReply);
//    EXPECT_EQ(status, status_codes::BadRequest);
//    EXPECT_EQ(jsonReply, json::value::null());
}


