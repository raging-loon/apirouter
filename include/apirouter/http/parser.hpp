#ifndef API_ROUTER_HTTP_PARSER_HPP_
#define API_ROUTER_HTTP_PARSER_HPP_

#include "request.hpp"

#include "apirouter/generic/str_util.hpp"

#include <string_view>
#include <string>
#include <iostream>
namespace apirouter {
namespace http {

struct parser
{
    static http::request parse_request(const std::string& raw_request)
    {
        if (raw_request.empty() || raw_request.length() == 1)
            return {};

        auto line_view = generic::sv_split_from_str(raw_request, "\r\n");

        http::request req{};
       
        parse_request_line(line_view[0], req);
        parse_headers(line_view, req);
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

    static void parse_request_line(const std::string_view& view, http::request& req)
    {
        std::string s{ view };
        auto split = generic::sv_split(s, ' ');
        
        assert(split.size() == 3);

        req.method = parse_method(split[0]);

        req.path = std::string{ split[1] };
    }

    static void parse_headers(const generic::str_view_list& list, http::request& req)
    {
        auto begin = list.begin() + 1;

        auto end = list.end();

        while (begin != end)
        {
            size_t split_loc = begin->find(": ");
            if (split_loc == std::string::npos)
                break;
            
            std::string key{ begin->substr(0, split_loc) };
            std::string value{ begin->substr(split_loc + 2) };

            //std::cout << key << " => " << value << std::endl;

            req.headers.insert({ key, value });

            begin++;
        }
    }
};


} // http
} // apirouter


#endif // API_ROUTER_HTTP_PARSER_HPP_