#include "gtest/gtest.h"
#include "VolatileDatabase.hpp"
#include "ExampleData.hpp"

#include <iostream>
#include <numeric>

class VolatileDatabaseTests : public ::testing::Test {
public:
    VolatileDatabaseTests( )
    {
    }

    void SetUp( )
    {
        db_.reset();
        db_.addSeances(data_.getExampleSeancesList());
    }

    void TearDown( )
    {
    }

    ~VolatileDatabaseTests( )
    {
    }

    VolatileDatabase db_;
    ExampleData data_;
};


TEST_F(VolatileDatabaseTests, getAllPlayingMoviesTest)
{
    auto allPlayingMovies = db_.getAllPlayingMovies();
    EXPECT_EQ(allPlayingMovies, data_.getExampleMoviesList());
}

//TEST_F(VolatileDatabaseTests, getTheatersPlayingMovie)
//{
//    auto theaters = db_.getAllTheatersPlayingMovie(ALL_MOVIES[0]);
//    auto expected = std::vector<Theater>{ALL_THEATERS[0], ALL_THEATERS[2]};
//    EXPECT_EQ(theaters, expected);

//    theaters = db_.getAllTheatersPlayingMovie(ALL_MOVIES[1]);
//    expected = std::vector<Theater>{ALL_THEATERS[0]};
//    EXPECT_EQ(theaters, expected);

//    theaters = db_.getAllTheatersPlayingMovie(ALL_MOVIES[2]);
//    expected = std::vector<Theater>{ALL_THEATERS[0], ALL_THEATERS[1]};
//    EXPECT_EQ(theaters, expected);

//    theaters = db_.getAllTheatersPlayingMovie(ALL_MOVIES[3]);
//    expected = std::vector<Theater>{ALL_THEATERS[1], ALL_THEATERS[2]};
//    EXPECT_EQ(theaters, expected);
//}

TEST_F(VolatileDatabaseTests, getSeatsForSeance_Empty)
{
    Seats emptySeats = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    EXPECT_EQ(emptySeats, db_.getSeatsForSeance(0));
    EXPECT_EQ(emptySeats, db_.getSeatsForSeance(1));
    EXPECT_EQ(emptySeats, db_.getSeatsForSeance(6));
}

TEST_F(VolatileDatabaseTests, makeReservation)
{
    EXPECT_EQ(true, db_.makeReservation(SeanceId(0), Seats{0, 1}));

    Seats seats = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(0));

    EXPECT_EQ(false, db_.makeReservation(SeanceId(0), Seats{0, 1}));
    EXPECT_EQ(seats, db_.getSeatsForSeance(0));

    EXPECT_EQ(true, db_.makeReservation(SeanceId(0), Seats{7, 8}));
    seats = {2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(0));

    EXPECT_EQ(false, db_.makeReservation(SeanceId(0), Seats{7, 8, 9}));
    seats = {2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(0));

    EXPECT_EQ(true, db_.makeReservation(SeanceId(0), Seats{10, 11, 12, 13}));
    seats = {2, 3, 4, 5, 6, 9, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(0));
}

