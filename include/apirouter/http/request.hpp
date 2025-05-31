#ifndef API_ROUTER_HTTP_REQUEST_HPP_
#define API_ROUTER_HTTP_REQUEST_HPP_

#include <string>
#include <unordered_map>



namespace apirouter {
namespace http {

enum class http_method
{
    UNKNOWN, GET, POST, HEAD
};

///
/// @brief
///     Interface representing an HTTP Request
/// 
/// @details
///     Contains
///      - URL
///      - Method
///      - Headers
///      - URL Parameters
///      - Path Parameters 
///      - Client Information
///      - Cookies
///      - Body
/// 
struct request
{
    http_method method;

    std::string path;

    std::unordered_map<
        std::string,
        std::string
    > headers;

};


} // http
} // apirouter

#endif // API_ROUTER_HTTP_REQUEST_HPP_