#include "utils.hpp"

#include <string>
#include <algorithm>
#include <sstream>

namespace utils
{

std::string toLower(const std::string& s)
{
    std::string lower;
    lower.resize(s.size());
    std::transform(s.begin(), s.end(), lower.begin(), ::tolower);
    return lower;
}

std::vector<std::string> splitByDelimeter(const std::string& s, char delimeter)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delimeter))
    {
      elems.push_back(item);
    }
    return elems;
}

}
