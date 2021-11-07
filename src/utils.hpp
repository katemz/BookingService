#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

using MovieName = std::string;
using TheaterName = std::string;

namespace utils
{

std::string toLower(const std::string& s);
std::vector<std::string> splitByDelimeter(const std::string& s, char delimeter);

}
#endif // UTILS_HPP
