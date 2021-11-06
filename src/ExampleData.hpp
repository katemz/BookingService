#ifndef EXAMPLEDATA_HPP
#define EXAMPLEDATA_HPP

#include "Movie.hpp"
#include "Theater.hpp"
#include "Seance.hpp"

#include <vector>

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
