#ifndef THEATER_HPP
#define THEATER_HPP

#include <string>

static constexpr uint16_t SEATS_COUNT = 20;

using TheaterName = std::string;

struct Theater
{
    uint16_t id_;
    std::string name_;
};

inline bool operator==(const Theater& lhs, const Theater& rhs)
{
    return (lhs.id_ == rhs.id_);
}

inline bool operator<(const Theater& lhs, const Theater& rhs)
{
    return (lhs.id_ < rhs.id_);
}

inline std::ostream& operator << (std::ostream& os, const Theater& theater)
{
    os << "Theater[Id: " << theater.id_ << ", " << theater.name_ << "]";
    return os;
}


#endif // THEATER_HPP
