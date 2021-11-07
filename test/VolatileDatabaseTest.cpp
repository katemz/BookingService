#include "gtest/gtest.h"
#include "VolatileDatabase.hpp"
#include "ExampleData.hpp"

#include <iostream>
#include <numeric>

class VolatileDatabaseTests : public ::testing::Test {
public:
    VolatileDatabaseTests( )
    {
        MOVIES_ = data_.getExampleMoviesList();
        THEATERS_ = data_.getExampleTheatersList();
        SEANCES_ = data_.getExampleSeancesList();
    }

    void SetUp( )
    {
        db_.reset();
        db_.addSeances(SEANCES_);
    }

    void TearDown( )
    {
    }

    ~VolatileDatabaseTests( )
    {
    }

    VolatileDatabase db_;
    ExampleData data_;

    std::vector<MovieName> MOVIES_;
    std::vector<TheaterName> THEATERS_;
    std::vector<Seance> SEANCES_;
};


TEST_F(VolatileDatabaseTests, getAllPlayingMoviesTest)
{
    auto allPlayingMovies = db_.getAllPlayingMovies();
    EXPECT_EQ(allPlayingMovies, MOVIES_);
}

TEST_F(VolatileDatabaseTests, getTheatersPlayingMovie)
{
    auto theaters = db_.getAllTheatersPlayingMovie(MOVIES_[0]);
    auto expected = std::vector<TheaterName>{THEATERS_[0], THEATERS_[2]};
    EXPECT_EQ(theaters, expected);

    theaters = db_.getAllTheatersPlayingMovie(MOVIES_[1]);
    expected = std::vector<TheaterName>{THEATERS_[0]};
    EXPECT_EQ(theaters, expected);

    theaters = db_.getAllTheatersPlayingMovie(MOVIES_[2]);
    expected = std::vector<TheaterName>{THEATERS_[0], THEATERS_[1]};
    EXPECT_EQ(theaters, expected);

    theaters = db_.getAllTheatersPlayingMovie(MOVIES_[3]);
    expected = std::vector<TheaterName>{THEATERS_[1], THEATERS_[2]};
    EXPECT_EQ(theaters, expected);
}

TEST_F(VolatileDatabaseTests, getSeatsForSeance_Empty)
{
    Seats emptySeats = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    EXPECT_EQ(emptySeats, db_.getSeatsForSeance(SEANCES_[0].movie_, SEANCES_[0].theater_));
    EXPECT_EQ(emptySeats, db_.getSeatsForSeance(SEANCES_[1].movie_, SEANCES_[1].theater_));
    EXPECT_EQ(emptySeats, db_.getSeatsForSeance(SEANCES_[2].movie_, SEANCES_[2].theater_));
}

TEST_F(VolatileDatabaseTests, getSeatsForSeance_NoSuchSeance)
{
    Seats noSeats = {};

    EXPECT_EQ(noSeats, db_.getSeatsForSeance("dune", "nosuchtheater"));
}

TEST_F(VolatileDatabaseTests, makeReservation)
{
    Seance seance = SEANCES_[0];
    EXPECT_EQ(true, db_.makeReservation(seance.movie_, seance.theater_, Seats{0, 1}));

    Seats seats = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(seance.movie_, seance.theater_));

    EXPECT_EQ(false, db_.makeReservation(seance.movie_, seance.theater_, Seats{0, 1}));
    EXPECT_EQ(seats, db_.getSeatsForSeance(seance.movie_, seance.theater_));

    EXPECT_EQ(true, db_.makeReservation(seance.movie_, seance.theater_, Seats{7, 8}));
    seats = {2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(seance.movie_, seance.theater_));

    EXPECT_EQ(false, db_.makeReservation(seance.movie_, seance.theater_, Seats{7, 8, 9}));
    seats = {2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(seance.movie_, seance.theater_));

    EXPECT_EQ(true, db_.makeReservation(seance.movie_, seance.theater_, Seats{10, 11, 12, 13}));
    seats = {2, 3, 4, 5, 6, 9, 14, 15, 16, 17, 18, 19};
    EXPECT_EQ(seats, db_.getSeatsForSeance(seance.movie_, seance.theater_));
}

