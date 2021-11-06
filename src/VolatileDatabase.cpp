#include "VolatileDatabase.hpp"
#include <iostream>
#include <algorithm>
#include <string>
#include <set>
#include "utils.hpp"
#include <numeric>

VolatileDatabase::VolatileDatabase()
    : seances_(),
      availableSeats(),
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
    std::cout << "Get all theaters playing movie: " << movie << std::endl;

    MovieName movieNameLower = movie;

    std::transform(movieNameLower.begin(),
                   movieNameLower.end(),
                   movieNameLower.begin(),
                   ::tolower);


    if (cachedMoviesToTheaterListMap_.empty())
    {
        std::cout << "Cache is empty... searching " << std::endl;

        for (const auto& seance : seances_)
        {
            std::cout << "Seance: " << seance.movie_ << " in " << seance.theater_ << std::endl;

            if (cachedMoviesToTheaterListMap_.find(seance.movie_) == cachedMoviesToTheaterListMap_.end())
            {
                std::cout << "Not yet in cache: adding " << std::endl;
                cachedMoviesToTheaterListMap_[seance.movie_] = {seance.theater_};
            }
            else
            {
                std::cout << "Already in cache: append " << std::endl;
                cachedMoviesToTheaterListMap_[seance.movie_].push_back(seance.theater_);
            }
        }

        for (auto& e : cachedMoviesToTheaterListMap_)
        {
            std::sort(e.second.begin(), e.second.end());
        }

    }

    std::cout << "map size : " << cachedMoviesToTheaterListMap_.size() << std::endl;


    for (const auto& elem : cachedMoviesToTheaterListMap_)
    {
        std::cout << "Movie: " << elem.first << " is played in:\n ";

        for (const auto& th : elem.second)
        {
            std::cout << "         " << th << std::endl;
        }
    }
    std::cout << std::endl;

    std::vector<TheaterName> theaterList;
    if (cachedMoviesToTheaterListMap_.find(movieNameLower) != cachedMoviesToTheaterListMap_.end())
    {
        theaterList = cachedMoviesToTheaterListMap_[movieNameLower];
    }
    return theaterList;

}

//Seats VolatileDatabase::getSeatsForSeance(SeanceId id)
//{
//    // range check
//    return reservations_[id];
//}

SeanceId VolatileDatabase::seanceIdForMovieInTheater(const MovieName& movie, const TheaterName& theater) const
{
    auto it = std::find_if(seances_.begin(), seances_.end(),
                           [&] (const Seance& s) { return ((s.movie_ == movie) && (s.theater_ == theater)); } );

    SeanceId id = -1;
    if (it != seances_.end())
    {
        id = it->id_;
    }
    return id;
}

bool VolatileDatabase::makeReservation(const MovieName& movie, const TheaterName& theater, const Seats& seats)
{
    SeanceId id = seanceIdForMovieInTheater(movie, theater);

    if (id == INVALID_ID)
    {
        std::cout << "Error: no such seance. Reservation failed" << std::endl;
        return false;
    }

    // ensure no duplicates in request

    Seats availableSeatsForSeance = availableSeats[id];
    Seats successfullyReserved;


    for (const uint16_t& seatId : seats)
    {
        auto seatPositionInAvailableList = std::find(availableSeatsForSeance.begin(), availableSeatsForSeance.end(), seatId);

        if(seatPositionInAvailableList != availableSeatsForSeance.end() )
        {
            std::cout << "Seat id: " << seatId << " is available " << std::endl;
            availableSeatsForSeance.remove(seatId);
            successfullyReserved.push_back(seatId);
        }
        else
        {
            std::cout << "Seat id: " << seatId << " is already taken; error " << std::endl;
            return false;
        }
    }
    availableSeats[id] = availableSeatsForSeance;
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

    if (availableSeats.find(id) == availableSeats.end())
    {
       return Seats();
    }

    return availableSeats[id];
}

//bool VolatileDatabase::makeReservation(SeanceId id, const Seats& seats)
//{
//    // ensure no duplicates in request

//    Seats availableSeatsForSeance = reservations_[id];
//    Seats successfullyReserved;


//    for (const uint16_t& seatId : seats)
//    {
//        auto seatPositionInAvailableList = std::find(availableSeatsForSeance.begin(), availableSeatsForSeance.end(), seatId);

//        if(seatPositionInAvailableList != availableSeatsForSeance.end() )
//        {
//            std::cout << "Seat id: " << seatId << " is available " << std::endl;
//            availableSeatsForSeance.remove(seatId);
//            successfullyReserved.push_back(seatId);
//        }
//        else
//        {
//            std::cout << "Seat id: " << seatId << " is already taken; error " << std::endl;
//            return false;
//        }
//    }
//    reservations_[id] = availableSeatsForSeance;
//    return true;
//}

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

        availableSeats[s.id_] = Seats(SEATS_COUNT);
        std::iota(availableSeats[s.id_].begin(), availableSeats[s.id_].end(), 0);
    }
}
