#include "VolatileDatabase.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include "utils.hpp"
#include <numeric>

VolatileDatabase::VolatileDatabase()
    : seances_(),
      availableSeats_(),
      cachedAllMovies_(),
      cachedMoviesToTheaterListMap_()
{
}

std::vector<MovieName> VolatileDatabase::getAllPlayingMovies()
{
    if (cachedAllMovies_.empty())
    {
        std::set<MovieName> moviesWithoutDups;

        for (const auto& seance : seances_)
        {
            moviesWithoutDups.insert(seance.movie_);
        }

        std::copy(moviesWithoutDups.begin(), moviesWithoutDups.end(), std::back_inserter(cachedAllMovies_));
        std::sort(cachedAllMovies_.begin(), cachedAllMovies_.end());
    }

    return cachedAllMovies_;
}

std::vector<TheaterName> VolatileDatabase::getAllTheatersPlayingMovie(const MovieName &movie)
{
    MovieName movieNameLower = utils::toLower(movie);

    if (cachedMoviesToTheaterListMap_.empty())
    {
        for (const auto& seance : seances_)
        {
            if (cachedMoviesToTheaterListMap_.find(seance.movie_) == cachedMoviesToTheaterListMap_.end())
            {
                cachedMoviesToTheaterListMap_[seance.movie_] = {seance.theater_};
            }
            else
            {
                cachedMoviesToTheaterListMap_[seance.movie_].push_back(seance.theater_);
            }
        }

        for (auto& e : cachedMoviesToTheaterListMap_)
        {
            std::sort(e.second.begin(), e.second.end());
        }
    }

    std::vector<TheaterName> theatersList;
    if (cachedMoviesToTheaterListMap_.find(movieNameLower) != cachedMoviesToTheaterListMap_.end())
    {
        theatersList = cachedMoviesToTheaterListMap_[movieNameLower];
    }

    return theatersList;
}

SeanceId VolatileDatabase::seanceIdForMovieInTheater(const MovieName& movie, const TheaterName& theater) const
{
    auto it = std::find_if(seances_.begin(), seances_.end(),
                           [&] (const Seance& s) { return ((s.movie_ == movie) && (s.theater_ == theater)); } );

    SeanceId id = INVALID_ID;
    if (it != seances_.end())
    {
        id = it->id_;
    }
    return id;
}

bool VolatileDatabase::makeReservation(const MovieName& movie, const TheaterName& theater, const Seats& seats)
{
    const std::lock_guard<std::mutex> lock(dbReserveMutex_);

    SeanceId id = seanceIdForMovieInTheater(movie, theater);

    if (id == INVALID_ID)
    {
        std::cout << "Error: no such seance. Reservation failed" << std::endl;
        return false;
    }

    // ensure no duplicates in request

    Seats availableSeatsForSeance = availableSeats_[id];
    Seats successfullyReserved;

    for (const uint16_t& seatId : seats)
    {
        auto seatPositionInAvailableList = std::find(availableSeatsForSeance.begin(), availableSeatsForSeance.end(), seatId);

        if(seatPositionInAvailableList != availableSeatsForSeance.end() )
        {
            availableSeatsForSeance.remove(seatId);
            successfullyReserved.push_back(seatId);
        }
        else
        {
            std::cout << "Seat id: " << seatId << " is already taken; error " << std::endl;
            return false;
        }
    }
    availableSeats_[id] = availableSeatsForSeance;
    return true;
}

Seats VolatileDatabase::getSeatsForSeance(const MovieName& movie, const TheaterName& theater)
{
    SeanceId id = seanceIdForMovieInTheater(movie, theater);

    if (id == INVALID_ID)
    {
        std::cout << "Error: no such seance" << std::endl;
        return Seats();
    }

    if (availableSeats_.find(id) == availableSeats_.end())
    {
        return Seats();
    }

    return availableSeats_[id];
}

void VolatileDatabase::reset()
{
    seances_.clear();

    clearCache();
}

void VolatileDatabase::clearCache()
{
    cachedAllMovies_.clear();
    cachedMoviesToTheaterListMap_.clear();
}

void VolatileDatabase::addSeances(const std::vector<Seance>& seances)
{
    clearCache();

    for ( const auto& seance : seances)
    {
        Seance s = seance;
        MovieName movieName = utils::toLower(seance.movie_);
        TheaterName theaterName = utils::toLower(seance.theater_);

        s.movie_= movieName;
        s.theater_ = theaterName;

        seances_.push_back(s);

        availableSeats_[s.id_] = Seats(SEATS_COUNT);
        std::iota(availableSeats_[s.id_].begin(), availableSeats_[s.id_].end(), 0);
    }
}
