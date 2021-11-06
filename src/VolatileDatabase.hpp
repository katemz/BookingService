#ifndef VOLATILEDATABASE_HPP
#define VOLATILEDATABASE_HPP

#include <vector>
#include "Movie.hpp"
#include "Theater.hpp"
#include "Seance.hpp"
#include "IDatabase.hpp"
#include <numeric>

#include <set>
#include <map>
#include <string>

class VolatileDatabase : public IDatabase
{
public:
    VolatileDatabase();

    std::vector<MovieName> getAllPlayingMovies() override;
    std::vector<TheaterName> getAllTheatersPlayingMovie(const MovieName& movie) override;
    Seats getSeatsForSeance(SeanceId id) override;

    bool makeReservation(SeanceId id, const Seats& seats) override;

    void reset();
    void clearCache();

    void addSeances(const std::vector<Seance>& seances);

protected:
    std::vector<Seance> seances_;
    std::map<SeanceId, Seats> reservations_;


    // Cache should be cleared on every theater program update
    std::vector<MovieName> cachedAllMovies_;
    std::map<MovieName, std::vector<TheaterName>> cachedMoviesToTheaterListMap_;
};

#endif // VOLATILEDATABASE_HPP
