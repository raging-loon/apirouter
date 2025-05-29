#ifndef API_ROUTER_ROUTING_ROUTER_HPP_
#define API_ROUTER_ROUTING_ROUTER_HPP_

#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

namespace apirouter
{

using route_callback_t = std::function<void()>;
using route_table_t = std::unordered_map < std::string, route_callback_t >;

class router
{
public:

    inline router(const std::string& prefix);

    inline void add_route(const std::string& name, route_callback_t);

    inline const auto get_route_table() const { return m_route_table; }

    inline const auto& get_prefix() const { return m_prefix; }

private:
    std::shared_ptr<route_table_t> m_route_table;
    std::string m_prefix;
};

router::router(const std::string& prefix)
    : m_prefix{ prefix }, m_route_table{}
{
    m_route_table = std::make_shared<route_table_t>();
}

void router::add_route(const std::string& name, route_callback_t cb)
{
    if (m_route_table)
        m_route_table->insert({ name, cb });
}

} // apirouter


#endif // API_ROUTER_ROUTING_ROUTER_HPP_