#ifndef API_ROUTER_HTTP_PARSER_HPP_
#define API_ROUTER_HTTP_PARSER_HPP_

#include "request.hpp"

#include <string_view>
#include <string>

namespace apirouter {
namespace http {

struct parser
{
    static http::request parse_request(const std::string& raw_request)
    {
        if (raw_request.empty() || raw_request.length() == 1)
            return {};
        size_t fpos = raw_request.find(' ') + 1;
        size_t spos = raw_request.find(' ', fpos);

        http::request req{};
        std::string_view test{ raw_request.begin(), raw_request.begin() + fpos-1 };

        req.method = parse_method(test);

        req.path = raw_request.substr(fpos, (spos - fpos));
        req.path = req.path.erase(req.path.find('\r'));
        return req;
    }

    static http::http_method parse_method(const std::string_view& method_str)
    {
        if (method_str == "GET")
            return http_method::GET;

        if (method_str == "POST")
            return http_method::POST;

        return http_method::UNKNOWN;
    }
};


} // http
} // apirouter


#endif // API_ROUTER_HTTP_PARSER_HPP_