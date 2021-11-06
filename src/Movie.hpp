#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <string>
#include <iostream>

using MovieName = std::string;

struct Movie
{
    uint16_t id_;
    MovieName name_;
};



inline bool operator==(const Movie& lhs, const Movie& rhs)
{
    return (lhs.id_ == rhs.id_);
}

inline bool operator<(const Movie& lhs, const Movie& rhs)
{
    return (lhs.id_ < rhs.id_);
}

inline std::ostream& operator << (std::ostream& os, const Movie& movie)
{
    os << "Movie[Id: " << movie.id_ << ", " << movie.name_ << "]";
    return os;
}

inline std::string toJsonString(const Movie& movie)
{
    std::string jsonString = "{ \"id\": ";
    jsonString += std::to_string(movie.id_);
    jsonString += ", \"name\": ";
    jsonString += movie.name_;
    jsonString += "}";
    return jsonString;
}


#endif // MOVIE_HPP
