#ifndef API_ROUTER_GENERIC_STR_UTIL_HPP_
#define API_ROUTER_GENERIC_STR_UTIL_HPP_

#include <vector>
#include <string>
#include <string_view>

namespace apirouter {
namespace generic {

using string_list = std::vector<std::string>;
using str_view_list = std::vector<std::string_view>;

///
/// @brief
///     Split a string into a vector of sub strings based on 
///     a delimiter
/// 
/// @params
///     str - target string
///     delimiter - character delimiter
/// 
/// @returns
///     std::vector of strings
/// 
/// @notes
///     If the string ends with it's delimiter, an empty string
///     will NOT be added to the end of the array
/// 
inline string_list split_to_str(const std::string& str, char delimiter)
{
    string_list split{};

    size_t current_pos = 0;
    size_t new_pos = 0;
    while ((new_pos = str.find(delimiter, current_pos)) != std::string::npos)
    {
        if ((new_pos - current_pos) > 0)
        {
            split.push_back(
                str.substr(current_pos, (new_pos - current_pos))
            );
        }

        current_pos = new_pos + 1;
    }

    if (!str.ends_with(delimiter))
    {
        split.push_back(
            str.substr(current_pos)
        );
    }
    
    return split;
}


} // generic
} // apirouter

#endif // API_ROUTER_GENERIC_STR_UTIL_HPP_