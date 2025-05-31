#ifndef API_ROUTER_ROUTING_ROUTER_HPP_
#define API_ROUTER_ROUTING_ROUTER_HPP_

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

#include "apirouter/http/request.hpp"
#include "apirouter/http/response.hpp"

namespace apirouter
{

using route_callback_t = std::function<http::response(const http::request&)>;

struct route_data
{
    route_callback_t callback;
    http::http_method method;
};

using route_table_t = std::unordered_map < std::string, route_data >;

class router
{
public:

    inline router(const std::string& prefix);

    inline void add_route(const std::string& name, route_callback_t cb, http::http_method method);

    inline const auto get_route_table() const { return m_route_table; }

    inline const auto& get_prefix() const { return m_prefix; }

    inline void get(const std::string& name, route_callback_t cb)
    {
        add_route(name, cb, http::http_method::GET);
    }

    inline void post(const std::string& name, route_callback_t cb)
    {
        add_route(name, cb, http::http_method::POST);
    }



private:
    std::shared_ptr<route_table_t> m_route_table;
    std::string m_prefix;
};

router::router(const std::string& prefix)
    : m_prefix{ prefix }, m_route_table{}
{
    m_route_table = std::make_shared<route_table_t>();
}

void router::add_route(const std::string& name, route_callback_t cb, http::http_method method)
{
    if (m_route_table) 
    {
        (*m_route_table)[name] = {
            .callback = cb, .method = method
        };

    }
}


} // apirouter


#endif // API_ROUTER_ROUTING_ROUTER_HPP_