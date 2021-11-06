#ifndef VOLATILEDATABASE_HPP
#define VOLATILEDATABASE_HPP

#include <vector>
#include <map>
#include <string>
#include "Movie.hpp"
#include "Theater.hpp"
#include "Seance.hpp"
#include "IDatabase.hpp"

/**
 * Class implementing database operations for Booking Service.
 * Data will not be persistent between runs.
 */
class VolatileDatabase : public IDatabase
{
public:
    /**
     * Constructor
     */
    VolatileDatabase();

    /**
     * Returns all movies played in theaters
     * @return vector of movie names
     */
    std::vector<MovieName> getAllPlayingMovies() override;

    /**
     * Returns all theaters that play specified movie
     * @param movie - name of the movie
     * @return vector of theater names
     */
    std::vector<TheaterName> getAllTheatersPlayingMovie(const MovieName& movie) override;

    /**
     * Returns all available seats numbers for the seance specified by movie and theater name
     * @param movie - name of the movie
     * @param theater - name of the theater
     * @return List of available seats numbers (eg. {4,5,6})
     */
    Seats getSeatsForSeance(const MovieName& movie, const TheaterName& theater) override;

    /**
     * Makes reservation for seance specified by movie and theater name
     * @param movie - name of the movie
     * @param theater - name of the theater
     * @param seats - list of number of seats to be reserved (eg. {4,5,6})
     * @return True if reservation was successful; false otherwise
     */
    bool makeReservation(const MovieName& movie, const TheaterName& theater, const Seats& seats) override;

    /**
     * Clears all data and cache
     */
    void reset();

    /**
     * Insert new seances into database
     * All seats are available for new inserted seances
     * After this operation the cache will be cleaned
     */
    void addSeances(const std::vector<Seance>& seances);

protected:
    /**
     * Clears cache
     */
    void clearCache();

    /**
     * Returns SeanceId for specified movie and theater
     * @param movie - name of the movie
     * @param theater - name of the theater
     * @return SeanceId - valid id if seance was found in database, -1 otherwise
     */
    SeanceId seanceIdForMovieInTheater(const MovieName& movie, const TheaterName& theater) const;

    /**
     * All seances available
     */
    std::vector<Seance> seances_;

    /**
     * Available seats for seance
     */
    std::map<SeanceId, Seats> availableSeats;

    /**
     * Cached list of all played movies
     * This list should be cleared with clearCache when seances_ list is updated
     */
    std::vector<MovieName> cachedAllMovies_;

    /**
     * Cached list of all theaters that play specified movie
     * This list should be cleared with clearCache when seances_ list is updated
     */
    std::map<MovieName, std::vector<TheaterName>> cachedMoviesToTheaterListMap_;
};

#endif // VOLATILEDATABASE_HPP
