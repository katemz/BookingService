#ifndef EXAMPLEDATA_HPP
#define EXAMPLEDATA_HPP

#include "Seance.hpp"
#include "utils.hpp"
#include <vector>


/**
 * This class returns sets of example data for testing
 */
class ExampleData
{
public:
    ExampleData();

    std::vector<MovieName> getExampleMoviesList() const;
    std::vector<TheaterName> getExampleTheatersList() const;
    std::vector<Seance> getExampleSeancesList() const;

private:
    std::vector<MovieName> movies_;
    std::vector<TheaterName> theatres_;
    std::vector<Seance> seances_;
};

#endif // EXAMPLEDATA_HPP
