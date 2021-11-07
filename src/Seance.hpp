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

/**
 * @brief This struct represent the seance entity
 */
struct Seance
{
    /**
     * @brief Unique id
     */
    SeanceId id_;

    /**
     * @brief Movie played during seance
     */
    MovieName movie_;

    /**
     * @brief Theater that plays the movie
     */
    TheaterName theater_;
};

#endif // SEANCE_HPP
