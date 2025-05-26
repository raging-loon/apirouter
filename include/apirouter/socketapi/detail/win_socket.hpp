#ifndef API_ROUTER_SOCKET_API_DETAIL_WIN_SOCKET_HPP_
#define API_ROUTER_SOCKET_API_DETAIL_WIN_SOCKET_HPP_

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

#include <string>
#include <memory>
#include <cassert>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <exception>


#pragma comment(lib, "Ws2_32.lib")

namespace apirouter {
namespace details {

constexpr int WIN_SOCK_BUFFER_SIZE = 1024;

///
/// @brief
///     WinSock implementation
/// 
class socket_impl
{
public:

    ///
    /// @brief
    ///     Start up winsock and make a socket
    /// 
    explicit socket_impl(uint16_t port, std::optional<std::string> address = std::nullopt);

    ~socket_impl();

    socket_impl(socket_impl&& other)
        : m_socket{ std::exchange(other.m_socket, INVALID_SOCKET) },
        m_addrInfo{ std::exchange(other.m_addrInfo, nullptr) }
    {

    }

    socket_impl& operator=(socket_impl&& other)
    {
        m_socket = std::exchange(other.m_socket, INVALID_SOCKET);
        m_addrInfo = std::exchange(other.m_addrInfo, nullptr);

        return *this;
    }

    socket_impl(const socket_impl& other)
        : m_socket{ other.m_socket },
        m_addrInfo{ other.m_addrInfo }
    {
    }

    socket_impl& operator=(const socket_impl& other)
    {
        m_socket = other.m_socket;
        m_addrInfo = other.m_addrInfo;

        return *this;
    }

   
    void bind();

    void listen();

    
    std::shared_ptr<
        socket_impl
    > accept();

    void connect();

    std::optional<std::string> recv();

    bool send(const std::string& data);

    void shutdown();

    void close();

    explicit socket_impl(SOCKET sock)
        : m_socket{ sock },
        m_addrInfo{ nullptr }
    {}

private:
    SOCKET  m_socket;

    struct addrinfo* m_addrInfo;
};

socket_impl::socket_impl(uint16_t port, std::optional<std::string> address)
    : m_socket{ INVALID_SOCKET },
    m_addrInfo{ nullptr }
{
    static bool wsa_init = false;
    
    if (!wsa_init)
    {
        WSADATA wsaData{};

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
            throw std::runtime_error("Failed to start WinSock");

        wsa_init = true;
    }

    struct addrinfo* result, hints;

    std::memset(&hints, 0, sizeof(hints));

    hints = {
        .ai_flags = AI_PASSIVE,
        .ai_family = AF_INET,
        .ai_socktype = SOCK_STREAM,
        .ai_protocol = IPPROTO_TCP,
    };

    char port_str[8] = { 0 };

    snprintf(
        port_str, 8, "%d", port
    );

    int iResult = getaddrinfo(
        address.value_or("localhost").c_str(),
        port_str,
        &hints,
        &result
    );

    if (iResult != 0)
        throw std::exception();

    m_socket = ::socket(
        result->ai_family,
        result->ai_socktype,
        result->ai_protocol
    );

    if (m_socket == INVALID_SOCKET)
        throw std::exception();

    m_addrInfo = result;
}

socket_impl::~socket_impl()
{
    if (m_addrInfo)
    {
        freeaddrinfo(m_addrInfo);
        m_addrInfo = nullptr;
    }

    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
}

void socket_impl::bind()
{
    assert(m_addrInfo && (m_socket != INVALID_SOCKET));

    int res = ::bind(
        m_socket,
        m_addrInfo->ai_addr,
        (int)m_addrInfo->ai_addrlen
    );

    if (res == SOCKET_ERROR)
        throw std::exception();

}

void socket_impl::listen()
{
    if (::listen(m_socket, SOMAXCONN) == SOCKET_ERROR)
        throw std::exception();
}



std::shared_ptr<socket_impl> socket_impl::accept()
{
    SOCKET client_sock = INVALID_SOCKET;

    client_sock = ::accept(m_socket, NULL, NULL);

    if (client_sock == INVALID_SOCKET)
        return nullptr;
    return std::make_shared<socket_impl>(client_sock);
}

void socket_impl::connect()
{
    if (::connect(
        m_socket, 
        m_addrInfo->ai_addr, 
        (int)m_addrInfo->ai_addrlen
    ) == SOCKET_ERROR)
        throw std::exception();
}


std::optional<std::string> socket_impl::recv()
{
    std::string buffer{};
    buffer.resize(WIN_SOCK_BUFFER_SIZE - 1);
    int res = ::recv(
        m_socket,
        buffer.data(),
        WIN_SOCK_BUFFER_SIZE - 1,
        0
    );

    if (res == SOCKET_ERROR)
        return std::nullopt;

    buffer.resize(res + 1);
    buffer.at(res) = 0;
    return buffer;

}

bool socket_impl::send(const std::string& data)
{
    int res = ::send(m_socket, data.c_str(), data.length(), 0);

    return res != SOCKET_ERROR;

}

void socket_impl::shutdown()
{
    assert(m_socket != INVALID_SOCKET);

    ::shutdown(m_socket, SD_SEND);

    close();
}

void socket_impl::close()
{
    closesocket(m_socket);
    m_socket = INVALID_SOCKET;
}

} // details
} // apirouter

#endif // _WIN32

#endif // API_ROUTER_SOCKET_API_DETAIL_WIN_SOCKET_HPP_