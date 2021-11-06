#ifndef SEANCE_HPP
#define SEANCE_HPP

#include "Movie.hpp"
#include "Theater.hpp"
#include <vector>
#include <list>
#include <array>

using SeanceId = int16_t;
using Seats = std::list<uint16_t>;

constexpr SeanceId INVALID_ID = -1;

struct Seance
{
    SeanceId id_;
    MovieName movie_;
    TheaterName theater_;
};

#endif // SEANCE_HPP
