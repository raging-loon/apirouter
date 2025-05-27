#include <apirouter/apirouter.hpp>

int main()
{
    apirouter::server srv(80);

    srv.run();
}