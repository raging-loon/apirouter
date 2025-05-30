#ifndef API_ROUTER_SERVER_HPP_
#define API_ROUTER_SERVER_HPP_

#include "routing/radix.hpp"
#include "routing/router.hpp"
#include "generic/str_util.hpp"
#include "socketapi/socketapi.hpp"
#include <cstdint>
#include <optional>
#include <stdexcept>

namespace apirouter
{

///
/// @brief
///     Main entrypoint into API Router
/// 
class server
{
public:
    constexpr static int DEFAULT_PORT = 8000;

    inline server(uint16_t port, std::optional<std::string> host = std::nullopt)
        : m_srv_sock{ port, host }, m_route_tree{}
    {
    }


    inline void run();

    inline void include_router(const router& r);
    radix::tree m_route_tree;

private:

    apirouter::socket m_srv_sock;
};

void server::run()
{
    m_srv_sock.bind();
    m_srv_sock.listen();

    while (true)
    {
        auto new_sock = m_srv_sock.accept();
        if (!new_sock)
            continue;
        printf("new connection\n");
        std::optional<std::string> buf;
        while ((buf = new_sock->recv()) != std::nullopt)
        {
            auto req = http::parser::parse_request(buf.value());
            printf("%d\n", (int)req.method);
            printf("%s\n", req.path.c_str());

            radix::node* final_path = m_route_tree.search(generic::split_to_str(req.path, '/'));
            
            if (final_path && final_path->get_callback())
                (final_path->get_callback())();
        }
    }
}

void server::include_router(const router& r) 
{
    if (!r.get_route_table())
        return;

    std::string root = r.get_prefix();

    if (root.starts_with('/'))
        root = root.substr(1);

    m_route_tree.insert({ root });

    auto entry_node = m_route_tree.search({ root });

    if (!entry_node)
        throw std::runtime_error{"node was inserted but somehow does not exist"};

    for (const auto& [path, cb] : *r.get_route_table())
    {
        auto list = generic::split_to_str(path, '/');
        m_route_tree.insert(*entry_node, list, cb);
    }


}


} // apiroute
#endif // API_ROUTER_SERVER_HPP_