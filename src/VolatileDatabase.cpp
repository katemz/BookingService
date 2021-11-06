#include "VolatileDatabase.hpp"
#include <iostream>
#include <algorithm>

VolatileDatabase::VolatileDatabase()
    : seances_(),
      cachedAllMovies_()
{

}

std::vector<MovieName> VolatileDatabase::getAllPlayingMovies()
{
    if (cachedAllMovies_.empty())
    {
        std::set<MovieName> moviesWithoutDups;

        for (const auto& seance : seances_)
        {
            moviesWithoutDups.insert(seance.movie_.name_);
        }

        std::copy(moviesWithoutDups.begin(), moviesWithoutDups.end(), std::back_inserter(cachedAllMovies_));
        std::sort(cachedAllMovies_.begin(), cachedAllMovies_.end());
    }

    return cachedAllMovies_;
}

std::vector<TheaterName> VolatileDatabase::getAllTheatersPlayingMovie(const MovieName &movie)
{
    if (cachedMoviesToTheaterListMap_.empty())
    {
        for (const auto& seance : seances_)
        {
            if (cachedMoviesToTheaterListMap_.find(seance.movie_.name_) == cachedMoviesToTheaterListMap_.end())
            {
                cachedMoviesToTheaterListMap_[seance.movie_.name_] = {seance.theater_.name_};
            }
            else
            {
                cachedMoviesToTheaterListMap_[seance.movie_.name_].push_back(seance.theater_.name_);
            }
        }

            std::cout << "Theaters";
            for (auto& theater : cachedMoviesToTheaterListMap_[movie])
            {
                std::cout << theater;
            }

//        for (auto& movieAndTheaterList : cachedMoviesToTheaterListMap_)
//        {
//            std::sort(movieAndTheaterList.second.begin(), movieAndTheaterList.second.end());
//        }
    }

//    std::cout << "Theaters";
//    for (auto& theater : cachedMoviesToTheaterListMap_[movie])
//    {
//        std::cout << theater;
//    }
    return cachedMoviesToTheaterListMap_[movie];
}

Seats VolatileDatabase::getSeatsForSeance(SeanceId id)
{
    // range check
    return reservations_[id];
}

bool VolatileDatabase::makeReservation(SeanceId id, const Seats& seats)
{
   // ensure no duplicates in request

    Seats availableSeatsForSeance = reservations_[id];
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
    reservations_[id] = availableSeatsForSeance;
    return true;
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
