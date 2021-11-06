#ifndef IDATABASE_HPP
#define IDATABASE_HPP

#include <vector>
#include "Movie.hpp"
#include "Theater.hpp"
#include "Seance.hpp"

/**
 * Interface class for Booking Service database operations
 */
class IDatabase
{
public:
    /**
     * Returns all movies played in theaters
     * @return vector of movie names
     */
    virtual std::vector<MovieName> getAllPlayingMovies() = 0;

    /**
     * Returns all theaters that play specified movie
     * @param movie - name of the movie
     * @return vector of theater names
     */
    virtual std::vector<TheaterName> getAllTheatersPlayingMovie(const MovieName& movie) = 0;

    /**
     * Returns all available seats numbers for the seance specified by movie and theater name
     * @param movie - name of the movie
     * @param theater - name of the theater
     * @return List of available seats numbers (eg. {4,5,6})
     */
    virtual Seats getSeatsForSeance(const MovieName& movie, const TheaterName& theater) = 0;

    /**
     * Makes reservation for seance specified by movie and theater name
     * @param movie - name of the movie
     * @param theater - name of the theater
     * @param seats - list of number of seats to be reserved (eg. {4,5,6})
     * @return True if reservation was successful; false otherwise
     */
    virtual bool makeReservation(const MovieName& movie, const TheaterName& theater, const Seats& seats) = 0;

    virtual ~IDatabase(){}
};

#endif // IDATABASE_HPP
