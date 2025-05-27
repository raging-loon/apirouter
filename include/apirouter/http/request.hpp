#ifndef API_ROUTER_HTTP_REQUEST_HPP_
#define API_ROUTER_HTTP_REQUEST_HPP_

#include <string>

namespace apirouter {
namespace http {

struct url
{
    
};

enum class http_method
{
    GET, POST, HEAD
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


};


} // http
} // apirouter

#endif // API_ROUTER_HTTP_REQUEST_HPP_