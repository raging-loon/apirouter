#ifndef API_ROUTER_SOCKET_API_SOCKET_API_HPP_
#define API_ROUTER_SOCKET_API_SOCKET_API_HPP_

#ifdef _WIN32
#   include "detail/win_socket.hpp"
#elif defined(__linux__)
#   include "detail/posix_socket.hpp"
#endif // _WIN32

namespace apirouter
{

///
/// @brief
///     Platform-agnostic wrapper around different Socket APIs
/// 
class socket
{
public:
    ///
    /// @brief
    ///     Make a socket
    /// 
    /// @param port - target port number
    /// @param address - optional IP address to bind/connect to
    ///                  this will be localhost if left empty
    /// 
    socket(uint16_t port, std::optional<std::string> address = std::nullopt)
        : m_impl(port, address)
    {
    }
    
    ///
    /// @brief
    ///     Bind a socket to a __local__ address
    /// 
    inline void bind() { m_impl.bind(); }

    ///
    /// @brief
    ///     Let this socket listen for incoming connections
    /// 
    inline void listen() { m_impl.listen(); }
    
    ///
    /// @brief
    ///     If this is a bound socket, try to accept a new connection
    /// 
    /// @returns
    ///     A socket_impl shared_ptr
    /// 
    inline auto accept() { return m_impl.accept(); }
    
    ///! Connect to a socket
    inline void connect() { m_impl.connect(); }

    ///! Receive data from this socket
    inline auto recv() { return m_impl.recv(); }

    ///! Send data over this socket
    inline bool send(const std::string& data) { return m_impl.send(data); }

    ///! Shutdown communications
    inline void shutdown() { m_impl.shutdown(); }

    ///! Close the socket for good, invalidates it's state
    inline void close() { m_impl.close(); }

private:
    details::socket_impl m_impl;
};

} // apirouter

#endif // API_ROUTER_SOCKET_API_SOCKET_API_HPP_