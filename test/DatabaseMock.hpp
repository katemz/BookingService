#ifndef DATABASEMOCK_HPP
#define DATABASEMOCK_HPP

#include "IDatabase.hpp"

#include "gmock/gmock.h"

class DatabaseMock : public IDatabase {
public:
    MOCK_METHOD(std::vector<MovieName>, getAllPlayingMovies, (), (override));
    MOCK_METHOD(std::vector<TheaterName>, getAllTheatersPlayingMovie, (const MovieName& movie), (override));
    MOCK_METHOD(Seats, getSeatsForSeance, (const MovieName& movie, const TheaterName& theater), (override));
    MOCK_METHOD(bool, makeReservation, (const MovieName& movie, const TheaterName& theater, const Seats& seats), (override));
};

#endif // DATABASEMOCK_HPP

