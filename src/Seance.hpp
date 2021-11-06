#ifndef SEANCE_HPP
#define SEANCE_HPP

#include "Movie.hpp"
#include "Theater.hpp"
#include <vector>
#include <list>
#include <array>

using SeanceId = uint16_t;
using Seats = std::list<uint16_t>;

struct Seance
{
    SeanceId id_;
    MovieName movie_;
    TheaterName theater_;
};

#endif // SEANCE_HPP
