#ifndef API_ROUTER_SOCKET_API_DETAIL_POSIX_SOCKET_HPP_
#define API_ROUTER_SOCKET_API_DETAIL_POSIX_SOCKET_HPP_

#ifdef __linux__

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string>
#include <memory>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <exception>

namespace apirouter {
namespace details {

constexpr int POSIX_SOCK_BUFFER_SIZE = 1024;

class socket_impl
{
public:
    explicit socket_impl(uint16_t port, std::optional<std::string> address = std::nullopt);

    explicit socket_impl(int other_fd) 
        : m_sockfd(other_fd) 
    {}

    ~socket_impl();

    
    void bind();

    void listen();

    void connect();

    std::shared_ptr<
        socket_impl
    > accept();

    std::optional<std::string> recv();

    bool send(const std::string& data);

    void shutdown();

    void close();

private:
    int m_sockfd;
    
    sockaddr_in m_addr;
};


socket_impl::socket_impl(uint16_t port, std::optional<std::string> address)
    : m_sockfd{ -1 }
{
    memset(&m_addr, 0, sizeof(sockaddr_in));

    m_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };

    m_addr.sin_addr.s_addr = inet_addr(
        address.value_or("127.0.0.1").c_str()
    );

    m_sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_sockfd == -1)
        throw std::runtime_error("Failed to create socket");
}

socket_impl::~socket_impl()
{
    close();
}

void socket_impl::bind()
{
    if(::bind(m_sockfd, (const struct sockaddr*)&m_addr, sizeof(m_addr)) == -1)
        throw std::logic_error("Failed to bind socket");
}

void socket_impl::listen()
{
    //! FIXME FIXME
    if(::listen(m_sockfd, SOMAXCONN) == -1)
        throw std::logic_error("Failed to listen on socket");
}

std::shared_ptr<socket_impl> socket_impl::accept()
{
    int cfd = -1;
    socklen_t len = sizeof(m_addr);

    cfd = ::accept(m_sockfd, NULL, NULL);

    if(cfd == -1)
    return nullptr;
    
    return std::make_shared<socket_impl>(cfd);
}

void socket_impl::connect()
{
    if(::connect(m_sockfd, 
        (const struct sockaddr*)&m_addr,
        sizeof(m_addr)
    ) == -1)
        throw std::logic_error("Could not connect");
}

std::optional<std::string> socket_impl::recv()
{
    std::string buffer{};
    buffer.reserve(POSIX_SOCK_BUFFER_SIZE);
    
    ssize_t len = ::recv(m_sockfd, buffer.data(), POSIX_SOCK_BUFFER_SIZE - 1, MSG_PEEK);
     
    if(len <= 0)
        return std::nullopt;
        
    buffer.resize(len + 1);

    len = ::recv(m_sockfd, buffer.data(), POSIX_SOCK_BUFFER_SIZE - 1, 0);
    
    if(len <= 0)
        return std::nullopt;
    
    buffer.at(len) = 0;

    return buffer;
}

bool socket_impl::send(const std::string& data)
{
    int res = ::send(m_sockfd, data.c_str(), data.length(), 0);

    return res != -1;
}

void socket_impl::shutdown()
{
    ::shutdown(m_sockfd, SHUT_WR);
}

void socket_impl::close()
{
    ::close(m_sockfd);
    m_sockfd = -1;
}

} // details
} // apirouter


#endif // __linux__


#endif // API_ROUTER_SOCKET_API_DETAIL_POSIX_SOCKET_HPP_