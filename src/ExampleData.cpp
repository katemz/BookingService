#include "ExampleData.hpp"

#include <algorithm>

ExampleData::ExampleData()
{
    movies_ = {
        "dune",
        "mrhyde",
        "batman",
        "spiderman",
        "gonewiththewind",
        "yesman"
    };

    std::sort(movies_.begin(), movies_.end());

    theatres_ = {
            "cinemacity",
            "helios",
            "nowehoryzonty"};

    std::sort(theatres_.begin(), theatres_.end());

    seances_ = {
            Seance{0, movies_[1], theatres_[0]},
            Seance{1, movies_[0], theatres_[0]},
            Seance{2, movies_[2], theatres_[0]},
            Seance{3, movies_[2], theatres_[1]},
            Seance{4, movies_[0], theatres_[2]},
            Seance{5, movies_[3], theatres_[2]},
            Seance{6, movies_[3], theatres_[1]},
            Seance{7, movies_[4], theatres_[1]},
            Seance{8, movies_[4], theatres_[2]},
            Seance{9, movies_[5], theatres_[0]}
        };
}

std::vector<MovieName> ExampleData::getExampleMoviesList() const
{
    return movies_;
}

std::vector<TheaterName> ExampleData::getExampleTheatersList() const
{
    return theatres_;
}

std::vector<Seance> ExampleData::getExampleSeancesList() const
{
    return seances_;
}
