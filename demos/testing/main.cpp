#include <apirouter/apirouter.hpp>
#include <apirouter/socketapi/detail/win_socket.hpp>

int main()
{
    apirouter::socket sock((uint16_t)900);

    sock.bind();

    sock.listen();

    while (true)
    {
        auto new_sock = sock.accept();
        if(!new_sock)
            continue;
        printf("new connectino\n");
        std::optional<std::string> buf;
        while ((buf = new_sock->recv()) != std::nullopt)
        {
            new_sock->send(buf.value());
        }
       
        
    }


}