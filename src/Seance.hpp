#ifndef SEANCE_HPP
#define SEANCE_HPP

#include "utils.hpp"
#include <vector>
#include <list>
#include <array>

using SeanceId = int16_t;
using Seats = std::list<uint16_t>;

static constexpr SeanceId INVALID_ID = -1;
static constexpr uint16_t SEATS_COUNT = 20;

struct Seance
{
    SeanceId id_;
    MovieName movie_;
    TheaterName theater_;
};

#endif // SEANCE_HPP
