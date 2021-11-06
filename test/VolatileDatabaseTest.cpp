#include "gtest/gtest.h"
#include "VolatileDatabase.hpp"

#include <iostream>
#include <numeric>

const std::vector<Movie> ALL_MOVIES = {
    Movie{0, "Dune"},
    Movie{1, "MrHyde"},
    Movie{2, "Batman"},
    Movie{3, "Spiderman"}};

const std::vector<Theater> ALL_THEATERS = {
    Theater{0, "NoweHoryzonty"},
    Theater{1, "Helios"},
    Theater{2, "CinemaCity"}};

const std::vector<Seance> ALL_SEANCES = {
    Seance{0, ALL_MOVIES[1], ALL_THEATERS[0]},
    Seance{1, ALL_MOVIES[0], ALL_THEATERS[0]},
    Seance{2, ALL_MOVIES[2], ALL_THEATERS[0]},
    Seance{3, ALL_MOVIES[2], ALL_THEATERS[1]},
    Seance{4, ALL_MOVIES[0], ALL_THEATERS[2]},
    Seance{5, ALL_MOVIES[3], ALL_THEATERS[2]},
    Seance{6, ALL_MOVIES[3], ALL_THEATERS[1]}
};


class VolatileDatabaseWithData : public VolatileDatabase
{
public:
    void addSeances(const std::vector<Seance>& seances)
    {
        for (const auto& seance : seances)
        {
            seances_.push_back(seance);
            reservations_[seance.id_] = Seats(SEATS_COUNT);
            std::iota(reservations_[seance.id_].begin(), reservations_[seance.id_].end(), 0);
        }
    }

};


class VolatileDatabaseTests : public ::testing::Test {
public:
    VolatileDatabaseTests( )
    {
        // initialization code here
    }

    void SetUp( )
    {
        db_.reset();
        db_.addSeances(ALL_SEANCES);
    }

    void TearDown( )
    {
    }

    ~VolatileDatabaseTests( )
    {
    }

    VolatileDatabaseWithData db_;
};


//TEST_F(VolatileDatabaseTests, getAllPlayingMoviesTest)
//{
//    auto allPlayingMovies = db_.getAllPlayingMovies();
//    EXPECT_EQ(allPlayingMovies, ALL_MOVIES);
//}

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

