#ifndef API_ROUTER_GENERIC_STR_UTIL_HPP_
#define API_ROUTER_GENERIC_STR_UTIL_HPP_

#include <vector>
#include <string>
#include <string_view>
#include <type_traits>

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
template <class DelimiterType = char>
inline string_list split_str(const std::string& str, DelimiterType delimiter)
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

        if constexpr (std::is_fundamental_v<DelimiterType>)
            current_pos = new_pos + sizeof(DelimiterType);
        else
            current_pos = new_pos + delimiter.length();
    }

    if (!str.ends_with(delimiter))
    {
        split.push_back(
            str.substr(current_pos)
        );
    }
    
    return split;
}

template <class DelimiterType = char>
inline str_view_list sv_split(const std::string& str, DelimiterType delimiter)
{
    str_view_list split{};

    size_t current_pos = 0;
    size_t new_pos = 0;
    while ((new_pos = str.find(delimiter, current_pos)) != std::string::npos)
    {
        if ((new_pos - current_pos) > 0)
        {
            auto iter = str.begin();
            split.push_back(
                { iter + current_pos, iter + (new_pos) }
            );
        }

        if constexpr (std::is_fundamental_v<DelimiterType>)
            current_pos = new_pos + sizeof(DelimiterType);
        else
            current_pos = new_pos + delimiter.length();
    }

    if (!str.ends_with(delimiter))
    {
        split.push_back(
            {str.begin() + current_pos, str.end()}
        );
    }

    return split;
}

inline string_list split_from_str(const std::string& str, const std::string& delim)
{
    return split_str<const std::string&>(str, delim);
}

inline str_view_list sv_split_from_str(const std::string& str, const std::string& delim)
{
    return sv_split <const std::string&>(str, delim);
}

} // generic
} // apirouter

#endif // API_ROUTER_GENERIC_STR_UTIL_HPP_