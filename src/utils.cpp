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

}
