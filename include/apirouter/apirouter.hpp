#ifndef APIROUTER_APIROUTER_HPP_
#define APIROUTER_APIROUTER_HPP_

#include "socketapi/socketapi.hpp"
#include "http/parser.hpp"
#include <cstdint>
#include <optional>

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
        : m_srv_sock{ port, host } { }


    inline void run();


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
            printf("%s\n",req.path.c_str());
        }
    }
}


} // apiroute


#endif // APIROUTER_APIROUTER_HPP_