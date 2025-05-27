#ifndef API_ROUTER_HTTP_PARSER_HPP_
#define API_ROUTER_HTTP_PARSER_HPP_

#include "request.hpp"

#include <span>
#include <string>

namespace apirouter {
namespace http {

struct parser
{
    static http::request parse_request(const std::string& raw_request)
    {
        size_t fpos = raw_request.find(' ') + 1;
        size_t spos = raw_request.find(' ', fpos);

        http::request req{};

        req.path = raw_request.substr(fpos, (spos - fpos));

        return req;
    }


};


} // http
} // apirouter


#endif // API_ROUTER_HTTP_PARSER_HPP_