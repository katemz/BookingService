#ifndef IDATABASE_HPP
#define IDATABASE_HPP

#include <vector>
#include <set>
#include <array>
#include "Movie.hpp"
#include "Theater.hpp"
#include "Seance.hpp"

class IDatabase
{
public:
    virtual std::vector<MovieName> getAllPlayingMovies() = 0;
    virtual std::vector<TheaterName> getAllTheatersPlayingMovie(const MovieName& movie) = 0;
    virtual Seats getSeatsForSeance(SeanceId id) = 0;

    virtual bool makeReservation(SeanceId id, const Seats& seats) = 0;
};

#endif // IDATABASE_HPP
